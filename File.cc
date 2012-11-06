
#include "jet/File.h"
#include "jet/Utf8String.h"
#include "jet/Exception.h"

#include <iostream>
#include <fstream>

namespace jet{


    File::File()
        :state(1), filename(""), contents(""){

    }

    File::File( Utf8String filename )
        :state(1), filename(filename)
    {


    }


    File::File( const char *filename )
        :state(1), filename(Utf8String(filename))
    {


    }


    void File::write( const char *output ){

        this->contents = output;

        std::ofstream myfile;
        myfile.open( this->filename.getCString() );
        myfile << this->contents;
        myfile.close();

    }


    void File::write( Utf8String &output ){

        this->contents = output;

        std::ofstream myfile;
        myfile.open( this->filename.getCString() );
        myfile << this->contents;
        myfile.close();

    }


    Utf8String File::getContents(){

        using namespace std;

        ifstream::pos_type size;
        Utf8String *new_contents;

        char *memblock;

        ifstream myfile( this->filename.getCString(), ios::in|ios::binary|ios::ate );
        if( myfile.is_open() ){

            size = myfile.tellg();
            memblock = new char[ size ];
            myfile.seekg( 0, ios::beg );
            myfile.read( memblock, size );
            myfile.close();

            new_contents = new Utf8String( memblock, size );

            this->contents = *new_contents;

            delete[] memblock;
            delete new_contents;

        }else{

            this->contents = Utf8String();
            throw new Exception( "Unable to open file." );

        }

        return this->contents;

    }

}
