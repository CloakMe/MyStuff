#pragma once
#include <iostream>
#include <WS2tcpip.h>
#include "Utilities.h"
#include "Constants.h"
#include "GeoCmd.h"

class Server
{
public:  
    Server();
    void Run();    
private:
    void Cleanup();
    SOCKET mClientSocket[Constants::MAX_CLIENTS];
    SOCKET mMasterSocket;
};

