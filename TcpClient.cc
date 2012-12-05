#include "jet/TcpClient.h"


namespace jet{



    TcpClient::TcpClient()
        :connection(connection)
    {


    }


    TcpClient::TcpClient( TcpConnection connection )
        :connection(connection)
    {


    }



    TcpClient::~TcpClient(){


    }


    void TcpClient::setConnection( TcpConnection connection ){

        this->connection = connection;

    }


    TcpConnection TcpClient::getConnection(){

        return this->connection;

    }


}

