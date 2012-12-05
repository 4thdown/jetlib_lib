#include "jet/TcpServer.h"


namespace jet{



    TcpServer::TcpServer()
        :connection(connection)
    {


    }


    TcpServer::TcpServer( TcpConnection connection )
        :connection(connection)
    {


    }



    TcpServer::~TcpServer(){


    }


    void TcpServer::setConnection( TcpConnection connection ){

        this->connection = connection;

    }


    TcpConnection TcpServer::getConnection(){

        return this->connection;

    }


}

