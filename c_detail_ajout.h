#ifndef C_DETAIL_AJOUT_H
#define C_DETAIL_AJOUT_H

#include <QDialog>
#include <QTextEdit>

namespace Ui {
class C_detail_ajout;
}

class C_detail_ajout : public QDialog
{
    Q_OBJECT

public:
    explicit C_detail_ajout(QWidget *parent = nullptr, QString titre="",QString ID_loc = "", QString titreFilm_1="", QTextEdit *nom=nullptr);
    ~C_detail_ajout();

private slots:
    void on_btn_enregistrer_detail_clicked();

private:
    Ui::C_detail_ajout *ui;
    QTextEdit *m_nom;
};

#endif // C_DETAIL_AJOUT_H
