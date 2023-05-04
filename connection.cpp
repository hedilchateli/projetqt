#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("hedil");
db.setUserName("hedil");//inserer nom de l'utilisateur
db.setPassword("hedil");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;

    return  test;
}
