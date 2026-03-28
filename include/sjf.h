#ifndef SJF_H
#define SJF_H

#include "process.h"

/**
 * @brief Exécute l'algorithme d'ordonnancement SJF.
 *
 * Trie les processus par date d'arrivée puis les exécute dans cet ordre.
 * Remplit les champs start_time, finish_time, waiting_time,
 * turnaround_time et response_time de chaque processus.
 *
 * @param processes  Tableau de processus à ordonnancer
 * @param n          Nombre de processus dans le tableau
 */
void sjf_schedule(Process processes[], int n);

#endif /* SJF_H */
