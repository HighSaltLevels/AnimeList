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

