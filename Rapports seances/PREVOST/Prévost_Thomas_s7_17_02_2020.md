**Rapport de séance du Lundi 17 Février 2020 (séance 7):**

Tout d'abord pendant le weekend j'ai réussi à résoudre partiellement le problème de surconsommation de la RAM par la classe Vector.
C'était assez laborieux. La vidéo se trouve sur la chaîne YouTube du projet.



Pendant la séance, je me suis occupé au système de la seringue (pour la pâte). On utilise pour cela un moteur pas-à-pas 28BYJ-48.
Tous les documents et schémas de montage se trouvent dans le dossier datasheets. Le problème principal avec ces moteurs a été le suivant: tous les tutoriels sur Internet invitaient à le faire fonctionner en 5V avec l'alimentation de l'Arduino.
Malheureusement avec cette alimentation il n'avait quasiment aucun couple. En fait j'ai dû aller chercher la documentation officielle sur le site web du fabriquant (en chinois) pour découvrir que les moteurs s'alimentent en 12V.
J'ai fabriqué très rapidement vu le peu de temps qu'il nous reste une petite poulie, que j'ai dû usiner avec une perceuse vu qu'il n'y a pas de fraiseuse en salle de TP ou au FabLab.
Pour rendre le code plus propre, jai créé la classe MiniStepper.

Une fois que Clara est rentrée du FabLab, nous avons continué la structure. Les moteurs Nema 17 fonctionnent maintenant parfaitement (un des drivers L293D a cependant grillé).
Le problème est le suivant: l'axe du moteur n'accroche pas à l'intérieur des roues dentées, quand bien même on leur a donné la bonne forme. Je vais voir si je peux arranger ça avec de la thermocolle mais honnêtement je n'y crois pas trop.
