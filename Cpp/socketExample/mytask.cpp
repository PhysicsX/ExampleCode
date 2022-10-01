// mytask.cpp

#include "mytask.h"
#include <QDebug>
#include <thread>
#include <chrono>

MyTask::MyTask()
{
    qDebug() << "MyTask()";
}

// When the thread pool kicks up
// it's going to hit this run, and it's going to do this time consuming task.
// After it's done, we're going to send the results back to our main thread.
// This runs in the separate thread, and we do not have any control over this thread,
// but Qt does.
// This may just stay in the queue for several ms depending on how busy the server is.

void MyTask::run()
{
    // time consumer

    qDebug() << "Task started";

    int iNumber = 0;
    for(int i = 0; i < 100; i++)
    {
        iNumber += 1;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(30000));


    qDebug() << "Task done";
    emit Result(iNumber);
}
