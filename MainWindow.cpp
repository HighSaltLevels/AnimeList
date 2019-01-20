/*********************************************************************************************
* MainWindow.cpp
*
* Description: This file builds the MainWindow GUI as well as loads the lists of anime into
*              their respective Text Edits
*
* Functions:
*            MainWindow:             Constructor that builds the MainWindow and loads the
*                                    anime into both text edits
*            OnClosePress:           Function that closes the program when the close button
*                                    is pressed
*            OnUnwatchedAddPress:    Function that builds an Add window and waits for user
*                                    input
*            OnWatchedAddPress:      Function that builds an Add Window and waits for user
*                                    input
*            OnUnwatchedRemovePress: Function that builds a Select Window and waits for user
*                                    input
*            OnWatchedRemovePress:   Function that builds a Select Window and waits for user
*                                    input
*            OnUnwatchedMovePress:   Function that builds a Select Window and waits for user
*                                    input
*            OnWatcheMovePress:      Function that builds a Select Window and waits for user
*                                    input
*            OnUnwatchedEditPress:   Function that builds a Select Window with the extra
*                                    rating field and waits for user input
*            OnWatchedEditPress:     Function that builds a Select Window with the extra
*                                    rating field and waits for user input
*            OnUnwatchedSortPress:   Function that builds a Sort Window and waits for user
*                                    input
*            OnWatchedSortPress:     Function that builds a Sort Window and waits for user
*                                    input
*            loadLists:              Function that formats the anime lists and outputs them to
*                                    the text edits
*
*********************************************************************************************/

#include "MainWindow.h"

// Global Text Edits that can be accessed by any function in this file
// TODO Find a way to keep these from being global variables
QTextEdit* unwatched_edit;
QTextEdit* watched_edit;

MainWindow::MainWindow() : QWidget()
/*********************************************************************************************
* Function: 
*   MainWindow
*
* Params:
*   void
*
* returns:
*   void
*********************************************************************************************/
{
    // Declare blank anime vectors and QStrings for the labels above the text edits
    std::vector<Anime_t> watched_vec, unwatched_vec;
    QString watched_str = "Watched";
    QString unwatched_str = "Unwatched";

    // Create the labels above the text edits and set their fonts to Times New Roman 20pt
    QLabel* watched_lbl = new QLabel(watched_str,this);
    watched_lbl->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    watched_lbl->setFont(QFont("Times",20));
    QLabel* unwatched_lbl = new QLabel(unwatched_str,this);
    unwatched_lbl->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    unwatched_lbl->setFont(QFont("Times",20));

    // Create the text edits, set them to read only, and use a monospace 10pt font
    unwatched_edit = new QTextEdit(this);
    watched_edit = new QTextEdit(this);
    unwatched_edit->setReadOnly(true);
    watched_edit->setReadOnly(true);
    unwatched_edit->setFont(QFont("Monospace",10));
    watched_edit->setFont(QFont("Monospace",10));

    // Get both lists of anime
    watched_vec = getWatchedList();
    unwatched_vec = getUnwatchedList();

    // Load the anime into the text edits
    loadLists(unwatched_vec, watched_vec);

    // Create all the buttons for the GUI
    QPushButton* close_btn = new QPushButton("Close",this);
    QPushButton* sort_unwatched = new QPushButton("Sort List", this);
    QPushButton* add_unwatched = new QPushButton("Add", this);
    QPushButton* remove_unwatched = new QPushButton("Remove", this);
    QPushButton* move_unwatched = new QPushButton("Move to Watched >>", this);
    QPushButton* edit_unwatched = new QPushButton("Edit", this);
    QPushButton* edit_watched = new QPushButton("Edit", this);
    QPushButton* move_watched = new QPushButton("<< Move to Unwatched", this);
    QPushButton* remove_watched = new QPushButton("Remove", this);
    QPushButton* add_watched = new QPushButton("Add", this);
    QPushButton* sort_watched = new QPushButton("Sort List", this);

    // Create a QGridLayout to sort the elements
    QGridLayout* grid = new QGridLayout();

    // Assign functions to each of the buttons
    connect(close_btn, &QPushButton::clicked, this, &MainWindow::OnClosePress);
    connect(add_unwatched, &QPushButton::clicked, this, &MainWindow::OnUnwatchedAddPress);
    connect(add_watched, &QPushButton::clicked, this, &MainWindow::OnWatchedAddPress);
    connect(remove_unwatched, &QPushButton::clicked, this, &MainWindow::OnUnwatchedRemovePress);
    connect(remove_watched, &QPushButton::clicked, this, &MainWindow::OnWatchedRemovePress);
    connect(move_unwatched, &QPushButton::clicked, this, &MainWindow::OnUnwatchedMovePress);
    connect(move_watched, &QPushButton::clicked, this, &MainWindow::OnWatchedMovePress);
    connect(edit_unwatched, &QPushButton::clicked, this, &MainWindow::OnUnwatchedEditPress);
    connect(edit_watched, &QPushButton::clicked, this, &MainWindow::OnWatchedEditPress);
    connect(sort_unwatched, &QPushButton::clicked, this, &MainWindow::OnUnwatchedSortPress);
    connect(sort_watched, &QPushButton::clicked, this, &MainWindow::OnWatchedSortPress);

    // Sort all of the GUI elements in the QGridLayout
    grid->addWidget(unwatched_lbl,0,0);
    grid->addWidget(watched_lbl,0,1);
    grid->addWidget(unwatched_edit,1,0);
    grid->addWidget(watched_edit,1,1);
    grid->addWidget(add_unwatched,2,0);
    grid->addWidget(add_watched,2,1);
    grid->addWidget(edit_unwatched,3,0);
    grid->addWidget(edit_watched,3,1);
    grid->addWidget(remove_unwatched,4,0);
    grid->addWidget(remove_watched,4,1);
    grid->addWidget(move_unwatched,5,0);
    grid->addWidget(move_watched,5,1);
    grid->addWidget(sort_unwatched,6,0);
    grid->addWidget(sort_watched,6,1);
    grid->addWidget(close_btn,7,0,7,2);

    // Set the grid layout
    setLayout(grid);
}

