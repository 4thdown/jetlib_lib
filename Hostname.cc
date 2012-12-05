#include "jet/Hostname.h"


namespace jet{



    Hostname::Hostname()
        :host(host)
    {


    }


    Hostname::Hostname( Utf8String host )
        :host(host)
    {


    }



    Hostname::~Hostname(){


    }


    void Hostname::setHost( Utf8String host ){

        this->host = host;

    }


    Utf8String Hostname::getHost(){

        return this->host;

    }


}

