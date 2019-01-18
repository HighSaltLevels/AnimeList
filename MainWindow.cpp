#include "MainWindow.h"

// TODO Find a way to keep these from being global variables
QTextEdit* unwatched_edit;
QTextEdit* watched_edit;

MainWindow::MainWindow() : QWidget()
{
    std::vector<Anime_t> watched_vec, unwatched_vec;
    QString watched_str = "Watched";
    QString unwatched_str = "Unwatched";
    
    QLabel* watched_lbl = new QLabel(watched_str,this);
    watched_lbl->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    watched_lbl->setFont(QFont("Times",20));
    QLabel* unwatched_lbl = new QLabel(unwatched_str,this);
    unwatched_lbl->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    unwatched_lbl->setFont(QFont("Times",20));

    unwatched_edit = new QTextEdit(this);
    watched_edit = new QTextEdit(this);
    unwatched_edit->setReadOnly(true);
    watched_edit->setReadOnly(true);
    unwatched_edit->setFont(QFont("Monospace",10));
    watched_edit->setFont(QFont("Monospace",10));

    watched_vec = getWatchedList();
    unwatched_vec = getUnwatchedList();

    loadLists(unwatched_vec, watched_vec);

    QPushButton* sort_unwatched = new QPushButton("Sort List", this);
    QPushButton* add_unwatched = new QPushButton("Add", this);
    QPushButton* remove_unwatched = new QPushButton("Remove", this);
    QPushButton* move_unwatched = new QPushButton("Move to Watched >>", this);
    QPushButton* edit_unwatched = new QPushButton("Edit", this);
    QPushButton* edit_watched = new QPushButton("Edit", this);
    QPushButton* move_watched = new QPushButton("<< Move to Unwatched", this);
    QPushButton* remove_watched = new QPushButton("Remove", this);
    QPushButton* add_watched = new QPushButton("Add", this);
    QPushButton* sort_watched = new QPushButton("Sort List", this);

    QGridLayout* grid = new QGridLayout();

    connect(add_unwatched, &QPushButton::clicked, this, &MainWindow::OnUnwatchedAddPress);
    connect(add_watched, &QPushButton::clicked, this, &MainWindow::OnWatchedAddPress);
    connect(remove_unwatched, &QPushButton::clicked, this, &MainWindow::OnUnwatchedRemovePress);
    connect(remove_watched, &QPushButton::clicked, this, &MainWindow::OnWatchedRemovePress);
    connect(move_unwatched, &QPushButton::clicked, this, &MainWindow::OnUnwatchedMovePress);
    connect(move_watched, &QPushButton::clicked, this, &MainWindow::OnWatchedMovePress);
    connect(edit_unwatched, &QPushButton::clicked, this, &MainWindow::OnUnwatchedEditPress);
    connect(edit_watched, &QPushButton::clicked, this, &MainWindow::OnWatchedEditPress);
    connect(sort_unwatched, &QPushButton::clicked, this, &MainWindow::OnUnwatchedSortPress);
    connect(sort_watched, &QPushButton::clicked, this, &MainWindow::OnWatchedSortPress);

    grid->addWidget(unwatched_lbl,0,0);
    grid->addWidget(watched_lbl,0,1);
    grid->addWidget(unwatched_edit,1,0);
    grid->addWidget(watched_edit,1,1);
    grid->addWidget(add_unwatched,2,0);
    grid->addWidget(add_watched,2,1);
    grid->addWidget(edit_unwatched,3,0);
    grid->addWidget(edit_watched,3,1);
    grid->addWidget(remove_unwatched,4,0);
    grid->addWidget(remove_watched,4,1);
    grid->addWidget(move_unwatched,5,0);
    grid->addWidget(move_watched,5,1);
    grid->addWidget(sort_unwatched,6,0);
    grid->addWidget(sort_watched,6,1);

    setLayout(grid);
}

void MainWindow::OnUnwatchedAddPress()
{
    Anime_t anime;
    AddWindow* window = new AddWindow(false, false, anime);
    window->setFixedSize(500,300);
    window->setWindowTitle("Add an Anime");
    window->setWindowIcon(QIcon(ICONPATH));
    window->show();
}

void MainWindow::OnWatchedAddPress()
{
    Anime_t anime;
    AddWindow* window = new AddWindow(true, false, anime);
    window->setFixedSize(500,300);
    window->setWindowTitle("Add an Anime");
    window->setWindowIcon(QIcon(ICONPATH));
    window->show();
}

void MainWindow::OnUnwatchedRemovePress()
{
    bool result;
    SelectWindow* window = new SelectWindow(1,false, &result);
    window->setFixedSize(300,125);
    window->setWindowTitle("Select an Anime");
    window->setWindowIcon(QIcon(ICONPATH));
    if (!result)
    {
        window->close();
        return;
    }    
    window->show();
}

