#ifndef ACTIVITER_H
#define ACTIVITER_H
#include<QString>
#include <QDate>
#include <QSqlQueryModel>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QGridLayout>
#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <QPieSlice>
class activiter
{
private:
int CODEACTIVITE;
QString NOMACTIVITE,DESCRIPTION,TYPE;
int DUREE,NBPARTICIPENT;
QDate DATE_AC; // <-- new attribute


public:
     activiter();
     activiter(int,QString,QString,QString,int,int,QDate); // <-- updated constructor
     void set_CODEACTIVITE(int);
     void set_NOMACTIVITE(QString);
     void set_DESCRIPTION(QString);
     void set_TYPE(QString);
     void set_DUREE(int);
     void set_NBPARTICIPENT(int);
     void set_DATEACTIVITE(QDate); // <-- new setter

     int get_CODEACTIVITE();
     QString get_NOMACTIVITE();
     QString get_DESCRIPTION();
     QString get_TYPE();
     int get_DUREE();
     int get_NBPARTICIPENT();
     QDate get_DATEACTIVITE(); // <-- new getter

     QSqlQueryModel* GETALL();
     bool DELETEE(int);
     QSqlQueryModel* FINDBYCODEACTIVITE(int);
     bool ADD();
     bool employexiste(QString CODEACTIVITE);
     bool UPDATE();
     QSqlQueryModel* trie(QString croissance,QString critere);
     QChartView *stat_capacite();

};

#endif // ACTIVITER_H
