# TODO

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
- [OK] Rotation de la camera avec fleches gauche et droite
- [OK] W A S D permettent de se deplacer
- [OK] ESC et croix rouge quittent le programme proprement
- [OK] map entouree de murs

## Parsing

- [OK] utiliser get_next_line pour stocker la map dans un tableau de strings
- [OK] Verifier qu'il n'y a pas d'elements etrangers dans la map (0, 1, N, S, W, E)
- [OK] Verifier qu'il n'y a qu'un seul joueur
- [OK] Verifier qu'il n'y a pas d'autres lignes que les lignes demandées
- [OK] Verrifier que la map est entouree de murs

## Raycasting etapes

- [OK] Creer un background
- [OK] Creer un point (personnage)
- [OK] permettre les deplacements du point
- [OK] dessiner la map avec le tableau de strings (appeler cette fonction avant le joueur)
- [OK] ajouter les lignes pour visualiser les carres
- [OK] tracer un trait devant le joueur qui s'arrete au premier mur
- [OK] convertir la taille du trait en une ligne de pixels de la bonne taille selon la distance
- [OK] placer ces lignes au centre de la fenetre
- [OK] regler le probleme des lignes qui disparaissent quand leur hauteur est supperieure a la taille de l'ecran
- [  ] changer la meniere de se deplacer (pouvoir avancer et translater en meme temps)
- [  ] selon l'orientation des murs, placer des ombres
- [  ] gerer le probleme de fish-eye
- [  ] ajouter des textures

## Bonus

- [  ] Collision contre les murs
- [  ] Un système de minicarte.
- [  ] Porte qui peuvent être ouvertes/fermées.
- [  ] Animations (des sprites animés).
- [  ] Faites pivoter le point de vue avec la souris.

## Misc

- [OK] Reformater le code avec une bonne gestion d'erreurs
- [  ] Reflechir a des structures de donnees plus pertinentes
- [  ] GNL leak

## git gems

- git add . && git commit -m "message" == git commit -am "message"
- git config --global alias.ac "commit -am" ==> git ac "message"
- git commit --amend -m "message corrige" (modifie le nom du predecent commit)
- git add . && git commit --amend --no-edit (rajoute des fichiers au commit)
- git stash list / git stash pop (reajoute au code) / git stash save "name" / git stash apply *index*
- git log --graph --oneline --decorate
- git checkout - (retourne sur la precedente branche)
