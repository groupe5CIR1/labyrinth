                Projet de génération et de solveur de labyrinthe

Par :
- Valentin TANG-PATUREL
- Gabriel PAGNIEZ


Dépot github : https://github.com/groupe5CIR1/labyrinth/



        Algorithme de génération : Origin Shift


D'abord on génère une grille (struct Grid), qui contient :
- la hauteur et la largeur de la grille
- un tableau de cellules (struct Cell*). Ce tableau est continu, ce qui permet de faire de l'arithmétique sur les pointeurs.
- un pointeur vers la cellule d'arrivée de la grille (initialisée à NULL pour l'instant, générée plus tard).

Chaque cellule comporte trois valeurs :
- (int)type : le type de la cellule, utilisé pour l'affichage uniquement
- (int)connections : un bitmask de directions (voir enum Directions), qui représente toutes les connections de la cellule avec ses cellules voisines
- (int)adjacents : un bitmask de directions, qui représente toutes les cellules voisines qui ont été générées (utilisé uniquement pour la génération, pour savoir où ne pas aller, ainsi les bordures sont considérées comme des cellules déjà générées)

L'idée des bitmasks est de ne pas avoir à générer et stocker des tableaux de pointeurs pour chaque cellule, mais à la place stocker des directions dans une seule variable. Ainsi, l'enum Directions définit les directions comme des puissances de deux plutôt que de simple nombres décimaux :
- WEST = 1
- EAST = 2
- SOUTH = 4
- NORTH = 8
Ainsi, une cellule connectée aux cellules sud, east et nord aura SOUTH|EAST|NORTH = 14 pour valeur (int)connections.

Etant donné qu'on ne stocke pas de coordonnées, cette implémentation oblige à faire de l'arithmétique sur les pointeurs, et donc l'utilisation d'un tableau continu de cellules dans la grille plutôt qu'un tableau à deux dimensions (en réalité on aurait aussi pu utiliser un tableau continu, et un autre tableau de tableau qui pointe sur le début de chaque ligne de la grille pour obtenir le même tableau en deux dimensions mais continu et ainsi utiliser les indices facilement, mais ça ne paraît pas vraiment rendre les choses plus simples).

Une fois la grille entièrement initialisée, la génération commence sur la cellule en haut à gauche (première cellule du tableau).
L'idée est de fonctionner sur un système de "neighbour updates", c'est-à-dire de mise à jour des cellules voisines dès qu'une cellule est générée (un peu comme dans Minecraft : lorsqu'un block est modifié, il force les blocks voisins à se mettre à jour pour réagir aux modifications).
Ainsi, dès qu'une cellule est générée, elle met à jour la valeur (int)adjacents des cellules voisines pour leur indiquer qu'elle a été générée, et qu'elles ne doivent pas tenter d'aller dans cette direction durant le reste de la génération.
L'algorithme de génération devient alors (depuis la cellule de départ) :

tant que (toutes le cellules ne sont pas générées) {
    choisir une direction où aller, en fonction des directions disponibles dans (int)adjacents de la cellule actuelle
    si (une direction valide est trouvée) {
        aller dans cette direction
        connecter les deux cellules (= ajouter les directions correspondantes dans (int)connections pour chacune des cellules)
        mettre à jour les valeurs (int)adjacents des cellules voisines
    }
    sinon {
        revenir à la dernière cellule qui a une direction valide où aller
    }
}

Pour pourvoir revenir sur son chemin, il faut pouvoir stocker le chemin quelque part. On utilise donc une pile, qui contient non pas les cellules du chemin, mais les directions où on est allé, c'est-à-dire une suite d'instructions (directions) depuis la cellule de départ. Cela permet de séparer le chemin du labyrinthe, puisqu'on ne stocke pas des pointeurs, ce qui peut être intéressant dans un cas théorique où on aurait le même labyrinthe à un emplacement mémoire différent par exemple, ou bien si on voulait donner une aide au joueur sans avoir à modifier la grille pour montrer où aller (donner des instructions dans le terminal).

