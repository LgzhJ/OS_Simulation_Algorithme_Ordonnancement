/**
 * @file fifo.c
 * @brief Implémentation de l'algorithme d'ordonnancement FIFO (FCFS).
 *
 * @authors NOM1 (xx%), NOM2 (xx%), NOM3 (xx%)
 */

#include <stdio.h>
#include <stdlib.h>
#include "fifo.h"
#include "file.h"

/* -----------------------------------------------------------------------
 * Fonctions internes (static = non visibles hors de ce fichier)
 * ----------------------------------------------------------------------- */

/**
 * @brief Compare deux processus par leur date d'arrivée.
 *
 * Fonction de comparaison utilisée par qsort() pour trier les processus
 * dans l'ordre croissant des dates d'arrivée.
 *
 * @param a  Pointeur vers le premier processus
 * @param b  Pointeur vers le second processus
 * @return   Négatif si a arrive avant b, positif sinon, 0 si égalité
 */
static int compare_arrival(const void *a, const void *b)
{
    const Process *pa = (const Process *)a;
    const Process *pb = (const Process *)b;
    return pa->arrival_time - pb->arrival_time;
}

/* -----------------------------------------------------------------------
 * Implémentation publique
 * ----------------------------------------------------------------------- */

/**
 * @brief Exécute l'algorithme FIFO sur un tableau de processus.
 *
 * Principe :
 *   - Les processus sont triés par date d'arrivée puis placés dans une
 *     file d'attente (FileTQ) représentant la file prête du système.
 *   - Le CPU dépile les processus un par un et les exécute jusqu'à la
 *     fin de leur cycle CPU (algorithme non-préemptif).
 *   - Si le CPU est libre avant l'arrivée du prochain processus,
 *     il reste inactif (temps mort).
 *   - Les E/S sont parallélisées : elles n'empêchent pas le CPU
 *     d'exécuter d'autres processus.
 *
 * Formules utilisées :
 *   - start_time      = max(current_time, arrival_time)
 *   - finish_time     = start_time + cpu_burst
 *   - response_time   = start_time - arrival_time
 *   - turnaround_time = finish_time - arrival_time
 *   - waiting_time    = turnaround_time - cpu_burst
 *
 * @param processes  Tableau de processus à ordonnancer
 * @param n          Nombre de processus dans le tableau
 */
void fifo_schedule(Process processes[], int n)
{
    int current_time = 0; /* Horloge du simulateur (ms) */
    FileTQ file_prete;    /* File d'attente des processus prêts */
    Process p;            /* Processus en cours de traitement */

    /* Étape 1 : trier les processus par ordre d'arrivée */
    qsort(processes, n, sizeof(Process), compare_arrival);

    /* Étape 2 : placer tous les processus dans la file d'attente */
    file_init(&file_prete);
    for (int i = 0; i < n; i++) {
        file_enfiler(&file_prete, processes[i]);
    }

    /* Étape 3 : simuler l'exécution FIFO en vidant la file */
    int i = 0;
    while (!file_est_vide(&file_prete)) {
        file_defiler(&file_prete, &p);

        /*
         * Si le CPU est libre AVANT l'arrivée du prochain processus,
         * on avance l'horloge jusqu'à son arrivée (temps mort CPU).
         */
        if (current_time < p.arrival_time) {
            current_time = p.arrival_time;
        }

        /* Le processus commence à s'exécuter */
        p.start_time = current_time;

        /* Il s'exécute pendant toute la durée de son cycle CPU */
        p.finish_time = p.start_time + p.cpu_burst;

        /* Calcul des indicateurs de performance */
        p.response_time   = p.start_time  - p.arrival_time;
        p.turnaround_time = p.finish_time  - p.arrival_time;

        /*
         * Temps d'attente = temps de restitution - temps utile (CPU)
         * Note : on ne compte PAS l'E/S dans le temps d'attente
         * car les E/S sont parallélisées.
         */
        p.waiting_time = p.turnaround_time - p.cpu_burst;

        /* L'horloge avance après la fin du cycle CPU */
        current_time = p.finish_time;

        /* On recopie le processus mis à jour dans le tableau d'origine */
        processes[i++] = p;
    }
}
