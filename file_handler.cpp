#include "file_handler.h"
#include "MainWindow.h"

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
    char line[100] = {0};
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

    while (fgets(line, 100, fp))
    {
        if (line[0] == '\n')
            break;
        for (i=0; i<100; i++)
        {
            if (line[i] == '|')
                break;
            name = name + line[i];
        }
        if (name.length() > 43)
        {
            name.resize(43);
            name.replace(39,3,"...");
        }
        for (j=++i; j<=100; j++)
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

    entry = anime.name + "|" + std::to_string(anime.num_episodes) + "|" + std::to_string(anime.rating) + "\n";
    fputs(entry.c_str(),fp);

    fclose(fp);
}

void removeEntry(std::string filename, std::string anime)
{
    char line[100];
    int line_num, line_index = 0;

    std::string file_str = "";
    FILE* fread = fopen(filename.c_str(), "r");
    line_num = findLine(fread, anime);
    rewind(fread);

    while(fgets(line, 100, fread))
    {
        if (line_index != line_num)
            file_str+=line;
        line_index++;
    }
    fclose(fread);
    FILE* fwrite = fopen(filename.c_str(), "w");
    fprintf(fwrite, "%s", file_str.c_str());
    fclose(fwrite);
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

void sortList(bool watched, int sort_type, bool low_to_high)
{
    std::vector<Anime_t> unsorted_anime, sorted_anime, other_vec;
    std::vector<Anime_t>::iterator it = sorted_anime.begin();
    std::string original1, original2, lower_str, compare_str;
    int current, size;

    if (watched)
    {
        unsorted_anime = getList(WATCHEDPATH);
        other_vec = getList(UNWATCHEDPATH);
    }
    else
    {
        unsorted_anime = getList(UNWATCHEDPATH);
        other_vec = getList(WATCHEDPATH);
    }
    size = unsorted_anime.size();

    // Selection Sort TODO: see if insertion sort or quick sort is faster
    switch (sort_type)
    {
        case 0:
            for(int i=0; i<size; i++)
            {
                current = 0;
                if (low_to_high)
                {
                    for (unsigned int j=0; j<unsorted_anime.size(); j++)
                    {
                        original1 = unsorted_anime[j].name;
                        original2 = unsorted_anime[current].name;
                        std::transform(original1.begin(),original1.end(),original1.begin(), ::tolower);
                        std::transform(original2.begin(),original2.end(),original2.begin(), ::tolower);
                        if (original1 < original2)
                            current = j;
                    }
                }
                else
                {
                    for (int j=unsorted_anime.size()-1; j>=0; j--)
                    {
                        original1 = unsorted_anime[j].name;
                        original2 = unsorted_anime[current].name;
                        std::transform(original1.begin(),original1.end(),original1.begin(), ::tolower);
                        std::transform(original2.begin(),original2.end(),original2.begin(), ::tolower);
                        if (original1 > original2)
                            current = j;
                    }
                }
                it = sorted_anime.insert(it,unsorted_anime[current]);
                unsorted_anime.erase(unsorted_anime.begin()+current);
            }
            break;

        case 1:
            for(int i=0; i<size;  i++)
            {
                current = 0;
                if (low_to_high)
                {
                    for (unsigned int j=0; j<unsorted_anime.size(); j++)
                    {
                        if (unsorted_anime[j].num_episodes < unsorted_anime[current].num_episodes)
                            current = j;
                    }
                }
                else
                {
                    for (int j=unsorted_anime.size()-1; j>=0; j--)
                    {
                        if (unsorted_anime[j].num_episodes > unsorted_anime[current].num_episodes)
                            current = j;
                    }
                }
                it = sorted_anime.insert(it,unsorted_anime[current]);
                unsorted_anime.erase(unsorted_anime.begin()+current);
            }
            break;

        case 2:
            for (int i=0; i<size; i++)
            {
                current = 0;
                if (low_to_high)
                {
                    for (unsigned int j=0; j<unsorted_anime.size(); j++)
                    {
                        if (unsorted_anime[j].rating < unsorted_anime[current].rating)
                            current = j;
                    }
                }
                else
                {
                    for (int j=unsorted_anime.size()-1; j>=0; j--)
                    {
                        if (unsorted_anime[j].rating > unsorted_anime[current].rating)
                            current = j;
                    }
                }
                it = sorted_anime.insert(it,unsorted_anime[current]);
                unsorted_anime.erase(unsorted_anime.begin()+current);
            }
            break;

        default: break;
    }
    if (watched)
    {
        overwriteFile(WATCHEDPATH, sorted_anime);
        loadLists(other_vec, sorted_anime);
    }
    else
    {
        overwriteFile(UNWATCHEDPATH, sorted_anime);
        loadLists(sorted_anime, other_vec);
    }
}

void overwriteFile(std::string filename, std::vector<Anime_t> anime_vec)
{
    FILE* fp = fopen(filename.c_str(), "w");
    std::string line = "";
    for (int i=anime_vec.size()-1; i>=0; i--)
    {
        line+=anime_vec[i].name + '|';
        line+=std::to_string(anime_vec[i].num_episodes) + '|';
        line+=std::to_string(anime_vec[i].rating) + '\n';
        fprintf(fp, "%s", line.c_str());
        line = "";
    }
    fclose(fp);
}

bool getAnimeVec(std::vector<std::string>* animes, std::string filename)
{
    FILE* fp = fopen(filename.c_str(), "r");
    char line[100] = {0};
    std::string name;
    std::vector<std::string>::iterator it = animes->begin();
    
    if(!fp)
        return false;
    while(fgets(line, 100, fp))
    {
        if (line[0] == '\n')
            break;
        for (int i=0; i<100; i++)
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
    char line[100] = {0};
    int line_num = 0;
    std::string name_in_file;
    while (fgets(line, 100, fp))
    {
        if (line[0] == '\n')
            break;
        for (int i=0; i<100; i++)
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
    char line[100] = {0};
    std::string working_str = "";
    FILE* fp = fopen(filename.c_str(), "r");

    while (fgets(line, 100, fp))
    {
        if (line[0] == '\n')
            break;
        for (int i=0; i<100; i++)
        {
            if (line[i] == '\n')
                break;
            if (line[i] == '|')
                if (!name.compare(working_str))
                {
                    working_str = "";
                    for (int j=i+1; j<100; j++)
                    {
                        if (line[j] == '|')
                        {
                            anime.num_episodes = stoi(working_str);
                            working_str = "";
                            for (int k=j+1; k<100; k++)
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

