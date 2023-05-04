#include "gestion_activiter.h"
#include "ui_gestion_activiter.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlQuery>
#define file_tx "^[A-Za-z ]+$"
#define file_ex "^[0-9]+$"
#include <QtLocation>
#include <QSqlRecord>
#include <QResource>
gestion_activiter::gestion_activiter(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gestion_activiter)
{
    ui->setupUi(this);
    ui->nomactiviter_ajout->setValidator(new QRegExpValidator( QRegExp(file_tx),this));
    ui->type_ajout->setValidator(new QRegExpValidator( QRegExp(file_tx),this));
     ui->codeactiviter_ajout->setValidator(new QRegExpValidator( QRegExp(file_ex),this));
    ui->nombrepartici_ajout->setValidator(new QRegExpValidator( QRegExp(file_ex),this));
    ui->duree_ajout->setValidator(new QRegExpValidator( QRegExp(file_ex),this));
    ui->id_supp->setValidator(new QRegExpValidator( QRegExp(file_ex),this));

}

gestion_activiter::~gestion_activiter()
{
    delete ui;
}

bool gestion_activiter::controlSaisie(){
    if (


            ui->description_ajout->text().isEmpty() ||
            ui->description_ajout->text() =="" ||
                                                ui->nomactiviter_ajout->text().isEmpty() ||
                                                ui->nomactiviter_ajout->text() =="" ||



                                                ui->codeactiviter_ajout->text().isEmpty() ||
                                                ui->codeactiviter_ajout->text().toInt() == 0 ||

                                                ui->duree_ajout->text().isEmpty() ||
                                                ui->duree_ajout->text().toInt() == 0 ||

                                                ui->nombrepartici_ajout->text().isEmpty() ||
                                                ui->nombrepartici_ajout->text().toFloat() == 0

                                               )

                                            return 0;

                                        else

                                            return 1;};
void gestion_activiter::CLEAR()
{
    ui->codeactiviter_ajout->clear();
    ui->nomactiviter_ajout->clear();
    ui->description_ajout->clear();
    ui->type_ajout->clear();
    ui->duree_ajout->clear();
    ui->nombrepartici_ajout->clear();

}

void gestion_activiter::on_bouton_ajouter_2_clicked()
{
    QMessageBox msgBox;
        if(controlSaisie()==1)
    {

            bool test1=ac.employexiste(ui->codeactiviter_ajout->text());
            if(test1==true)
    {            msgBox.setText("!!ID existe !!");
                msgBox.exec();}else{
    int CODEACTIVITE=ui->codeactiviter_ajout->text().toInt();
    QString NOMACTIVITE=ui->nomactiviter_ajout->text();
    QString DESCRIPTION=ui->description_ajout->text();
    QString TYPE=ui->type_ajout->text();
    int DUREE=ui->duree_ajout->text().toInt();
    int NBPARTICIPENT=ui->nombrepartici_ajout->text().toInt();
    QDate DATE_AC = ui->calendarWidget->selectedDate();
    activiter acc(CODEACTIVITE,NOMACTIVITE,DESCRIPTION,TYPE,DUREE,NBPARTICIPENT,DATE_AC);

    bool test=acc.ADD();

     if(test)
     {
     CLEAR();
     msgBox.setText("Ajout avec succes.");
     }
     else
       {msgBox.setText("!!Echec d'ajout!!");}


        msgBox.exec();   }}
    else if(controlSaisie()==0)
    {
    QMessageBox::critical(nullptr, QObject::tr("not ok"),
    QObject::tr("veuiller remplir tous les champs.\n !!!Il existe des champs VIDE ou INCORRECT!!!\n"
    "Click cancel to exit."), QMessageBox::Cancel);
    }

        ui->table_activiter->setModel(ac.GETALL());

}

void gestion_activiter::on_pb_modifier_2_clicked()
{
    if(controlSaisie()==1)
    {
        int CODEACTIVITE=ui->codeactiviter_ajout->text().toInt();
        QString NOMACTIVITE=ui->nomactiviter_ajout->text();
        QString DESCRIPTION=ui->description_ajout->text();
        QString TYPE=ui->type_ajout->text();
        int DUREE=ui->duree_ajout->text().toInt();
        int NBPARTICIPENT=ui->nombrepartici_ajout->text().toInt();
        QDate DATE_AC = ui->calendarWidget->selectedDate();

        activiter acc(CODEACTIVITE,NOMACTIVITE,DESCRIPTION,TYPE,DUREE,NBPARTICIPENT,DATE_AC);

bool test1=ac.employexiste(ui->codeactiviter_ajout->text());
            if(test1==true)
 {
    bool test=acc.UPDATE();
            QMessageBox msgBox;
            if(test)
            {ui->table_activiter->setModel(ac.GETALL());
                 CLEAR();
                msgBox.setText("modification avec succes.");
                msgBox.exec(); }

            else
            {
            msgBox.setText("!!Echec de modification!!");
            msgBox.exec();
             }
    }

            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                 QObject::tr("activiter n'existe pas pour modifier !\n"
                 "Click Cancel to exit."), QMessageBox::Cancel);

            }


    }
  else if(controlSaisie()==0)
  {
       // qDebug() <<"veuiller remplir tous les champs!!! Il existe des champs VIDE ou INCORRECT!!!\n";
       QMessageBox::critical(nullptr, QObject::tr("not ok"),

                          QObject::tr("veuiller remplir tous les champs.\n !!!Il existe des champs VIDE ou INCORRECT!!!\n"

                                      "Click cancel to EXIT."), QMessageBox::Cancel);
    }
}





