#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "toutes_les_fonctions.h"
#include <QMainWindow>
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_pushButton_Ajouter_c_clicked();

    void on_pushButton_Supprimer_c_clicked();

    void on_pushButton_Ajouter_r_clicked();

    void on_pushButton_Supprimer_r_clicked();

    void on_pushButton_Ajouter_p_clicked();

    void on_pushButton_Supprimer_p_clicked();

    void on_pushButton_Modifier_c_clicked();

    void on_pushButton_Modifier_p_clicked();

    void on_pushButton_Modifier_r_clicked();

    void on_pushButton_Ajouter_t_clicked();

    void on_pushButton_supprimer_t_clicked();

    void on_pushButton_Ajouter_t_4_clicked();

    void on_pushButton_recherche_2_clicked();

    void on_pushButton_recherche_clicked();

    void on_pushButton_recherche_3_clicked();

    void on_pushButton_recherche_4_clicked();

    void on_pushButton_recherche_5_clicked();

private:
    Ui::MainWindow *ui;
    QMediaPlayer * player;
    Caisse tmpcaisse;
    Rayon tmprayon;
    Produit tmpproduit;
    Produit_vendue tmpproduit_v;
    Ticket_caisse tmpticket;
};
#endif // MAINWINDOW_H
