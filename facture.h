class Facture
{public:
    Facture();
    Facture(int,int,QString,QString,float,QString);
    int get_Ref_Facture();
    int get_ID_Commande();
    int get_montant();
    QString get_description();
    QString get_date();
    QString get_etat();
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficher_recherche(QString);
    QSqlQueryModel * afficher_tri_date();
    QSqlQueryModel * afficher_tri_ref();
    QSqlQueryModel * afficher_tri_etat();
    bool supprimer(int);
    bool modifier_facture(int,int,QString,QString,float,QString);
private:
   int Ref_Facture, ID_Commande;
   float montant;
   QString description,etat,date;
};
class Commande
{public:
    Commande();
    Commande(int,int,QString,QString,float,int,float);
    QString get_Categorie();
    QString get_Produit();
    int get_ID_Commande();
    int get_ID_Founisseur();
    int get_Quantite();
    float get_Prix();
    //float get_Total();
    bool ajouter_commande();
    QSqlQueryModel * afficher();
    bool supprimer_commande(int);
    bool modifier_commande(int,int,QString,QString,float,int,float);
    bool rechercher_commande(int);
    QSqlQueryModel * afficher_recherche(QString);
    QSqlQueryModel * afficher_tri_ref();
    QSqlQueryModel * afficher_tri_categorie();
    QSqlQueryModel * afficher_tri_quantite();
    float calcul_total;

private:
    QString CategorieP,Produit;
    int ID_Commande,ID_Fournisseur,Quantite;
    float PrixU,total;
};
/*******************************************************************/
class Livraison
{public:
    Livraison();
    Livraison(int,int,int,int,QString,QString,QString);
    int get_Ref_Fournisseur();
    int get_id_livraison();
    int get_ID_Commande();
    int get_position();
    QString get_heure_livraison();
    QString get_date_livraison();
    QString get_agent_responsable();
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficher_recherche(QString);
    QSqlQueryModel * afficher_tri_id_livraison();
    QSqlQueryModel * afficher_tri_Ref_Fournisseur();
    QSqlQueryModel * afficher_tri_position_livraison();
    QSqlQueryModel * afficher_tri_date_livraison();

    bool supprimer(int);
    bool modifier_livraison(int,int,int,int,QString,QString,QString);
private:
   int id_livraison,Ref_Fournisseur, ID_Commande,position_livraison;
   QString heure_livraison,date_livraison,agent_responsable;
};
/*******************************************************************/
class Recu
{public:
    Recu();
    Recu(int,int,QString);
    int get_Num_Recu();
    int get_Ref_Facture();
    QString get_etat();
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficher_recherche(QString);
    QSqlQueryModel * afficher_tri_num();
    QSqlQueryModel * afficher_tri_ref();
    QSqlQueryModel * afficher_tri_etat();
    bool supprimer(int);
private:
   int Num_Recu, Ref_Facture;
   QString etat;
};



namespace Ui {
class facture;
}

class QSerialPort;

class facture: public QMainWindow
{
    Q_OBJECT

public:
   explicit facture(QWidget *parent = nullptr);
    ~facture();
    void comboBox_commandeMarque();
    void comboBox_5Marque();

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



    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton__clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_ajouter_livraison_clicked();

    void on_pushButton_modifier_clicked();

    void on_pushButton_supprimer_clicked();

    void on_lineEdit_rechercher_livraison_textChanged(const QString &arg1);

    void on_comboBox_5_currentTextChanged(const QString &arg1);

    void on_lineEdit_livraison_ID_livraison_2_textChanged(const QString &arg1);

    void on_pushButton_modifier_2_clicked();

    void on_pb_ajouter_facture_2_clicked();

    void on_pb_supprimer_facture_2_clicked();

    void on_comboBox_6_editTextChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

void on_tableView_2_activated(const QModelIndex &index);

    void on_tableView_3_activated(const QModelIndex &index);

    void on_lineEdit_recherch_commande_textChanged(const QString &arg1);
    void  on_lineEdit_recherch_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QSerialPort *arduino;
    Facture tmpFacture;
    Commande tmpCommande;
    Livraison tmpLivraison;
    Recu tmpRecu;

};