
#include "jet/File.h"


#include <iostream>
#include <fstream>

namespace jet{


    File::File()
        :state(1), filename(""){

    }

    File::File( const char *filename )
        :state(1), filename(filename){

    }


    void File::write( const char *output ){

        std::ofstream myfile;
        myfile.open( this->filename.c_str() );
        myfile << output;
        myfile.close();

    }

}
