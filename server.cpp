//
//  server.cpp
//  HttpHighload
//
//  Created by Андронов Дмитрий on 14.04.2020.
//  Copyright © 2020 Andronov Dima. All rights reserved.
//

#include "server.hpp"

void Server::start (Config &config) {
    createServerSocket(config.port, config.queueSocket);
    std::cout << "Create Server socket DONE!\n";
    
    int pid = 0;
    for (int i = 0; i < config.workersNumber; i++) {
        pid = fork();
        if (pid == -1) {
            std::cerr << "fork error";
        exit(3);
    }
        
    if (pid == 0) {
            auto worker = std::make_unique<Worker>(config.documentRootPath, config.buffSize);
            std::cout << "RUN WORKER!\n";
            worker->run(mainSocket);
        }
    }

    if (pid > 0) {
        std::cout << "WAIT MAIN PROCESS!\n";
        wait(nullptr);
    }
}

void Server::createServerSocket(uint32_t port, uint32_t queueSize) {
    int sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);
    
    bind(sd, (struct sockaddr*) &servAddr, sizeof(servAddr));
    ::listen(sd, queueSize);
    mainSocket = sd;
}