void MainWindow::OnClosePress()
/*********************************************************************************************
* Function: 
*   OnClosePress
*
* Params:
*   void
*
* returns:
*   void
*********************************************************************************************/
{
    // Close the application if the close button is pressed
    this->close();
}

void MainWindow::OnUnwatchedAddPress()
/*********************************************************************************************
* Function: 
*   OnUnwatchedAddPress
*
* Params:
*   void
*
* returns:
*   void
*********************************************************************************************/
{
    Anime_t anime;

    // Build an Add Window telling it to use the unwatched anime list
    AddWindow* window = new AddWindow(false, false, anime);
    window->setFixedSize(500,300);
    window->setWindowTitle("Add an Anime");
    window->setWindowIcon(QIcon(ICONPATH));
    window->show();
}

void MainWindow::OnWatchedAddPress()
/*********************************************************************************************
* Function: 
*   OnWatchedAddPress
*
* Params:
*   void
*
* returns:
*   void
*********************************************************************************************/
{
    Anime_t anime;

    // Build an Add Window telling it to use the watched anime list
    AddWindow* window = new AddWindow(true, false, anime);
    window->setFixedSize(500,300);
    window->setWindowTitle("Add an Anime");
    window->setWindowIcon(QIcon(ICONPATH));
    window->show();
}

void MainWindow::OnUnwatchedRemovePress()
/*********************************************************************************************
* Function: 
*   OnUnwatchedRemovePress
*
* Params:
*   void
*
* returns:
*   void
*********************************************************************************************/
{
    bool result;

    // Create a Select Window with action "Remove"
    SelectWindow* window = new SelectWindow(1,false, &result);
    window->setFixedSize(300,125);
    window->setWindowTitle("Select an Anime");
    window->setWindowIcon(QIcon(ICONPATH));

    // If lists are empty (There is no anime in the list) return
    if (!result)
    {
        window->close();
        return;
    }

    // Otherwise, show the Select Window
    window->show();
}

