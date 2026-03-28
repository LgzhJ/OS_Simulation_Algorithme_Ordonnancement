#include <stdio.h>
#include <stdlib.h>
#include "sjf.h"

/* -----------------------------------------------------------------------
 * Fonctions internes (static = non visibles hors de ce fichier)
 * ----------------------------------------------------------------------- */

/**
 * @brief Compare deux processus par leur durée du cycle CPU.
 *
 * Fonction de comparaison utilisée par qsort() pour trier les processus
 * dans l'ordre croissant des durées de cycle.
 *
 * @param a  Pointeur vers le premier processus
 * @param b  Pointeur vers le second processus
 * @return   Négatif si durée du cyle de a plus petit que b, positif sinon, 0 si égalité
 */
static int compare_burst(const void *a, const void*b){
    const Process *pa = (const Process *)a;
    const Process *pb = (const Process *)b;
    return pa->cpu_burst - pb->cpu_burst;
}

void sjf_schedule(Process processes[], int n){
    int current_time = 0; /* Horloge du simulateur (ms) */

    /* Étape 1 : trier les processus leur durée de cycle */
    qsort(processes, n, sizeof(Process), compare_burst);

    /* Étape 2 : simuler l'exécution SJF */
    for (int i = 0; i < n; i++) {
        Process *p = &processes[i];

        /*
         * Si le CPU est libre AVANT l'arrivée du prochain processus,
         * on avance l'horloge jusqu'à son arrivée (temps mort CPU).
         */
        if (current_time < p->arrival_time) {
            current_time = p->arrival_time;
        }

        /* Le processus commence à s'exécuter */
        p->start_time = current_time;

        /* Il s'exécute pendant toute la durée de son cycle CPU */
        p->finish_time = p->start_time + p->cpu_burst;

        /* Calcul des indicateurs de performance */
        p->response_time   = p->start_time  - p->arrival_time;
        p->turnaround_time = p->finish_time  - p->arrival_time;

        /*
         * Temps d'attente = temps de restitution - temps utile (CPU)
         * Note : on ne compte PAS l'E/S dans le temps d'attente
         * car les E/S sont parallélisées.
         */
        p->waiting_time = p->turnaround_time - p->cpu_burst;

        /* L'horloge avance après la fin du cycle CPU */
        current_time = p->finish_time;
    }
}


