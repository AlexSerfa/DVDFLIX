#ifndef C_DETAILS_H
#define C_DETAILS_H

#include <QWidget>
#include <C_mysqlmanager.h>
#include <C_minifilm.h>
#include <c_bddsecu.h>


namespace Ui {
class C_details;
}

class C_details : public QWidget
{
    Q_OBJECT

public:
    explicit C_details(QWidget *parent = nullptr);
    ~C_details();

    void addAffichePicture(QPixmap( picture));
    void addAffiche(QString affiche);
    void addTitre(QString titre);
    void addTitreOri(QString titreOri);
    void addLanguage(QString language);
    void addBackdrop(QString backdrop);
    void addAdult(bool value);
    void addNote(QString note);
    void addVote(QString vote);
    void addGenre(QString genre);
    void addDateReal(QString date);
    void addIdDistant(int id);
    void addIdLocal(int id);
    void addResum(QString resum);
    void addVideo(QString video);
    void addDispo(QString icone);
    void setLocal(bool value);
    void setFilm(C_miniFilm &film);
    void listStockage();
    void idLocalDetail();


    C_miniFilm & getFilm();
    QMainWindow *getMain() const;
    void setMain(QMainWindow *main);

public slots:
    void modification();
signals:
    void modifier();
private slots:
    void on_btn_modifier_clicked();
    void on_btn_enregistrer_clicked();
    void on_cbb_stockage_currentIndexChanged(const QString &arg1);
    void on_chk_adult_stateChanged(int arg1);
    void on_btn_acteur_clicked();
    void on_btn_metteurEnScene_clicked();
    void on_btn_realisateur_clicked();
    void on_btn_producteur_clicked();
    void on_btn_suppression_clicked();

private:
    C_MySQLManager *sql;     /*!< objet gérant la partie Mysql */
    Ui::C_details *ui;
    QString m_affiche;
    QString m_backdrop;
    QVector<QString> m_genres[10];
    QString m_video;
    bool m_local;
    bool m_modif=false;
    C_miniFilm *m_film;
    QString idMondial;

};

#endif // C_DETAILS_H
