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
        result = getAnimeVec(&animes, WATCHEDPATH);
    else
        result = getAnimeVec(&animes, UNWATCHEDPATH);

    if (!result)
    {
        QMessageBox::information(this, "No Anime", "There are no anime in this list!", QMessageBox::Ok);
        *success = false;
        return;
    }
    for (int i=animes.size()-1; i>=0; i--)
    {
        box->addItem(QString::fromUtf8(animes[i].c_str()));
    }

    QPushButton* cancel_btn = new QPushButton("Cancel", this);
    QPushButton* ok_btn = new QPushButton("Ok", this);
    connect(cancel_btn, &QPushButton::clicked, this, &SelectWindow::OnCancelPress);
    connect(ok_btn, &QPushButton::clicked, this, &SelectWindow::OnOkPress);

    QGridLayout* grid = new QGridLayout();

    if (action == 2)
    {
        QString str = "Give a rating (1-10)";
        QLabel* rating_lbl = new QLabel(str, this);
        rating_edit = new QLineEdit(this);
        grid->addWidget(msg_lbl,0,0,1,5);
        grid->addWidget(box,1,0,1,5);
        grid->addWidget(rating_lbl,2,0,2,3);
        grid->addWidget(rating_edit,2,2,2,4);
        grid->addWidget(cancel_btn,4,0);
        grid->addWidget(ok_btn,4,4);
    }
    else
    {
        grid->addWidget(msg_lbl,0,0,1,5);
        grid->addWidget(box,1,0,1,5);
        grid->addWidget(cancel_btn,2,0);
        grid->addWidget(ok_btn,2,4);
    }

    setLayout(grid);
    *success = true;
}

void SelectWindow::OnOkPress()
{
    std::vector<Anime_t> unwatched_vec, watched_vec;
    std::string current_text = box->currentText().toUtf8().constData();
    std::string file_str = "";
    std::string add_to_file_str = "";
    std::string rating_input = "";
    int rating = 0;
    AddWindow* edit_window = NULL;

    if (class_watched)
    {
        file_str = WATCHEDPATH;
        add_to_file_str = UNWATCHEDPATH;
    }
    else
    {
        file_str = UNWATCHEDPATH;
        add_to_file_str = WATCHEDPATH;
    }

    Anime_t anime = getAnimeByName(current_text, file_str);

    switch (class_action)
    {
        case 0: // edit
            edit_window = new AddWindow(class_watched, true, anime);
            edit_window->setFixedSize(500,300);
            edit_window->setWindowTitle("Edit an Anime");
            edit_window->setWindowIcon(QIcon(ICONPATH));
            edit_window->show();
            break;

        case 1: // remove
            removeEntry(file_str, anime.name);
            break;

        case 2: // move
            rating_input = rating_edit->text().toUtf8().constData();
            if (rating_input == "")
            {
                QMessageBox::information(this, "Invalid Input", "Please provide a rating.", QMessageBox::Ok);
                return;
            }
            rating = std::stoi(rating_edit->text().toUtf8().constData());
            if (rating < 0 || rating > 10)
            {
                QMessageBox::information(this, "Invalid Input", "The rating number must be a number between 1 and 10!", QMessageBox::Ok);
                return;
            }
            anime.rating = rating;
            switchEntry(file_str, add_to_file_str, anime);
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

