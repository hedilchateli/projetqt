#ifndef GESTION_ACTIVITER_H
#define GESTION_ACTIVITER_H

#include <QMainWindow>
#include"activiter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class gestion_activiter; }
QT_END_NAMESPACE

class gestion_activiter : public QMainWindow
{
    Q_OBJECT

public:
    gestion_activiter(QWidget *parent = nullptr);
    ~gestion_activiter();

private slots:
void showNotification(QString code_activite, QString nom_activite, QString description, QString type, QString duree_activite, QString nb_participants, QString date_ac);

    void on_bouton_ajouter_2_clicked();
    bool controlSaisie();
    void  CLEAR();


    void on_pb_modifier_2_clicked();


    void on_table_activiter_activated(const QModelIndex &index);

    void on_tabWidget_2_currentChanged();

    void on_pb_meilleur_clicked();

    void on_pb_supprimer_clicked();

    void on_radioButton_a_2_clicked();

    void on_radioButton_d_2_clicked();

    void on_pb_supprimer_2_clicked();

    void on_historique_clicked();

    void on_label_28_linkActivated(const QString &link);

    void on_pb_supprimer_3_clicked();

private:
    Ui::gestion_activiter *ui;
       activiter ac;
};
#endif // GESTION_ACTIVITER_H
