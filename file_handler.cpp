/*********************************************************************************************
* file_handler.cpp
*
* Description: This file contains all of the functions necessary for reading and writing to
*              the text files
*
* Functions:
*            getUnwatchedList: Function that returns a vector of all of the unwatched anime
*            getWatchedList:   Function that returns a vector of all of the watched anime
*            getList:          Function that returns a vector of the specified list of anime
*            addEntry:         Function that adds an anime to the specified file
*            removeEntry:      Function that removes an anime from the specified file
*            editEntry:        Function that replaces an anime with the updated entry to the
*                              specified file
*            switchEntry:      Function that adds the entry to the other list and removes the 
*                              entry from the original list
*            sortList:         Function that sorts the specified list based on name, number of
*                              episodes, or rating from either high to low or low to high
*            overwriteFile:    Function that overwites the specified file with the given 
*                              vector of anime
*            getAnimeVec:      Function that creates a vector of all of the anime in the
*                              specified file. Returns true if success or false if the file
*                              does not exist 
*            findLine:         Function that finds the line number of the specified anime in
*                              the specified text file
*            getAnimeByName:   Function that returns an anime of specified name
*
*********************************************************************************************/

#include "file_handler.h"
#include "MainWindow.h"

std::vector<Anime_t> getUnwatchedList(void)
/*********************************************************************************************
* Function: 
*   getUnwatchedList
*
* Params:
*   void
*
* returns:
*   A vector of type Anime_t 
*********************************************************************************************/
{
    // Return the unwatched list
    return getList(UNWATCHEDPATH);
}

std::vector<Anime_t> getWatchedList(void)
/*********************************************************************************************
* Function: 
*   getWatchedList
*
* Params:
*   void
*
* returns:
*   A vector of type Anime_t 
*********************************************************************************************/
{
    // Return the watched list
    return getList(WATCHEDPATH);
}

std::vector<Anime_t> getList(std::string filename)
/*********************************************************************************************
* Function: 
*   getList
*
* Params:
*   std::string filename: A specified filepath to read anime from
*
* returns:
*   A vector of type Anime_t 
*********************************************************************************************/
{
    char line[100] = {0};
    Anime_t anime;
    std::vector<Anime_t> anime_list;
    std::vector<Anime_t>::iterator it = anime_list.begin();
    std::string name = "", num_episodes = "", rating = "";
    int i, j;

    // Open the specified file for reading and alert the user if it does not yet exist
    FILE* fp = fopen(filename.c_str(), "r");
    if (!fp)
    {
        std::cout << "Could not find file " << filename << ". A new one will be created when you add an Anime to a list.\n";
        return anime_list;
    }

    // Read until the end of the file
    while (fgets(line, 100, fp))
    {
        // Break if the file is blank
        if (line[0] == '\n')
        {
            fclose(fp);
            break;
        }

        // Read until a '|' is reached indicating the end of the name string. Store the name
        for (i=0; i<100; i++)
        {
            if (line[i] == '|')
                break;
            name = name + line[i];
        }

        // If the name is longer than can be displayed, resize it and end it with a ...
        if (name.length() > 43)
        {
            name.resize(43);
            name.replace(39,3,"...");
        }

        // Contine until another '|' is reached indicating the end of the number of
        // episodes field. Store the number
        for (j=++i; j<=100; j++)
        {
            if (line[j] == '|')
                break;
            num_episodes = num_episodes + line[j];
        }
        j++;

        // Continue until the end of the line. Then store this last number as the
        // rating
        while (line[j] != '\n')
        {
            rating = rating + line[j];
            j++;
        }

        // Assign the corresponding values to the anime and add it to the list
        anime.name = name;
        anime.num_episodes = std::stoi(num_episodes);
        anime.rating = std::stoi(rating);
        it = anime_list.insert(it, anime);
        name = num_episodes = rating = "";
    }

    // Close the file and return the list
    fclose(fp);
    return anime_list;
}

