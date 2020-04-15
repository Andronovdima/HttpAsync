//
//  parser.hpp
//  HttpHighload
//
//  Created by Андронов Дмитрий on 14.04.2020.
//  Copyright © 2020 Andronov Dima. All rights reserved.
//

#ifndef parser_hpp
#define parser_hpp

#include <iostream>
#include <unordered_map>
#include <experimental/filesystem>

std::string GetFormatDate();
void toLowerString(std::string &s);
std::string getExtension(std::string &p);

typedef std::unordered_map<std::string, std::string> Headers;

struct HttpReuestHeader {
    std::string method;
    std::string uri;
    std::string httpVersion;
};

struct HttpRequest {
    HttpReuestHeader mainInfo;
    Headers headers;
};

class HTTPParser {

public:
    HTTPParser() {}
    HttpRequest parseHeader(std::string &query);
    std::string decodeUri(std::string &uri);
    
};

const std::unordered_map<int, std::string> statuses {
    std::pair<int, std::string>{200, "OK"},
    std::pair<int, std::string>{403, "Forbidden"},
    std::pair<int, std::string>{404, "Not Found"},
    std::pair<int, std::string>{405, "Method Not Allowed"},
};

const std::unordered_map<std::string, std::string> contentTypes {
    std::pair<std::string, std::string>{".html", "text/html"},
    std::pair<std::string, std::string>{".css", "text/css"},
    std::pair<std::string, std::string>{".js", "application/javascript"},
    std::pair<std::string, std::string>{".jpg", "image/jpeg"},
    std::pair<std::string, std::string>{".jpeg", "image/jpeg"},
    std::pair<std::string, std::string>{".png", "image/png"},
    std::pair<std::string, std::string>{".gif", "image/gif"},
    std::pair<std::string, std::string>{".swf", "application/x-shockwave-flash"},
};

#endif /* parser_hpp */
