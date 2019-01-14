#include "SelectWindow.h"

SelectWindow::SelectWindow(int action, bool watched, bool* success) : QWidget()
{
    std::vector<std::string> animes;
    bool result;

    class_action = action;
    class_watched = watched;
    box = new QComboBox(this);

    QString msg = "Please select an anime from the drop-down box";
    QLabel* msg_lbl = new QLabel(msg, this);

    if (watched)
        result = getAnimeVec(&animes, "watched.txt");
    else
        result = getAnimeVec(&animes, "unwatched.txt");

    if (!result)
    {
        QMessageBox::information(this, "No Anime", "There are no anime in this list!", QMessageBox::Ok);
        *success = false;
        return;
    }
    for (unsigned int i=0; i < animes.size(); i++)
    {
        box->addItem(QString::fromUtf8(animes[i].c_str()));
    }

    QPushButton* cancel_btn = new QPushButton("Cancel", this);
    QPushButton* ok_btn = new QPushButton("Ok", this);
    connect(cancel_btn, &QPushButton::clicked, this, &SelectWindow::OnCancelPress);
    connect(ok_btn, &QPushButton::clicked, this, &SelectWindow::OnOkPress);

    QGridLayout* grid = new QGridLayout();

    grid->addWidget(msg_lbl,0,0,1,5);
    grid->addWidget(box,1,0,1,5);
    grid->addWidget(cancel_btn,2,0);
    grid->addWidget(ok_btn,2,4);

    setLayout(grid);
    *success = true;
}

void SelectWindow::OnOkPress()
{
    std::vector<Anime_t> unwatched_vec, watched_vec;
    std::string current_text = box->currentText().toUtf8().constData();
    std::string file_str = "";

    if (class_watched)
        file_str = "watched.txt";
    else
        file_str = "unwatched.txt";

    Anime_t anime = getAnimeByName(current_text, file_str);

    switch (class_action)
    {
        case 0: // edit
            break;

        case 1: // remove
            removeEntry(file_str, anime.name);

        case 2: // move
            break;

        default: break;
    }

    watched_vec = getWatchedList();
    unwatched_vec = getUnwatchedList();
    loadLists(unwatched_vec, watched_vec);
    this->close();
    return;
}

void SelectWindow::OnCancelPress()
{
    this->close();
}

SelectWindow::~SelectWindow() {}