void gestion_activiter::on_table_activiter_activated(const QModelIndex &index)
{
    CLEAR();
    QString val=ui->table_activiter->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from GES_ACTIVI where CODEACTIVITE='"+val+"'");
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->codeactiviter_ajout->setText(qry.value(0).toString());
            ui->nomactiviter_ajout->setText(qry.value(1).toString());
            ui->description_ajout->setText(qry.value(2).toString());
            ui->type_ajout->setText(qry.value(3).toString());
            ui->duree_ajout->setText(qry.value(4).toString());
            ui->nombrepartici_ajout->setText(qry.value(5).toString());

            QDate DATE_AC = qry.value(8).toDate();
            QDate currentDate = QDate::currentDate();
            int daysTo = currentDate.daysTo(DATE_AC);

            if (daysTo <= 7)
            {
                // Pass the activity data to the showNotification function
                QString code_activite = qry.value(0).toString();
                QString nom_activite = qry.value(1).toString();
                QString description = qry.value(2).toString();
                QString type = qry.value(3).toString();
                QString duree_activite = qry.value(4).toString();
                QString nb_participants = qry.value(5).toString();
                QString date_ac = qry.value(8).toDate().toString(Qt::ISODate);

                showNotification(code_activite, nom_activite, description, type, duree_activite, nb_participants, date_ac);
            }
        }
    }
    else
    {
        qDebug()<<"erreur";
    }
}


void gestion_activiter::showNotification(QString code_activite, QString nom_activite, QString description, QString type, QString duree_activite, QString nb_participants, QString date_ac)
{
    // Construct the notification message using the activity data
    QString message = "L'activité " + nom_activite + " aura lieu le " + date_ac + ".\n";
    message += "Type: " + type + "\n";
    message += "Durée: " + duree_activite + " minutes\n";
    message += "Nombre de participants: " + nb_participants + "\n";
    message += "Description: " + description;

    // Display the notification to the user
    QMessageBox::information(this, "Activité prochaine", message);
}


void gestion_activiter::on_tabWidget_2_currentChanged()
{
    ui->table_activiter->setModel(ac.GETALL());
}

