**Rapport de séance du Mardi 7 Janvier 2020 (séance 2):**

La séance d'avant les vacances (Vendredi 20 Décembre 2019) a été annulée pour cause de mauvais temps.

Une chose que j'ai oublié de dire dans le rapport précédent: j'ai commencé le développement d'une application Java pour dessiner les pancakes.
Pour me simplifier la vie, j'ai réutilisé le code du TP "ardoise magique" d'OpenClassrooms (https://openclassrooms.com/fr/courses/26832-apprenez-a-programmer-en-java/24857-tp-creez-une-ardoise-magique). J'ai réalisé ce TP à l'époque où j'apprenais le Java.
Le code de l'application PC est donc basé sur celui du TP (mon code, pas la correction).


Pendant la semain "sans Arduino" et pendant les vacances, je n'ai pas pu tester le nouveau matériel. Je me suis donc occupé à écrire proprement des classes pour le code de fonctionnement des moteurs pas-à-pas.
Vous trouverez ces codes dans le dossier _src_.
En haut de votre fenêtre Github, vous trouverez un onglet __Wiki__. Il y a une documentation pour chacune des classes que j'ai écrites. Ne vous étonnez donc pas de l'absence de commentaires.

Pour avoir un code plus "propre", chaque classe est encapsulée dans le namespace *pancar*.
Par exemple, pour accéder à la classe Stepper, il faudra écrire *pancar::Stepper*.

Les différentes classes écrites pendant l'intervalle entre les 2 séances:

__Stepper:__ Contrôle les moteurs pas-à-pas

__GroupStepper:__ Permet de contrôler un groupe de moteurs pas-à-pas. En effet si vous demandez à un moteur de faire n pas, le programme se bloque jusqu'à ce que les n pas soient effectués. Cela vient du fait qu'il n'y a qu'un seul fil d'exécution sur Arduino (monothread). L'astuce consiste donc à alterner les pas pour donner l'illusion que les 2 moteurs tournent en même temps, ce qui est vrai si on tient compte de l'inertie.

__Vector:__ Permet de créer des tableaux dynamiques, dans le style des collections de Java ou des conteneurs de la bibliothèque standard du C++ (qui n'est évidemment pas disponible en Arduino).
J'ai eu beau chercher, je n'ai pas trouvé la moindre bibliothèque pour faire ça (c'est pourtant très pratique). Ca va nous être utile pour le dessin du pancake, qui est en réalité une collection de points (la classe Point est à faire, à voir si Clara veut la faire).
Peut-être que la classe __GroupStepper__ va en hériter, à voir...
Cette classe fonctionne par une récursivité sur des pointeurs de tableaux de pointeurs de référence de template. L'utilisation des pointeurs s'avère difficile en Arduino parce que comme on programme dans l'espace noyau, on ne bénéficie pas des protections de l'espace utilisateur (erreurs de segmentation...) et donc le code est difficile à valider. Pour plus d'infos: https://fr.wikipedia.org/wiki/Espace_noyau https://fr.wikipedia.org/wiki/Espace_utilisateur https://wiki.osdev.org/Main_Page.
D'autre part le compilateur fournit avec le logiciel Arduino (avr-g++) ne gère pas par défaut les exceptions (try, catch...). Il semblerait cependant qu'il soit possible d'activer cette fonctionnalité. Pour garder mon code le plus portable possible, j'ai décidé de ne pas utiliser les excptions. Il en résulte malheureusement un code un peu moins propre, et ce d'autant plus qu'on programme dans l'espace noyau.
J'ai prévu un pdf d'explication du code dans le dossier __documents divers__: __pancarvector - explications.pdf__.




Pour information, j'avais utilisé le cours suivant pour apprendre le langage C++: https://openclassrooms.com/fr/courses/1894236-programmez-avec-le-langage-c
