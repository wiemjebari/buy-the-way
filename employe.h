#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QDialog>
#include"ge.h"

namespace Ui {
class employe;
}

class employe : public QDialog
{
    Q_OBJECT

public:
    explicit employe(QWidget *parent = nullptr);
    ~employe();

private slots:
    void on_pb_ajouter_clicked();


    void on_pb_supprimer_clicked();

    void on_pb_recherche_clicked();

    void on_pb_modifier_clicked();











private:
    Ui::employe *ui;
    ge tmpemploye;
};

#endif // EMPLOYE_H
