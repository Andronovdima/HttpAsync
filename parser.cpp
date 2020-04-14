//
//  parser.cpp
//  HttpHighload
//
//  Created by Андронов Дмитрий on 14.04.2020.
//  Copyright © 2020 Andronov Dima. All rights reserved.
//

#include "parser.hpp"
#include <sstream>

int HTTPParser::parse(std::string query) {
    std::string elem;
    std::string conLen;
       std::stringstream ss;
       ss << query;
       while (ss >> elem) {
           if (elem == "Content-Length:") {
               ss >> conLen;
               int contentLength = std::stoi(conLen);
               return contentLength;
           }
       }
    return 0;
}


//int HTTPParser::getContentLength() {
//    return contentLength;
//}

