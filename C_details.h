#ifndef C_DETAILS_H
#define C_DETAILS_H

#include <QWidget>

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
    void addBackdropPicture(QPixmap( picture));
    void addBackdrop(QString backdrop);
    void addAdult(QString adult);
    void addNote(QString note);
    void addVote(QString vote);
    void addGenre(QString genre);
    void addDateReal(QString date);
    void addIdDistant(int id);
    void addIdLocal(int id);
    void addResum(QString resum);
    void addVideo(QString video);


private slots:
    void on_btn_modifier_clicked();

private:
    Ui::C_details *ui;
    QString m_affiche;
    QString m_backdrop;
    QVector<QString> m_genres[10];
    QString m_video;
};

#endif // C_DETAILS_H
