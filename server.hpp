//
//  server.hpp
//  HttpHighload
//
//  Created by Андронов Дмитрий on 14.04.2020.
//  Copyright © 2020 Andronov Dima. All rights reserved.
//

#ifndef server_hpp
#define server_hpp

#include <unistd.h> // close socket
#include <memory>
#include <netdb.h>
#include "instance.hpp"

struct Config {
    const int port = 80;
    const int queueSocket = 30;
    const int workersNumber = 4;
    std::string documentRootPath = "/Users/andronovdima/Desktop/Development/parkMailru/http-test-suite";
    const int buffSize = 1024;
};


class Server {
    
public:
    Server() : mainSocket(-1) {}
    
    ~Server() {
        if (mainSocket > 0)
            close(mainSocket);
    }
    
    void start(Config& config);
    
private:
    int mainSocket;
    
    void createServerSocket(uint32_t port, uint32_t queueSize);
};

#endif /* server_hpp */
