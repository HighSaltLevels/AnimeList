#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "file_handler.h"
#include "AddWindow.h"
#include "SelectWindow.h"

class MainWindow : public QWidget
{
    //Q_OBJECT

    public:
        MainWindow(QWidget* parent = 0);
        ~MainWindow();

    signals:
    public slots:
        void OnWatchedAddPress();
        void OnUnwatchedAddPress();
        void OnWatchedRemovePress();
        void OnUnwatchedRemovePress();
        void OnWatchedMovePress();
        void OnUnwatchedMovePress();
        void OnWatchedEditPress();
        void OnUnwatchedEditPress();
};

void loadLists(std::vector<Anime_t>,std::vector<Anime_t>);
std::string parseItem(std::string,int,int,char);

#endif

