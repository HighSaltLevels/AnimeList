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

