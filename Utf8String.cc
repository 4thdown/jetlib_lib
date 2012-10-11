#include "jet/Utf8String.h"
#include "jet/Exception.h"

#include <cstring>
#include <string>
#include <algorithm>

#include <iostream>


namespace jet{


    Utf8String::Utf8String():
        include_bom( true ),
        number_of_characters( 0 ),
        size_of_character_data( 0 ),
        characters( NULL )
    {

    }


    Utf8String::Utf8String( const Utf8String& other ){

        //use the default constructor to build this
        Utf8String *temp_string = new Utf8String( "abc", 3 );
            swap( *this, *temp_string );
            delete temp_string;

        //copy the elements
            //this->include_bom = other.include_bom;
            //this->number_of_characters = other.number_of_characters;
            //this->size_of_character_data = other.size_of_character_data;

            /*
            if( this->size_of_character_data > 0 ){
                this->characters = new char[ this->size_of_character_data ];
                memcpy( this->characters, other.characters, this->size_of_character_data );
            }
           */

    }


    Utf8String::Utf8String( Utf8String&& other ){

        //use the default constructor to build this
            Utf8String *temp_string = new Utf8String;
            swap( *this, *temp_string );
            delete temp_string;

        //steal the contents of "other"
            swap( *this, other );

    }


    Utf8String::Utf8String( const char *source_string, size_t size_in_bytes ){

        if( size_in_bytes == 0 ){
            throw Exception( "Utf8String size cannot be zero." );
        }

        this->characters = new char[ size_in_bytes ];
        memcpy( this->characters, source_string, size_in_bytes );

        this->number_of_characters = size_in_bytes;
        this->size_of_character_data = size_in_bytes;

    }


    Utf8String::Utf8String( const std::string &source_string ){

        const char *string_data = source_string.c_str();

        Utf8String *temp_string = new Utf8String( string_data, source_string.length() );

        swap( *this, *temp_string );

        delete temp_string;

    }


    Utf8String& Utf8String::operator=( const Utf8String &other ){

        //copy and swap
        Utf8String *temp_string = new Utf8String( other );
        swap( *this, *temp_string );
        delete temp_string;

        return *this;

    }


    Utf8String::~Utf8String(){

        if( this->size_of_character_data != 0 ){
            delete[] this->characters;
        }

    }


    void Utf8String::clear(){

        if( this->size_of_character_data == 0 ){
            return;
        }

        Utf8String *temp = new Utf8String;

        swap( *this, *temp );

        delete temp;

    }


    unsigned int Utf8String::getSize(){

        return this->number_of_characters;

    }

    unsigned int Utf8String::getLength(){

        return this->number_of_characters;

    }






    void swap( Utf8String& first, Utf8String& second ){

        // enable ADL (not necessary in our case, but good practice)
        using std::swap;

        // by swapping the members of two classes,
        // the two classes are effectively swapped
        swap( first.include_bom, second.include_bom );
        swap( first.number_of_characters, second.number_of_characters );
        swap( first.size_of_character_data, second.size_of_character_data );
        swap( first.characters, second.characters );

    }


}
