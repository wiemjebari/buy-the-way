#include "connexion.h"
#include<QtDebug>
#include"QtSql"
#include <QSqlQuery>
#include <QApplication>
#include <QCoreApplication>
#include <QSqlDatabase>
connexion::connexion()
{

}
bool connexion::createconnect()
{
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet");
    db.setUserName("eya");//inserer nom de l'utilisateur
    db.setPassword("esprit19");//inserer mot de passe de cet utilisateur

    if (db.open())
    { test=true;}


  return  test;
}
