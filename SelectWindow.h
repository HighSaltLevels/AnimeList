#ifndef SELECTWINDOW_H
#define SELECTWINDOW_H

#include "file_handler.h"

class SelectWindow : public QWidget
{
    public:
        SelectWindow(QWidget* parent = 0, int action = 0, bool watched = false, bool* success = NULL);
        ~SelectWindow();

    signals:
    public slots:
        void OnOkPress();
        void OnCancelPress();

    private:
        QComboBox* selectbox;
};

#endif

