#ifndef C_OPTIONS_H
#define C_OPTIONS_H

#include <QDialog>
#include "C_mysqlmanager.h"
#include "c_bddsecu.h"

namespace Ui {
class C_options;
}

class C_options : public QDialog
{
    Q_OBJECT

public:
    explicit C_options(QWidget *parent = nullptr);
    ~C_options();


private slots:
    void on_pushButton_clicked();


    void on_pushButton_modifier_clicked();

    void on_pushButton_cheminTempo_clicked();

    void on_pushButton_cheminFixe_clicked();

public slots:

    /**
     * @brief
     *
     */
    void infoConnection();
    /**
     * @brief
     *
     */
    void update(QString nomUt, QString pass, QString adr, int port);

    void infoDeconnection();
private:
    Ui::C_options *ui;
    C_MySQLManager *sql;
    QSqlDatabase upd_secu;
    QSqlDatabase upd_param;
    C_bddSecu secu;

};

#endif // C_OPTIONS_H
