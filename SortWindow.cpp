#include "SortWindow.h"

SortWindow::SortWindow(bool watched)
{
    class_watched = watched;
    QGroupBox* radio_group = new QGroupBox("Sort by...", this);

    name_radio = new QRadioButton("Name", this);
    episodes_radio = new QRadioButton("Number of Episodes", this);
    rating_radio = new QRadioButton("Personal Rating", this);

    name_radio->setChecked(true);

    QVBoxLayout* vbox = new QVBoxLayout(this);
    vbox->addWidget(name_radio);
    vbox->addWidget(episodes_radio);
    vbox->addWidget(rating_radio);
    vbox->addStretch(1);
    radio_group->setLayout(vbox);

    QPushButton* cancel_btn = new QPushButton("Cancel", this);
    QPushButton* sort_btn = new QPushButton("Sort", this);

    connect(cancel_btn, &QPushButton::clicked, this, &SortWindow::OnCancelPress);
    connect(sort_btn, &QPushButton::clicked, this, &SortWindow::OnSortPress);

    QGridLayout* grid = new QGridLayout(this);
    grid->addWidget(radio_group,0,0,0,1);
    grid->addWidget(cancel_btn,1,0);
    grid->addWidget(sort_btn,1,1);

    setLayout(grid);
}

void SortWindow::OnCancelPress()
{
    this->close();
}

void SortWindow::OnSortPress()
{
    int sort_type;

    if (name_radio->isChecked())
        sort_type = 0;
    else if (episodes_radio->isChecked())
        sort_type = 1;
    else
        sort_type = 2;

    sortList(class_watched, sort_type);
    this->close();
}

SortWindow::~SortWindow() {}

