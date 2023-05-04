#include "activiter.h"
#include <QSqlQuery>
#include<QDebug>
#include <QSqlQueryModel>
#include <QObject>
#include <QSqlError>
activiter::activiter()
{
      CODEACTIVITE=0;
      NOMACTIVITE="";
      DESCRIPTION="";
      TYPE="";
      DUREE=0;
      NBPARTICIPENT=0;
}
activiter::activiter(int CODEACTIVITE,QString NOMACTIVITE,QString DESCRIPTION,QString TYPE,int DUREE,int NBPARTICIPENT,QDate DATE_AC){
    this->CODEACTIVITE=CODEACTIVITE;
    this->NOMACTIVITE=NOMACTIVITE;
    this->DESCRIPTION=DESCRIPTION;
    this->TYPE=TYPE;
    this->DUREE=DUREE;
    this->NBPARTICIPENT=NBPARTICIPENT;
    this->DATE_AC=DATE_AC;
            };

void activiter::set_CODEACTIVITE(int CODEACTIVITE){this->CODEACTIVITE=CODEACTIVITE;};
void activiter::set_NOMACTIVITE(QString NOMACTIVITE){this->NOMACTIVITE=NOMACTIVITE;};
void activiter::set_DESCRIPTION(QString DESCRIPTION){this->DESCRIPTION=DESCRIPTION;};
void activiter::set_TYPE(QString TYPE){this->TYPE=TYPE;};
void activiter::set_DUREE(int DUREE){this->DUREE=DUREE;};
void activiter::set_NBPARTICIPENT(int NBPARTICIPENT){this->NBPARTICIPENT=NBPARTICIPENT;};
void activiter::set_DATEACTIVITE(QDate DATE_AC){this->DATE_AC=DATE_AC;};

int activiter::get_CODEACTIVITE(){return CODEACTIVITE;};
QString activiter::get_NOMACTIVITE(){return NOMACTIVITE;};
QString activiter::get_DESCRIPTION(){return DESCRIPTION;};
QString activiter::get_TYPE(){return TYPE;};
int activiter::get_DUREE(){return DUREE;};
int activiter::get_NBPARTICIPENT(){return NBPARTICIPENT;};
QDate activiter::get_DATEACTIVITE(){return DATE_AC;};

QSqlQueryModel* activiter::GETALL()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CODEACTIVITE, NOMACTIVITE, DESCRIPTION, TYPE, DUREE, NBPARTICIPENT, DATE_AC FROM GES_ACTIVI");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CODEACTIVITE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOMACTIVITE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DUREE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("NBPARTICIPENT"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("DATE_AC")); // set the header for the new column
    return model;
}



bool activiter::DELETEE(int CODEACTIVITE)
{
    QSqlQuery query;
    query.prepare("Delete from GES_ACTIVI where CODEACTIVITE=:CODEACTIVITE");
     query.bindValue(":CODEACTIVITE",CODEACTIVITE);
     return  query.exec();
}

QSqlQueryModel* activiter::FINDBYCODEACTIVITE(int CODEACTIVITE){
    QSqlQueryModel *modal=new QSqlQueryModel();
    modal->setQuery("select * from GES_ACTIVI where CODEACTIVITE like '%"+QString::number(CODEACTIVITE)+"%'");
    return modal;};

bool activiter::ADD(){
    QSqlQuery query;
    query.prepare("INSERT INTO GES_ACTIVI (CODEACTIVITE,NOMACTIVITE,DESCRIPTION,TYPE,DUREE,NBPARTICIPENT,DATE_AC) "
                   "VALUES (:CODEACTIVITE,:NOMACTIVITE,:DESCRIPTION,:TYPE,:DUREE,:NBPARTICIPENT,:DATE_AC)");
     query.bindValue(":CODEACTIVITE", CODEACTIVITE);
     query.bindValue(":NOMACTIVITE", NOMACTIVITE);
     query.bindValue(":DESCRIPTION", DESCRIPTION);
     query.bindValue(":TYPE", TYPE);
     query.bindValue(":DUREE", DUREE);
     query.bindValue(":NBPARTICIPENT", NBPARTICIPENT);
     query.bindValue(":DATE_AC", DATE_AC);
    return query.exec();
};


