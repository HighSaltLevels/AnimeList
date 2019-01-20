/*********************************************************************************************
* AddWindow.cpp
*
* Description: This is the add window GUI. It will show up whenever the user decides to add an
*              anime to either list by clicking either add button or edit button.
*
* Functions:
*            AddWindow:    Constructor that builds the GUI and all of the GUI elements.
*            OnAddPress:   Function that is triggered whenever the add button from the add
*                          window is pressed. It writes the new anime to the corresponding 
*                          text file.
*            OnClosePress: Function that is triggered whenever the close button from the add
*                          window is pressed. It closes the add window.
*
*********************************************************************************************/
#include "AddWindow.h"

AddWindow::AddWindow(bool watched, bool edit, Anime_t anime) : QWidget()
/*********************************************************************************************
* Function: 
*   AddWindow
*
* Params:
*   bool watched:  A boolean value that indicates if this is using the unatched or the watched
*                  anime list
*   bool edit:     A boolean value that indicates if the user chose to edit or add an anime
*   Anime_t anime: An anime that is used to populate the add window if the user chose to edit
*                  instead of add
*
* returns:
*   void
*********************************************************************************************/
{
    // Create the line edits for entering the name, episode num, and rating
    name_edit = new QLineEdit(this);
    episode_edit = new QLineEdit(this);
    rating_edit = new QLineEdit(this);
    has_been_watched = watched;
    // Use class variables to share data to the button press functions
    class_edit = edit;
    class_anime.name = anime.name;
    class_anime.num_episodes = anime.num_episodes;
    class_anime.rating = anime.rating;

    // Make a label to indicate which line edit is for the name
    QString name_str = "Name:";
    QLabel* name_lbl = new QLabel(name_str, this);
    name_lbl->setFont(QFont("Times",12));

    // Make a label to indicate which line edit is for the number of episodes
    QString episode_str = "Number of Episodes:";
    QLabel* episode_lbl = new QLabel(episode_str, this);
    episode_lbl->setFont(QFont("Times",12));

    // Make a label to indicate which line edit is for the rating
    QString rating_str = "Personal Rating (Out of 10):";
    QLabel* rating_lbl = new QLabel(rating_str, this);
    rating_lbl->setFont(QFont("Times",12));

    // Create the add button and the cancel button
    QPushButton* cancel_btn = new QPushButton("Cancel", this);
    QPushButton* add_btn;

    // If the user clicked edit, make the add button say "Update" and the line
    // edits should be populated with the original fields., otherwise the user
    // has clicked the add button and the button should say add.
    if (edit)
    {
        add_btn = new QPushButton("Update", this);
        name_edit->setText(QString::fromUtf8(anime.name.c_str()));
        episode_edit->setText(QString::fromUtf8(std::to_string(anime.num_episodes).c_str()));
        rating_edit->setText(QString::fromUtf8(std::to_string(anime.rating).c_str()));
    }
    else
    {
        add_btn = new QPushButton("Add", this);
    }

    // Set the buttons to call their respected functions when clicked
    connect(cancel_btn, &QPushButton::clicked, this, &AddWindow::OnCancelPress);
    connect(add_btn, &QPushButton::clicked, this, &AddWindow::OnAddPress);

    // Create a grid layout and organize the gui elements
    QGridLayout* grid = new QGridLayout();

    grid->addWidget(name_lbl,0,0);
    grid->addWidget(name_edit,0,1);
    grid->addWidget(episode_lbl,1,0);
    grid->addWidget(episode_edit,1,1);
    grid->addWidget(rating_lbl,2,0);
    grid->addWidget(rating_edit,2,1);
    grid->addWidget(cancel_btn,3,0);
    grid->addWidget(add_btn,3,1);

    // Set the grid layout
    setLayout(grid);
}

void AddWindow::OnAddPress()
/*********************************************************************************************
* Function: 
*   OnAddPress
*
* Params:
*   void
*
* returns:
*   void 
*********************************************************************************************/
{
    std::vector<Anime_t> watched_vec, unwatched_vec;
    std::string episode_str, rating_str, file_to_use;
    Anime_t anime;
    char* p;

    // Get the name from the name line edit
    anime.name = name_edit->text().toUtf8().constData();

    // Get the number of episodes from the num_episodes line edit
    episode_str = episode_edit->text().toUtf8().constData();

    // Ensure that the episode number is an integer. If not, display an error message.
    strtol(episode_str.c_str(), &p, 10);
    if (*p)
    {
        QMessageBox::information(this, "Invalid Input", "The episode number must be a number!", QMessageBox::Ok);
        return;
    }

    // Save the number of episodes and validate that it is a valid unsigned integer.
    // If not, then display an error message
    anime.num_episodes = std::stoi(episode_str);
    if (anime.num_episodes < 1 || anime.num_episodes > 99999999)
    {
        QMessageBox::information(this, "Invalid Input", "The episode number must be greater than 1!", QMessageBox::Ok);
        return;
    }

    // Get the rating from the rating line edit
    rating_str = rating_edit->text().toUtf8().constData();

    // Ensure that the rating is an integer. If not, display an error message
    strtol(rating_str.c_str(), &p, 10);
    if (*p)
    {
        QMessageBox::information(this, "Invalid Input", "The rating number must be a number!", QMessageBox::Ok);
        return;
    }

    // Save the rating and validate that it is an interger between 0 and 10. If
    // not, then display an error message
    anime.rating = std::stoi(rating_str);
    if (anime.rating < 0 || anime.rating > 10)
    {
        QMessageBox::information(this, "Invalid Input", "The rating number must be a number between 0 and 10!", QMessageBox::Ok);
        return;
    }

    // Set the file path accordingly
    if (has_been_watched)
        file_to_use = WATCHEDPATH;
    else
        file_to_use = UNWATCHEDPATH;

    // If editing, remove the old entry
    if (class_edit)
        removeEntry(file_to_use, class_anime.name);

    // Add the new entry
    addEntry(file_to_use, anime);

    // Reload both lists
    watched_vec = getWatchedList();
    unwatched_vec = getUnwatchedList();
    loadLists(unwatched_vec, watched_vec);

    // Close the window
    this->close();
}

void AddWindow::OnCancelPress()
/*********************************************************************************************
* Function: 
*   OnCancelPress
*
* Params:
*   void
*
* returns:
*   void 
*********************************************************************************************/
{
    // Close the window
    this->close();
}

AddWindow::~AddWindow() {}

