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
        bool class_watched;

};

#endif

