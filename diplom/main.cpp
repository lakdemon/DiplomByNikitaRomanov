#include "mainwindow.h"
#include "workhourspage.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>
#include <QDebug>
#include <QSqlError>
#include <QTabWidget>
#include <QPushButton>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WorkhoursPage page1;

    //MainWindow window;
    //window.view->resizeColumnsToContents();
    //window.view->resizeRowsToContents();

    QTabWidget tabber;

    QLabel inProgress1;
    QLabel inProgress2;
    inProgress1.setText("In Progress");
    inProgress2.setText("In Progress");

    tabber.setGeometry(300,300,600,500);
    tabber.addTab(&page1,"Work hours");
    tabber.addTab(&inProgress1,"Positions");
    tabber.addTab(&inProgress2,"Employee");
    tabber.show();


    return a.exec();
}
