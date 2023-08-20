#pragma once
#include "DataBaseThread.h"

class Server: public DataBaseThread
{
public:
    Server();


protected:
     void ThreadHandleFunc(void) override;
};

