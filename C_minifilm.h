#ifndef C_MINIFILM_H
#define C_MINIFILM_H

#include <QWidget>

namespace Ui {
class C_miniFilm;
}

/**
 * @brief
 *
 */
class C_miniFilm : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief constructeur
     *
     * @param parent
     */
    explicit C_miniFilm(QWidget *parent = nullptr);
    /**
     * @brief destructeur
     *
     */
    ~C_miniFilm();


    /**
     * @brief
     *
     * @param QString
     */
    void setTitre(QString);
    QString getTitre();
    /**
     * @brief
     *
     * @param QString
     */
    void setGenre(QString);
    /**
     * @brief
     *
     * @param QString
     */
    void setAffiche(QString);
    /**
     * @brief
     *
     * @param int
     */
    void setAnnee(int);
    /**
     * @brief
     *
     * @return QString
     */
    QString getAffiche();
    void addAffiche();

    /**
     * @brief
     *
     * @return QString
     */
    QString getNote() const;
    /**
     * @brief
     *
     * @param note
     */
    void setNote(QString note);

    /**
     * @brief
     *
     * @param annee
     */
    void setAnnee(QString annee);

    /**
     * @brief
     *
     * @return bool
     */
    bool getAdult() const;
    /**
     * @brief
     *
     * @param adult
     */
    void setAdult(bool adult);

    /**
     * @brief
     *
     * @return QString
     */
    QString getBackdrop() const;
    /**
     * @brief
     *
     * @param backdrop
     */
    void setBackdrop(const QString &backdrop);

    /**
     * @brief
     *
     * @param index
     * @param genre
     */
    void setGenres(int index ,int genre);
    /**
     * @brief
     *
     * @param index
     * @return int
     */
    int getGenre(int index);


    /**
     * @brief
     *
     * @return int
     */
    int getIdLocal() const;
    /**
     * @brief
     *
     * @param idLocal
     */
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

private slots:

    /**
     * @brief
     *
     */
    void on_btn_details_clicked();

private:
    Ui::C_miniFilm *ui; /**< UI de la classeTODO: describe */
    QString m_Affiche; /**< nom du fichier de l'affiche du film */
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



};

#endif // C_MINIFILM_H
