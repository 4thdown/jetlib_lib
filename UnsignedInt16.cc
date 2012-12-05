#include "jet/UnsignedInt16.h"


namespace jet{



    UnsignedInt16::UnsignedInt16()
        :number(number)
    {


    }


    UnsignedInt16::UnsignedInt16( short number )
        :number(number)
    {


    }



    UnsignedInt16::~UnsignedInt16(){


    }


    void UnsignedInt16::setNumber( short number ){

        this->number = number;

    }


    short UnsignedInt16::getNumber(){

        return this->number;

    }


}

