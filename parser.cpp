//
//  parser.cpp
//  HttpHighload
//
//  Created by Андронов Дмитрий on 14.04.2020.
//  Copyright © 2020 Andronov Dima. All rights reserved.
//

#include "parser.hpp"
#include <iostream>
#include <cctype>
#include <algorithm>
#include <sstream>


HttpRequest HTTPParser::parseHeader(std::string &query_) {
    std::istringstream query{query_};
    std::string line;
       std::getline(query, line);
       std::cout << line << std::endl;
    
    auto methodEnd = line.find(' ');
    auto uriEnd = line.find(' ', methodEnd + 1);

    HttpReuestHeader httpHeader = {
        line.substr(0, methodEnd),
        line.substr(methodEnd + 1, uriEnd - 1 - methodEnd),
        line.substr(uriEnd + 1, line.length() - uriEnd - 2)
    };

    
    if (httpHeader.httpVersion != "HTTP/1.0" and httpHeader.httpVersion != "HTTP/1.1") {
           throw std::exception();
       }
    
    
    Headers headers;
    while (std::getline(query, line) && line != "\r") {
        auto name_end = line.find(':');

        auto name = line.substr(0, name_end);
        toLowerString(name);
        
        auto value = line.substr(name_end + 2, line.length() - name_end - 3);

        headers.emplace(name, value);
    }
    

    return {httpHeader, headers};
}

std::string HTTPParser::decodeUri(std::string &uri){
    std::string result;
    char symb = 0;
    unsigned code = 0;

    for (int i = 0; i < uri.length(); i++) {
        if (uri[i] != '%') {
            if (uri[i] == '+') {
                result += ' ';
            } else {
                result += uri[i];
            }
        } else {
            sscanf(uri.substr(i + 1, 2).c_str(), "%x", &code);
            symb = static_cast<char>(code);
            result += symb;
            i = i + 2;
        }
    }

    return result;
}

void toLowerString(std::string &s) {
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
}


std::string GetFormatDate() {
    char buf[80];

    auto now = time(nullptr);
    auto time_info = gmtime(&now);

    strftime(buf, 80, "%a, %d %b %Y %T GMT", time_info);

    return buf;
}

std::string getExtension(std::string &p) {
    if (p[p.length() - 1] == '/') {
        return ".html";
    }
    std::experimental::filesystem::path filePath(p);
    return filePath.extension().string();
}
