# OS_Simulation_d'Algorithme_d'Ordonnancement

Simulateur en C d'algorithmes d'ordonnancement de processus. Produit des métriques en console et un export CSV.

## Fonctionnalités
- Implémente les algorithmes : **FIFO**, **SJF**, **SRJF**, **RR**, avec possibilité d'ajouter facilement d'autres algorithmes.
- Entrée : jeux de processus avec cycles CPU et cycles d'E/S parallélisables (unité : ms).
- Sortie : textuelle (CSV compatible tableur) ou graphique, avec indicateurs de performance :
  - Temps d'attente moyen / par processus
  - Temps de restitution moyen / par processus
  - Temps de réponse moyen / par processus
  - Taux d'occupation du CPU

## Extensions possibles
- Interface graphique pour la restitution des résultats
- Intégration d'autres logiques d'ordonnancement

## Compilation
Avant de compiler, assurez-vous que tous les fichiers source sont placés dans le répertoire de votre choix sous Linux.

1. Compiler le projet :
```bash
make
```
2. Installer les dépendances Python pour la génération des graphiques :
```bash
make deps
```
3. Compiler et lancer les 4 algos sur le fichier de test :
```bash
make run
```
4. Supprimer les `.o`, le binaire et les CSV :
```bash
make clean
```
5. Permet de clean + supprimer les dépendances python et venv :
```bash
make cleanall
```
6. Générer la documentation Doxygen :
```bash
make doc
```
7. Permet d'afficher l'aide :
```bash
make help
```

## Utilisation
Lancer le simulateur sur un algo précis : `./scheduler [<fichier.txt>] [<ALGO>] [quantum]`  
Les résultats sont affichés dans le terminal et exportés dans un fichier CSV.

| Paramètre | Description |
|-----------|-------------|
| `fichier_processus.txt` | Fichier de processus (voir format ci-dessous) |
| `ALGO` | `FIFO`, `SJF`, `RR` ou `SRJF` |
| `quantum` | Durée du quantum en ms — obligatoire pour `RR` |

Les valeurs par défaut sont lues dans `conf.ini`. Les arguments CLI ont toujours la priorité.

**Exemples :**
```bash
./scheduler data/test_processus.txt FIFO
./scheduler data/test_processus.txt SJF
./scheduler data/test_processus.txt RR 4
./scheduler data/test_processus.txt SRJF
```

## Génération des graphiques

Les résultats des simulations sont enregistrés dans des fichiers CSV.  
Un script Python permet ensuite de générer automatiquement des graphiques à partir de ces données.

Les graphiques produits permettent de visualiser et comparer les performances des différents algorithmes d’ordonnancement.

| Fichier | Description |
|--------|-------------|
| `resultats_*.csv` | Résultats générés par le simulateur |
| `graph.py` | Script Python qui génère les graphiques |
| `*.png` | Graphiques exportés |
| `*.xlsx` | Graphiques exportés pour LibreOffice |

**Exemple d'utilisation :**

```bash
python3 graph.py resultats_fifo.csv
```

**Dépendance python :**

```bash
pandas, matplotlib, openpyxl
```

## Format du fichier d'entrée
Une ligne par processus. Les lignes vides et celles commençant par `#` sont ignorées.
```
PID  arrival_time  cpu0 [io0  cpu1 [io1  cpu2 ...]]
```
Les valeurs après `arrival_time` alternent cycles CPU et cycles E/S. La première valeur est toujours un CPU.
```
# PID  arr  cpu   io
1      0    8     2
2      1    4     0
3      2    9     3

# Multi-burst : PID  arr  cpu0  io0  cpu1  io1  cpu2
6      0    6     3    4    2    2
```

**Règles de validation :**
- Une valeur négative est remplacée par sa valeur absolue (avertissement affiché).
- Un burst CPU nul est remplacé par 1 (avertissement affiché).
- Au-delà de 8 cycles CPU par processus, les bursts supplémentaires sont ignorés.
- Une ligne sans aucun burst CPU valide est ignorée (erreur affichée).

## Algorithmes

| Algo | Type | Critère de sélection |
|------|------|----------------------|
| `FIFO` | Non-préemptif | Date à laquelle le processus est devenu prêt, puis PID |
| `SJF` | Non-préemptif | Durée du burst CPU courant (plus court d'abord), puis date d'arrivée, puis PID |
| `RR` | Préemptif | File circulaire, quantum fixe |
| `SRJF` | Préemptif | Temps CPU restant dans le burst courant (plus court d'abord) |

## Métriques produites

| Métrique | Définition |
|----------|------------|
| Temps d'attente | `turnaround_time − total_cpu − somme(E/S intercalées)` |
| Temps de restitution | `finish_time − arrival_time` |
| Temps de réponse | `start_time − arrival_time` |
| Taux d'occupation CPU | `total_cpu de tous les processus / durée totale de simulation × 100` |

## Structure du projet

```
.
├── src
│   ├── config.c / .h       # Lecture de conf.ini
│   ├── process.c / .h      # Structure Process et API d'état
│   ├── metrics.c / .h      # Affichage console et export CSV
│   ├── main.c              # Point d'entrée, parsing CLI, dispatch algorithme
│   └──algos/
│       ├── fifo.c / .h     # Algorithme FIFO
│       ├── sjf.c / .h      # Algorithme SJF
│       ├── rr.c / .h       # Algorithme Round Robin
│       └── srjf.c / .h     # Algorithme SRJF
├── .venv/                  # Environnement virtuel Python pour isoler les dépendances
├── .pip-deps               # Liste des dépendances Python installées
├── data/                   # Dossiers des listes de processus
├── resultats_graphes/      # Dossier contenant les graphes
├── graphes.py              # Permet de créer les diagrammes à partir de fichier csv
├── conf.ini                # Configuration par défaut
└── Makefile
```

## Auteurs
JIANG Longzhou · BISIAUX Valentin · COSTA Mathéo
