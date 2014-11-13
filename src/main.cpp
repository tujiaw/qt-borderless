#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTextEdit>

#include "MainFrame.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    MainFrame box;

    QMainWindow* mainWindow = box.mainWindow();
    //QTextEdit *edit = new QTextEdit(mainWindow);
    //mainWindow->setCentralWidget(edit);


    QTextEdit *edit = new QTextEdit();
    box.setContentWidget(edit);

    box.show();
    return app.exec();
}
