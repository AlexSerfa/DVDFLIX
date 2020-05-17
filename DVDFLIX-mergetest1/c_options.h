#ifndef C_OPTIONS_H
#define C_OPTIONS_H

#include <QDialog>
#include "C_mysqlmanager.h"

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
    void infoDeconnection();
private:
    Ui::C_options *ui;
    C_MySQLManager *sql;
};

#endif // C_OPTIONS_H
