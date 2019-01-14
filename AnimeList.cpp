#include "MainWindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MainWindow window;

    window.setFixedSize(1000,500);
    window.setWindowTitle("Anime List");
    window.setWindowIcon(QIcon("lonk.png"));
    window.show();

    return app.exec();
}

