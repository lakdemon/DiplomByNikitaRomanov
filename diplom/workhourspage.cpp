#include "workhourspage.h"

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QBoxLayout>
#include <QLineEdit>
#include <QSqlQueryModel>
//#include <QHeaderView>
#include <QDebug>
#include <QSqlError>
#include <QtCore>

WorkhoursPage::WorkhoursPage(QWidget *parent) :
    QWidget(parent)
{

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db_name.sqlite");
    if(!db.open())
        qDebug() << db.lastError().text();

    QSqlQuery* selectfromworkhours = new QSqlQuery();
    selectfromworkhours->prepare("SELECT workhours.work_Date AS DATE, employee.full_Name AS NAME, stavka.dolznost AS POSITION, workhours.arrival_Time AS ARRIVAL, workhours.departure_Time AS DEPARTURE FROM workhours JOIN employee ON workhours.id_employee == employee.id JOIN stavka ON workhours.id_dolznost == stavka.id");
    if(!selectfromworkhours->exec())
        qDebug() << selectfromworkhours->lastError().text();

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(*selectfromworkhours);

    view = new QTableView(this);
    view->setModel(model);
    //view->resizeColumnsToContents();
    //view->resizeRowsToContents();
    /*
    view->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    view->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    view->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    view->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);
    view->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Stretch);
    view->horizontalHeader()->setSectionResizeMode(4,QHeaderView::Stretch);
*/

    addRecordLabel   = new QLabel;
    addRecordLabel->setText("Add new record");
    paySalariesLabel = new QLabel;
    paySalariesLabel->setText("Pay salarie");


    QSqlQuery allEmployeeQuery;
    if(!allEmployeeQuery.exec("SELECT full_Name FROM employee"))
        qDebug() << allEmployeeQuery.lastError().text();

    QSqlQuery allPositionsQuery;
    if(allPositionsQuery.exec("SELECT dolznost FROM stavka"))
        qDebug() << allPositionsQuery.exec();


    Position_Choice      = new QComboBox;
    Name_Choice          = new QComboBox;
    Name_Choice_Salaries = new QComboBox;
    while (allEmployeeQuery.next()) {
        QString name = allEmployeeQuery.value(0).toString();
        Name_Choice->addItem(name);
        Name_Choice_Salaries->addItem(name);
    }
    while (allPositionsQuery.next()){
        QString position = allPositionsQuery.value(0).toString();
        Position_Choice->addItem(position);
    }

    Date           = new QLineEdit;
    Date->setPlaceholderText("DATE");
    Arrival_Time   = new QLineEdit;
    Arrival_Time->setPlaceholderText("Arrival");
    Departure_Time = new QLineEdit;
    Departure_Time->setPlaceholderText("Departure");

    addRecordButton = new QPushButton;
    addRecordButton->setText("Add");

    paySalariesButton = new QPushButton;
    paySalariesButton->setText("Pay");

    h_layout = new QHBoxLayout;
    h_layout->addWidget(Name_Choice);
    h_layout->addWidget(Position_Choice);
    h_layout->addWidget(Date);
    h_layout->addWidget(Arrival_Time);
    h_layout->addWidget(Departure_Time);
    h_layout->addWidget(addRecordButton);

    salarie_h_layout = new QHBoxLayout;
    salarie_h_layout->addWidget(Name_Choice_Salaries);
    salarie_h_layout->addWidget(paySalariesButton);

    v_layout = new QVBoxLayout;
    v_layout->addWidget(view);
    v_layout->addWidget(addRecordLabel);
    v_layout->addLayout(h_layout);
    v_layout->addWidget(paySalariesLabel);
    v_layout->addLayout(salarie_h_layout);
    this->setLayout(v_layout);

    connect(addRecordButton,SIGNAL(released()),this,SLOT(AddRecordSLOT()));

}

WorkhoursPage::~WorkhoursPage()
{
    delete view;
    delete v_layout;
    delete h_layout;
    delete addRecordLabel;
    delete addRecordButton;
    delete Name_Choice;
    delete Position_Choice;
    delete Arrival_Time;
    delete Departure_Time;
    delete Date;
    db.close();

}

void WorkhoursPage::AddRecordSLOT()
{

    QString NameToInsert     = Name_Choice->currentText();
    QString PositionToInsert = Position_Choice->currentText();
    QString DateToInsert     = Date->text();
    QString ArrivalToInsert  = Arrival_Time->text();
    QString DepartureToInsert= Departure_Time->text();
    QString EmployeeId;
    QString PositionId;
    QString IDToInsert;

    if(ArrivalToInsert.isEmpty() || DepartureToInsert.isEmpty()){
        qDebug() << "Some data were not entered";
        return;
    }

    qDebug() << NameToInsert;
    QSqlQuery findIndexByName;
    findIndexByName.prepare("SELECT id, full_Name FROM employee WHERE full_Name = '"+NameToInsert+"'");
    findIndexByName.exec();
    while(findIndexByName.next()){
        EmployeeId = findIndexByName.value(0).toString();
        qDebug() << EmployeeId << findIndexByName.value(1).toString();
    }

    qDebug() << PositionToInsert;
    QSqlQuery findIndexByPosition;
    findIndexByPosition.prepare("SELECT id, dolznost FROM stavka WHERE dolznost = '"+PositionToInsert+"'");
    findIndexByPosition.exec();
    while(findIndexByPosition.next()){
        qDebug() << findIndexByPosition.lastError().text();
        PositionId = findIndexByPosition.value(0).toString();
        qDebug() << PositionId << findIndexByPosition.value(1).toString();
    }

    QSqlQuery findLastID;
    findLastID.prepare("SELECT MAX(id) FROM workhours");
    findLastID.exec();
    while(findLastID.next()){
        IDToInsert = findLastID.value(0).toString();
        IDToInsert = QString::number(IDToInsert.toInt()+1);
    }

    QSqlQuery insertRecord;
    insertRecord.prepare("INSERT INTO workhours(id, id_employee, id_dolznost, work_Date, arrival_Time, departure_Time)"
                         "VALUES (:id, :id_employee, :id_dolznost, :work_Date, :arrival_Time, :departure_Time)");
    insertRecord.bindValue(":id", IDToInsert);
    insertRecord.bindValue(":id_employee",EmployeeId);
    insertRecord.bindValue(":id_dolznost",PositionId);
    insertRecord.bindValue(":work_Date",DateToInsert);
    insertRecord.bindValue(":arrival_Time",ArrivalToInsert);
    insertRecord.bindValue(":departure_Time",DepartureToInsert);
    insertRecord.exec();
    qDebug() << insertRecord.lastError().text();


    QSqlQuery* selectfromworkhours = new QSqlQuery();
    selectfromworkhours->prepare("SELECT workhours.work_Date AS DATE, employee.full_Name AS NAME, stavka.dolznost AS POSITION, workhours.arrival_Time AS ARRIVAL, workhours.departure_Time AS DEPARTURE FROM workhours JOIN employee ON workhours.id_employee == employee.id JOIN stavka ON workhours.id_dolznost == stavka.id");
    selectfromworkhours->exec();

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(*selectfromworkhours);

    view->setModel(model);
    Arrival_Time->clear();
    Departure_Time->clear();

    //this is last version
}
