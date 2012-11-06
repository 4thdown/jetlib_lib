#include "jet/Utf8String.h"
#include "jet/Exception.h"

#include <cstring>
#include <string>
#include <algorithm>
#include <utility>
#include <iostream>


namespace jet{

    #define Utf8StringDefaultValues include_bom(true),number_of_characters(0),size_of_character_data(0),characters(NULL)



    Utf8String::Utf8String(): Utf8StringDefaultValues{

    }



    Utf8String::Utf8String( const Utf8String& other ): Utf8StringDefaultValues{

        this->include_bom = other.include_bom;
        this->number_of_characters = other.number_of_characters;
        this->size_of_character_data = other.size_of_character_data;

        if( this->size_of_character_data > 0 ){
            this->characters = new char[ this->size_of_character_data ];
            memcpy( this->characters, other.characters, this->size_of_character_data );
        }

    }



    Utf8String::Utf8String( Utf8String&& other ): Utf8StringDefaultValues{

        *this = std::move( other );

    }



    Utf8String::Utf8String( const char *source_string, size_t size_in_bytes ): Utf8StringDefaultValues{

        if( size_in_bytes == 0 ){
            throw Exception( "Utf8String size cannot be zero." );
        }

        this->characters = new char[ size_in_bytes ];
        memcpy( this->characters, source_string, size_in_bytes );

        this->number_of_characters = size_in_bytes;
        this->size_of_character_data = size_in_bytes;

    }



    Utf8String::Utf8String( const char *source_string ): Utf8StringDefaultValues{

        size_t size_in_bytes = strlen( source_string );

        if( size_in_bytes == 0 ){
            throw Exception( "Utf8String size cannot be zero." );
        }

        this->characters = new char[ size_in_bytes ];
        memcpy( this->characters, source_string, size_in_bytes );

        this->number_of_characters = size_in_bytes;
        this->size_of_character_data = size_in_bytes;

    }



    Utf8String::Utf8String( char source_character ): Utf8StringDefaultValues{

        this->characters = new char[ 1 ];
        this->characters[0] = source_character;

        this->number_of_characters = 1;
        this->size_of_character_data = 1;

    }



    Utf8String::Utf8String( const std::string &source_string ): Utf8StringDefaultValues{

        const char *string_data = source_string.c_str();

        Utf8String *temp_string = new Utf8String( string_data, source_string.length() );

        swap( *this, *temp_string );

        delete temp_string;

    }



    Utf8String::Utf8String( const Utf8Character &other ): Utf8StringDefaultValues{

        char ascii_character = other.getAsciiCharacter();

        Utf8String *temp_string = new Utf8String( ascii_character );

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



    Utf8String& Utf8String::operator=( Utf8String &&other ){

        //create an empty string and replace *this
            Utf8String *temp = new Utf8String;
            swap( *this, *temp );
            delete temp; //frees the existing *this

        //steal the contents of "other" and set "other" to the empty string
            swap( *this, other );

        //now "other" should be the blank string
            return *this;

    }



    Utf8String::~Utf8String(){

        if( this->size_of_character_data != 0 ){
            delete[] this->characters;
        }

    }



    char Utf8String::getAsciiCharacterAtIndex( size_t index ) const{

        if( index >= this->number_of_characters ){

            throw new Exception( "Index out of range." );

        }

        return this->characters[ index ];

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


    bool Utf8String::isEmpty(){

        return this->getSize() == 0;

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



    Utf8String& Utf8String::operator+=( const Utf8String &right ){

        //if either is empty, return a copy of the other
            if( right.number_of_characters == 0 ){
                return *this;
            }

            if( this->number_of_characters == 0 ){
                *this = right;
                return *this;
            }


        //else, concatenate them into a new third (and swap with *this)
            size_t new_size_of_character_data = this->size_of_character_data + right.size_of_character_data;
            size_t new_number_of_characters = this->number_of_characters + right.number_of_characters;

            Utf8String *temp = new Utf8String;


            temp->characters = new char[ new_size_of_character_data ];

            memcpy( temp->characters, this->characters, this->size_of_character_data );
            memcpy( temp->characters + this->size_of_character_data, right.characters, right.size_of_character_data );

            temp->number_of_characters = new_number_of_characters;
            temp->size_of_character_data = new_size_of_character_data;
            temp->include_bom = this->include_bom;

            swap( *this, *temp );
            delete temp;

        return *this;


    }



    Utf8String& Utf8String::operator+=( const char right ){

        Utf8String *right_string = new Utf8String( right );
        *this += *right_string;
        delete right_string;
        return *this;

    }



    const Utf8String Utf8String::operator+( const Utf8String &right ){

        return Utf8String(*this) += right;

    }



    const Utf8String Utf8String::operator+( const char right ){

        return Utf8String(*this) += Utf8String(right);

    }



    std::ostream& operator<<( std::ostream &output_stream, const Utf8String &output_string ){

        output_stream.write( output_string.characters, output_string.size_of_character_data );
        return output_stream;

    }



    std::ostream& print_as_binary( std::ostream& output_stream, const Utf8String &output_string ){

        size_t byte_index = 0;
        size_t bit_index;
        size_t shift_by;

        char bit_mask;

        char *byte_iterator = output_string.characters;
        char current_byte;

        while( byte_index < output_string.size_of_character_data ){

            current_byte = *byte_iterator;

            bit_index = 0;

            while( bit_index < 8 ){

                shift_by = 7 - bit_index;
                bit_mask = 1 << shift_by;

                if( current_byte & bit_mask ){
                    output_stream.write( "1", 1 );
                }else{
                    output_stream.write( "0", 1 );
                }

                bit_index++;

            }

            byte_index++;

            byte_iterator++;

        }


        return output_stream;

    }


}
