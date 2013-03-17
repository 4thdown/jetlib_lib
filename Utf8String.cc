#include "jet/Utf8String.h"
#include "jet/Exception.h"

#include <cstring>
#include <string>
#include <algorithm>
#include <utility>
#include <iostream>
#include <iomanip>
#include <sstream>


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

        //make room for null character so we don't have to free memory after ->getCString() calls
        size_in_bytes++;

        this->characters = new char[ size_in_bytes ];
        this->number_of_characters = size_in_bytes - 1;
        this->size_of_character_data = size_in_bytes;

        if( size_in_bytes == 1 ){
            *this->characters = 0;
            //no characters, just add the NULL character, no copy to do (see Invariant 001)
            return;
        }
        memcpy( this->characters, source_string, size_in_bytes - 1 );

        //add the null character to the last position (because the last byte hasn't been initialized)
        *(this->characters + (size_in_bytes-1)) = 0;

    }



    Utf8String::Utf8String( const char *source_string ): Utf8StringDefaultValues{

        size_t size_in_bytes = strlen( source_string );

        //make room for null character so we don't have to free memory after ->getCString() calls
        size_in_bytes++;

        this->characters = new char[ size_in_bytes ];
        this->number_of_characters = size_in_bytes - 1;
        this->size_of_character_data = size_in_bytes;

        if( size_in_bytes == 1 ){
            *this->characters = 0;
            //no characters, just add the NULL character, no copy to do (see Invariant 001)
            return;
        }

        memcpy( this->characters, source_string, size_in_bytes );

    }



    Utf8String::Utf8String( char source_character ): Utf8StringDefaultValues{

        this->characters = new char[ 2 ];
        this->characters[0] = source_character;
        this->characters[1] = 0;  //null terminate

        this->number_of_characters = 1;
        this->size_of_character_data = 2;

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




#define LEXICAL_CAST_NUMBER \
    std::ostringstream convert; \
    convert << number; \
    Utf8String *temp_string = new Utf8String( convert.str() ); \
    swap( *this, *temp_string ); \
    delete temp_string;

    Utf8String::Utf8String( long number ): Utf8StringDefaultValues{ LEXICAL_CAST_NUMBER }
    Utf8String::Utf8String( unsigned long number ): Utf8StringDefaultValues{ LEXICAL_CAST_NUMBER }
    Utf8String::Utf8String( int number ): Utf8StringDefaultValues{ LEXICAL_CAST_NUMBER }
    Utf8String::Utf8String( unsigned int number ): Utf8StringDefaultValues{ LEXICAL_CAST_NUMBER }
    Utf8String::Utf8String( short number ): Utf8StringDefaultValues{ LEXICAL_CAST_NUMBER }
    Utf8String::Utf8String( unsigned short number ): Utf8StringDefaultValues{ LEXICAL_CAST_NUMBER }





    Utf8String& Utf8String::operator=( const Utf8String &other ){

        //copy and swap
        Utf8String *temp_string = new Utf8String( other );
        swap( *this, *temp_string );
        delete temp_string;

        return *this;

    }


    Utf8String& Utf8String::operator=( const char *other ){

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


    const char* Utf8String::getCString() const{

        return this->characters;

    }



    void Utf8String::clear(){

        if( this->size_of_character_data == 0 ){
            return;
        }

        Utf8String *temp = new Utf8String;

        swap( *this, *temp );

        delete temp;

    }



    unsigned int Utf8String::getSize() const{

        return this->number_of_characters;

    }


    unsigned int Utf8String::getLength() const{

        return this->number_of_characters;

    }


    bool Utf8String::isEmpty() const{

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

            //remove one of the NULL characters
            new_size_of_character_data--;

            temp->characters = new char[ new_size_of_character_data ];

            memcpy( temp->characters, this->characters, this->size_of_character_data );
            memcpy( temp->characters + this->size_of_character_data - 1, right.characters, right.size_of_character_data );

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

    Utf8String& Utf8String::operator+=( const char *right ){

        Utf8String *right_string = new Utf8String( right );
        *this += *right_string;
        delete right_string;
        return *this;

    }



    Utf8String Utf8String::operator+( const Utf8String &right ) const{

        return Utf8String(*this) += right;

    }



    Utf8String Utf8String::operator+( const char right ) const{

        return Utf8String(*this) += Utf8String(right);

    }


    Utf8String Utf8String::operator+( const char *right ) const{

        return Utf8String(*this) += Utf8String(right);

    }


    Utf8String operator+( const char *left, const Utf8String& right ){

        return Utf8String(left) + right;

    }

    Utf8String operator+=( const char *left, const Utf8String& right ){

        return Utf8String(left) + right;

    }


    Utf8String operator+( const char left, const Utf8String& right ){

        return Utf8String(left) + right;

    }

    Utf8String operator+=( const char left, const Utf8String& right ){

        return Utf8String(left) + right;

    }



    std::ostream& operator<<( std::ostream &output_stream, const Utf8String &output_string ){

        if( output_string.getSize() > 0 ){
            output_stream.write( output_string.characters, output_string.size_of_character_data - 1 );
        }
        return output_stream;

    }



    std::ostream& print_as_binary( std::ostream& output_stream, const Utf8String &output_string ){

        size_t byte_index = 0;
        size_t bit_index;
        size_t shift_by;

        char bit_mask;

        char *byte_iterator = output_string.characters;
        char current_byte;

        while( byte_index < output_string.getSize() ){

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


    std::ostream& print_as_hex( std::ostream& output_stream, const Utf8String &output_string ){

        size_t byte_index = 0;

        char *byte_iterator = output_string.characters;
        char current_byte;

        while( byte_index < output_string.size_of_character_data ){

            current_byte = *byte_iterator;

            output_stream << std::setw(2) << std::setfill('0') << std::hex << (int) current_byte;

            byte_index++;

            byte_iterator++;

        }

        return output_stream;

    }



    bool Utf8StringComparator::operator()( Utf8String const &left, Utf8String const &right ) const{

        size_t left_length = left.getLength();
        size_t right_length = right.getLength();
        size_t shortest = ( left_length < right_length )? left_length : right_length;

        size_t x = 0;

        char left_character, right_character;

        for( ; x < shortest; x++ ){

            left_character = left.getAsciiCharacterAtIndex( x );
            right_character = right.getAsciiCharacterAtIndex( x );

            if( left_character < right_character ){
                return true;
            }

            if( left_character > right_character ){
                return false;
            }

        }

        if( left_length == right_length ){
            //strings are equal
            return false;
        }

        if( right_length > left_length ){
            //right has more characters
            return true;
        }

        //left has more characters
        return false;

    }



    int Utf8String::compare( Utf8String const &left, Utf8String const &right ){

        size_t left_length = left.getLength();
        size_t right_length = right.getLength();
        size_t shortest = ( left_length < right_length )? left_length : right_length;

        size_t x = 0;

        char left_character, right_character;

        for( ; x < shortest; x++ ){

            left_character = left.getAsciiCharacterAtIndex( x );
            right_character = right.getAsciiCharacterAtIndex( x );

            if( left_character < right_character ){
                return -1;
            }

            if( left_character > right_character ){
                return 1;
            }

        }

        if( left_length == right_length ){
            //strings are equal
            return 0;
        }

        if( right_length > left_length ){
            //right has more characters
            return 1;
        }

        //left has more characters
        return -1;

    }


    int Utf8String::compare( const char* left, Utf8String const &right ){

        Utf8String left_utf8string( left );
        return Utf8String::compare( left_utf8string, right );

    }

    int Utf8String::compare( Utf8String const &left, const char* right ){

        Utf8String right_utf8string( right );
        return Utf8String::compare( left, right_utf8string );

    }

    int Utf8String::compare( const std::string& left, Utf8String const &right ){

        Utf8String left_utf8string( left );
        return Utf8String::compare( left_utf8string, right );

    }

    int Utf8String::compare( Utf8String const &left, const std::string& right ){

        Utf8String right_utf8string( right );
        return Utf8String::compare( left, right_utf8string );

    }





    int Utf8String::compare( const Utf8String& other ){
        return Utf8String::compare( *this, other );
    }


    int Utf8String::compare( const char* other ){
        return Utf8String::compare( *this, Utf8String(other) );
    }


    int Utf8String::compare( const std::string& other ){
        return Utf8String::compare( *this, Utf8String(other) );
    }



    bool operator==( const Utf8String& lhs, const Utf8String& rhs ){ return Utf8String::compare( lhs, rhs ) == 0; }

    bool operator==( const char* lhs, const Utf8String& rhs ){ return Utf8String::compare( lhs, rhs ) == 0; }

    bool operator==( const Utf8String& lhs, const char* rhs ){ return Utf8String::compare( lhs, rhs ) == 0; }

    bool operator==( const std::string& lhs, const Utf8String& rhs ){ return Utf8String::compare( lhs, rhs ) == 0; }

    bool operator==( const Utf8String& lhs, const std::string& rhs ){ return Utf8String::compare( lhs, rhs ) == 0; }



    bool operator!=( const Utf8String& lhs, const Utf8String& rhs ){ return Utf8String::compare( lhs, rhs ) != 0; }

    bool operator!=( const char* lhs, const Utf8String& rhs ){ return Utf8String::compare( lhs, rhs ) != 0; }

    bool operator!=( const Utf8String& lhs, const char* rhs ){ return Utf8String::compare( lhs, rhs ) != 0; }

    bool operator!=( const std::string& lhs, const Utf8String& rhs ){ return Utf8String::compare( lhs, rhs ) != 0; }

    bool operator!=( const Utf8String& lhs, const std::string& rhs ){ return Utf8String::compare( lhs, rhs ) != 0; }



    bool operator<( const Utf8String& lhs, const Utf8String& rhs ){ return Utf8String::compare( lhs, rhs ) < 0; }

    bool operator<( const char* lhs, const Utf8String& rhs ){ return Utf8String::compare( lhs, rhs ) < 0; }

    bool operator<( const Utf8String& lhs, const char* rhs ){ return Utf8String::compare( lhs, rhs ) < 0; }

    bool operator<( const std::string& lhs, const Utf8String& rhs ){ return Utf8String::compare( lhs, rhs ) < 0; }

    bool operator<( const Utf8String& lhs, const std::string& rhs ){ return Utf8String::compare( lhs, rhs ) < 0; }



    bool operator>( const Utf8String& lhs, const Utf8String& rhs ){ return Utf8String::compare( lhs, rhs ) > 0; }

    bool operator>( const char* lhs, const Utf8String& rhs ){ return Utf8String::compare( lhs, rhs ) > 0; }

    bool operator>( const Utf8String& lhs, const char* rhs ){ return Utf8String::compare( lhs, rhs ) > 0; }

    bool operator>( const std::string& lhs, const Utf8String& rhs ){ return Utf8String::compare( lhs, rhs ) > 0; }

    bool operator>( const Utf8String& lhs, const std::string& rhs ){ return Utf8String::compare( lhs, rhs ) > 0; }



    bool operator<=( const Utf8String& lhs, const Utf8String& rhs ){ return Utf8String::compare( lhs, rhs ) <= 0; }

    bool operator<=( const char* lhs, const Utf8String& rhs ){ return Utf8String::compare( lhs, rhs ) <= 0; }

    bool operator<=( const Utf8String& lhs, const char* rhs ){ return Utf8String::compare( lhs, rhs ) <= 0; }

    bool operator<=( const std::string& lhs, const Utf8String& rhs ){ return Utf8String::compare( lhs, rhs ) <= 0; }

    bool operator<=( const Utf8String& lhs, const std::string& rhs ){ return Utf8String::compare( lhs, rhs ) <= 0; }



    bool operator>=( const Utf8String& lhs, const Utf8String& rhs ){ return Utf8String::compare( lhs, rhs ) >= 0; }

    bool operator>=( const char* lhs, const Utf8String& rhs ){ return Utf8String::compare( lhs, rhs ) >= 0; }

    bool operator>=( const Utf8String& lhs, const char* rhs ){ return Utf8String::compare( lhs, rhs ) >= 0; }

    bool operator>=( const std::string& lhs, const Utf8String& rhs ){ return Utf8String::compare( lhs, rhs ) >= 0; }

    bool operator>=( const Utf8String& lhs, const std::string& rhs ){ return Utf8String::compare( lhs, rhs ) >= 0; }







    Utf8String Utf8String::toCamelCase() const{

        size_t current_character_index = 0;

        Utf8String new_string;
        char current_character;
        bool is_first_character = true;

        while( current_character_index < this->number_of_characters ){

            current_character = this->getAsciiCharacterAtIndex( current_character_index );

            if(
                ( current_character >= 0x41 && current_character <= 0x5A ) ||  //upper-case alpha
                ( current_character >= 0x61 && current_character <= 0x7A ) ||  //lower-case alpha
                ( current_character >= 0x30 && current_character <= 0x39 ) ||  //numeric
                ( current_character == 0x5F )                                  //underscore
            ){

                if( is_first_character && ( current_character >= 0x61 && current_character <= 0x7A ) ){  //is lower

                    new_string += ( current_character - 32 );  //convert to uppercase and add it to the new string
                    current_character_index++;
                    is_first_character = false;
                    continue;

                }

                if( ( current_character >= 0x61 && current_character <= 0x7A ) || ( current_character >= 0x30 && current_character <= 0x39 ) ){  //is lower or numeric

                    new_string += current_character; //add it to the new string as lower case
                    current_character_index++;
                    is_first_character = false;
                    continue;

                }


                if( current_character == 0x5F ){   //is underscore

                    is_first_character = true;
                    current_character_index++;
                    continue;

                }

                //skip all other characters


            }

            current_character_index++;

        }

        return new_string;

    }



    Utf8String Utf8String::toLowerCase() const{

        size_t current_character_index = 0;

        Utf8String new_string;
        char current_character;

        while( current_character_index < this->number_of_characters ){

            current_character = this->getAsciiCharacterAtIndex( current_character_index );

            if( current_character >= 0x41 && current_character <= 0x5A ){  //upper-case alpha

                new_string += ( current_character + 32 );  //convert to lower case and add it to the new string

            }else{

                new_string += current_character;

            }

            current_character_index++;

        }

        return new_string;

    }



    Utf8String Utf8String::toUpperCase() const{

        size_t current_character_index = 0;

        Utf8String new_string;
        char current_character;

        while( current_character_index < this->number_of_characters ){

            current_character = this->getAsciiCharacterAtIndex( current_character_index );

            if( current_character >= 0x61 && current_character <= 0x7A ){  //lower-case alpha

                new_string += ( current_character - 32 );  //convert to upper case and add it to the new string

            }else{

                new_string += current_character;

            }

            current_character_index++;

        }

        return new_string;

    }


    Utf8String Utf8String::escapeShellArgument() const{

        size_t current_character_index = 0;

        Utf8String new_string;
        char current_character;

        while( current_character_index < this->number_of_characters ){

            current_character = this->getAsciiCharacterAtIndex( current_character_index );

            if( current_character == 0x27 ){  //single quote

                //this will replace all single quotes with '\''
                new_string += 0x27;  //single quote
                new_string += 0x5C;  //backslash
                new_string += 0x27;  //single quote
                new_string += 0x27;  //single quote

            }else{

                new_string += current_character;

            }

            current_character_index++;

        }

        return '\'' + new_string + '\'';

    }



    std::vector<Utf8String> Utf8String::split( char delimiter ) const{

        size_t current_character_index = 0;

        Utf8String new_string;
        char current_character;

        std::vector<Utf8String> list;

        while( current_character_index < this->number_of_characters ){

            current_character = this->getAsciiCharacterAtIndex( current_character_index );

            if( current_character == delimiter ){

                list.push_back( std::move(new_string) );  //this will empty out this string (effectively doing new_string = "";)

            }else{

                new_string += current_character;

            }

            current_character_index++;

        }

        list.push_back( std::move(new_string) );

        return list;

    }




}
