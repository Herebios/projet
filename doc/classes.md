# Liste des personnages :

-- Nom de classe
type : rôle du personnage



-- Mage:
type : polyvalent (spécialisation)
Pv : 50
Portée d’attaque : moyenne / longue
Attaque de base - boule de feu :
    dmg : 15
    cd : 1s
Attaque puissante -  :

Compétence utilitaire -  :

Déplacement - téléportation :
    distance : tuile


-- Archer:
type : dégâts à distance
Pv : 60
Portée d’attaque : longue
Attaque de base - tir à l'arc :
    dmg : 10
    cd : 0.8
Attaque puissante - pluie de flèches :
    X tirs sur une zone
    cd : 15s
Compétence utilitaire - tirs rapides :
    rechargement de l'attaque de base à -50% pendant 10s
    réduction instantannée du temps de recharge de 'pluie de flèches' de 5s
Déplacement - roulade :
    esquive dans une direction
    cd : 10s


-- Tank:
type : défense
Pv : 100
Portée d’attaque : cac
Attaque de base -  :
    dmg : 20
    cd : 2
Attaque puissante -  :
    X tirs sur une zone
    cd : 15s
Compétence utilitaire - cri de guerre :
    les monstres ciblent ce personnage pendant 6s
    résistance aux capacités de contrôle pendant 6s
    cd : 12s
Déplacement - charge :
    déplacement assez rapide dans une direction verouillée
    cd : 20s


-- Guerrier:
type : dégâts au corps-à-corps
Pv : 80
Portée d'attaque : courte
Attaque de base - coup d'épée :
	dmg : 15
	cd : 0.8s
Attaque puissante - attaque rotative :
	peut être lancée juste après un coup d'épée
	attaque en cercle autour du guerrier
	dmg : 10
	cd : 15s
Compétence utilitaire - récupération rapide :
	Soin 10 Pv + augmente sa régénération naturelle de pv pour 10s
	baisse sa vitesse de déplacement
	cd : 30s
Déplacement - saut :
	saute par-dessus un obstacle au sol
	déplacement rapide de plusieurs cases
	cd : 12s


-- Informaticien:
type : information
Pv: 50
Portée d'attaque : courte
Attaque de base - coup de taser :
	dmg : 8
	cd : 1s
Compétence 1 - tourelle d'attaque :
	tourelle fixe (devient plus forte en fonction du niveau)
		pv : 30
		portée : longue
		dmg : 5
		cd : 1s
		nombre max : de 2 à N
Compétence 2 - tourelle à information :
	si pas encore posée, pose une caméra sur une tuile (?destruction possible?)	
		cd : 10s
	sinon:
		si même tuile, récupère la caméra
			cd : 5s
		sinon, change la vision pour voir à travers la caméra à distance (?toute la tuile?)
			cd : 10s après être revenu au personnage
Passif - maître de l'information :
	Si minimap, plus d'informations sur alliés, ennemis?
	Information sur quêtes et évènements en avance

-- Ninja:
type : furtif
Description :
    Déplacements furtifs et rapides;
    Coups critiques lorsqu'il attaque par surprise.
Pv : 60
Portée d’attaque : 
Dash : invisible pendant quelques secondes tant qu’il ne tire pas ou ne se fait pas tirer dessus


-- Druide:
type : support
Description :
    Quêtes pour améliorer et protéger sa forêt;
    Gagne des bonus dans biome forêt (déplacement facile, soin, ...);
    Gagne des transformations en animaux pour se renforcer.
Pv : 50
Portée d’attaque : variable
Dash : ?


-- Vampire:
type : dégâts à distance
Description :
    Absorbe le sang des adversaires et monstres pour utiliser ses compétences;
    Sacrifie des PV pour attaquer.

-- Imitateur:
type : polyvalent
Description : 
    Copie pour le combat, attaques et statistiques d'un allié;
    Copie d'apparence, les ennemis vont recevoir les mauvaises informations.

# Solo

-- Druide:
Description :
	Progression très forte au cours de la partie avec ses quêtes propres;
	Revient à la vie dans sa forêt en cas de mort sans pénalité (sauf temps);
Victoire :
	Forêt complètement étendue;
Défaite :
	Victoire d'une équipe;
	Destruction de son arbre sacré;
Quêtes :
	Sauver des animaux pour débloquer des transformations;
	Agrandir sa forêt;
	Renforcer l'arbre pour gagner des avantages dans la forêt


-- Ninja -> Assassin:
Description :
	Le meilleur des combattants dès le début, mais ne progresse pas
	comme les autres joueurs, il doit pas être rattrapé.
Victoire :
	Tuer chaque joueur au moins une fois
Défaite :
	Victoire d'une équipe;
	Son temps est compté, il gagne du temps en éliminant les monstres
	mais surtout les joueurs;
Quêtes :
	Contrats particuliers pour tuer un joueur/monstre et gagne un bonus
