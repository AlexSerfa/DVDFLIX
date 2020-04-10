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

private:
    Ui::C_miniFilm *ui;
};

#endif // C_MINIFILM_H