void addEntry(std::string filename, Anime_t anime)
/*********************************************************************************************
* Function: 
*   addEntry
*
* Params:
*   std::string filename: A specified filepath to write to
*   Anime_t anime:        An anime to add to the file
*
* returns:
*   void
*********************************************************************************************/
{
    // Open the file to append so that data is not overwritten
    FILE* fp = fopen(filename.c_str(), "a");
    std::string entry = "";

    // Build a string to write to the file and write it
    entry = anime.name + "|" + std::to_string(anime.num_episodes) + "|" + std::to_string(anime.rating) + "\n";
    fputs(entry.c_str(),fp);

    // Close the file
    fclose(fp);
}

void removeEntry(std::string filename, std::string anime)
/*********************************************************************************************
* Function: 
*   removeEntry
*
* Params:
*   std::string filename: A specified filepath to read and write to
*   std::string anime:    The name of the anime to remove
*
* returns:
*   void
*********************************************************************************************/
{
    char line[100];
    int line_num, line_index = 0;

    // Create a blank file string, open the file to read, and get the line number of the anime
    // in the file
    std::string file_str = "";
    FILE* fread = fopen(filename.c_str(), "r");
    line_num = findLine(fread, anime);

    // Reset the file pointer to the beginning
    rewind(fread);

    // Read until the end of the file
    while(fgets(line, 100, fread))
    {
        // Read the contents of the file into memory without the specified anime to remove
        if (line_index != line_num)
            file_str+=line;
        line_index++;
    }

    // Close the file
    fclose(fread);

    // Write the contents of the file overwriting the original file
    FILE* fwrite = fopen(filename.c_str(), "w");
    fprintf(fwrite, "%s", file_str.c_str());

    // Close the file
    fclose(fwrite);
}

void editEntry(std::string filename, std::string old_anime, Anime_t new_anime)
{
/*********************************************************************************************
* Function: 
*   editEntry
*
* Params:
*   std::string filename:  A specified filepath to read and write to
*   std::string old_anime: Name of anime to remove
*   Anime_t new_anime:     Updated anime to re-add
*
* returns:
*   void
*********************************************************************************************/

    // Remove the old entry and add the new entry
    removeEntry(filename, old_anime);
    addEntry(filename, new_anime);
}

void switchEntry(std::string remove_from_filename, std::string add_to_filename, Anime_t anime)
/*********************************************************************************************
* Function: 
*   switchEntry
*
* Params:
*   std::string remove_from_filename: Specified filepath to remove anime from
*   std::string add_to_filename:      Specified filepath to add anime to
*   Anime_t anime:                    Anime to move from one file to another
*
* returns:
*   void
*********************************************************************************************/
{
    // Remove the anime from one list and add it to the other
    removeEntry(remove_from_filename, anime.name);
    addEntry(add_to_filename, anime);
}

