#include "threadmanager.h"
#include "managedtask.h"
#include <QMutexLocker>

int ThreadManager::MaxThreads = QThread::idealThreadCount();

ThreadManager::ThreadManager(QObject *parent) : QObject(parent), m_activeThreads(0) {}

void ThreadManager::startTask(ManagedTask* task) {
    QMutexLocker locker(&m_mutex);
    m_tasks.enqueue(task);
    ensureThreadAvailable();
}

void ThreadManager::taskFinished() {
    QMutexLocker locker(&m_mutex);
    m_activeThreads--;
    m_condition.wakeOne();  // Wake one thread to handle pending tasks
}

void ThreadManager::ensureThreadAvailable() {
    if (m_activeThreads < MaxThreads && !m_tasks.isEmpty()) {
        m_activeThreads++;
        QThread* thread = new QThread;
        ManagedTask* task = m_tasks.dequeue();
        task->moveToThread(thread);

        connect(thread, &QThread::started, task, &ManagedTask::execute);
        connect(task, &ManagedTask::taskCompleted, thread, &QThread::quit);
        connect(task, &ManagedTask::taskFailed, thread, &QThread::quit);
        connect(thread, &QThread::finished, thread, &QThread::deleteLater);
        connect(task, &ManagedTask::taskCompleted, this, &ThreadManager::taskFinished);
        connect(task, &ManagedTask::taskFailed, this, &ThreadManager::taskFinished);

        thread->start();
    } else {
        m_condition.wait(&m_mutex);  // Wait for a thread to become available or a new task
    }
}

ThreadManager &ThreadManager::instance() {
    static ThreadManager manager;
    return manager;
}


