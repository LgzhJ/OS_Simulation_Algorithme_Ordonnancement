/**
 * @file rr.h
 * @brief Déclaration de l'algorithme d'ordonnancement Round Robin.
 *
 * Le Round Robin attribue à chaque processus un quantum de temps fixe.
 * Si le processus n'a pas fini à la fin de son quantum, il est replacé
 * en fin de file d'attente. L'algorithme est donc préemptif.
 *
 * @authors NOM1 (xx%), NOM2 (xx%), NOM3 (xx%)
 */

#ifndef RR_H
#define RR_H

#include "process.h"

/**
 * @brief Exécute l'algorithme d'ordonnancement Round Robin.
 *
 * Remplit les champs start_time, finish_time, waiting_time,
 * turnaround_time et response_time de chaque processus.
 *
 * @param processes  Tableau de processus à ordonnancer
 * @param n          Nombre de processus dans le tableau
 * @param quantum    Durée du quantum de temps (ms)
 */
void rr_schedule(Process processes[], int n, int quantum);

#endif /* RR_H */
