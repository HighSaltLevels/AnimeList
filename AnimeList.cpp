/*********************************************************************************************
* AnimeList.cpp
*
* Description: This is the file that contains main(). It builds the Main Window and waits for
*              user input
*
* Functions:
*            main: Builds the Main Window and watis for user input.
*
*********************************************************************************************/

#include "MainWindow.h"

int main(int argc, char* argv[])
/*********************************************************************************************
* Function: 
*   main
*
* Params:
*   int argc:     Integer that represents the total number of command line arguments.
*                 Currently any command line arguments will be ignored
*   char* argv[]: Argument vector from command line arguments. Currently any command line
*                 arguments will be ignored
*
* returns:
*   An integer that represents the exit code for this application. Currently it only returns 0
*********************************************************************************************/
{
    // Create a QApplication
    QApplication app(argc, argv);

    // Make an instance of the MainWindow GUI and show it
    MainWindow window;
    window.setFixedSize(1000,500);
    window.setWindowTitle("Anime List");
    window.setWindowIcon(QIcon(ICONPATH));
    window.show();

    // Begin the infinite loop of waiting for user input
    return app.exec();
}

