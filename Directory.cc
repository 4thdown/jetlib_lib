
#include "jet/Directory.h"
#include "jet/Utf8String.h"
#include "jet/Exception.h"

#include <iostream>
#include <fstream>
#include <string>


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include <unistd.h>



namespace jet{


    Directory::Directory(){

        this->full_path = Directory::getWorkingPath();

    }

    Directory::Directory( const Utf8String &full_path )
        :full_path(full_path)
    {

        if( this->full_path.getSize() == 0 ){
            this->full_path = Directory::getWorkingPath();
        }

    }


    Directory::Directory( const char *full_path )
        :full_path( Utf8String(full_path) )
    {

        if( this->full_path.getSize() == 0 ){
            this->full_path = Directory::getWorkingPath();
        }

    }


    bool Directory::exists() const{

        struct stat file_status;
        if( stat( full_path.getCString(), &file_status ) == 0 ){
            return true;
        }
        return false;

    }



    vector<File*>* Directory::getFiles() const{

        vector<File*> *files = new vector<File*>;


        DIR *directory;
        struct dirent *directory_entry;
        File *current_file;
        Utf8String filename;


        directory = opendir( this->full_path.getCString() );
        if( directory != NULL ){

            while( (directory_entry = readdir(directory)) ){

                // Only recognize regular files or symlinks
                if( directory_entry->d_type != DT_REG && directory_entry->d_type != DT_LNK ){
                    continue;
                }

                filename = this->full_path;
                filename += Utf8String( "/" ) + Utf8String( directory_entry->d_name );

                current_file = new File( filename );
                files->insert( files->end(), current_file );

            }
            closedir(directory);
            return files;

        }else{

            delete files;
            throw new Exception( Utf8String("Couldn't open the directory: ") + this->full_path );

        }

    }


    vector<Directory*>* Directory::getDirectories() const{


        DIR *directory;
        struct dirent *directory_entry;
        Directory *current_directory;
        Utf8String filename;


        directory = opendir( this->full_path.getCString() );
        if( directory != NULL ){

            vector<Directory*> *directories = new vector<Directory*>;

            while( (directory_entry = readdir(directory)) ){

                // Only recognize directories
                if( directory_entry->d_type != DT_DIR ){
                    continue;
                }

                filename = this->full_path;
                filename += Utf8String( "/" ) + Utf8String( directory_entry->d_name );

                current_directory = new Directory( filename );
                directories->insert( directories->end(), current_directory );

            }
            closedir(directory);
            return directories;

        }else{

            throw new Exception( Utf8String("Couldn't open the directory: ") + this->full_path );

        }

    }


    Utf8String Directory::getFullPath() const{

        return this->full_path;

    }


    void Directory::appendToPath( Utf8String path_suffix ){

        this->full_path += path_suffix;

    }


    Utf8String Directory::getName() const{

        using namespace std;
        string name = this->full_path.getCString();

        size_t found;


        found = name.find_last_of( "/\\" );

        if( found ){

            name = name.substr( found + 1 );
            return Utf8String( name );

        }

        return this->full_path;

    }


    bool Directory::create(){

        int status;
        status = mkdir( this->full_path.getCString(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH );

        if( status == 0 ){
            return true;
        }

        int error = errno;

        switch( error ){

            case EACCES:
                throw new Exception( "mkdir failed: The process did not have search permission on some component of pathname, or did not have write permission on the parent directory of the directory to be created." );

            case EEXIST:
                throw new Exception( "mkdir failed: Either the named file refers to a symbolic link, or there is already a file or directory with the given pathname." );

            case ELOOP:
                throw new Exception( "mkdir failed: A loop exists in symbolic links. This error is issued if more than POSIX_SYMLOOP (defined in the limits.h header file) symbolic links are detected in the resolution of pathname." );

            case EMLINK:
                throw new Exception( "mkdir failed: The link count of the parent directory has already reached LINK_MAX (defined in the limits.h header file)." );

            case ENAMETOOLONG:
                throw new Exception( "mkdir failed: pathname is longer than PATH_MAX characters or some component of pathname is longer than NAME_MAX characters while _POSIX_NO_TRUNC is in effect. For symbolic links, the length of the pathname string substituted for a symbolic link exceeds PATH_MAX. The PATH_MAX and NAME_MAX values can be determined using pathconf()." );

            case ENOENT:
                throw new Exception( "mkdir failed: Some component of pathname does not exist, or pathname is an empty string." );

            case ENOSPC:
                throw new Exception( "mkdir failed: The file system does not have enough space to contain a new directory, or the parent directory cannot be extended." );

            case ENOTDIR:
                throw new Exception( "mkdir failed: A component of the pathname prefix is not a directory." );

            case EROFS:
                throw new Exception( "mkdir failed: The parent directory of the directory to be created is on a read-only file system." );

            default: {
                throw new Exception( "mkdir failed: Unrecognised error from mkdir." );
            }

        };

        return false;

    }



    /**
     * Gets the current working directory as a string.
     *
     */
    Utf8String Directory::getWorkingPath(){

        char buffer[ PATH_MAX ];
        char *result;

        result = getcwd( buffer, PATH_MAX );

        //free(result);

        return Utf8String( buffer );


        int error = errno;

        switch( error ){

            case EACCES:
                throw new Exception( "Permission to read or search a component of the filename was denied." );

            case ENOMEM:
                throw new Exception( "Insufficient storage error from getcwd." );

            case EFAULT:
                throw new Exception( "buf points to a bad address." );

            case EINVAL:
                throw new Exception( "The size argument is zero and buf is not a NULL pointer." );

            case ENAMETOOLONG:
                throw new Exception( "The size of the null-terminated absolute pathname string exceeds PATH_MAX bytes." );

            case ENOENT:
                throw new Exception( "The current working directory has been unlinked." );

            case ERANGE:
                throw new Exception( "The size argument is less than the length of the absolute pathname of the working directory, including the terminating null byte. You need to allocate a bigger array and try again." );

            default: {
                throw new Exception( "Unrecognised error from getcwd." );
            }

        };

    }



    /**
     * Determines if the filesystem entry at the provided location is a directory.
     *
     */
    bool Directory::isDirectory( const Utf8String &full_path ){

        return Directory::isDirectory( full_path.getCString() );

    }



    /**
     * Determines if the filesystem entry at the provided location is a directory.
     *
     */
    bool Directory::isDirectory( const char *full_path ){

        struct stat filesystem_stats;

        if( stat(full_path, &filesystem_stats) == 0 ){

            if( filesystem_stats.st_mode & S_IFDIR ){
                return true;
            }
            return false;

        }

        return false;

    }


}
