#ifndef C_CENSURE_H
#define C_CENSURE_H

#include <QWidget>

namespace Ui {
class C_Censure;
}

class C_Censure : public QWidget
{
    Q_OBJECT

public:
    explicit C_Censure(QWidget *parent = nullptr);
    ~C_Censure();

private:
    Ui::C_Censure *ui;
};

#endif // C_CENSURE_H
