#include "jet/TcpEndpoint.h"


namespace jet{



    TcpEndpoint::TcpEndpoint()
        :address(address), host(host), port(port)
    {


    }


    TcpEndpoint::TcpEndpoint( IpAddress address, Hostname host, UnsignedInt16 port )
        :address(address), host(host), port(port)
    {


    }



    TcpEndpoint::~TcpEndpoint(){


    }


    void TcpEndpoint::setAddress( IpAddress address ){

        this->address = address;

    }


    IpAddress TcpEndpoint::getAddress(){

        return this->address;

    }


    void TcpEndpoint::setHost( Hostname host ){

        this->host = host;

    }


    Hostname TcpEndpoint::getHost(){

        return this->host;

    }


    void TcpEndpoint::setPort( UnsignedInt16 port ){

        this->port = port;

    }


    UnsignedInt16 TcpEndpoint::getPort(){

        return this->port;

    }


}

