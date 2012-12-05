#include "jet/HttpClient.h"


namespace jet{



    HttpClient::HttpClient()
        :tcp_client(tcp_client)
    {


    }


    HttpClient::HttpClient( TcpClient tcp_client )
        :tcp_client(tcp_client)
    {


    }



    HttpClient::~HttpClient(){


    }


    void HttpClient::setTcpClient( TcpClient tcp_client ){

        this->tcp_client = tcp_client;

    }


    TcpClient HttpClient::getTcpClient(){

        return this->tcp_client;

    }


}

