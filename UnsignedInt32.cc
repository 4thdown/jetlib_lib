#include "jet/UnsignedInt32.h"


namespace jet{



    UnsignedInt32::UnsignedInt32()
        :number(number)
    {


    }


    UnsignedInt32::UnsignedInt32( int number )
        :number(number)
    {


    }



    UnsignedInt32::~UnsignedInt32(){


    }


    void UnsignedInt32::setNumber( int number ){

        this->number = number;

    }


    int UnsignedInt32::getNumber(){

        return this->number;

    }


}

