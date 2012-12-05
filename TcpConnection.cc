#include "jet/TcpConnection.h"


namespace jet{



    TcpConnection::TcpConnection()
        :destination_endpoint(destination_endpoint), source_endpoint(source_endpoint), state(state)
    {


    }


    TcpConnection::TcpConnection( TcpEndpoint destination_endpoint, TcpEndpoint source_endpoint, TcpConnectionState state )
        :destination_endpoint(destination_endpoint), source_endpoint(source_endpoint), state(state)
    {


    }



    TcpConnection::~TcpConnection(){


    }


    void TcpConnection::setDestinationEndpoint( TcpEndpoint destination_endpoint ){

        this->destination_endpoint = destination_endpoint;

    }


    TcpEndpoint TcpConnection::getDestinationEndpoint(){

        return this->destination_endpoint;

    }


    void TcpConnection::setSourceEndpoint( TcpEndpoint source_endpoint ){

        this->source_endpoint = source_endpoint;

    }


    TcpEndpoint TcpConnection::getSourceEndpoint(){

        return this->source_endpoint;

    }


    void TcpConnection::setState( TcpConnectionState state ){

        this->state = state;

    }


    TcpConnectionState TcpConnection::getState(){

        return this->state;

    }


}

