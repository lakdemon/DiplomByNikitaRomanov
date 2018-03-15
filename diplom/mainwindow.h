#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>
#include <QBoxLayout>


namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QSqlDatabase db;
    QSqlTableModel *model;
    QTableView *view;
    QVBoxLayout *layout;

    void CreateTables();
    void InsertStavka(QString id, QString dolznost, QString d_stavka, QString n_stavka);

//private:
    //Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
