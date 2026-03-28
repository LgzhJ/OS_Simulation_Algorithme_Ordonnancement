/**
 * @file scheduler.h
 * @brief Interface commune à tous les algorithmes d'ordonnancement.
 *
 * Pour ajouter un nouvel algorithme, il suffit de :
 *   1. Créer un fichier mon_algo.c / mon_algo.h
 *   2. Implémenter une fonction respectant le prototype ci-dessous
 *   3. L'appeler depuis main.c
 *
 * @authors NOM1 (xx%), NOM2 (xx%), NOM3 (xx%)
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"

/**
 * @brief Type pointeur vers une fonction d'ordonnancement.
 *
 * Chaque algorithme doit respecter ce prototype :
 * @param processes  Tableau de processus à ordonnancer
 * @param n          Nombre de processus
 */
typedef void (*SchedulerFunc)(Process processes[], int n);

#endif /* SCHEDULER_H */
