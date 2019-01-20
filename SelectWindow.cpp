/*********************************************************************************************
* SelectWindow.cpp
*
* Description: This file builds the Select Window GUI
*
* Functions:
*            SelectWindow:  Constructor that builds the GUI and all of its elements. If the
*                           user pressed the edit button (action = 2) it adds the extra rating
*                           GUI elements
*            OnOkPress:     Function that handles what to do when Ok is pushed based on the
*                           action given by MainWindow when it generates this GUI
*            OnCancelPress: Function that closes the Select Window when Cancel is pushed
*
*********************************************************************************************/

#include "SelectWindow.h"

SelectWindow::SelectWindow(int action, bool watched, bool* success) : QWidget()
/*********************************************************************************************
* Function: 
*   SelectWindow
*
* Params:
*   int action:    Integer that represents the action to do. 0 = Edit an entry, 1 = Remove an
*                  entry, 2 = Move an entry from one list to another
*   bool watched:  Boolean value that indicates if this is for the unwatched anime list or the
*                  watched anime list
*   bool* success: Pointer to a value that indicates that loading the list was successful or
*                  not
*
* returns:
*   void
*********************************************************************************************/
{
    std::vector<std::string> anime;
    bool result;

    // Set the class variables so that they can be accessed by all of the class functions
    class_action = action;
    class_watched = watched;
    box = new QComboBox(this);

    // Create the Label that describes what to do on the Select Window GUI
    QString msg = "Please select an anime from the drop-down box";
    QLabel* msg_lbl = new QLabel(msg, this);

    // Set the filepath based on if it is a watched list or unwatched list
    if (watched)
        result = getAnimeVec(&anime, WATCHEDPATH);
    else
        result = getAnimeVec(&anime, UNWATCHEDPATH);

    // If unable to load any anime, Alert the user with a message box and set the success
    // pointer to false
    if (!result)
    {
        QMessageBox::information(this, "No Anime", "There are no anime in this list!", QMessageBox::Ok);
        *success = false;
        return;
    }

    // Add each anime name as an entry to the drop down box
    for (int i=anime.size()-1; i>=0; i--)
    {
        box->addItem(QString::fromUtf8(anime[i].c_str()));
    }

    // Create the push buttons and link them to their respective functions
    QPushButton* cancel_btn = new QPushButton("Cancel", this);
    QPushButton* ok_btn = new QPushButton("Ok", this);
    connect(cancel_btn, &QPushButton::clicked, this, &SelectWindow::OnCancelPress);
    connect(ok_btn, &QPushButton::clicked, this, &SelectWindow::OnOkPress);

    // Create a grid layout to format the GUI elements
    QGridLayout* grid = new QGridLayout();

    // If we are moving from one list to another
    if (action == 2)
    {
        // Create the extra label and line edit and format them in the grid layout
        QString str = "Give a rating (1-10)";
        QLabel* rating_lbl = new QLabel(str, this);
        rating_edit = new QLineEdit(this);
        grid->addWidget(msg_lbl,0,0,1,5);
        grid->addWidget(box,1,0,1,5);
        grid->addWidget(rating_lbl,2,0,2,3);
        grid->addWidget(rating_edit,2,2,2,4);
        grid->addWidget(cancel_btn,4,0);
        grid->addWidget(ok_btn,4,4);
    }

    // Otherwise...
    else
    {
        // Just format the already existing GUI elements
        grid->addWidget(msg_lbl,0,0,1,5);
        grid->addWidget(box,1,0,1,5);
        grid->addWidget(cancel_btn,2,0);
        grid->addWidget(ok_btn,2,4);
    }

    // Set the grid layout and indicate that loading the anime was successful
    setLayout(grid);
    *success = true;
}

void SelectWindow::OnOkPress()
/*********************************************************************************************
* Function: 
*   OnOkPress
*
* Params:
*   void
*
* returns:
*   void
*********************************************************************************************/
{
    std::vector<Anime_t> unwatched_vec, watched_vec;
    std::string current_text = box->currentText().toUtf8().constData();
    std::string file_str = "";
    std::string add_to_file_str = "";
    std::string rating_input = "";
    char* p;
    int rating = 0;
    AddWindow* edit_window = NULL;

    // Set the filepaths according to the watched anime or unwatched anime being selected
    if (class_watched)
    {
        file_str = WATCHEDPATH;
        add_to_file_str = UNWATCHEDPATH;
    }
    else
    {
        file_str = UNWATCHEDPATH;
        add_to_file_str = WATCHEDPATH;
    }

    // Get all anime in the list based on its name
    Anime_t anime = getAnimeByName(current_text, file_str);

    // Handle the action based on what function in Main Window created the Select Window GUI
    switch (class_action)
    {
        case 0: // Edit
            // Create a special add window to indicate that it was editted and show it
            edit_window = new AddWindow(class_watched, true, anime);
            edit_window->setFixedSize(500,300);
            edit_window->setWindowTitle("Edit an Anime");
            edit_window->setWindowIcon(QIcon(ICONPATH));
            edit_window->show();
            break;

        case 1: // Remove
            // Remove the specified entry
            removeEntry(file_str, anime.name);
            break;

        case 2: // Move
            // Get the rating from the line edit
            rating_input = rating_edit->text().toUtf8().constData();

            // Verify that the rating exists. If not, display an error message
            if (rating_input == "")
            {
                QMessageBox::information(this, "Invalid Input", "Please provide a rating.", QMessageBox::Ok);
                return;
            }

            // Ensure that the rating is an integer. If not, display an error message
            strtol(rating_input.c_str(), &p, 10);
            if (*p)
            {
                QMessageBox::information(this, "Invalid Input", "The rating number must be a number!", QMessageBox::Ok);
                return;
            }

            // Convert the rating to integer and verify that it is between 0 and 10. If not, display an error message
            rating = std::stoi(rating_edit->text().toUtf8().constData());
            if (rating < 0 || rating > 10)
            {
                QMessageBox::information(this, "Invalid Input", "The rating number must be a number between 1 and 10!", QMessageBox::Ok);
                return;
            }

            // Set the rating and move it over to the other list
            anime.rating = rating;
            switchEntry(file_str, add_to_file_str, anime);
            break;

        default: break;
    }

    // Get both lists and load them into the text edits
    watched_vec = getWatchedList();
    unwatched_vec = getUnwatchedList();
    loadLists(unwatched_vec, watched_vec);

    // Close the window
    this->close();
}

void SelectWindow::OnCancelPress()
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

SelectWindow::~SelectWindow() {}