void gestion_activiter::on_pb_meilleur_clicked()
{
    QSqlQueryModel *model = ac.FINDBYCODEACTIVITE(ui->rechercher->text().toInt());
        if (model->rowCount() > 0) {
            // Get the record of the first row
              QSqlRecord record = model->record(0);
              ui->codeactiviter_ajout->setText(record.value(0).toString());
              ui->nomactiviter_ajout->setText(record.value(1).toString());
              ui->description_ajout->setText(record.value(2).toString());
              ui->type_ajout->setText(record.value(3).toString());
              ui->duree_ajout->setText(record.value(4).toString());
              ui->nombrepartici_ajout->setText(record.value(5).toString());
              QDate selectedDate = QDate::fromString(record.value(8).toString(), "yyyy-MM-dd");

              ui->calendarWidget->setSelectedDate(selectedDate);

        }
            else
            {
                //qDebug() <<"!!!activiter n'existe pas !!\n";
               QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                            QObject::tr("ACTIVITER n'existe pas !\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

            }
}

void gestion_activiter::on_pb_supprimer_clicked()
{
    activiter acc;
    acc.set_CODEACTIVITE(ui->id_supp->text().toInt());
    bool test1=acc.employexiste(ui->id_supp->text());



                if(test1==true)
     {
       bool test=acc.DELETEE(acc.get_CODEACTIVITE());
       QMessageBox msgBox;
       if(test)
       {
      msgBox.setText("Suppression avec succes.");
        ui->table_activiter->setModel(acc.GETALL());
      CLEAR();
       }
      else
       msgBox.setText("!!Echec de suppression!!");
      msgBox.exec();

     }
                else
                {
                    //qDebug() <<"!!!activiter n'existe pas !!\n";
                   QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                QObject::tr("CLIENT n'existe pas !\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);

                }
}

void gestion_activiter::on_radioButton_a_2_clicked()
{
    CLEAR();
          activiter c;

  if(ui->comboBox_trie_2->currentText() != "Choisir")
ui->table_activiter->setModel(c.trie("ASC",ui->comboBox_trie_2->currentText()));
else  ui->table_activiter->setModel(c.GETALL());
}

void gestion_activiter::on_radioButton_d_2_clicked()
{ CLEAR();
   activiter c;
    if(ui->comboBox_trie_2->currentText() != "Choisir")
  ui->table_activiter->setModel(c.trie("DESC",ui->comboBox_trie_2->currentText()));
  else  ui->table_activiter->setModel(c.GETALL());



}

void gestion_activiter::on_pb_supprimer_2_clicked()
{
    QChartView *chartView = ac.stat_capacite();
        chartView->show();
}

void gestion_activiter::on_historique_clicked() {
  // Get the start date and duration from the UI
  QDate date_debut = ui->calendarWidget_2->selectedDate();
  int duree = ui->duree->text().toInt();

  // Check if the start date and duration are valid
  if (!date_debut.isValid()) {
    QMessageBox::critical(this, "Erreur", "Veuillez sélectionner une date de début valide.");
    return;
  }

  if (duree <= 0) {
    QMessageBox::critical(this, "Erreur", "Veuillez entrer une durée valide.");
    return;
  }

  // Calculate the end date based on the start date and duration
  QDate date_fin = date_debut.addDays(duree);

  // Query the "activite" table for activities that fall within the date range
  QSqlQuery query;
  query.prepare("SELECT * FROM GES_ACTIVI WHERE DATE_AC BETWEEN :date_debut AND :date_fin");
  query.bindValue(":date_debut", date_debut);
  query.bindValue(":date_fin", date_fin);
  query.exec();

  // Create a new QStandardItemModel object to hold the query results
  QStandardItemModel *model = new QStandardItemModel();

  // Set the column headers for the table view
  model->setHorizontalHeaderLabels({"Code activite", "Nom activite", "Description", "Type", "Duree", "Nb participants", "Date ac"});

  // Loop through the query results and add them to the model
  while (query.next()) {
    int code_activite = query.value(0).toInt();
    QString nom_activite = query.value(1).toString();
    QString description = query.value(2).toString();
    QString type = query.value(3).toString();
    int duree_activite = query.value(4).toInt();
    int nb_participants = query.value(5).toInt();
    QDate date_ac = query.value(8).toDate();

    // Create a new row in the model
    QList<QStandardItem *> row_items;
    row_items.append(new QStandardItem(QString::number(code_activite)));
    row_items.append(new QStandardItem(nom_activite));
    row_items.append(new QStandardItem(description));
    row_items.append(new QStandardItem(type));
    row_items.append(new QStandardItem(QString::number(duree_activite)));
    row_items.append(new QStandardItem(QString::number(nb_participants)));
    row_items.append(new QStandardItem(date_ac.toString(Qt::ISODate)));

    // Add the row to the model
    model->appendRow(row_items);
  }

  // Set the model for the table view
  ui->table_activiter->setModel(model);
}



void gestion_activiter::on_label_28_linkActivated(const QString &link)
{

}


void gestion_activiter::on_pb_supprimer_3_clicked()
{


        QPdfWriter pdf("C:/Users/chate/Desktop/gestion_activiter/Liste.pdf");

           QPainter painter(&pdf);

           int i = 4000;
           painter.setPen(Qt::red);
           painter.setFont(QFont("PreferVerticalHinting", 30));
           painter.drawPixmap(QRect(100,400,2000,2000),QPixmap("C:/Users/chate/Desktop/gestion_activiter/LOGO.png"));
           painter.drawText(3000,1500,"LISTE DES ACTIVITES");
           painter.setPen(Qt::black);
           painter.setFont(QFont("PreferVerticalHinting", 50));
           painter.setPen(Qt::black);
           painter.setFont(QFont("PreferVerticalHinting", 20));
           painter.drawText(300,3300,"CODE");
           painter.drawText(1300,3300,"NOM");
           painter.drawText(5300,3300,"DESCRIPTION");
           painter.drawText(8300,3300,"TYPE");
           painter.drawText(25300,3300,"DUREE");
           painter.drawText(25600,3300,"NBPARTICIPENT");
           painter.drawText(30000,3300,"DATE_AC");

           QSqlQuery query;
           query.prepare("select * from GES_ACTIVI");
           query.exec();
           while (query.next())
           {
               painter.drawText(300,i,query.value(0).toString());
               painter.drawText(1300,i,query.value(1).toString());
               painter.drawText(5300,i,query.value(2).toString());
               painter.drawText(8300,i,query.value(3).toString());
               painter.drawText(25300,i,query.value(4).toString());
               painter.drawText(25600,i,query.value(5).toString());
               painter.drawText(30000,i,query.value(8).toString());

               i = i +500;
           }

           int reponse = QMessageBox::question(this, "PDF généré", "Afficher le PDF ?", QMessageBox::Yes |  QMessageBox::No);
           if (reponse == QMessageBox::Yes)
           {
               QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/chate/Desktop/gestion_activiter/Liste.pdf"));

               painter.end();
           }
           if (reponse == QMessageBox::No)
           {
               painter.end();
           }
    }



