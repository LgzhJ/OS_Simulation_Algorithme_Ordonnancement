# OS_Simulation_d’Algorithme_d’Ordonnancement

Simulation d’ordonnancement de processus pour un système d’exploitation, en mode console.

## Fonctionnalités
- Implémente les algorithmes : **FIFO**, **SJF**, **SJRF**, **RR**, avec possibilité d’ajouter facilement d’autres algorithmes.
- Entrée : jeux de processus avec cycles CPU et cycles d’E/S parallélisables (unité : ms).
- Sortie : textuelle (CSV compatible tableur) ou graphique, avec indicateurs de performance :
  - Temps d’attente moyen / par processus
  - Temps de restitution moyen / par processus
  - Temps de réponse moyen / par processus
  - Taux d’occupation du CPU

## Extensions possibles
- Interface graphique pour la restitution des résultats
- Génération automatique de graphiques via Office / LibreOffice
- Gestion des E/S non parallélisables

## Usage
1. Compiler : `make`
2. Lancer le simulateur : `./scheduler [fichier_processus.txt] [ALGO_D'ORDONNANCEMENT ex: FIFO, SJF, SRJF ou RR]` 
3. Les résultats sont exportés dans un fichier CSV et afficher dans le terminal
