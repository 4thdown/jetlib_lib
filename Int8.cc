#include "jet/Int8.h"


namespace jet{



    Int8::Int8()
        :number(number)
    {


    }


    Int8::Int8( char number )
        :number(number)
    {


    }



    Int8::~Int8(){


    }


    void Int8::setNumber( char number ){

        this->number = number;

    }


    char Int8::getNumber(){

        return this->number;

    }


}

