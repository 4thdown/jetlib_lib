
#include "jet/File.h"
#include "jet/Utf8String.h"
#include "jet/Exception.h"

#include <iostream>
#include <fstream>
#include <sys/stat.h>

namespace jet{


    File::File()
        :state(1), filename("")
    {

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

        Utf8String output_string( output );
        std::ofstream myfile;
        myfile.open( this->filename.getCString() );
        myfile << output_string;
        myfile.close();

    }



    void File::write( Utf8String &output ){

        std::ofstream myfile;
        myfile.open( this->filename.getCString() );
        myfile << output;
        myfile.close();

    }


    Utf8String File::getContents(){

        using namespace std;

        ifstream::pos_type size;
        Utf8String new_contents;

        char *memblock;

        ifstream myfile( this->filename.getCString(), ios::in | ios::binary | ios::ate );

        if( myfile.is_open() ){

            size = myfile.tellg();
            memblock = new char[ size ];
            myfile.seekg( 0, ios::beg );
            myfile.read( memblock, size );
            myfile.close();

            new_contents = std::move( Utf8String(memblock, size) );

            delete[] memblock;

        }else{

            throw new Exception( "Unable to open file.", __FILE__, __LINE__ );

        }

        return new_contents;

    }



    Utf8String File::getFilename() const{

        return this->filename;

    }


    void File::setFilename( Utf8String filename ){

        this->filename = std::move(filename);

    }


    bool File::exists() const{

        struct stat file_status;
        if( stat( this->filename.getCString(), &file_status ) == 0 ){
            return true;
        }
        return false;

    }



    bool File::exists( Utf8String filename ){

        struct stat file_status;
        if( stat( filename.getCString(), &file_status ) == 0 ){
            return true;
        }
        return false;

    }




}
