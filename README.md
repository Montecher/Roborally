# Projet Roborally

MONTERO Thomas p1812104
DECHER Nathan p1801979

Ce projet vise à créer un joueur automatique pour le jeu [Roborally](https://fr.wikipedia.org/wiki/RoboRally).
Le sujet est disponible en pdf [sur la page du cours](https://liris.cnrs.fr/vincent.nivoliers/lifap6/Supports/Projet/roborally.pdf).

## Utilisation / Compilation
- cloner le projet `git clone https://github.com/Montecher/Roborally`
- compiler le projet `make`
- lancer le projet `out/app appdata/board.txt` (ou `make run`)

Le projet s'affiche ensuite sous la forme d'un menu en ligne de commandes

## Contenu réalisé
### Graphe des mouvements
- `src/Graph.hpp` / `src/Graph.cpp`
- Représente le graphe par une hashmap position -> liste (mouvement, position)
    - Permet d'accéder au graphe depuis n'importe quelle position
- Construction du graphe par parcours en largeur
- Recherche du chemin le plus court sans contraintes par Dijkstra
    - Utilisation d'une file à priorité sans modification de priorité (on rajoute simplement avec une priorité plus faible et ignore les doublons)

### Création d'une main de mouvements
- `src/Deck.hpp` / `src/Deck.cpp`
- Crée un vecteur contenant les différents mouvements possible par le robot en un ou plusieurs exemplaires. (exemple de construction d'un deck dans `src/test.cpp` fonction `deal()` ligne 117)
- Permet de piocher les 9 cartes nécéssaires au jeu depuis le `Deck` mélangé au préalable dans un vecteur représentant la main pioché.

### Recherche du chemin possible selon la main de carte
- `src/MoveTree.hpp` / `src/MoveTree.cpp`
- Chaque nœud contient (position, main, coups restants, enfants: liste (mouvement, nœud))
- Construction récursive en prenant à chaque fois un coup de la main tant qu'il reste des coups restants
- Parcours en largeur pour trouver le plus court chemin
- Arbre entièrement construit donc possible de l'exploiter à d'autres fins

### Démo
- `src/test.cpp`
- 6 modes de fonctionnement:
    1. test de la génération du graphe et affichage des noeuds en résultant.
    2. test de la recherche d'un plus court chemin (le moins de mouvements effectués) d'une position à une autre dans le graphe.
    3. test de la génération d'une main a partir d'un `Deck` prédéfini (pondéré selon nos estimations de la fréquence de la carte dans le vrai jeu car nous n'y avons pas eu accès) puis pioche et affichage de la main de 9 carte.
    4. fait tourner le serveur web sur http://localhost:8080 (c'est juste ce que l'ancien main du projet original faisait)
    5. test de la génération de l'arbre de mouvements possibles à partir d'une main aléatoire provenant d'un `Deck` puis recherche d'un plus court chemin possible s'il en existe
    6. test de la génération de l'arbre de mouvements possibles à partir d'une main prédéfinie puis recherche d'un plus court chemin s'il en existe
