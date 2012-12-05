#include "jet/HttpServer.h"


namespace jet{



    HttpServer::HttpServer(){


    }


    HttpServer::HttpServer( TcpServer tcp_server )
        :tcp_server(tcp_server)
    {


    }



    HttpServer::~HttpServer(){


    }


    /*
    void HttpServer::setHandler( function handler ){

        this->handler = handler;

    }


    function HttpServer::getHandler(){

        return this->handler;

    }
    */


    void HttpServer::setTcpServer( TcpServer tcp_server ){

        this->tcp_server = tcp_server;

    }


    TcpServer HttpServer::getTcpServer(){

        return this->tcp_server;

    }


}

