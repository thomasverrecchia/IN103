#ifndef __LOAD_MAP_H__
#define __LOAD_MAP_H__

#include <stdbool.h>
#include "station.h"

/** Construit un graphe � partir de la desription textuelle se trouvant
    dans le fichier dont le nom est pass� en argument. */
bool load_map (char *name) ;

/** Retourne la liste cha�n�e de toutes les stations (noeuds) du graphe
    pr�alablement construit par un appel � load_map. */
struct stations_list_t* get_all_stations (void) ;

#endif
