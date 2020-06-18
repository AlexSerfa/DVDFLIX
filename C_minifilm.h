#ifndef C_MINIFILM_H
#define C_MINIFILM_H

#include <QWidget>


namespace Ui {
class C_miniFilm;
}

class C_miniFilm : public QWidget
{
    Q_OBJECT

public:

    explicit C_miniFilm(QWidget *parent = nullptr);
    ~C_miniFilm();
    void setTitre(QString);
    QString getTitre();
    void setAffiche(QString);
    void setAnnee(int);
    QString getAffiche();
    void addAffiche();
    QString getIcone();
    void setIcone(QString);
    void addIcone();
    QString getNote() const;
    void setNote(QString note);
    void setAnnee(QString annee);
    bool getAdult() const;
    void setAdult(bool adult);
    QString getBackdrop() const;
    void setBackdrop(const QString &backdrop);
    void setGenres(int index ,int genre);
    int getGenre(int index);
    void setGenre(QString);
    int getIdLocal() const;
    void setIdLocal(int idLocal);
    int getId_online() const;
    void setId_online(int id_online);
    QString getLanguage() const;
    void setLanguage(const QString &language);
    QString getTitreOri() const;
    void setTitreOri(const QString &titreOri);
    QString getResum() const;
    void setResum(const QString &resum);
    QString getPop() const;
    void setPop(QString pop);
    QString getRelease() const;
    void setRelease(const QString &release);
    QString getVideo() const;
    void setVideo(const QString &video);
    QString getVote() const;
    void setVote(const QString &vote);
    QString getDateEnr() const;
    void setDateEnr(const QString &DateEnr);
    void setLocal(bool value);
    bool getLocal() const;
    void setStockage(QString stock);
    QString getStockage();


public slots:
    void modification();

signals:
    void modifier();

private slots:

    void on_btn_details_clicked();

private:

    Ui::C_miniFilm *ui; /**< UI de la classe */
    QString m_Affiche; /**< chemin du fichier de l'affiche du film */
    QString m_Icone;
    QString m_notation; /**< note obtenue par le film */
    int  m_idLocal; /**< identifiant dans la database locale */
    bool m_adult;/**< fil madulte ou non */
    QString m_backdrop;/**< face arrière de la jacquette */
    int m_genres[10]= {0};/**< genres du film */
    int m_id_online; /**< Identificateur en ligne */
    QString m_language; /**< language original */
    QString m_titreOri; /**< titre original */
    QString m_titre; /**< titre du film */
    QString m_resum; /**< résumé du film */
    QString m_pop; /**< popularité */
    QString m_release;/**< date de réalisation */
    QString m_video; /**< lien vers le trailer */
    QString m_vote; /**< nombre de vote */
    QString m_date_enregistrement; /**< date d'enregistrement dans la base de données */
    bool m_local; /**< flag de film deja possédé*/
    QString m_stockage;/**< lieu de stockage du film */


};

#endif // C_MINIFILM_H
