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
    void setGenre(QString);
    void setAffiche(QString);
    void setAnnee(int);
    QString getAffiche();

private slots:

    void on_btn_details_clicked();

private:
    Ui::C_miniFilm *ui;
    QString m_Affiche;
};

#endif // C_MINIFILM_H
