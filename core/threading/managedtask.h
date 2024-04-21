#ifndef MANAGEDTASK_H
#define MANAGEDTASK_H

#include <QObject>

class ManagedTask : public QObject
{
    Q_OBJECT
public:
    explicit ManagedTask(QObject *parent = nullptr);

    virtual void execute() = 0;

signals:
    void taskCompleted();
    void taskFailed();
};

#endif // MANAGEDTASK_H
