# VoidBorn

**URL du dépôt Git** : [https://github.com/Herebios/projet](https://github.com/Herebios/projet)

---

## 👥 Contributeurs

- Baptiste MOULAY  
- Lucas REVERBEL-LONGHI  
- Nathan MORIN  
- Ilann THOURAULT  

---

## 📝 Description

Nous sommes un groupe de quatre étudiants à l’Université du Mans.  
Notre objectif a été de créer un jeu en respectant un délai d’environ **3 mois**.

Lors de notre phase de réflexion, nous souhaitions créer un **jeu multijoueur en deux dimensions** à l’aide de la librairie graphique **SDL2** en **langage C**.

---

## 🎯 Objectifs initiaux

- Jeu multijoueur (partie serveur, partie client)  
- Personnages avec une classe, des statistiques, des compétences et des objets  
- Système de combat via des compétences dépendantes des classes des personnages  
- Graphisme (personnages, map, objets, compétences)  
- Menu (interface de lancement du jeu)  

---

## ❌ Objectifs non atteints

- Intégration du système d'équipes  
- Développement des compétences pour le combat  
- Développement du système de victoire  

---

## ⚙️  Fonctionnement

Dans le menu, chaque joueur choisit son pseudo ainsi que la classe de son personnage, ce qui lui confère des capacités uniques qu'il peut utiliser au cours de la partie pour prendre l'avantage sur l'équipe adverse.  
Vous avez alors le choix entre être le serveur de la partie, être joueur d'une partie créée par une autre personne ou être les deux à la fois.  
Après cela, vous arrivez dans une salle d'attente, en attendant que les autres joueurs se joignent à vous. Une fois que la personne jouant le rôle de serveur lance la partie, le jeu démarre.  
La map de notre jeu se décompose en plusieurs zones que nous appelons tuiles, chacune ayant un biome (neige, plaine, etc) choisi aléatoirement.  
Les joueurs ne peuvent visualiser qu'une tuile du jeu à la fois.  
Cependant, il est possible de changer de tuile en passant par des portes placées à différents endroits aux bords de la tuile à la manière de The Binding of Isaac.  
Des obstacles sont générés aléatoirement sur la map, limitant les déplacements des joueurs.  
Des monstres sont également présents sur la map, se dirigeant vers le joueur le plus proche pour l'attaquer. Lorsque le monstre est tué, il lâche un objet que le joueur peut ramasser et ajouter à son inventaire.  
Chaque objet a une rareté et confère au joueur différents effets. Plus la rareté de l'objet est élevée, plus les effets bonus conférés au joueur sont importants.  
Un système de combat est mis en place entre les joueurs d'équipes différentes lorsqu'ils se trouvent sur la même tuile.  
Les points de vie ainsi que les objets du joueur sont affichés sur son écran à la manière d'un inventaire Minecraft.  
La gestion des entités dynamiques et des tuiles de la map est réalisée grâce à l'implémentation d'une liste générique.  
Le serveur communique avec les clients en envoyant toutes les informations nécessaires à l'affichage du jeu par le client qui renvoie des informations au serveur en fonction des actions du joueur.  

---

## Comment lancer une partie ?

Pour lancer une partie, il faut être au moins deux joueurs.  
Cependant, il est possible de jouer tout seul en lançant le jeu deux fois via deux terminaux en suivant les instructions suivantes et en saisissant *127.0.0.1* comme adresse IP.  
### Pour le joueur désigné comme serveur, il faut:
1. Communiquer avec tous les autres joueurs son adresse IP. Pour obtenir son adresse ip, il faut exécuter dans un terminal cette commande : *hostname -I*.
2. Lancer l'exécutable du jeu en faisant ./bin/VoidBorn si vous vous situez à la racine du projet.  
3. Insérer son pseudonyme, choisir son personnage, changer ses paramètres si besoin.  
4. Dans la section *Jouer*, tous les joueurs insèrent un même port dispo	nible.  
	> Dans le cas où le port ne serait pas accessible, un message d'erreur *libération* s'affiche dans le terminal dès le lancement du jeu. Pas de panique, il suffit de recommencer en changeant de port.

5. Choisir l'option *Créer partie*.
6. Insérer le nombre de clients à l'aide du clavier et choisir l'option *Etre joueur* si vous souhaitez être serveur et joueur.
	> L'option être serveur ne vous permettra pas de jouer mais seulement d'être l'hôte de la partie.   


### Pour les autres joueurs, il faut:

1. Lancer le jeu via la commande ./bin/VoidBorn.
2. Insérer son pseudonyme, choisir son personnage, changer ses paramètres si besoin.
3. Dans la section *Jouer*, insérer le port choisit, puis cliquer sur *Rejoindre partie*.
4. Il ne reste plus qu'à entrer l'adresse IP du serveur et d'attendre les autres joueurs !


## Comment jouer ?
Lorsque le jeu se lance, vous incarnez un personnage auquel il est possible de faire faire différentes actions :  
- se déplacer avec les 4 flèches directionelles *UP DOWN RIGHT LEFT*.
- récupérer un objet dans son inventaire en se déplaçant dessus et en appuyant sur la touche *E* du clavier. 
- jeter un objet de son inventaire, en appuyant sur une des touches 1 à 5.
- attaquer un autre joueur en regardant dans sa direction et en étant à deux cases de lui via la touche *espace*. 


### Bon jeu !




