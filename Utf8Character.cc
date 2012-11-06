#include "jet/Utf8Character.h"
#include "jet/Exception.h"

#include <cstring>
#include <string>
#include <algorithm>
#include <utility>
#include <iostream>


namespace jet{

    #define Utf8CharacterDefaultValues character(0)


    Utf8Character::Utf8Character(): Utf8CharacterDefaultValues{

    }


    Utf8Character::Utf8Character( const Utf8Character& other ): Utf8CharacterDefaultValues{

        this->character = other.character;

    }



    Utf8Character::Utf8Character( Utf8Character&& other ): Utf8CharacterDefaultValues{

        *this = std::move( other );

    }


    Utf8Character::Utf8Character( const char *source_string ): Utf8CharacterDefaultValues{

        this->character = *source_string;

    }


    Utf8Character::Utf8Character( const char source_character ): Utf8CharacterDefaultValues{

        this->character = source_character;

    }


    Utf8Character::Utf8Character( const std::string &source_string ): Utf8CharacterDefaultValues{

        const char *string_data = source_string.c_str();

        Utf8Character *temp_character = new Utf8Character( string_data );

        swap( *this, *temp_character );

        delete temp_character;

    }


    Utf8Character& Utf8Character::operator=( const Utf8Character &other ){

        this->character = other.character;

        return *this;

    }


    Utf8Character& Utf8Character::operator=( Utf8Character &&other ){

        this->character = other.character;
        other.character = 0;
        return *this;

    }





    Utf8Character::~Utf8Character(){


    }


    void Utf8Character::clear(){

        this->character = 0;

    }


    size_t Utf8Character::getSize(){

        return 1;

    }


    char Utf8Character::getAsciiCharacter() const{

        return this->character;

    }


    void swap( Utf8Character& first, Utf8Character& second ){

        // enable ADL (not necessary in our case, but good practice)
        using std::swap;

        swap( first.character, second.character );

    }



    const Utf8String Utf8Character::operator+( const Utf8Character &right ){

        return Utf8String(*this) + Utf8String(right);

    }

    const Utf8String Utf8Character::operator+( const Utf8String &right ){

        return Utf8String(*this) + right;

    }


    std::ostream& operator<<( std::ostream &out, const Utf8Character &output_character ){

        out.put( output_character.getAsciiCharacter() );
        return out;

    }


    std::ostream& print_as_binary( std::ostream& output_stream, const Utf8Character &output_character ){

        size_t byte_index = 0;
        size_t bit_index;
        size_t shift_by;

        char bit_mask;

        char *byte_iterator = (char*)&(output_character.character);
        char current_byte;

        while( byte_index < sizeof(output_character.character) ){

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


    std::ostream& print_as_binary( std::ostream& output_stream, char output_character ){

        size_t bit_index;
        size_t shift_by;

        char bit_mask;

        bit_index = 0;

        while( bit_index < 8 ){

            shift_by = 7 - bit_index;
            bit_mask = 1 << shift_by;

            if( output_character & bit_mask ){
                output_stream.put( '1' );
            }else{
                output_stream.put( '0' );
            }

            bit_index++;

        }

        return output_stream;

    }


}
