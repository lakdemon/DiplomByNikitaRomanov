#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QDebug>
#include <QBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)//,
    //ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db_name.sqlite");
    if (!db.open()) std::cout << "DB can't be opened" << std::endl;
    else            std::cout << "DB openned" << std::endl;


    view = new QTableView(this);
    model = new QSqlTableModel(this,db);
    model->setTable("stavka");
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);


    layout = new QVBoxLayout;
    layout->addWidget(view);
    this->setLayout(layout);
    view->resizeColumnsToContents();
    view->resizeRowsToContents();
    view->setModel(model);
    //view->horizontalHeader()->setStretchLastSection(true);


}

MainWindow::~MainWindow()
{
    //delete ui;
}

void MainWindow::CreateTables()
{
    QString stavka = "CREATE TABLE stavka ("
            "id integer PRIMARY KEY NOT NULL, "
            "dolznost VARCHAR(255), "
            "d_stavka integer, "
            "n_stavka integer"
            ");";

    QString employee = "CREATE TABLE employee ("
            "id integer PRIMARY KEY NOT NULL, "
            "full_Name VARCHAR(255), "
            "phone_Number VARCHAR(255), "
            "birth_Date VARCHAR(255)"
            ");";

    QString workhours = "CREATE TABLE workhours ("
            "id integer PRIMARY KEY NOT NULL, "
            "id_employee integer, "
            "id_dolznost integer, "
            "work_Date VARCHAR(255), "
            "arrival_Time VARCHAR(255), "
            "departure_Time VARCHAR(255)"
            ");";

    QSqlQuery query;
    query.prepare(stavka);
    query.exec();
    query.prepare(employee);
    query.exec();
    query.prepare(workhours);
    query.exec();

}

void MainWindow::InsertStavka(QString id, QString dolznost, QString d_stavka, QString n_stavka)
{
    QString insert = "INSERT INTO stavka(id, dolznost, d_stavka, n_stavka)"
               "VALUES (:id, :dolznost, :d_stavka, :n_stavka)";

    QSqlQuery insert_dolznost;
    insert_dolznost.prepare(insert);
    insert_dolznost.bindValue(":id",id);
    insert_dolznost.bindValue(":dolznost",dolznost);
    insert_dolznost.bindValue(":d_stavka",d_stavka);
    insert_dolznost.bindValue(":n_stavka",n_stavka);

    if(insert_dolznost.exec())  std::cout << "insert complited" << std::endl;
    else                        std::cout << "insert not complete" << std::endl;

}
