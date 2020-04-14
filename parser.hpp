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

class HTTPParser {

public:
    HTTPParser() {}
    int parse(std::string query);
    
};


#endif /* parser_hpp */
