#ifndef ADDWINDOW_H
#define ADDWINDOW_H

#include "file_handler.h"
#include "MainWindow.h"

class AddWindow : public QWidget
{
    public:
        AddWindow(QWidget* parent = 0, bool watched = false, QTextEdit* = NULL, QTextEdit* = NULL);
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
};

#endif

