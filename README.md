# **ENSEA Shell**

## **1. Description générale**

ENSEA Shell est un projet de shell interactif minimaliste qui permet aux utilisateurs d'exécuter des commandes en ligne de commande.
Ce shell repose sur un processus parent et enfant pour interpréter et exécuter les commandes, tout en affichant des informations utiles telles que les temps d'exécution et les codes de retour.

### **Fonctionnalités principales :**
- Affichage d'un prompt dynamique indiquant le statut de la commande précédente.
- Exécution des commandes via un processus enfant.
- Mesure et affichage du temps d'exécution de chaque commande.
- Support des commandes internes comme `exit` pour quitter le shell.

---

## **2. Structure du projet**

Le projet est organisé en plusieurs fichiers, chacun ayant un rôle spécifique :

### **a. `main.h`**
- Déclarations des constantes et variables globales :
  - **`MAX_COMMAND_LENGTH`** : Définit la longueur maximale d'une commande.
  - Messages utilisateur :
    - **`WELCOME_MESSAGE`** : Message de bienvenue.
    - **`EXIT_MESSAGE`** : Message expliquant comment quitter le shell.
    - **`BYE`** : Message de fermeture.
- Variable externe : **`command`** pour stocker la commande utilisateur.
- Inclusion des bibliothèques nécessaires, notamment pour la gestion des chaînes, des processus, et des horodatages.

---

### **b. `utils.c` et `utils.h`**
- Ensemble de fonctions utilitaires qui simplifient le code principal.
  
#### **Fonctions importantes :**
1. **`measure_time`**
   - Calcule le temps écoulé entre le début et la fin de l'exécution d'une commande.
   - Affiche le résultat en millisecondes.

2. **`displayText`**
   - Affiche des messages dans la sortie standard.

3. **`parse_command`**
   - Analyse une commande utilisateur pour en extraire les arguments.
   - Retourne un tableau d'arguments prêts pour l'exécution.

4. **`free_args`**
   - Libère la mémoire allouée dynamiquement pour le tableau d'arguments.

5. **`get_prompt`**
   - Génère un prompt dynamique en fonction du statut de la commande précédente (succès, échec ou signal).

---

### **c. `main.c`**
- Contient le point d'entrée du programme et la boucle principale du shell.

#### **Résumé du fonctionnement :**
1. **Initialisation** :
   - Affiche un message de bienvenue.
   - Initialise le statut de sortie des processus.

2. **Boucle principale** :
   - Génère un prompt dynamique.
   - Lit les commandes utilisateur, les interprète et les exécute dans un processus enfant.
   - Mesure le temps d'exécution et affiche le résultat.

3. **Gestion des erreurs** :
   - Messages explicites pour les erreurs (lecture, fork, exécution).

---

### **Organisation des fichiers :**
```
.
├── main.c         # Fichier principal (point d'entrée)
├── main.h         # Déclarations globales
├── utils.c        # Fonctions utilitaires
├── utils.h        # En-tête des fonctions utilitaires
└── README.md      # Documentation du projet
```
