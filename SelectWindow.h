#ifndef SELECTWINDOW_H
#define SELECTWINDOW_H

#include "file_handler.h"
#include "MainWindow.h"

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
        int class_action;
        bool class_watched;
};

#endif

