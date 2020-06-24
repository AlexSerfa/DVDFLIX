#ifndef C_BIBLIO_H
#define C_BIBLIO_H

#include <C_minifilm.h>
#include <C_censure.h>
#include <QObject>

class C_biblio : public QObject
{
    Q_OBJECT
public:
    explicit C_biblio(QObject *parent = nullptr);
    ~C_biblio();

    void addFilmLocal(int index, C_miniFilm *film);
    C_miniFilm* getFilmLocal(int index);
    void addFilmOnline(int index,C_miniFilm *film);
    C_miniFilm* getFilmOnline(int index);
    void videMinifilm();

signals:

private:
    C_miniFilm *min1[150];  /*!< collection de minifiche après une recherche d'un film en local*/
    C_miniFilm *min2[150];   /*!< collection de minifiche après une recherche d'un film en ligne*/
};

#endif // C_BIBLIO_H