void MainWindow::OnWatchedRemovePress()
/*********************************************************************************************
* Function: 
*   OnWatchedRemovePress
*
* Params:
*   void
*
* returns:
*   void
*********************************************************************************************/
{
    bool result;

    // Create a Select Window with action "Remove"
    SelectWindow* window = new SelectWindow(1,true, &result);
    window->setFixedSize(300,125);
    window->setWindowTitle("Select an Anime");
    window->setWindowIcon(QIcon(ICONPATH));

    // If lists are empty (There is no anime in the list) return
    if (!result)
    {
        window->close();
        return;
    }

    // Otherwise, show the Select Window
    window->show();
}

void MainWindow::OnUnwatchedMovePress()
/*********************************************************************************************
* Function: 
*   OnUnwatchedMovePress
*
* Params:
*   void
*
* returns:
*   void
*********************************************************************************************/
{
    bool result;

    // Create a Select Window with action "Move"
    SelectWindow* window = new SelectWindow(2,false, &result);
    window->setFixedSize(300,150);
    window->setWindowTitle("Move an Anime");
    window->setWindowIcon(QIcon(ICONPATH));

    // If lists are empty (There is no anime in the list) return
    if (!result)
    {
        window->close();
        return;
    }

    // Otherwise, show the Select Window
    window->show();
}

void MainWindow::OnWatchedMovePress()
/*********************************************************************************************
* Function: 
*   OnWatchedMovePress
*
* Params:
*   void
*
* returns:
*   void
*********************************************************************************************/
{
    bool result;

    // Create a Select Window with action "Move"
    SelectWindow* window = new SelectWindow(2,true, &result);
    window->setFixedSize(300,150);
    window->setWindowTitle("Move an Anime");
    window->setWindowIcon(QIcon(ICONPATH));

    // If lists are empty (There is no anime in the list) return
    if (!result)
    {
        window->close();
        return;
    }

    // Otherwise, show the Select Window
    window->show();
}

void MainWindow::OnUnwatchedEditPress()
/*********************************************************************************************
* Function: 
*   OnUnwatchedEditPress
*
* Params:
*   void
*
* returns:
*   void
*********************************************************************************************/
{
    bool result;

    // Create a Select Window with action "Edit"
    SelectWindow* window = new SelectWindow(0,false, &result);
    window->setFixedSize(300,125);
    window->setWindowTitle("Select an Anime");
    window->setWindowIcon(QIcon(ICONPATH));

    // If lists are empty (There is no anime in the list) return
    if (!result)
    {
        window->close();
        return;
    }

    // Otherwise, show the Select Window
    window->show();
}

void MainWindow::OnWatchedEditPress()
/*********************************************************************************************
* Function: 
*   OnWatchedEditPress
*
* Params:
*   void
*
* returns:
*   void
*********************************************************************************************/
{
    bool result;

    // Create a Select Window with action "Edit"
    SelectWindow* window = new SelectWindow(0,true, &result);
    window->setFixedSize(300,125);
    window->setWindowTitle("Select an Anime");
    window->setWindowIcon(QIcon(ICONPATH));

    // If lists are empty (There is no anime in the list) return
    if (!result)
    {
        window->close();
        return;
    }

    // Otherwise, show the Select Window
    window->show();
}

void MainWindow::OnUnwatchedSortPress()
/*********************************************************************************************
* Function: 
*   OnUnwatchedSortPress
*
* Params:
*   void
*
* returns:
*   void
*********************************************************************************************/
{
    // Create a Sort Window and show it
    SortWindow* window = new SortWindow(false);
    window->setFixedSize(300,175);
    window->setWindowTitle("Sort List");
    window->setWindowIcon(QIcon(ICONPATH));

    window->show();
}

void MainWindow::OnWatchedSortPress()
/*********************************************************************************************
* Function: 
*   OnWatchedSortPress
*
* Params:
*   void
*
* returns:
*   void
*********************************************************************************************/
{
    // Create a Sort Window and show it
    SortWindow* window = new SortWindow(true);
    window->setFixedSize(300,175);
    window->setWindowTitle("Sort List");
    window->setWindowIcon(QIcon(ICONPATH));

    window->show();
}

