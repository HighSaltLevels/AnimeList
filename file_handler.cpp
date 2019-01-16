#include "file_handler.h"

std::vector<Anime_t> getUnwatchedList(void)
{
    return getList(UNWATCHEDPATH);
}

std::vector<Anime_t> getWatchedList(void)
{
    return getList(WATCHEDPATH);
}

std::vector<Anime_t> getList(std::string filename)
{
    char line[60] = {0};
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

    while (fgets(line, 60, fp))
    {
        if (line[0] == '\n')
            break;
        for (i=0; i<60; i++)
        {
            if (line[i] == '|')
                break;
            name = name + line[i];
        }
        for (j=++i; j<=60; j++)
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
    FILE* fp = fopen(filename.c_str(), "a");
    std::string entry = "";

    if (anime.name.length() > 43)
    {
        anime.name.resize(43);
        anime.name.replace(41,3,"...");
    }
    entry = anime.name + "|" + std::to_string(anime.num_episodes) + "|" + std::to_string(anime.rating) + "\n";
    fputs(entry.c_str(),fp);

    fclose(fp);
}

void removeEntry(std::string filename, std::string anime)
{
    char line[60];
    int line_num, line_index = 0;
    char temp_file[] = "temp.txt";
    FILE* fread = fopen(filename.c_str(), "r");
    FILE* fwrite = fopen(temp_file, "w");
    line_num = findLine(fread, anime);
    rewind(fread);
    while(fgets(line, 60, fread))
    {
        if (line[0] == '\n')
            break;
        if (line_index != line_num)
            fprintf(fwrite, "%s", line);
        for (int i=0; i<60; i++)
        {
            if (line[i] == '\n')
            {
                line_index++;
                break;
            }
        }
    }
    fclose(fread);    
    fclose(fwrite);
    remove(filename.c_str());
    rename(temp_file, filename.c_str());
}

void editEntry(std::string filename, std::string old_anime, Anime_t new_anime)
{
    removeEntry(filename, old_anime);
    addEntry(filename, new_anime);
}

void switchEntry(std::string remove_from_filename, std::string add_to_filename, Anime_t anime)
{
    removeEntry(remove_from_filename, anime.name);
    addEntry(add_to_filename, anime);
}

bool getAnimeVec(std::vector<std::string>* animes, std::string filename)
{
    FILE* fp = fopen(filename.c_str(), "r");
    char line[60] = {0};
    std::string name;
    std::vector<std::string>::iterator it = animes->begin();
    
    if(!fp)
        return false;
    while(fgets(line, 60, fp))
    {
        if (line[0]  == '\n')
            break;
        for (int i=0; i<60; i++)
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

int findLine(FILE* fp, std::string name)
{
    char line[60] = {0};
    int line_num = 0;
    std::string name_in_file;
    while (fgets(line, 60, fp))
    {
        if (line[0] == '\n')
            break;
        for (int i=0; i<60; i++)
        {
            if (line[i] == '\n')
            {
                line_num++;
                break;
            }
            if (line[i] == '|')
                if (!name.compare(name_in_file))
                    return line_num;
            if (feof(fp))
                return 0;
            name_in_file = name_in_file + line[i];
        }
        name_in_file = "";
    }
    return -1;
}

Anime_t getAnimeByName(std::string name, std::string filename)
{
    Anime_t anime;
    anime.name = name;
    char line[60] = {0};
    std::string working_str = "";
    FILE* fp = fopen(filename.c_str(), "r");

    while (fgets(line, 60, fp))
    {
        if (line[0] == '\n')
            break;
        for (int i=0; i<60; i++)
        {
            if (line[i] == '\n')
                break;
            if (line[i] == '|')
                if (!name.compare(working_str))
                {
                    working_str = "";
                    for (int j=i+1; j<60; j++)
                    {
                        if (line[j] == '|')
                        {
                            anime.num_episodes = stoi(working_str);
                            working_str = "";
                            for (int k=j+1; k<60; k++)
                            {
                                if (line[k] == '\n')
                                {
                                    anime.rating = stoi(working_str);
                                    fclose(fp);
                                    return anime;
                                }
                                working_str+=line[k];
                            }
                        }
                        working_str+=line[j];
                    }
                }   
            working_str+=line[i];
        }
        working_str = "";
    }

    fclose(fp);
    return anime;
}

