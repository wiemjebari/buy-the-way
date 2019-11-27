#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include"connexion.h"
#include "facture.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_Commander_3_clicked();

    void on_pb_supprimer_5_clicked();

    void on_pb_modifier_commande_clicked();

    void on_pb_ajouter_facture_clicked();

    void on_pushButton_modifier_facture_clicked();

    void on_pb_supprimer_facture_clicked();

    void on_lineEdit_recherche_textChanged(const QString &arg1);

    void on_lineEdit_recherche_commande_textChanged(const QString &arg1);

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_lineEdit_Reference_12_textChanged(const QString &arg1);

    void on_comboBox_4_currentTextChanged(const QString &arg1);

    void on_lineEdit_modifierID_commande_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    Facture tmpFacture;
    Commande tmpCommande;
};
#endif // MAINWINDOW_H