void sortList(bool watched, int sort_type, bool low_to_high)
/*********************************************************************************************
* Function: 
*   sortList
*
* Params:
*   bool watched:     Boolean value to indicate watched or unwatched list
*   int sort_type:    What to sort by. 0=name 1=number of episodes 2=rating
*   bool low_to_high: Boolean value to indicate sorting from low to high or high to low
*
* returns:
*   void
*********************************************************************************************/
{
    std::vector<Anime_t> unsorted_anime, sorted_anime, other_vec;
    std::vector<Anime_t>::iterator it = sorted_anime.begin();
    std::string original1, original2, lower_str, compare_str;
    int current, size;

    // Assign filepaths according to which list is being sorted
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

    // Get the size of anime list
    size = unsorted_anime.size();

    // Selection Sort TODO: see if insertion sort or quick sort is faster
    switch (sort_type)
    {
        // Sort by name
        case 0:
            // Loop through the entire list
            for(int i=0; i<size; i++)
            {
                // Assume 0 for current highest or lowest
                current = 0;

                // Do this if sorting from low to high
                if (low_to_high)
                {
                    // Sort through the list decreasing after each iteration of the outer loop
                    for (unsigned int j=0; j<unsorted_anime.size(); j++)
                    {
                        // Store the strings of the 2 anime so that they can be made lowercase
                        original1 = unsorted_anime[j].name;
                        original2 = unsorted_anime[current].name;

                        // Translate both to lowercase
                        std::transform(original1.begin(),original1.end(),original1.begin(), ::tolower);
                        std::transform(original2.begin(),original2.end(),original2.begin(), ::tolower);

                        // If the new one is less, then make it the current low
                        if (original1 < original2)
                            current = j;
                    }
                }

                // Do this if sorting from high to low
                else
                {
                    // Sort through the list decreasing after each iteration of the outer loop
                    for (int j=unsorted_anime.size()-1; j>=0; j--)
                    {
                        // Store the strings of the 2 anime so that they can be made lowercase
                        original1 = unsorted_anime[j].name;
                        original2 = unsorted_anime[current].name;

                        // Translate both to lowercase
                        std::transform(original1.begin(),original1.end(),original1.begin(), ::tolower);
                        std::transform(original2.begin(),original2.end(),original2.begin(), ::tolower);

                        // If the new one is greater, then make it the current high
                        if (original1 > original2)
                            current = j;
                    }
                }

                // Store the highest or lowest value and remove that value from the other list
                it = sorted_anime.insert(it,unsorted_anime[current]);
                unsorted_anime.erase(unsorted_anime.begin()+current);
            }
            break;

        case 1:
            // Loop through the entire list
            for(int i=0; i<size;  i++)
            {
                // Assume 0 as the current lowest or highest
                current = 0;

                // Do this if sorting from low to high
                if (low_to_high)
                {
                    // Sort through the list decreasing after each iteration of the outer loop
                    for (unsigned int j=0; j<unsorted_anime.size(); j++)
                    {
                        // If the new one is less, then make it the current low
                        if (unsorted_anime[j].num_episodes < unsorted_anime[current].num_episodes)
                            current = j;
                    }
                }

                // Do this if sorting form high to low
                else
                {
                    // Sort through the list decreasing after each iteration of the outer loop
                    for (int j=unsorted_anime.size()-1; j>=0; j--)
                    {
                        // If the new one is more, then make it the current high
                        if (unsorted_anime[j].num_episodes > unsorted_anime[current].num_episodes)
                            current = j;
                    }
                }

                // Store the highest or lowest value and remove that value from the other list
                it = sorted_anime.insert(it,unsorted_anime[current]);
                unsorted_anime.erase(unsorted_anime.begin()+current);
            }
            break;

        case 2:
            // Loop through the entire list
            for (int i=0; i<size; i++)
            {
                // Assume 0 as the current lowest or highest
                current = 0;

                // Do this if sorting form low to high
                if (low_to_high)
                {
                    // Sort through the list decreasing after each iteration of the outer loop
                    for (unsigned int j=0; j<unsorted_anime.size(); j++)
                    {
                        // If the new one is less, then make it the current low
                        if (unsorted_anime[j].rating < unsorted_anime[current].rating)
                            current = j;
                    }
                }

                // Do this if sorting from low to high
                else
                {
                    // Sort through the list decreasing after each iteration of the outer loop
                    for (int j=unsorted_anime.size()-1; j>=0; j--)
                    {
                        // If the new one is more, then make it the current high
                        if (unsorted_anime[j].rating > unsorted_anime[current].rating)
                            current = j;
                    }
                }

                // Store the highest or lowest value and remove that value from the other list
                it = sorted_anime.insert(it,unsorted_anime[current]);
                unsorted_anime.erase(unsorted_anime.begin()+current);
            }
            break;

        default: break;
    }

    // Overwrite the respective file and reload the lists
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
/*********************************************************************************************
* Function: 
*   overwriteFile
*
* Params:
*   std::string filename:           A specified filepath to write to
*   std::vector<Anime_t> anime_vec: A vector that contains the entire list of anime
*
* returns:
*   void
*********************************************************************************************/
{
    // Open the file while overwritting the existing data
    FILE* fp = fopen(filename.c_str(), "w");
    std::string line = "";

    // Loop through the entire vector
    for (int i=anime_vec.size()-1; i>=0; i--)
    {
        // Build a line with each item being separated by '|' and terminated by '\n'
        line+=anime_vec[i].name + '|';
        line+=std::to_string(anime_vec[i].num_episodes) + '|';
        line+=std::to_string(anime_vec[i].rating) + '\n';

        // Write that line to the file
        fprintf(fp, "%s", line.c_str());
        line = "";
    }

    // Close the file
    fclose(fp);
}

bool getAnimeVec(std::vector<std::string>* anime, std::string filename)
/*********************************************************************************************
* Function: 
*   getAnimeVec
*
* Params:
*   std::vector<std::string>* anime: Pointer used to point to the requested list of anime
*                                     names
*   std::string filename:             A specified filepath to read from
*
* returns:
*   A boolean indicating that the file exists and read was successful 
*********************************************************************************************/
{
    FILE* fp = fopen(filename.c_str(), "r");
    char line[100] = {0};
    std::string name;
    std::vector<std::string>::iterator it = anime->begin();

    // Return false if the file does not exist
    if(!fp)
        return false;

    // Read until the end of the file
    while(fgets(line, 100, fp))
    {
        // If the file is blank, break
        if (line[0] == '\n')
        {
            fclose(fp);
            break;
        }

        // Loop through the line
        for (int i=0; i<100; i++)
        {
            // If '|' is found, then we've got the name
            if (line[i] == '|')
                break;
            // Add to the string one char at a time
            name += line[i];
        }

        // Add the anime name to the list
        it = anime->insert(it,name);
        name = "";
    }

    // Close the file and indicate success
    fclose(fp);
    return true;
}

int findLine(FILE* fp, std::string name)
/*********************************************************************************************
* Function: 
*   findLine
*
* Params:
*   FILE* fp:         Pointer to the file to read from
*   std::string name: Name of anime to find the line of
*
* returns:
*   An integer indicating the line number of the anime 
*********************************************************************************************/
{
    char line[100] = {0};
    int line_num = 0;
    std::string name_in_file;

    // Read until the end of the file
    while (fgets(line, 100, fp))
    {
        // If the file is blank, break
        if (line[0] == '\n')
            break;

        // Loop through every character in the line
        for (int i=0; i<100; i++)
        {
            // If end of line reached, increment the line number counter and break
            if (line[i] == '\n')
            {
                line_num++;
                break;
            }

            // Compare the names in the file and return the line number if it matches
            if (line[i] == '|')
                if (!name.compare(name_in_file))
                    return line_num;

            // Add on the next character
            name_in_file += line[i];
        }
        name_in_file = "";
    }

    // Return -1 if failed to find line number
    return -1;
}

Anime_t getAnimeByName(std::string name, std::string filename)
/*********************************************************************************************
* Function: 
*   getAnimeByName
*
* Params:
*   std::string name:     Name of the anime to search for
*   std::string filename: A filepath to read from
*
* returns:
*   An Anime_t of the requested anime
*********************************************************************************************/
{
    Anime_t anime;
    anime.name = name;
    char line[100] = {0};
    std::string working_str = "";
    FILE* fp = fopen(filename.c_str(), "r");

    // Read until the end of the file
    while (fgets(line, 100, fp))
    {
        // If the file is blank, break
        if (line[0] == '\n')
        {
            fclose(fp);
            break;
        }

        // Loop through the entire line
        for (int i=0; i<100; i++)
        {
            // Break if reached the end of the line
            if (line[i] == '\n')
                break;

            // If reached the first '|', compare names
            if (line[i] == '|')
                if (!name.compare(working_str))
                {
                    // If found matching name, prepare to get number of episodes
                    working_str = "";

                    // Continue looping through that line
                    for (int j=i+1; j<100; j++)
                    {
                        // If reached second '|', store episode number
                        if (line[j] == '|')
                        {
                            anime.num_episodes = stoi(working_str);
                            working_str = "";

                            // Continue looping through that line
                            for (int k=j+1; k<100; k++)
                            {
                                // If reached end of line, store the rating
                                if (line[k] == '\n')
                                {
                                    anime.rating = stoi(working_str);
                                    fclose(fp);
                                    return anime;
                                }
                                // Keep adding characters to the rating
                                working_str+=line[k];
                            }
                        }
                        // Keep adding characters to the number of episodes
                        working_str+=line[j];
                    }
                }
            // Keep adding characters to the name
            working_str+=line[i];
        }
        // Reset the working string
        working_str = "";
    }

    // Close the file and return the anime
    fclose(fp);
    return anime;
}

