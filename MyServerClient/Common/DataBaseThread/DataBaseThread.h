#pragma once

#include "DataBaseThread_global.h"
#include <QObject>
#include <qobject.h>
#include <mutex>
#include <tuple>
#include <vector>
#include <condition_variable>
#include <string.h>
#include <memory>


class DATABASETHREAD_EXPORT DataBaseThread : public std::enable_shared_from_this<DataBaseThread>
{
public:
    DataBaseThread(const DataBaseThread&) = delete;
    DataBaseThread(DataBaseThread&&) = delete;
    DataBaseThread& operator=(const DataBaseThread&) = delete;
    DataBaseThread& operator=(DataBaseThread&&) = delete;

    explicit DataBaseThread();
    virtual ~DataBaseThread();

    std::shared_ptr<DataBaseThread> GetUdpStreamPtr(){
        return std::shared_ptr<DataBaseThread>(this);
    }

protected:
    virtual void ThreadHandleFunc(void);

    bool m_bRunning = false;

private:
    std::shared_ptr<std::thread> m_ThreadPtr = nullptr;

public:
    std::condition_variable m_cvHandle;
    std::mutex m_mutexHandle;

public:
    virtual bool StartThread(void);
    virtual bool StopThread(void);
};
