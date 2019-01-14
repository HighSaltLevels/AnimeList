#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "widgets.h"

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
bool getAnimeVec(std::vector<std::string>*, std::string);
int findLine(FILE*,std::string);
Anime_t getAnimeByName(std::string,std::string);

#endif

