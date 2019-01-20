/*********************************************************************************************
* AddWindow.h
*
* Description: This file contains the class definition for AddWindow
*
* Functions:
*            void AddWindow:     Constructor that builds the GUI and all of its elements
*            void OnAddPress:    Button handler for the add button
*            void OnCancelPress: Button handler for the cancel button
*
* Variables:
*            QLineEdit* name_edit:    Line edit for inputting the name
*            QLineEdit* episode_edit: Line edit for inputting the number of episodes
*            QLineEdit* rating_edit:  Line edit for inputting the rating
*            bool has_been_watched:   Boolean value to indicate if it is using the watched or
*                                     unwatched list
*            bool class_edit:         Boolean value to indicate if user is editting an entry
*            Anime_t class_anime:     Anime that is loaded into the GUI if the user is
*                                     editting an entry
*
*********************************************************************************************/

#ifndef ADDWINDOW_H
#define ADDWINDOW_H

#include "file_handler.h"
#include "MainWindow.h"

class AddWindow : public QWidget
{
    public:
        AddWindow(bool watched, bool edit, Anime_t anime);
        ~AddWindow();

    signals:
    public slots:
        void OnAddPress();
        void OnCancelPress();

    private:
        QLineEdit* name_edit;
        QLineEdit* episode_edit;
        QLineEdit* rating_edit;
        bool has_been_watched;
        bool class_edit;
        Anime_t class_anime;
};

#endif

