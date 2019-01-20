/*********************************************************************************************
* SortWindow.h
*
* Description: This file contains the class definition for SortWindow
*
* Functions:
*            void SortWindow:    Constructor that builds the GUI and all of its elements
*            void OnSortPress:   Button handler for the sort button
*            void OnCancelPress: Button handler for the cancel button
*
* Variables:
*            QRadioButton* name_radio:     Radio button for name
*            QRadioButton* episodes_radio: Radio button for number of epsidoes
*            QRadioButton* rating_radio:   Radio button for rating
*            QCheckBox* sort_box:          Check box for sorting low to high or high to low
*            bool class_watched:           Class variable that indicates which file to use
*
*********************************************************************************************/

#ifndef SORTWINDOW_H
#define SORTWINDOW_H

#include "file_handler.h"

class SortWindow : public QWidget
{

    public:
        SortWindow(bool watched = false);
        ~SortWindow();

    signals:
    public slots:
        void OnSortPress();
        void OnCancelPress();

    private:
        QRadioButton* name_radio;
        QRadioButton* episodes_radio;
        QRadioButton* rating_radio;
        QCheckBox* sort_box;
        bool class_watched;

};

#endif