La méthode pour générer la cellule d'arrivée du labyrinthe est ensuite demandée dans le terminal. Il y a deux possibilités :
- la méthode par défaut : la cellule d'arrivée est celle en bas à droite (dernière cellule de la grille)
- la méthode aléatoire : elle génère la cellule d'arrivée dans un cul-de-sac aléatoire de la grille, avec une préférence pour les cellules éloignées (manhattan distance) de la cellule de départ. Ainsi, cette fonction stocke dans un tableau tous les culs-de-sac (cellules qui n'ont qu'une connection), et en choisit un au hasard. La cellule choisie a alors une certaine probabilité d'être définitevement sélectionnée, sinon une autre cellule est choisie et une autre probabilité est calculée, et ainsi de suite jusqu'à ce qu'une cellule soit définitivement sélectionnée, ou qu'il ne reste plus de cellules à choisir (auquel cas un cul-de-sac parfaitement aléatoire est choisi). Chaque probabilité est calculée selon la distance manhattan entre la cellule et celle de départ, auquel un polynôme du 2e ordre est appliqué, pour que les cellules les plus éloignées aient très largement plus de chances d'être sélectionnées par rapport à celles qui sont proches.






        Algorithme de résolution : méthode de la main droite


La méthode de la main droite est très simple : dans un labyrinthe parfait, il suffit de garder constamment sa main droite sur un mur (c'est-à-dire toujours longer le mur de droite, ou autrement dit toujours aller le plus à droite possible). Cette méthode assure de trouver la sortie car dans un labyrinthe parfait, il permet de visiter toutes les cellules de la grille. A noter que la méthode fonctionne aussi avec la main gauche.
L'implémentation est extrêmement simple : il suffit de stocker la direction dans une variable, et incrémenter cette variable lorsqu'on va à droite, sinon la décrementer pour tourner à gauche et réessayer l'algorithme. Cela donne :

tant que (la cellule actuelle n'est pas la cellule d'arrivée) {
    si (la cellule en face est libre) {
        aller sur cette cellule
        tourner à droite
    }
    sinon {
        tourner à gauche
    }
}

Mais il faut aussi pouvoir tracer la solution, c'est-à-dire modifier le (int)type des cellules. Pour marquer la solution et non pas tout le chemin fait, il faut pourvoir stocker le chemin, et donc utiliser une pile encore une fois. On détecte alors lorsqu'on revient sur nos pas en comparant l'orientation actuelle et la dernière direction de la pile.

Une mesure précise du temps de résolution (en ms) est aussi implémentée à titre indicatif.
De manière générale, d'après les quelques tests faits, il semble que la méthode de la main droite est la plus rapide.






        Joueur :


Générer un labyrinthe et le résoudre c'est pas mal, mais ne pas pouvoir le compléter soi même c'est quand même dommage.
Nous avons donc implémenté la possibilité de se déplacer dans le labyrinthe, d'arrêter de jouer, et de reprendre là où le joueur s'est arrêté.
Les déplacements sont extrêmement simples à implémenter, étant donné qu'il suffit de comparer les connections de la cellule actuelle avec la direction où le joueur souhaite se déplacer.
La difficulté provient de l'affichage du chemin du joueur et des cellules disponibles. Il faut donc *encore une fois* utiliser une pile pour savoir si le joueur revient sur ses pas ou non, et mettre à jour la valeur (int)type de la cellule de manière adéquate.
Pour pouvoir afficher les cellules disponibles, on modifie le (int)type des cellules voisines connectées à AVAILABLE.
Donc lors d'un déplacement, il faut remplacer le (int)type des cellules voisines pour qu'elles ne soient plus AVAILABLE, puis faire le déplacement, et enfin modifier le (int)type des cellules voisines connectées à AVAILABLE. Et tout ce processus ne doit bien évidemment ne pas modifier le type des cellules du chemin.
L'algorithme devient alors :

montrer la grille
tant que (la cellule actuelle n'est pas la cellule d'arrivée) {
    demander au joueur une direction valide où aller
    si (on revient sur nos pas) {
        modifier le type de la cellule à AVAILABLE
        supprimer la dernière direction de la pile
    }
    sinon {
        ajouter la direction à la pile
    }
    modifier le type des cellules voisines connectées à GENERATED
    aller à la cellule demandée
    modifier le type des cellules voisines connectées à AVAILABLE

    montrer la grille
}


