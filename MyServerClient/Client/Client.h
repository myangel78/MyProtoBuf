#pragma once
#include "DataBaseThread.h"


class Client:public DataBaseThread
{
public:
    Client();

protected:
     void ThreadHandleFunc(void) override;
};




