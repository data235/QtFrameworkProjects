#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include <QMutex>
#include <QObject>
#include <QQueue>
#include <QThread>
#include <QWaitCondition>
#include <atomic>

class ManagedTask;
class ThreadManager : public QObject {
    Q_OBJECT

public:
    static ThreadManager& instance();

    void startTask(ManagedTask* task);
    void taskFinished();

private:
    ThreadManager(QObject *parent = nullptr);
    ~ThreadManager();

    void ensureThreadAvailable();

    static int MaxThreads;
    QMutex m_mutex;
    QQueue<ManagedTask*> m_tasks;
    QWaitCondition m_condition;
    std::atomic<int> m_activeThreads = 0;
};

#endif // THREADMANAGER_H
