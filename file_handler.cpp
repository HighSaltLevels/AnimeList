#include "file_handler.h"

std::vector<Anime_t> getUnwatchedList(void)
{
    return getList("unwatched.txt"); //TODO find good place to put this file
}

std::vector<Anime_t> getWatchedList(void)
{
    return getList("watched.txt"); // TODO find a good place to put this file
}

std::vector<Anime_t> getList(std::string filename)
{
    char line[50] = {0};
    Anime_t anime;
    std::vector<Anime_t> anime_list;
    std::vector<Anime_t>::iterator it = anime_list.begin();
    std::string name = "", num_episodes = "", rating = "";
    int i, j;
    FILE* fp = fopen(filename.c_str(), "r");
    if (!fp)
    {
        std::cout << "Could not find file " << filename << ". A new one will be created when you add an Anime to a list.\n";
        return anime_list;
    }

    while (fgets(line, 50, fp))
    {
        if (line[0] == '\n')
            break;
        for (i=0; i<=50; i++)
        {
            if (line[i] == '|')
                break;
            name = name + line[i];
        }
        for (j=++i; j<=50; j++)
        {
            if (line[j] == '|')
                break;
            num_episodes = num_episodes + line[j];
        }
        j++;
        while (line[j] != '\n')
        {
            rating = rating + line[j];
            j++;
        }
        anime.name = name;
        anime.num_episodes = std::stoi(num_episodes);
        anime.rating = std::stoi(rating);
        it = anime_list.insert(it, anime);
        name = num_episodes = rating = "";
    }
    fclose(fp);
    return anime_list;
}

void addEntry(std::string filename, Anime_t anime)
{
    std::cout << "Writing this Function still In Progress\n";

    FILE* fp = fopen(filename.c_str(), "a");
    std::string entry = "";

    entry = anime.name + "|" + std::to_string(anime.num_episodes) + "|" + std::to_string(anime.rating) + "\n";
    fputs(entry.c_str(),fp);

    fclose(fp);
}

void removeEntry(std::string filename, Anime_t anime)
{
    std::cout << "Writing this Function still In Progress\n";

    FILE* fread = fopen(filename.c_str(), "r");
    FILE* fwrite = fopen("temp", "w");

    fclose(fread);    
    fclose(fwrite);
}

void editEntry(std::string filename, Anime_t old_anime, Anime_t new_anime)
{
    std::cout << "TODO edit entry for anime here\n";
    return;
}

void switchEntry(std::string remove_from_filename, std::string add_to_filename, Anime_t anime)
{
    std::cout << "TODO switch entry for anime here\n";
    return;
}

bool getAnimeVec(std::vector<std::string>* animes, std::string filename)
{
    FILE* fp = fopen(filename.c_str(), "r");
    char line[50] = {0};
    std::string name;
    std::vector<std::string>::iterator it = animes->begin();
    
    if(!fp)
        return false;
    while(fgets(line, 50, fp))
    {
        if (line[0]  == '\n')
            break;
        for (int i=0; i<50; i++)
        {
            if (line[i] == '|')
                break;
            name = name + line[i];
        }
        it = animes->insert(it,name);
        name = "";
    }
    fclose(fp);
    return true;
}

