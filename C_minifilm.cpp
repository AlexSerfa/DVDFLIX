#include "C_minifilm.h"
#include "ui_C_minifilm.h"

C_miniFilm::C_miniFilm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::C_miniFilm)
{
    ui->setupUi(this);
}

C_miniFilm::~C_miniFilm()
{
    delete ui;
}
