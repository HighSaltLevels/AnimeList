/*********************************************************************************************
* SelectWindow.h
*
* Description: This file contains the class definition for SelectWindow
*
* Functions:
*            void SelectWindow: Constructor that builds the GUI and all of its 
*
* Variables:
*            QComboBox* box:         Combo box for listing all the anime in a specified list
*            QLineEdit* rating_edit: Line edit for inputting a rating when moving an anime
*                                    from one list to another
*            int class_action:       Class variable for allowing all class functions to know
*                                    what action the user wants. 0=edit, 1=remove, 2=move
*            bool class_watched:     Class variable for allowing all class functions to know
*                                    if the user is editting the watched file or unwatched
*                                    file
*
*********************************************************************************************/

#ifndef SELECTWINDOW_H
#define SELECTWINDOW_H

#include "file_handler.h"
#include "MainWindow.h"
#include "AddWindow.h"

class SelectWindow : public QWidget
{
    public:
        SelectWindow(int action = 0, bool watched = false, bool* success = NULL);
        ~SelectWindow();

    signals:
    public slots:
        void OnOkPress();
        void OnCancelPress();

    private:
        QComboBox* box;
        QLineEdit* rating_edit;
        int class_action;
        bool class_watched;
};

#endif

