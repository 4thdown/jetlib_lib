#include "jet/Int32.h"


namespace jet{



    Int32::Int32()
        :number(number)
    {


    }


    Int32::Int32( int number )
        :number(number)
    {


    }



    Int32::~Int32(){


    }


    void Int32::setNumber( int number ){

        this->number = number;

    }


    int Int32::getNumber(){

        return this->number;

    }


}

