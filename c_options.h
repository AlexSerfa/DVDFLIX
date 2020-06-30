#ifndef C_OPTIONS_H
#define C_OPTIONS_H

#include <QDialog>
#include <QLineEdit>
#include "C_mysqlmanager.h"
#include "c_bddsecu.h"


namespace Ui {
class C_options;
}

class C_options : public QDialog
{
    Q_OBJECT

public:
    explicit C_options(QWidget *parent = nullptr, QString _dvdAdr="", QString _dvdPass="",
                       QString _dvdUser="",int _dvdport=0, QString code="",C_MySQLManager *_sql=nullptr);
    ~C_options();


    QString getDvdAdr() const;
    void setDvdAdr(const QString value);

    QString getDvdPass() const;
    void setDvdPass(const QString value);

    QString getDvdUser() const;
    void setDvdUser(const QString value);

    int getDvdport() const;
    void setDvdport(int value);

    QString getHardPath() const;
    void setHardPath(const QString hardPath);

    QString getTempoPath() const;
    void setTempoPath(const QString tempoPath);

    QString getCodeParental() const;
    void setCodeParental(const QString codeParental);



    void setSql(C_MySQLManager *value);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_modifier_clicked();

    void on_pushButton_cheminTempo_clicked();

    void on_pushButton_cheminFixe_clicked();

    void on_btn_enr_CP_clicked();

    void on_btn_enr_BD_dvd_clicked();

public slots:

    /**
     * @brief
     *
     */
    void update(QString nomUt, QString pass, QString adr, int port);

private:
    Ui::C_options *ui;
    C_MySQLManager *sql;
    QSqlDatabase upd_secu;
    QSqlDatabase upd_param;
    C_bddSecu secu;
    QString dvdAdr;
    QString dvdPass;
    QString dvdUser;
    int dvdport;
    QString m_hardPath;
    QString m_tempoPath;
    QString m_codeParentalLu;
    QString m_codeParental;
    QString m_nouveauCodeParental;
    void TexteChemin(QLineEdit *champTexte);
    void LectureInfoDB();
    void read();
};

#endif // C_OPTIONS_H
