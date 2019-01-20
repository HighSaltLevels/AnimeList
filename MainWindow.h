/*********************************************************************************************
* MainWindow.h
*
* Description: This file contains the class definition for MainWindow
*
* Functions:
*            void MainWindow:             Constructor that builds the GUI and all of its 
*                                         elements
*            void OnClosePress:           Button handler for the close button
*            void OnWatchedAddPress:      Button handler for the watched add button
*            void OnUnwatchedAddPress:    Button handler for the unwatched add button
*            void OnWatchedRemovePress:   Button handler for the watched remove button
*            void OnUnwatchedRemovePress: Button handler for the unwatched remove button
*            void OnWatchedMovePress:     Button handler for the watched move button
*            void OnUnwatchedMovePress:   Button handler for the unwatched move button
*            void OnWatchedEditPress:     Button handler for the watched edit button
*            void OnUnwatchedEditPress:   Button handler for the unwatched edit button
*            void OnWatchedSortPress:     Button handler for the watched sort button
*            void OnUnwatchedSortPress:   Button handler fot the unwatched sort button
*            void loadLists:              Function that loads both anime vectors into their
*                                         respective text edits
*            std::string parseItem:       Function that formats each item in the anime for
*                                         displaying it in the text edit
*
* Variables:
*            N/A
*
*********************************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "file_handler.h"
#include "AddWindow.h"
#include "SelectWindow.h"
#include "SortWindow.h"

class MainWindow : public QWidget
{
    //Q_OBJECT

    public:
        MainWindow();
        ~MainWindow();

    signals:
    public slots:
        void OnClosePress();
        void OnWatchedAddPress();
        void OnUnwatchedAddPress();
        void OnWatchedRemovePress();
        void OnUnwatchedRemovePress();
        void OnWatchedMovePress();
        void OnUnwatchedMovePress();
        void OnWatchedEditPress();
        void OnUnwatchedEditPress();
        void OnWatchedSortPress();
        void OnUnwatchedSortPress();
};

void loadLists(std::vector<Anime_t>,std::vector<Anime_t>);
std::string parseItem(std::string,int,int,char);

#endif

