//
//  main.cpp
//  HttpHighload
//
//  Created by Андронов Дмитрий on 01.03.2020.
//  Copyright © 2020 Andronov Dima. All rights reserved.
//

#include <iostream>
#include <memory>
#include <sys/socket.h> //bind
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h> // close socket
#include "parser.hpp"


class Client {
    int m_Sd;
    HTTPParser* parser;
public:
    Client() : m_Sd(-1), parser (nullptr) {}
    Client(HTTPParser* p) : m_Sd(-1), parser(p) {}
    Client(int sd, HTTPParser* p) : m_Sd(sd), parser(p) {}
    
    ~Client() {
        if (m_Sd > 0)
            close(m_Sd);
    }
    
    void connect (const std::string &host, int port) throw (std::exception);
    void send (const std::string &s);
    std::string recv() throw(std::exception);
    void setRcvTimeout(int sec, int microsec) throw (std::exception);
    void setNonBlocked(bool opt) throw (std::exception);
};


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

void Server::createServerSocket(uint32_t port, uint32_t queue_size) {
    int sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);
    
    bind(sd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
    ::listen(sd, queue_size);
    m_Sd = sd;
}

std::shared_ptr<Client> Server::accept(HTTPParser* p) throw (std::exception) {
    struct sockaddr_in client;
    socklen_t cli_len = sizeof(client);
    int cli_sd = ::accept(m_Sd, (struct sockaddr*)&client, &cli_len);
    std::cout << "+client: " << cli_sd << ", from: " << client.sin_addr.s_addr << std::endl;
    return std::make_shared<Client> (cli_sd, p);
}

void Server::setNonBlocked(bool opt) throw (std::exception) {
    int flags = fcntl(m_Sd, F_GETFL, 0);
    int new_flags = (opt) ? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
    if (fcntl(m_Sd, F_SETFL, new_flags) == -1)
        throw std::runtime_error("nonblocked: " + std::string(strerror(errno)));
}

void client_work(std::shared_ptr<Client> client) {
//    client->setRcvTimeout(/*sec*/ 30, /*microsec*/ 0);
    client->setNonBlocked(true);
    while (true)
        try {
            std::string line = client->recv();
            if (line != "") {
                std::cout << "Data receive: " + line + "\n";
                client->send("echo: " + line + "\n");
            }
        }
        catch(const std::exception &e) {
            return;
        }
}

int main(int argc, const char * argv[]) {
    int port = 7777;
    std::cout << "Starting HTTP Server on port: " +  std::to_string(port)+ " !\n";
    Server server;
    server.createServerSocket(port, 25);
    HTTPParser* parser = new HTTPParser();
    
    while (true) {
        std::shared_ptr<Client> client = server.accept(parser);
        client_work(client);
    }
    
    return 0;
}

void Client::connect(const std::string &host /*e.mail.ru*/, int port) throw (std::exception){
    
    m_Sd = socket(PF_INET, SOCK_STREAM, 0);
    struct hostent* hp = gethostbyname(host.c_str());
    struct sockaddr_in addr;
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    
    std::memcpy(&addr.sin_addr, hp->h_addr, hp->h_length);
    
    int connected = ::connect(m_Sd, (struct sockaddr*)& addr, sizeof(addr));
    if (connected != 0) {
        throw std::runtime_error(std::string(strerror(errno)));
    }
}

void Client::send(const std::string &msg) {
     std::string query = "HTTP/1.1 301 Moved Permanently\r\nCache-Control: public\r\nContent-Length: 151\r\nContent-Type: text/html; charset=UTF-8\r\nDate: Tue, 14 Apr 2020 10:16:41 GMT";
    std::cout << "SIZE : " << query.size() << std::endl;
        size_t left = query.size();
//    size_t left = msg.size();

    ssize_t sent = 0;
    while (left > 0) {
//        sent = ::send(m_Sd, msg.data() + sent, msg.size() - sent, 0);
        sent = ::send(m_Sd, query.data() + sent, query.size() - sent, 0);
        if (-1 == sent)
            throw std::runtime_error(std::string(strerror(errno)));
        left -= sent;
    }
    std::cout << "Sent : " + query + "\n";
}


std::string Client::recv() throw (std::exception) {
    std::string res;
    char buf[1024];
    while (true) {
        int n = ::recv(m_Sd, buf, sizeof(buf), 0);
        if (-1 == n && errno != EAGAIN)
             throw std::runtime_error("read");
        if (-1 == n)
            break;
        if (0 == n)
             throw std::runtime_error("end");
         res.append(buf, n);
    }
    
    return res;
}
//
//void Client::setRcvTimeout(int sec, int microsec) throw (std::exception) {
//    struct timeval tv;
//    tv.tv_sec = sec;
//    tv.tv_usec = microsec;
//    if (setsockopt(m_Sd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) != 0)
//        throw std::runtime_error("rcvtimeout: " + std::string(strerror(errno)));
//}

void Client::setNonBlocked(bool opt) throw (std::exception) {
    int flags = fcntl(m_Sd, F_GETFL, 0);
    int new_flags = (opt)? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
    if (fcntl(m_Sd, F_SETFL, new_flags) == -1)
        throw std::runtime_error("nonblocked: " + std::string(strerror(errno)));
}
