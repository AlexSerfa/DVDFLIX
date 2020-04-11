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
     * @brief
     *
     * @param parent
     */
    explicit C_miniFilm(QWidget *parent = nullptr);
    /**
     * @brief
     *
     */
    ~C_miniFilm();


    /**
     * @brief
     *
     * @param QString
     */
    void setTitre(QString);
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

private slots:

    /**
     * @brief
     *
     */
    void on_btn_details_clicked();

private:
    Ui::C_miniFilm *ui; /**< TODO: describe */
    QString m_Affiche; /**< TODO: describe */
};

#endif // C_MINIFILM_H
