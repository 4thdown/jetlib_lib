#include "jet/IpAddress.h"


namespace jet{



    IpAddress::IpAddress()
        :ipv4_address(ipv4_address)
    {


    }


    IpAddress::IpAddress( UnsignedInt32 ipv4_address )
        :ipv4_address(ipv4_address)
    {


    }



    IpAddress::~IpAddress(){


    }


    void IpAddress::setIpv4Address( UnsignedInt32 ipv4_address ){

        this->ipv4_address = ipv4_address;

    }


    UnsignedInt32 IpAddress::getIpv4Address(){

        return this->ipv4_address;

    }


}

