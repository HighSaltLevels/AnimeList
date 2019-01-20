/*********************************************************************************************
* SortWindow.cpp
*
* Description: This file builds the Sort Window GUI
*
* Functions:
*            SortWindow:    Constructor that builds the GUI and all of its elements
*            OnCancelPress: Function that closes the Sort Window when Cancel is pushed
*            OnSortPress:   Function that sorts the specified list based on user indicate
*                           radio buttons and check box
*
*********************************************************************************************/

#include "SortWindow.h"

SortWindow::SortWindow(bool watched)
/*********************************************************************************************
* Function: 
*   SortWindow
*
* Params:
*   bool watched: Boolean value that indicates whether the watched list or unwatched list
*                 should be sorted
*
* returns:
*   void
*********************************************************************************************/
{
    // Set a class value to be able to share the watched boolean to the other class functions
    class_watched = watched;

    // Create a group box to hold the 3 radio buttons
    QGroupBox* radio_group = new QGroupBox("Sort by...", this);

    // Declare the 3 readio buttons for name, number of episodes, and rating
    name_radio = new QRadioButton("Name", this);
    episodes_radio = new QRadioButton("Number of Episodes", this);
    rating_radio = new QRadioButton("Personal Rating", this);

    // Automatically assume sort by name
    name_radio->setChecked(true);

    // Create a QVBox layout for the radio buttons and set the group box as the layout
    QVBoxLayout* vbox = new QVBoxLayout(this);
    vbox->addWidget(name_radio);
    vbox->addWidget(episodes_radio);
    vbox->addWidget(rating_radio);
    vbox->addStretch(1);
    radio_group->setLayout(vbox);

    // Create a checkbox to indicate sort by low to high or high to low and assume low to high
    sort_box = new QCheckBox("Sort Lowest\nto Highest");
    sort_box->setChecked(true);

    // Create the sort button and the cancel button
    QPushButton* cancel_btn = new QPushButton("Cancel", this);
    QPushButton* sort_btn = new QPushButton("Sort", this);

    // Link the buttons to their respective functions
    connect(cancel_btn, &QPushButton::clicked, this, &SortWindow::OnCancelPress);
    connect(sort_btn, &QPushButton::clicked, this, &SortWindow::OnSortPress);

    // Create a grid layout and add the GUI elements to it
    QGridLayout* grid = new QGridLayout(this);
    grid->addWidget(radio_group,0,0);
    grid->addWidget(sort_box,0,1);
    grid->addWidget(cancel_btn,1,0);
    grid->addWidget(sort_btn,1,1);

    // Set the grid layout
    setLayout(grid);
}

void SortWindow::OnCancelPress()
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

void SortWindow::OnSortPress()
/*********************************************************************************************
* Function: 
*   OnSortPress
*
* Params:
*   void
*
* returns:
*   void
*********************************************************************************************/
{
    int sort_type;

    // Assign the sort type based on which radio button is selected
    if (name_radio->isChecked())
        sort_type = 0;
    else if (episodes_radio->isChecked())
        sort_type = 1;
    else
        sort_type = 2;

    // Sort based on the sort type and the state of the low to high check box
    sortList(class_watched, sort_type, sort_box->isChecked());

    // Close the window
    this->close();
}

SortWindow::~SortWindow() {}

