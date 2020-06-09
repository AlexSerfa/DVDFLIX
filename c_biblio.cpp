#include "c_biblio.h"
#include <C_censure.h>
#include <C_minifilm.h>

C_biblio::C_biblio(QObject *parent) : QObject(parent)
{

}

C_biblio::~C_biblio()
{
    delete this;
}

void C_biblio::addFilmLocal(int index, C_miniFilm *film)
{
    min1[index] = film;
}

C_miniFilm * C_biblio::getFilmLocal(int index)
{

    return min1[index];
}

void C_biblio::addFilmOnline(int index, C_miniFilm *film)
{
    min2[index] = film;
}

C_miniFilm * C_biblio::getFilmOnline(int index)
{
    return min2[index];
}

/**
 * @fn videMinifilm()
 * @author: Mercier Laurent
 * @date 05/05/2020
 * @brief vide le tableau des minifilm locaux
 *
 */
void C_biblio::videMinifilm()
{
    //on vide le tableau de minifilm de resultat en local
    for(int i =0;i<150;i++){
        if(min1[i]){
            min1[i]->~C_miniFilm();
        }
    }
    for(int i =0;i<150;i++){
          if(min2[i]){
              min2[i]->~C_miniFilm();
          }
      }
}


