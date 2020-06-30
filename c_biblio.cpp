#include "c_biblio.h"
#include <C_censure.h>
#include <C_minifilm.h>

/**
 * @author: Mercier Laurent
 * @date 29/06/2020
 * @brief  constructeur
 *
 */
C_biblio::C_biblio(QObject *parent) : QObject(parent)
{

}
/**
 * @author: Mercier Laurent
 * @date 29/06/2020
 * @brief  destructeur
 *
 */
C_biblio::~C_biblio()
{
    delete this;
}

/**
 * @author: Mercier Laurent
 * @date 29/06/2020
 * @brief  ajoute un film local au tableau min1
 *
 */
void C_biblio::addFilmLocal(int index, C_miniFilm *film)
{
    min1[index] = film;
}
/**
 * @author: Mercier Laurent
 * @date 29/06/2020
 * @brief  retourn un film local du tableau min1
 *
 */
C_miniFilm * C_biblio::getFilmLocal(int index)
{
    return min1[index];
}
/**
 * @author: Mercier Laurent
 * @date 29/06/2020
 * @brief  ajoute un film local au tableau min2
 *
 */
void C_biblio::addFilmOnline(int index, C_miniFilm *film)
{
    min2[index] = film;
}
/**
 * @author: Mercier Laurent
 * @date 29/06/2020
 * @brief  retourn un film local du tableau min2
 *
 */
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


