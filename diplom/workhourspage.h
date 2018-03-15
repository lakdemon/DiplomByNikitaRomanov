#ifndef WORKHOURSPAGE_H
#define WORKHOURSPAGE_H

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

namespace Ui {
class WorkhoursPage;
}

class WorkhoursPage : public QWidget
{
    Q_OBJECT

public:
    explicit WorkhoursPage(QWidget *parent = 0);
    ~WorkhoursPage();

    //QSqlTableModel *model;
    //QSqlQueryModel *model;
    QTableView  *view;
    QVBoxLayout *v_layout;
    QHBoxLayout *h_layout;
    QHBoxLayout *salarie_h_layout;
    QLabel      *addRecordLabel;
    QLabel      *paySalariesLabel;
    QPushButton *addRecordButton;
    QPushButton *paySalariesButton;
    QComboBox   *Name_Choice;
    QComboBox   *Position_Choice;
    QComboBox   *Name_Choice_Salaries;
    QLineEdit   *Arrival_Time;
    QLineEdit   *Departure_Time;
    QLineEdit   *Date;

public slots:
   void AddRecordSLOT();

//private:
    //Ui::WorkhoursPage *ui;
};
#endif // WORKHOURSPAGE_H
