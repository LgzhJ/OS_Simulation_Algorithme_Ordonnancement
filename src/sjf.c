#include <stdio.h>
#include <stdlib.h>
#include "sjf.h"

/* -----------------------------------------------------------------------
 * Fonctions internes (static = non visibles hors de ce fichier)
 * ----------------------------------------------------------------------- */

/**
 * @brief Compare deux processus par leur durée de cycle CPU.
 *
 * Fonction de comparaison utilisée pour sélectionner le processus
 * au cpu_burst minimal parmi les processus disponibles à l'instant t.
 * En cas d'égalité de burst, départage par date d'arrivée,
 * puis par pid si les deux critères sont identiques.
 *
 * @param a  Pointeur vers le premier processus
 * @param b  Pointeur vers le second processus
 * @return   Négatif si a est prioraitaire sur b, positif sinon, 0 si égalité
 */
static int compare_burst(const void *a, const void *b)
{
    const Process *pa = (const Process *)a;
    const Process *pb = (const Process *)b;
    if (pa->cpu_burst != pb->cpu_burst)
        return pa->cpu_burst - pb->cpu_burst;
    if (pa->arrival_time != pb->arrival_time)
        return pa->arrival_time - pb->arrival_time;
    return pa->pid - pb->pid;
}

int isDone(int tab[], int n){
    for(int i = 0; i < n; i++){
        if(tab[i] != 1) {
            return 0;
        }        
    }
    return 1;
}

void sjf_schedule(Process processes[], int n) {
    int current_time = 0;
    int done[n];
    for (int j = 0; j < n; j++) done[j] = 0;

    while (!isDone(done, n)) {
        // 1. Collecter les processus prêts
        Process temp[n];
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (!done[i] && current_time >= processes[i].arrival_time) {
                temp[count++] = processes[i];
            }
        }

        // Aucun processus prêt → avancer le temps
        if (count == 0) {
            current_time++;
            continue;
        }

        // 2. Trier et choisir UNIQUEMENT le premier (plus petit burst)
        qsort(temp, count, sizeof(Process), compare_burst);
        Process p = temp[0]; // ← on n'exécute QUE celui-là

        // 3. Exécuter ce seul processus
        p.start_time = current_time;
        p.finish_time = current_time + p.cpu_burst;
        p.response_time = p.start_time  - p.arrival_time;
        p.turnaround_time = p.finish_time  - p.arrival_time;
        p.waiting_time = p.turnaround_time - p.cpu_burst;
        current_time = p.finish_time;

        // 4. Marquer comme terminé
        for (int i = 0; i < n; i++) {
            if (!done[i] && processes[i].pid == p.pid) {
                processes[i] = p;
                done[i] = 1;
                break;
            }
        }
        // 5. Retour au while → on réévalue avec les nouveaux arrivants
    }
}


