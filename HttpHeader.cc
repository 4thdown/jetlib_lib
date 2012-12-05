#include "jet/HttpHeader.h"


namespace jet{



    HttpHeader::HttpHeader()
        :name(name), value(value)
    {


    }


    HttpHeader::HttpHeader( Utf8String name, Utf8String value )
        :name(name), value(value)
    {


    }



    HttpHeader::~HttpHeader(){


    }


    void HttpHeader::setName( Utf8String name ){

        this->name = name;

    }


    Utf8String HttpHeader::getName(){

        return this->name;

    }


    void HttpHeader::setValue( Utf8String value ){

        this->value = value;

    }


    Utf8String HttpHeader::getValue(){

        return this->value;

    }


}