void loadLists(std::vector<Anime_t> unwatched_vec, std::vector<Anime_t> watched_vec)
/*********************************************************************************************
* Function: 
*   loadLists
*
* Params:
*   std::vector<Anime_t> unwatched_vec: A vector of type Anime_t for the unwatched list
*   std::vector<Anime_t> watched_vec:   A vector of type Anime_t for the watched list
*
* returns:
*   void
*********************************************************************************************/
{
    std::string name, num_episodes, rating;

    // Start out the string with the Name, Episodes, and Rating title
    QString orig_text = "--------------------Name-------------------|Episodes|Rating\n\n";
    QString text = orig_text;

    // Load the info from each anime in the list and append it to the string
    for(int i=unwatched_vec.size()-1; i>=0; i--)
    {
        name = parseItem(unwatched_vec[i].name, 44, 21, '|');
        num_episodes = parseItem(std::to_string(unwatched_vec[i].num_episodes),9,3,'|');
        rating = parseItem(std::to_string(unwatched_vec[i].rating),6,1,' ');
        text.append(QString::fromUtf8(name.c_str()));
        text.append(QString::fromUtf8(num_episodes.c_str()));
        text.append(QString::fromUtf8(rating.c_str()));
    }

    // Put the text string into the unwatched text edit
    unwatched_edit->setText(text);

    // Set the title again to get ready for the second text edit
    text = orig_text;

    // Load the info from each anime in the list and append it to the string
    for (int i=watched_vec.size()-1; i>=0; i--)
    {
        name = parseItem(watched_vec[i].name, 44, 21, '|');
        num_episodes = parseItem(std::to_string(watched_vec[i].num_episodes),9,3,'|');
        rating = parseItem(std::to_string(watched_vec[i].rating),7,2,' ');
        text.append(QString::fromUtf8(name.c_str()));
        text.append(QString::fromUtf8(num_episodes.c_str()));
        text.append(QString::fromUtf8(rating.c_str()));
    }

    // Put the text string into the watched text edit
    watched_edit->setText(text);
}

std::string parseItem(std::string item, int size, int middle, char term)
/*********************************************************************************************
* Function: 
*   parseItem
*
* Params:
*   std::string item: A string that holds a name, number of episodes, or rating to be used to
*                     format the number of dashes needed on both sides
*   int size:         The size allocated for the name, number of episodes, or rating
*   int middle:       The number that represents the middle of the space allocated for name,
*                     number of episodes, or rating
*   char term:        The terminating character to put on the end. '|' for name and number of
*                     episodes and '\n' for rating
*
* returns:
*   A std::string that holds the entire line to be outputted
*********************************************************************************************/
{
    int length, dist, index = 0;
    std::string formatted_text = "";

    // Make sure that the return string has enough allocated space
    formatted_text.resize(size);

    // Calculate the length of the item and its distance from the middle to either side
    length = item.length();
    dist = length / 2;

    // If the item has an odd number of letters
    if (length%2)
    {
        // Add a dash for every character from the beginning to the beginning of the item
        for (int j=0; j<=middle-dist; j++)
            formatted_text[j] = '-';

        // Add each character of the item string
        for (int j=middle+1-dist; j<=middle+1+dist; j++)
        {
            formatted_text[j] = item[index];
            index++;
        }

        // Add dashes until the end of the allocated space for the item
        for (int j=middle+2+dist; j<=size-1; j++)
            formatted_text[j] = '-';
    }

    // If the item has an even number of letters
    else
    {
        // Add a dash for every character from the beginning to the beginning of the item  
        for (int j=0; j<=middle-dist; j++)
            formatted_text[j] = '-';

        // Add each character of the item string
        for (int j=middle+1-dist; j<=middle+dist; j++)
        {
            formatted_text[j] = item[index];
            index++;
        }

        // Add dashes until the end of the allocatted space for the item
        for (int j=middle+1+dist; j<=size-1; j++)
            formatted_text[j] = '-';
    }

    // Put the terminating character on the end
    formatted_text[size-1] = term;

    // Return the new formatted string
    return formatted_text;
}

MainWindow::~MainWindow() {}

