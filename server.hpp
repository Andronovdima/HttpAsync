//
//  server.hpp
//  HttpHighload
//
//  Created by Андронов Дмитрий on 14.04.2020.
//  Copyright © 2020 Andronov Dima. All rights reserved.
//

#ifndef server_hpp
#define server_hpp

#include <stdio.h>

class Server {
    
public:
    Server() : m_Sd(-1) {}
    
    ~Server() { if (m_Sd > 0) close(m_Sd); }
    
    void createServerSocket(uint32_t port, uint32_t queue_size);

     std::shared_ptr<Client> accept(HTTPParser* parser) throw (std::exception);
    
    void setNonBlocked(bool opt) throw (std::exception);
    
private:
    int m_Sd;
};

#endif /* server_hpp */
