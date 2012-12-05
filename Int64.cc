#include "jet/Int64.h"


namespace jet{



    Int64::Int64()
        :number(number)
    {


    }


    Int64::Int64( long number )
        :number(number)
    {


    }



    Int64::~Int64(){


    }


    void Int64::setNumber( long number ){

        this->number = number;

    }


    long Int64::getNumber(){

        return this->number;

    }


}

