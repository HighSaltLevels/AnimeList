/*********************************************************************************************
* filehandler.h
*
* Description: This file contains the anime struct, the file paths, and all of the function
*              definitions that interface with the text files. All file handling will be using
*              C functions since file streams are a rude I/O
*
* Functions:
*            std::vector<Anime_t> getWatchedList:   Function that returns a vector of all the
*                                                   anime in a specified list
*            std::vector<Anime_t> getUnWatchedList: Function that returns a vector of all the
*                                                   anime in the unwatched list
*            std::vector<Anime_t> getList:          Function that returns a vector of all the
*                                                   anime in the watched list
*            void addEntry:                         Function that adds an anime to a
*                                                   specified file
*            void removeEntry:                      Function that removes an anime from a
*                                                   specified file
*            void editEntry:                        Function that edits an anime from a
*                                                   specified file
*            void switchEntry:                      Function that moves an anime from one file
*                                                   to the other
*            void sortList:                         Function that sorts a specified list
*                                                   based on chosen criteria
*            void overwriteFile:                    Function that reads a file into memory,
*                                                   edits it and overwrites it to the new file
*            bool getAnimeVec:                      Function that gets a vector of anime from
*                                                   a specified list and returns a boolean
*                                                   value that indicates if the file exists
*            int findLine:                          Function that finds an anime in a file and
*                                                   returns the line number of that anime
*            Anime_t getAnimeByName:                Function that searches for an anime in a
*                                                   file and returns it.
*
* Variables:
*            Anime_t: A struct that holds an anime's name, number of episodes, and rating
*
*********************************************************************************************/

#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "widgets.h"

// File paths for unwatched text file, watched text file, and icon
#define WATCHEDPATH "/usr/lib/animelist/watched.txt"
#define UNWATCHEDPATH "/usr/lib/animelist/unwatched.txt"
#define ICONPATH "/usr/lib/animelist/icon.png"

// Struct that is used to hold an anime
typedef struct {
    std::string name;
    int num_episodes;
    int rating;
} Anime_t;

// Function defs
std::vector<Anime_t> getWatchedList(void);
std::vector<Anime_t> getUnwatchedList(void);
std::vector<Anime_t> getList(std::string);
void addEntry(std::string,Anime_t);
void removeEntry(std::string,std::string);
void editEntry(std::string,std::string,Anime_t);
void switchEntry(std::string,std::string, Anime_t);
void sortList(bool,int,bool);
void overwriteFile(std::string,std::vector<Anime_t>);
bool getAnimeVec(std::vector<std::string>*, std::string);
int findLine(FILE*,std::string);
Anime_t getAnimeByName(std::string,std::string);

#endif