void MainWindow::OnWatchedRemovePress()
{
    bool result;
    SelectWindow* window = new SelectWindow(1,true, &result);
    window->setFixedSize(300,125);
    window->setWindowTitle("Select an Anime");
    window->setWindowIcon(QIcon(ICONPATH));
    if (!result)
    {
        window->close();
        return;
    }    
    window->show();
}

void MainWindow::OnUnwatchedMovePress()
{
    bool result;
    SelectWindow* window = new SelectWindow(2,false, &result);
    window->setFixedSize(300,150);
    window->setWindowTitle("Move an Anime");
    window->setWindowIcon(QIcon(ICONPATH));
    if (!result)
    {
        window->close();
        return;
    }    
    window->show();
}

void MainWindow::OnWatchedMovePress()
{
    bool result;
    SelectWindow* window = new SelectWindow(2,true, &result);
    window->setFixedSize(300,150);
    window->setWindowTitle("Move an Anime");
    window->setWindowIcon(QIcon(ICONPATH));
    if (!result)
    {
        window->close();
        return;
    }    
    window->show();
}

void MainWindow::OnUnwatchedEditPress()
{
    bool result;
    SelectWindow* window = new SelectWindow(0,false, &result);
    window->setFixedSize(300,125);
    window->setWindowTitle("Select an Anime");
    window->setWindowIcon(QIcon(ICONPATH));
    if (!result)
    {
        window->close();
        return;
    }    
    window->show();
}

void MainWindow::OnWatchedEditPress()
{
    bool result;
    SelectWindow* window = new SelectWindow(0,true, &result);
    window->setFixedSize(300,125);
    window->setWindowTitle("Select an Anime");
    window->setWindowIcon(QIcon(ICONPATH));
    if (!result)
    {
        window->close();
        return;
    }    
    window->show();
}

void MainWindow::OnUnwatchedSortPress()
{
    SortWindow* window = new SortWindow(false);
    window->setFixedSize(300,175);
    window->setWindowTitle("Sort List");
    window->setWindowIcon(QIcon(ICONPATH));

    window->show();
}

void MainWindow::OnWatchedSortPress()
{
    SortWindow* window = new SortWindow(true);
    window->setFixedSize(300,175);
    window->setWindowTitle("Sort List");
    window->setWindowIcon(QIcon(ICONPATH));

    window->show();
}

void loadLists(std::vector<Anime_t> unwatched_vec, std::vector<Anime_t> watched_vec)
{
    std::string name, num_episodes, rating;
    QString orig_text = "--------------------Name-------------------|Episodes|Rating\n\n";
    QString text = orig_text;

    for(int i=unwatched_vec.size()-1; i>=0; i--)
    {
        name = parseItem(unwatched_vec[i].name, 44, 21, '|');
        num_episodes = parseItem(std::to_string(unwatched_vec[i].num_episodes),9,3,'|');
        rating = parseItem(std::to_string(unwatched_vec[i].rating),6,1,' ');
        text.append(QString::fromUtf8(name.c_str()));
        text.append(QString::fromUtf8(num_episodes.c_str()));
        text.append(QString::fromUtf8(rating.c_str()));
    }
    unwatched_edit->setText(text);
    text = orig_text;

    for (int i=watched_vec.size()-1; i>=0; i--)
    {
        name = parseItem(watched_vec[i].name, 44, 21, '|');
        num_episodes = parseItem(std::to_string(watched_vec[i].num_episodes),9,3,'|');
        rating = parseItem(std::to_string(watched_vec[i].rating),7,2,' ');
        text.append(QString::fromUtf8(name.c_str()));
        text.append(QString::fromUtf8(num_episodes.c_str()));
        text.append(QString::fromUtf8(rating.c_str()));
    }
    watched_edit->setText(text);
}

std::string parseItem(std::string item, int size, int middle, char term)
{
    int length, dist, index = 0;
    std::string formatted_text = "";
    formatted_text.resize(size);

    length = item.length();
    dist = length / 2;

    if (length%2)
    {
        for (int j=0; j<=middle-dist; j++)
            formatted_text[j] = '-';
        for (int j=middle+1-dist; j<=middle+1+dist; j++)
        {
            formatted_text[j] = item[index];
            index++;
        }
        for (int j=middle+2+dist; j<=size-1; j++)
            formatted_text[j] = '-';
    }
    else
    {
        for (int j=0; j<=middle-dist; j++)
            formatted_text[j] = '-';
        for (int j=middle+1-dist; j<=middle+dist; j++)
        {
            formatted_text[j] = item[index];
            index++;
        }
        for (int j=middle+1+dist; j<=size-1; j++)
            formatted_text[j] = '-';
    }
    formatted_text[size-1] = term;
    return formatted_text;
}

MainWindow::~MainWindow() {}

