#include "jet/Exception.h"
#include "jet/Utf8String.h"

#include <cstring>


namespace jet{

    Exception::Exception( const char *exception_message ){

        this->message = Utf8String( exception_message );

    }

}
