#include "jet/UnsignedInt8.h"


namespace jet{



    UnsignedInt8::UnsignedInt8()
        :number(number)
    {


    }


    UnsignedInt8::UnsignedInt8( char number )
        :number(number)
    {


    }



    UnsignedInt8::~UnsignedInt8(){


    }


    void UnsignedInt8::setNumber( char number ){

        this->number = number;

    }


    char UnsignedInt8::getNumber(){

        return this->number;

    }


}

