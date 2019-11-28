#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "toutes_les_fonctions.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView_c->setModel(tmpcaisse.Afficher());
    ui->tableView_r->setModel(tmprayon.Afficher());
    ui->tableView_p->setModel(tmpproduit.Afficher());
    ui->tableView_aff_t->setModel(tmpticket.Afficher());//refresh
    ui->tableView_p_v->setModel(tmpproduit_v.Afficher_PV());//refresh



    ui->comboBox_Type->addItem("Marche frais");
    ui->comboBox_Type->addItem("Alimentaire");
    ui->comboBox_Type->addItem("Hygiene/Beaute");
    ui->comboBox_Type->addItem("Maison/Jardin");
    ui->comboBox_Type->addItem("H.T/Electro");
    ui->comboBox_Type->addItem("Textile");

    ui->comboBox_Type_3->addItem("Marche frais");
    ui->comboBox_Type_3->addItem("Alimentaire");
    ui->comboBox_Type_3->addItem("Hygiene/Beaute");
    ui->comboBox_Type_3->addItem("Maison/Jardin");
    ui->comboBox_Type_3->addItem("H.T/Electro");
    ui->comboBox_Type_3->addItem("Textile");

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_Ajouter_c_clicked()
{
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("C:/Users/Occurence/Desktop/Swoosh sound effect.mp3"));
    player->setVolume(50);
    player->play();
    int id = ui->lineEdit_ID->text().toInt();
    QString etat;
    if(ui->radioButton_fonc_2->isChecked())
    {
        etat= ui->radioButton_fonc_2->text();
    }
    else if(ui->radioButton_rep_2->isChecked())
    {
        etat= ui->radioButton_rep_2->text();
    }
    else if(ui->radioButton_panne_2->isChecked())
    {
        etat= ui->radioButton_panne_2->text();
    }

    Caisse c(id,etat);

    bool test=c.Ajouter();
    if(test)
    {
        ui->tableView_c->setModel(tmpcaisse.Afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Ajouter une caisse"),
                  QObject::tr("Caisse ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Ajouter une caisse"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

    player->stop();
}

void MainWindow::on_pushButton_Supprimer_c_clicked()
{
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("C:/Users/Occurence/Desktop/Swoosh sound effect.mp3"));
    player->setVolume(50);
    player->play();

    int id = ui->lineEdit_ID_s->text().toInt();
    bool test=tmpcaisse.Supprimer(id);
    if(test)
    {ui->tableView_c->setModel(tmpcaisse.Afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer une caisse"),
                    QObject::tr("Caisse supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer une caisse"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
     player->stop();
}

void MainWindow::on_pushButton_Ajouter_r_clicked()
{
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("C:/Users/Occurence/Desktop/Swoosh sound effect.mp3"));
    player->setVolume(50);
    player->play();
    int id = ui->lineEdit_Num->text().toInt();
    QString type= ui->comboBox_Type->currentText();

    Rayon r(id,type);
    bool test=r.Ajouter();
    if(test)
    {
        ui->tableView_r->setModel(tmprayon.Afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Ajouter un rayon"),
                  QObject::tr("Rayon ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Ajouter un rayon"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
    player->stop();
}

void MainWindow::on_pushButton_Supprimer_r_clicked()
{
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("C:/Users/Occurence/Desktop/Swoosh sound effect.mp3"));
    player->setVolume(50);
    player->play();
    int id = ui->lineEdit_Num_s->text().toInt();
    bool test=tmprayon.Supprimer(id);
    if(test)
    {ui->tableView_r->setModel(tmprayon.Afficher());//refresh
        ui->tableView_p->setModel(tmpproduit.Afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer un rayon"),
                    QObject::tr("Rayon supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un rayon"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    player->stop();
}

void MainWindow::on_pushButton_Ajouter_p_clicked()
{
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("C:/Users/Occurence/Desktop/Swoosh sound effect.mp3"));
    player->setVolume(50);
    player->play();
    int id = ui->lineEdit_IDp->text().toInt();
    QString nom= ui->lineEdit_nom->text();
    int qant = ui->lineEdit_qant->text().toInt();
    float prix = ui->lineEdit_prix->text().toFloat();
    QString dle= ui->lineEdit_DLE->text();
    int num = ui->lineEdit_NumR->text().toInt();

    Produit p(id,nom,qant,prix,dle,num);

    bool test=p.Ajouter();
    if(test)
    {
        ui->tableView_p->setModel(tmpproduit.Afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Ajouter un produit"),
                  QObject::tr("Produit ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Ajouter un produit"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
    player->stop();
}

void MainWindow::on_pushButton_Supprimer_p_clicked()
{
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("C:/Users/Occurence/Desktop/Swoosh sound effect.mp3"));
    player->setVolume(50);
    player->play();
    int id = ui->lineEdit_IDp_s->text().toInt();
    bool test=tmpproduit.Supprimer(id);
    if(test)
    {ui->tableView_p->setModel(tmpproduit.Afficher());//refresh
        ui->tableView_p_v->setModel(tmpproduit_v.Afficher_PV());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer un produit"),
                    QObject::tr("Produit supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un produit"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    player->stop();
}

void MainWindow::on_pushButton_Modifier_c_clicked()
{
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("C:/Users/Occurence/Desktop/Swoosh sound effect.mp3"));
    player->setVolume(50);
    player->play();

    int id = ui->lineEdit_ID_2->text().toInt();
    QString etat;
    if(ui->radioButton_fonc->isChecked())
    {
        etat= ui->radioButton_fonc->text();
    }
    else if(ui->radioButton_rep->isChecked())
    {
        etat= ui->radioButton_rep->text();
    }
    else if(ui->radioButton_panne->isChecked())
    {
        etat= ui->radioButton_panne->text();
    }

    bool test=tmpcaisse.Modifier(id,etat);
    if(test)
    {ui->tableView_c->setModel(tmpcaisse.Afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Modifier une caisse"),
                    QObject::tr("Caisse modifier.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Modifier une caisse"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    player->stop();

}

void MainWindow::on_pushButton_Modifier_p_clicked()
{
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("C:/Users/Occurence/Desktop/Swoosh sound effect.mp3"));
    player->setVolume(50);
    player->play();

    int id = ui->lineEdit_IDp_2->text().toInt();
    QString nom= ui->lineEdit_nom_2->text();
    int qant = ui->lineEdit_qant_2->text().toInt();
    float prix = ui->lineEdit_prix_2->text().toFloat();
    QString dle= ui->lineEdit_DLE_2->text();
    int num = ui->lineEdit_NumR_2->text().toInt();
    bool test=tmpproduit.Modifier(id,nom,qant,prix,dle,num);
    if(test)
    {ui->tableView_p->setModel(tmpproduit.Afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Modifier un produit"),
                    QObject::tr("Produit modifier.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Modifier un produit"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    player->stop();

}

void MainWindow::on_pushButton_Modifier_r_clicked()
{
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("C:/Users/Occurence/Desktop/Swoosh sound effect.mp3"));
    player->setVolume(50);
    player->play();

    int id = ui->lineEdit_Num_3->text().toInt();
    QString type= ui->comboBox_Type_3->currentText();
    bool test=tmprayon.Modifier(id,type);
    if(test)
    {ui->tableView_r->setModel(tmprayon.Afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Modifier un rayon"),
                    QObject::tr("Rayon modifier.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Modifier un rayon"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    player->stop();
}



void MainWindow::on_pushButton_Ajouter_t_clicked()
{
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("C:/Users/Occurence/Desktop/Swoosh sound effect.mp3"));
    player->setVolume(50);
    player->play();

    int num = ui->lineEdit_ID_t->text().toInt();
    QString date= ui->lineEdit_Date->text();

    Ticket_caisse t(num,date);
    bool test = t.Ajouter();


    if(test)
    {
        ui->tableView_aff_t->setModel(tmpticket.Afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Ajouter un ticket"),
                  QObject::tr("ticket ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("Ajouter un ticket"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
    }
    player->stop();
}

void MainWindow::on_pushButton_supprimer_t_clicked()
{
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("C:/Users/Occurence/Desktop/Swoosh sound effect.mp3"));
    player->setVolume(50);
    player->play();

    int id = ui->lineEdit_IDt_s->text().toInt();
    bool test=tmpticket.Supprimer(id);
    if(test)
    {ui->tableView_aff_t->setModel(tmpticket.Afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer un ticket"),
                    QObject::tr("Ticket supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un ticket"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    player->stop();
}

void MainWindow::on_pushButton_Ajouter_t_4_clicked()
{
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("C:/Users/Occurence/Desktop/Swoosh sound effect.mp3"));
    player->setVolume(50);
    player->play();

    int id = ui->lineEdit_ID_t_r->text().toInt();
    int idp = ui->lineEdit_p_v_4->text().toInt();
    int quant= ui->lineEdit_quant_t_4->text().toInt();


    Produit_vendue pv(idp,quant,id);
    Produit p;
    Ticket_caisse t;
    bool test = pv.Ajouter_PV();
    bool test1 = p.Mise_a_jour_Qantitee(idp,quant);
    bool test2 = t.Mettre_a_jour_Ticket(idp,id,quant);


    if(test && test1 && test2)
    {
        ui->tableView_p_v->setModel(tmpproduit_v.Afficher_PV());//refresh
        ui->tableView_p->setModel(tmpproduit.Afficher());
        ui->tableView_aff_t->setModel(tmpticket.Afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Ajouter un produit au ticket"),
                  QObject::tr("Produit ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("Ajouter un produit au ticket"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
    }


    player->stop();
}

void MainWindow::on_pushButton_recherche_2_clicked()
{
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("C:/Users/Occurence/Desktop/Swoosh sound effect.mp3"));
    player->setVolume(50);
    player->play();

    QString id= ui->lineEdit_recherche_2->text();


        ui->tableView_p->setModel(tmpproduit.Afficher_recherche(id));//refresh

    player->stop();

}


void MainWindow::on_pushButton_recherche_clicked()
{
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("C:/Users/Occurence/Desktop/Swoosh sound effect.mp3"));
    player->setVolume(50);
    player->play();

    QString id= ui->lineEdit_recherche->text();


        ui->tableView_p_v->setModel(tmpproduit_v.Afficher_PV_recherche(id));//refresh

    player->stop();
}

void MainWindow::on_pushButton_recherche_3_clicked()
{
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("C:/Users/Occurence/Desktop/Swoosh sound effect.mp3"));
    player->setVolume(50);
    player->play();

    QString id= ui->lineEdit_recherche_3->text();


        ui->tableView_c->setModel(tmpcaisse.Afficher_recherche(id));
     player->stop();
}

void MainWindow::on_pushButton_recherche_4_clicked()
{
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("C:/Users/Occurence/Desktop/Swoosh sound effect.mp3"));
    player->setVolume(50);
    player->play();

    QString id= ui->lineEdit_recherche_4->text();


    ui->tableView_r->setModel(tmprayon.Afficher_recherche(id));

    player->stop();
}

void MainWindow::on_pushButton_recherche_5_clicked()
{
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("C:/Users/Occurence/Desktop/Swoosh sound effect.mp3"));
    player->setVolume(50);
    player->play();

    QString id= ui->lineEdit_recherche_5->text();


    ui->tableView_aff_t->setModel(tmpticket.Afficher_recherche(id));

    player->stop();

}
