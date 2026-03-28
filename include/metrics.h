/**
 * @file metrics.h
 * @brief Calcul et affichage des indicateurs de performance.
 *
 * Ce module est indépendant de l'algorithme d'ordonnancement utilisé.
 * Il peut être réutilisé tel quel pour FIFO, SJF, SJRF et RR.
 *
 * @authors NOM1 (xx%), NOM2 (xx%), NOM3 (xx%)
 */

#ifndef METRICS_H
#define METRICS_H

#include "process.h"

/**
 * @brief Affiche les résultats de l'ordonnancement dans la console.
 *
 * Affiche pour chaque processus ses indicateurs, puis les moyennes
 * globales et le taux d'occupation du CPU.
 *
 * @param processes  Tableau de processus après ordonnancement
 * @param n          Nombre de processus
 * @param algo_name  Nom de l'algorithme (ex: "FIFO")
 */
void print_metrics(Process processes[], int n, const char *algo_name);

/**
 * @brief Sauvegarde les résultats dans un fichier CSV.
 *
 * Le fichier CSV peut être ouvert directement dans un tableur.
 * Les en-têtes de colonnes sont conçus pour servir de labels de graphiques.
 *
 * @param processes  Tableau de processus après ordonnancement
 * @param n          Nombre de processus
 * @param algo_name  Nom de l'algorithme (ex: "FIFO")
 * @param filename   Chemin du fichier CSV de sortie
 */
void save_csv(Process processes[], int n, const char *algo_name,
              const char *filename);

#endif /* METRICS_H */
