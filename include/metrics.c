/**
 * @file metrics.c
 * @brief Implémentation du calcul et de l'affichage des indicateurs.
 *
 * @authors NOM1 (xx%), NOM2 (xx%), NOM3 (xx%)
 */

#include <stdio.h>
#include <stdlib.h>
#include "metrics.h"

/**
 * @brief Calcule le taux d'occupation du CPU en pourcentage.
 *
 * Le taux d'occupation est le rapport entre le temps total de calcul CPU
 * et la durée totale de la simulation (de l'arrivée du premier processus
 * à la fin du dernier).
 *
 * @param processes  Tableau de processus après ordonnancement
 * @param n          Nombre de processus
 * @return           Taux d'occupation du CPU en pourcentage (0.0 à 100.0)
 */
static double cpu_utilization(Process processes[], int n)
{
    int total_cpu  = 0;
    int first_arrival = processes[0].arrival_time;
    int last_finish   = 0;

    for (int i = 0; i < n; i++) {
        total_cpu += processes[i].cpu_burst;
        if (processes[i].finish_time > last_finish)
            last_finish = processes[i].finish_time;
        if (processes[i].arrival_time < first_arrival)
            first_arrival = processes[i].arrival_time;
    }

    int total_duration = last_finish - first_arrival;
    if (total_duration == 0) return 0.0;

    return (double)total_cpu / total_duration * 100.0;
}

/**
 * @brief Affiche les résultats dans la console (format tabulaire).
 */
void print_metrics(Process processes[], int n, const char *algo_name)
{
    double sum_wait = 0, sum_turnaround = 0, sum_response = 0;

    printf("\n=== Résultats algorithme : %s ===\n\n", algo_name);
    printf("%-5s %-10s %-10s %-10s %-12s %-14s %-12s\n",
           "PID", "Arrivée", "CPU", "E/S",
           "Attente", "Restitution", "Réponse");
    printf("----------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        Process *p = &processes[i];
        printf("%-5d %-10d %-10d %-10d %-12d %-14d %-12d\n",
               p->pid, p->arrival_time, p->cpu_burst, p->io_burst,
               p->waiting_time, p->turnaround_time, p->response_time);
        sum_wait       += p->waiting_time;
        sum_turnaround += p->turnaround_time;
        sum_response   += p->response_time;
    }

    printf("----------------------------------------------------------------------\n");
    printf("Temps d'attente moyen    : %.2f ms\n", sum_wait       / n);
    printf("Temps de restitution moy : %.2f ms\n", sum_turnaround / n);
    printf("Temps de réponse moyen   : %.2f ms\n", sum_response   / n);
    printf("Taux d'occupation CPU    : %.2f %%\n",  cpu_utilization(processes, n));
}

/**
 * @brief Sauvegarde les résultats dans un fichier CSV.
 *
 * Format CSV compatible tableur (séparateur point-virgule).
 * La première ligne contient les en-têtes de colonnes.
 */
void save_csv(Process processes[], int n, const char *algo_name,
              const char *filename)
{
    FILE *f = fopen(filename, "w");
    if (!f) {
        perror("Erreur ouverture fichier CSV");
        return;
    }

    /* En-têtes — servent de labels pour les graphiques */
    fprintf(f, "Algorithme;PID;Arrivee_ms;CPU_ms;ES_ms;"
               "Attente_ms;Restitution_ms;Reponse_ms\n");

    double sum_wait = 0, sum_turnaround = 0, sum_response = 0;

    for (int i = 0; i < n; i++) {
        Process *p = &processes[i];
        fprintf(f, "%s;%d;%d;%d;%d;%d;%d;%d\n",
                algo_name,
                p->pid, p->arrival_time, p->cpu_burst, p->io_burst,
                p->waiting_time, p->turnaround_time, p->response_time);
        sum_wait       += p->waiting_time;
        sum_turnaround += p->turnaround_time;
        sum_response   += p->response_time;
    }

    /* Ligne de moyennes */
    fprintf(f, "%s;MOYENNE;;;;"  "%.2f;%.2f;%.2f\n",
            algo_name,
            sum_wait / n, sum_turnaround / n, sum_response / n);

    /* Taux CPU */
    fprintf(f, "%s;CPU_UTILIZATION;;;;;"
               "%.2f%%\n", algo_name, cpu_utilization(processes, n));

    fclose(f);
    printf("Résultats sauvegardés dans : %s\n", filename);
}
