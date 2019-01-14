#include "AddWindow.h"

AddWindow::AddWindow(bool watched, bool edit, Anime_t anime) : QWidget()
{
    name_edit = new QLineEdit(this);
    episode_edit = new QLineEdit(this);
    rating_edit = new QLineEdit(this);
    has_been_watched = watched;
    class_edit = edit;
    class_anime.name = anime.name;
    class_anime.num_episodes = anime.num_episodes;
    class_anime.rating = anime.rating;

    QString name_str = "Name:";
    QLabel* name_lbl = new QLabel(name_str, this);
    name_lbl->setFont(QFont("Times",12));

    QString episode_str = "Number of Episodes:";
    QLabel* episode_lbl = new QLabel(episode_str, this);
    episode_lbl->setFont(QFont("Times",12));

    QString rating_str = "Personal Rating (Out of 10):";
    QLabel* rating_lbl = new QLabel(rating_str, this);
    rating_lbl->setFont(QFont("Times",12));

    QPushButton* cancel_btn = new QPushButton("Cancel", this);
    QPushButton* add_btn;
    if (edit)
        add_btn = new QPushButton("Update", this);
    else
        add_btn = new QPushButton("Add", this);
    connect(cancel_btn, &QPushButton::clicked, this, &AddWindow::OnCancelPress);
    connect(add_btn, &QPushButton::clicked, this, &AddWindow::OnAddPress);

    if (edit)
    {
        name_edit->setText(QString::fromUtf8(anime.name.c_str()));
        episode_edit->setText(QString::fromUtf8(std::to_string(anime.num_episodes).c_str()));
        rating_edit->setText(QString::fromUtf8(std::to_string(anime.rating).c_str()));
    }

    QGridLayout* grid = new QGridLayout();

    grid->addWidget(name_lbl,0,0);
    grid->addWidget(name_edit,0,1);
    grid->addWidget(episode_lbl,1,0);
    grid->addWidget(episode_edit,1,1);
    grid->addWidget(rating_lbl,2,0);
    grid->addWidget(rating_edit,2,1);
    grid->addWidget(cancel_btn,3,0);
    grid->addWidget(add_btn,3,1);

    setLayout(grid);
}

void AddWindow::OnAddPress()
{
    std::vector<Anime_t> watched_vec, unwatched_vec;
    std::string episode_str, rating_str, file_to_use;
    Anime_t anime;
    char* p;

    anime.name = name_edit->text().toUtf8().constData();

    episode_str = episode_edit->text().toUtf8().constData();
    strtol(episode_str.c_str(), &p, 10);
    if (*p)
    {
        QMessageBox::information(this, "Invalid Input", "The episode number must be a number!", QMessageBox::Ok);
        return;
    }
    anime.num_episodes = std::stoi(episode_str);
    if (anime.num_episodes < 1 || anime.num_episodes > 99999999)
    {
        QMessageBox::information(this, "Invalid Input", "The episode number must be greater than 1!", QMessageBox::Ok);
        return;
    }

    rating_str = rating_edit->text().toUtf8().constData();
    strtol(rating_str.c_str(), &p, 10);
    if (*p)
    {
        QMessageBox::information(this, "Invalid Input", "The rating number must be a number!", QMessageBox::Ok);
        return;
    }
    anime.rating = std::stoi(rating_str);
    if (anime.rating < 0 || anime.rating > 10)
    {
        QMessageBox::information(this, "Invalid Input", "The rating number must be a number between 0 and 10!", QMessageBox::Ok);
        return;
    }

    if (has_been_watched)
        file_to_use = "watched.txt";
    else
        file_to_use = "unwatched.txt";

    if (class_edit)
        removeEntry(file_to_use, class_anime.name);
        
    addEntry(file_to_use, anime);

    watched_vec = getWatchedList();
    unwatched_vec = getUnwatchedList();
    loadLists(unwatched_vec, watched_vec);

    this->close();
}

void AddWindow::OnCancelPress()
{
    this->close();
}

AddWindow::~AddWindow() {}

