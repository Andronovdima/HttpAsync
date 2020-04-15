//
//  instance.hpp
//  HttpHighload
//
//  Created by Андронов Дмитрий on 14.04.2020.
//  Copyright © 2020 Andronov Dima. All rights reserved.
//

#ifndef instance_hpp
#define instance_hpp

#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <sys/socket.h> // sockets
#include <netinet/in.h> // sockaddr_in
#include <unistd.h> // close socket
#include <fcntl.h> // for O_RDONLY

#include "parser.hpp"

namespace fs = std::experimental::filesystem;

class Worker {
public:
    explicit Worker(std::string &rootPath, const int buffSize);
    void run(int socket);
    void runThread(int socket);
    
private:
    std::string docRootPath;
    const int buffSize;
    
    std::string getRequest(int clientSocket);
    void executeRequest(HttpRequest req, int clientSocket);
    bool makePath(std::string &path);
    void writeStartLine(std::string &version, int status, int clientSocket);
    void writeHeaders(bool isOK, std::string &uri, uintmax_t length, int clienSocket);
    void writeFile(std::string &uri, int clientSocket);
};


#endif /* instance_hpp */

