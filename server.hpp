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
    const int port = 7777;
    const int queueSocket = 30;
    const int workersNumber = 4;
    std::string documentRootPath = "/Users/andronovdima/Desktop/Development/parkMailru/http-test-suite";
    const int buffSize = 1024;
};


class Server {
    
public:
    Server() : m_Sd(-1) {}
    
    ~Server() { if (m_Sd > 0) close(m_Sd); }
    
    void start(Config& config);
    
private:
    int m_Sd;
    
    void createServerSocket(uint32_t port, uint32_t queue_size);
};

#endif /* server_hpp */
