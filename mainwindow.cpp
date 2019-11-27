#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "facture.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
ui->setupUi(this);
ui->TabCommandes_3->setModel(tmpCommande.afficher());
ui->tableView->setModel(tmpFacture.afficher());

ui->comboBox->addItem("");
ui->comboBox->addItem("En fonction de la date");
ui->comboBox->addItem("En fonction de la Reference");
ui->comboBox->addItem("En fonction de l'etat");

ui->comboBox_4->addItem("");
ui->comboBox_4->addItem("En fonction de la catégorie");
ui->comboBox_4->addItem("En fonction de la Reference");
ui->comboBox_4->addItem("En fonction de la quantité");

ui->comboBox_2->addItem("");
ui->comboBox_2->addItem("Marche frais");
ui->comboBox_2->addItem("Alimentaire");
ui->comboBox_2->addItem("Hygiene/Beaute");
ui->comboBox_2->addItem("Maison/Jardin");
ui->comboBox_2->addItem("H.T/Electro");
ui->comboBox_2->addItem("Textile");

ui->comboBox_3->addItem("");
ui->comboBox_3->addItem("Marche frais");
ui->comboBox_3->addItem("Alimentaire");
ui->comboBox_3->addItem("Hygiene/Beaute");
ui->comboBox_3->addItem("Maison/Jardin");
ui->comboBox_3->addItem("H.T/Electro");
ui->comboBox_3->addItem("Textile");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_facture_clicked()
{
    int Ref_Facture = ui->lineEdit_Reference_8->text().toInt();
    int ID_Commande= ui->lineEdit_Reference_10->text().toInt();
    QString description=ui->lineEdit_description_facture->text();
    QString date=ui->lineEdit_Date->text();
    float montant=ui->lineEdit_ID_Commande3_3->text().toFloat();
    QString etat;
    if(ui->radioButton->isChecked())
    {
        etat= ui->radioButton->text();
    }
    else if(ui->radioButton_2->isChecked())
    {
        etat= ui->radioButton_2->text();
    }

    Facture c(Ref_Facture,ID_Commande,description,date,montant,etat);

    bool test=c.ajouter();
    if(test)
    {
        ui->tableView->setModel(tmpFacture.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Ajouter une facture"),
                  QObject::tr("facture ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Ajouter une facture"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pushButton_modifier_facture_clicked()
{
    int Ref_Facture = ui->lineEdit_Reference_12->text().toInt();
    int ID_Commande= ui->lineEdit_Reference_11->text().toInt();
    QString description=ui->lineEdit_ID_Fournisseur3_4->text();
    QString date=ui->lineEdit_ID_Fournisseur3_5->text();
    float montant=ui->lineEdit_ID_Commande3_4->text().toFloat();
    QString etat;
    if(ui->radioButton_3->isChecked())
    {
        etat= ui->radioButton_3->text();
    }
    else if(ui->radioButton_4->isChecked())
    {
        etat= ui->radioButton_4->text();
    }
    bool test= tmpFacture.modifier_facture(Ref_Facture,ID_Commande,description,date,montant,etat);
    if(test)
    {
        ui->tableView->setModel(tmpFacture.afficher());
        QMessageBox::information(nullptr, QObject::tr("Modifier une facture"),
                  QObject::tr("facture modifié.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
     {   QMessageBox::critical(nullptr, QObject::tr("Modifier une facture"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
}


void MainWindow::on_pb_supprimer_facture_clicked()
{
    {
        int Ref_Facture = ui->lineEdit_Reference_9->text().toInt();
        bool test=tmpFacture.supprimer(Ref_Facture);
        if(test)
        {ui->tableView->setModel(tmpFacture.afficher());//refresh
            QMessageBox::information(nullptr, QObject::tr("Supprimer une facture"),
                        QObject::tr("facture supprimée.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Supprimer une facture"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
    }



}

void MainWindow::on_lineEdit_recherche_textChanged(const QString &arg1)
{
    QString Ref_Facture= ui->lineEdit_recherche->text();

        ui->tableView_2->setModel(tmpFacture.afficher_recherche(Ref_Facture));
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    QString tri=ui->comboBox->currentText();
    if(tri=="")
        ui->tableView->setModel(tmpFacture.afficher());
    else if(tri=="En fonction de la Reference")
        ui->tableView->setModel(tmpFacture.afficher_tri_ref());
    else if(tri=="En fonction de la date")
        ui->tableView->setModel(tmpFacture.afficher_tri_date());
    else if(tri=="En fonction de l'etat")
        ui->tableView->setModel(tmpFacture.afficher_tri_etat());
}

void MainWindow::on_lineEdit_Reference_12_textChanged(const QString &arg1)
{
    QString Ref_Facture=ui->lineEdit_Reference_12->text();
    QSqlQuery gry;
    gry.prepare("select * from facture where REF_FACTURE='"+Ref_Facture+"'");
    if(gry.exec())
    {
        while (gry.next())
        {
         ui->lineEdit_Reference_11->setText(gry.value(1).toString());
         ui->lineEdit_ID_Fournisseur3_4->setText(gry.value(2).toString());
         ui->lineEdit_ID_Fournisseur3_5->setText(gry.value(3).toString());
         ui->lineEdit_ID_Commande3_4->setText(gry.value(4).toString());

        }
    }

}



/*********************************************************************************/


void MainWindow::on_Commander_3_clicked()
{
    int ID_Commande = ui->lineEdit_ID_Commande_3->text().toInt();
    int ID_Fournisseur= ui->lineEdit_ID_Fournisseur_3->text().toInt();
    QString CategorieP=  ui->comboBox_2->currentText();
    QString Produit= ui->lineEdit_Produit_3->text();
    float PrixU= ui->lineEdit_PrixU_3->text().toFloat();
    int Quantite = ui->lineEdit_Quantite_3->text().toInt();
  Commande e(ID_Commande,ID_Fournisseur,CategorieP,Produit,PrixU,Quantite);
  bool test=e.ajouter_commande();
  if(test)
{ui->TabCommandes_3->setModel(tmpCommande.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter une Commande"),
                  QObject::tr("Commande ajoutée.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}

  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter une Commande"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pb_supprimer_5_clicked()
{
    int ID_Commande = ui->lineEdit_SupprimerCommande->text().toInt();
    bool test=tmpCommande.supprimer_commande(ID_Commande);
    if(test)
    {ui->TabCommandes_3->setModel(tmpCommande.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer une Commande"),
                    QObject::tr("Commande supprimée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer une Commande"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}


void MainWindow::on_pb_modifier_commande_clicked()
{
    int ID_Commande = ui->lineEdit_modifierID_commande->text().toInt();
    int ID_Fournisseur= ui->lineEdit_modifierID_fournisseur->text().toInt();
    QString CategorieP=  ui->comboBox_3->currentText();
    QString Produit= ui->lineEdit_modifierProduit->text();
    float PrixU= ui->lineEdit_modifier_PrixU->text().toFloat();
    int Quantite = ui->lineEdit_modifier_quantite->text().toInt();

          bool test=tmpCommande.modifier_commande(ID_Commande,ID_Fournisseur,CategorieP,Produit,PrixU,Quantite);
          if(test)
            {ui->TabCommandes_3->setModel(tmpCommande.afficher());//refresh
                QMessageBox::information(nullptr, QObject::tr("Modifier une commande"),
                            QObject::tr("Donnée modifié.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

            }
            else
               { QMessageBox::critical(nullptr, QObject::tr("Modifier une commande"),
                            QObject::tr("Erreur !.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);}
}






void MainWindow::on_lineEdit_recherche_commande_textChanged(const QString &arg1)
{
    QString ID_Commande= ui->lineEdit_recherche_commande->text();

        ui->tableView_3->setModel(tmpCommande.afficher_recherche(ID_Commande));
}

void MainWindow::on_comboBox_4_currentTextChanged(const QString &arg1)
{
    QString tri=ui->comboBox_4->currentText();
    if(tri=="")
        ui->TabCommandes_3->setModel(tmpCommande.afficher());
    else if(tri=="En fonction de la quantité")
        ui->TabCommandes_3->setModel(tmpCommande.afficher_tri_quantite());
    else if(tri=="En fonction de la catégorie")
        ui->TabCommandes_3->setModel(tmpCommande.afficher_tri_categorie());
    else if(tri=="En fonction de la Reference")
        ui->TabCommandes_3->setModel(tmpCommande.afficher_tri_ref());
}

void MainWindow::on_lineEdit_modifierID_commande_textChanged(const QString &arg1)
{
    QString ID_COMMANDE=ui->lineEdit_modifierID_commande->text();
    QSqlQuery gry;
    gry.prepare("select * from tabcommande where ID_COMMANDE='"+ID_COMMANDE+"'");
    if(gry.exec())
    {
        while (gry.next())
        {
         ui->lineEdit_modifierID_fournisseur->setText(gry.value(1).toString());
         ui->lineEdit_modifierProduit->setText(gry.value(3).toString());
         ui->lineEdit_modifier_PrixU->setText(gry.value(4).toString());
         ui->lineEdit_modifier_quantite->setText(gry.value(5).toString());

        }
    }
}
