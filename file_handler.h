#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "widgets.h"

#define WATCHEDPATH "/usr/lib/animelist/watched.txt"
#define UNWATCHEDPATH "/usr/lib/animelist/unwatched.txt"
#define ICONPATH "/usr/lib/animelist/icon.png"

typedef struct {
    std::string name;
    int num_episodes;
    int rating;
} Anime_t;

std::vector<Anime_t> getWatchedList(void);
std::vector<Anime_t> getUnwatchedList(void);
std::vector<Anime_t> getList(std::string);
void addEntry(std::string,Anime_t);
void removeEntry(std::string,std::string);
void editEntry(std::string,std::string,Anime_t);
void switchEntry(std::string,std::string, Anime_t);
void sortList(bool,int);
void overwriteFile(std::string,std::vector<Anime_t>);
bool getAnimeVec(std::vector<std::string>*, std::string);
int findLine(FILE*,std::string);
Anime_t getAnimeByName(std::string,std::string);

#endif

