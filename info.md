
<center>**TODO**</center>

## Consignes

- [OK] Mis à part la description de la map, chaque type d’élément peut être séparée par une ou plusieurs lignes vides.
- [OK]La description de la carte sera toujours en dernier dans le fichier, le reste des
      éléments peut être dans n’importe quel ordre.
- [OK]Sauf pour la map elle-même, les informations de chaque élément peuvent être
      séparées par un ou plusieurs espace(s).
- [OK]La carte doit être parsée en accord avec ce qui est présenté dans le fichier. Les
      espaces sont une partie valable de la carte, c’est à vous de les gérer correctement. Vous devez pouvoir parser n’importe quelle sorte de carte, tant qu’elle
      respecte les règles de carte
- [  ] Pouvoir changer les couleurs du sol et plafond
- [  ] Rotation de la camera avec fleches gauche et droite
- [  ] W A S D permettent de se deplacer
- [  ] ESC et croix rouge quittent le programme proprement
- [  ] map entouree de murs

## Parsing

- [OK] utiliser get_next_line pour stocker la map dans un tableau de strings
- [OK] Verifier qu'il n'y a pas d'elements etrangers dans la map (0, 1, N, S, W, E)
- [OK] Verifier qu'il n'y a qu'un seul joueur
- [OK] Verifier qu'il n'y a pas d'autres lignes que les lignes demandées
- [  ] Verrifier que la map est entouree de murs

## Raycasting etapes

- [  ] Creer un background
- [  ] Creer un point (personnage)
- [  ] permettre les deplacements du point
- [  ] dessiner la map avec le tableau de strings (appeler cette fonction avant le joueur)
- [  ] ajouter les lignes pour visualiser les carres
- [  ] permettre la rotation du joueur

## Bonus

- [  ] Collision contre les murs
- [  ] Un système de minicarte.
- [  ] Porte qui peuvent être ouvertes/fermées.
- [  ] Animations (des sprites animés).
- [  ] Faites pivoter le point de vue avec la souris.

## Misc

- [  ] Reformater le code avec une bonne gestion d'erreurs
- [  ] Reflechir a des structures de donnees plus pertinentes
- [  ] GNL leak
