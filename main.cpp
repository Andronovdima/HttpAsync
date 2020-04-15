//
//  main.cpp
//  HttpHighload
//
//  Created by Андронов Дмитрий on 01.03.2020.
//  Copyright © 2020 Andronov Dima. All rights reserved.
//


#include "parser.hpp"
#include "server.hpp"

int main(int argc, const char * argv[]) {
    Config config;
    Server server;
    std::cout << "Starting HTTP Server on port: " +  std::to_string(config.port)+ " !\n";
    
    server.start(config);
    
    return 0;
}

