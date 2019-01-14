#include "SelectWindow.h"

SelectWindow::SelectWindow(QWidget* parent, int action, bool watched, bool* success)
{
    std::vector<std::string> animes;
    bool result;

    QString msg = "Please select an anime from the drop-down box";
    QLabel* msg_lbl = new QLabel(msg, this);

    QComboBox* box = new QComboBox(this);
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
    std::cout << "TODO Load the next GUI\n";
    this->close();
    return;
}

void SelectWindow::OnCancelPress()
{
    this->close();
}

SelectWindow::~SelectWindow() {}

