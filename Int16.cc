#include "jet/Int16.h"


namespace jet{



    Int16::Int16()
        :number(number)
    {


    }


    Int16::Int16( short number )
        :number(number)
    {


    }



    Int16::~Int16(){


    }


    void Int16::setNumber( short number ){

        this->number = number;

    }


    short Int16::getNumber(){

        return this->number;

    }


}

