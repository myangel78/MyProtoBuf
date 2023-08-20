#include "DataBaseThread.h"
#include <QDebug>

DataBaseThread::DataBaseThread()
{

}
DataBaseThread::~DataBaseThread()
{
    StopThread();
}

bool DataBaseThread::StartThread(void)
{

    if (!m_bRunning && m_ThreadPtr == nullptr)
    {
        m_bRunning = true;
        m_ThreadPtr = std::make_shared<std::thread>(&DataBaseThread::ThreadHandleFunc, this);
        return m_ThreadPtr != nullptr;
    }
    return false;
}

void DataBaseThread::ThreadHandleFunc(void)
{
    while(m_bRunning)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    };
}

bool DataBaseThread::StopThread(void)
{
    m_bRunning = false;
    m_cvHandle.notify_one();

    if (m_ThreadPtr.get() != nullptr)
    {
        if (m_ThreadPtr->joinable())
        {
            m_ThreadPtr->join();
        }
        m_ThreadPtr.reset();
    }
    return true;
}
