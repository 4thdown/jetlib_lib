#include "jet/UnsignedInt64.h"


namespace jet{



    UnsignedInt64::UnsignedInt64()
        :number(number)
    {


    }


    UnsignedInt64::UnsignedInt64( long number )
        :number(number)
    {


    }



    UnsignedInt64::~UnsignedInt64(){


    }


    void UnsignedInt64::setNumber( long number ){

        this->number = number;

    }


    long UnsignedInt64::getNumber(){

        return this->number;

    }


}

