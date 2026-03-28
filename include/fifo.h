/**
 * @file fifo.h
 * @brief Déclaration de l'algorithme d'ordonnancement FIFO (FCFS).
 *
 * L'algorithme FIFO (First In, First Out) exécute les processus dans
 * l'ordre de leur arrivée. Il est non-préemptif : un processus s'exécute
 * jusqu'à la fin de son cycle CPU avant de libérer le processeur.
 * Les cycles d'E/S sont considérés comme parallélisés (ils ne bloquent
 * pas le CPU).
 *
 * @authors NOM1 (xx%), NOM2 (xx%), NOM3 (xx%)
 */

#ifndef FIFO_H
#define FIFO_H

#include "process.h"

/**
 * @brief Exécute l'algorithme d'ordonnancement FIFO.
 *
 * Trie les processus par date d'arrivée puis les exécute dans cet ordre.
 * Remplit les champs start_time, finish_time, waiting_time,
 * turnaround_time et response_time de chaque processus.
 *
 * @param processes  Tableau de processus à ordonnancer
 * @param n          Nombre de processus dans le tableau
 */
void fifo_schedule(Process processes[], int n);

#endif /* FIFO_H */
