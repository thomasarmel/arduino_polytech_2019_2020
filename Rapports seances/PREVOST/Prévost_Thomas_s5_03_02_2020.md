**Rapport de séance du Lundi 3 Février 2020 (séance 5):**


Au début de la séance, Clara est passée au FabLab pour faire découper au laser les crémaillères et roues dentées dont nous aurons besoin pour déplacer la tête d'impression.

Pendant ce temps-là, j'ai essayé de "stabiliser" le fonctionnement des moteurs pas-à-pas, sans succès. En effet, lorsqu'on leur commande d'effectuer un certain nombre de pas, il arrive qu'ils en fassent un peu moins.
A titre d'exemple: il faut 200 pas pour faire un tour complet. Avec une boucle infinie qui commande 200 pas dans un sens puis dans l'autre, le moteur ne se retrouvera pas toujours dans sa position initiale.


J'ai aussi essayé de stabiliser la liaison Wifi. 2 problèmes principaux se posaient.
D'abord certains points sont mals transmis, ce qui fait qu'on se retrouve avec des "points vides" ou bien des valeurs aberrantes.
Pour stabiliser le programme, je donne non plus 10 mais 1 seconde à la méthode *listenForPoints()* pour attendre la liste des points. A terme, on pourra aussi "trier" les valeurs aberrantes.
Le second problème est le suivant: à partir d'un certain nombre de points transmis, la carte Arduino s'arrête complètement de fonctionner (en tous cas c'est ce que laisse penser le retour sur le port série).
Mes soupçons se sont rapidement portés sur la faible quantité de mémoire RAM de notre Arduino nano ATmega328P -> https://www.arduino.cc/en/tutorial/memory.
Pour vérifier, j'ai trouvé comment vérifier en temps réel la quantité de mémoire disponible sur https://github.com/McNeight/MemoryFree.
J'ai arrangé ça en une classe pour faire plus "propre": **pancarmemory.h**.
Effectivement mes soupçons se sont avérés être fondés c'est bien la quantité de RAM disponible qui pose problème.
Pour la prochaine séance je vais donc essayer d'arranger ça, le problème vient très probablement de ma classe Vector, et donc du destructeur.



Enfin, nous nous sommes occupés à continuer la structure, notamment à installer les crémaillères et les roues dentées. On a d'ailleurs passé pas mal de temps à chercher des rondelles.
