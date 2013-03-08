#include "jet/Exception.h"
#include "jet/Utf8String.h"

#include <cstring>


namespace jet{


    Exception::Exception( const char *exception_message ){

        this->message = Utf8String( exception_message );

    }

    Exception::Exception( const Utf8String exception_message ){

        this->message = exception_message;

    }

    Exception::Exception( const char *exception_message, const char *filename, const int line_number ){

        this->message = Utf8String( exception_message );
        this->filename = Utf8String( filename );
        this->line_number = line_number;

    }

    Exception::Exception( const Utf8String exception_message, const char *filename, const int line_number ){

        this->message = exception_message;
        this->filename = Utf8String( filename );
        this->line_number = line_number;

    }


}