bool activiter:: employexiste(QString CODEACTIVITE)
{
   bool exists = false;
   QSqlQuery checkQuery;
   checkQuery.prepare("SELECT CODEACTIVITE FROM GES_ACTIVI WHERE CODEACTIVITE=:CODEACTIVITE");
   checkQuery.bindValue(":CODEACTIVITE", CODEACTIVITE);
   if (checkQuery.exec())
   { if (checkQuery.next())
       { exists = true;}
   }
   else
   {qDebug() << "activiter not found:" << checkQuery.lastError();}
return exists;
}

bool activiter::UPDATE(){
    QSqlQuery query;
    query.prepare("UPDATE GES_ACTIVI SET NOMACTIVITE=:NOMACTIVITE, DESCRIPTION=:DESCRIPTION, TYPE=:TYPE, DUREE=:DUREE, NBPARTICIPENT=:NBPARTICIPENT, DATE_AC=:DATE_AC WHERE CODEACTIVITE=:CODEACTIVITE");
    query.bindValue(":CODEACTIVITE",CODEACTIVITE);
    query.bindValue(":NOMACTIVITE", NOMACTIVITE);
    query.bindValue(":DESCRIPTION", DESCRIPTION);
    query.bindValue(":TYPE", TYPE);
    query.bindValue(":DUREE", DUREE);
    query.bindValue(":NBPARTICIPENT", NBPARTICIPENT);
    query.bindValue(":DATE_AC", DATE_AC);
    return query.exec();
};

QSqlQueryModel *activiter::trie(QString croissance,QString critere)
{
   QSqlQueryModel *modal=new QSqlQueryModel();

   if(critere == "CODEACTIVITE" && croissance == "ASC")
       modal->setQuery("select * from GES_ACTIVI order by CODEACTIVITE ASC ");
   else if(critere == "CODEACTIVITE" && croissance == "DESC")
       modal->setQuery("select * from GES_ACTIVI order by CODEACTIVITE DESC ");

   else if(critere == "NOMACTIVITE" && croissance == "ASC")
       modal->setQuery("select * from GES_ACTIVI order by NOMACTIVITE ASC ");

   else if(critere == "NOMACTIVITE" && croissance == "DESC")
       modal->setQuery("select * from GES_ACTIVI order by NOMACTIVITE DESC ");

   else if(critere == "DUREE" && croissance == "ASC")
       modal->setQuery("select * from GES_ACTIVI order by DUREE ASC ");
   else if(critere == "DUREE" && croissance == "DESC")
       modal->setQuery("select * from GES_ACTIVI order by DUREE DESC ");

   return  modal;
}
QChartView *activiter::stat_capacite()
  {
      int a1=0;
      int a2=0;
      int a3=0;
      int a4=0;

      QSqlQuery query;
      query.prepare("select * from GES_ACTIVI where ((DUREE>=1)and(DUREE<=10))");
      query.exec();

      while(query.next())
          a1++;

      query.prepare("select * from GES_ACTIVI where ((DUREE>=10)and(DUREE<=20))");
      query.exec();

      while(query.next())
          a2++;
      query.prepare("select * from GES_ACTIVI where ((DUREE>=20)and(DUREE<=30))");
      query.exec();

      while(query.next())
          a3++;
      query.prepare("select * from GES_ACTIVI where ((DUREE>=30)and(DUREE<=60))");
      query.exec();

      while(query.next())
          a4++;


      qDebug() << a1<< a2 <<a3 <<a4 ;

      QPieSeries *series = new QPieSeries();
          series->append("duree entre 1 et 10", a1);
          series->append("duree entre 10 et 20", a2);
          series->append("duree entre 20 et 30", a3);
          series->append("duree entre 30 et 40", a4);


          QPieSlice *slice = series->slices().at(0);
          slice->setExploded(true);
          slice->setColor("#7fffd4	");

          QPieSlice *slice2 = series->slices().at(1);
          slice2->setColor("#6495ed");
          QPieSlice *slice3 = series->slices().at(2);
          slice2->setColor("#008b8b");
          QPieSlice *slice4 = series->slices().at(3);
          slice2->setColor("#1e90ff");


          QChart *chart = new QChart();
          chart->addSeries(series);
          chart->setTitle("Statistique du duree de lactivite");


          series->setLabelsVisible();

          QChartView *chartView = new QChartView(chart);
          chartView->setRenderHint(QPainter::Antialiasing);
          chartView->chart()->setAnimationOptions(QChart::AllAnimations);
          chartView->chart()->legend()->hide();
          chartView->resize(1000,500);
          return chartView;
}
