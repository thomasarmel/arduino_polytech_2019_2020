__Rapport de séance du Vendredi 10 Janvier 2020 (séance 3):__

Du fait que la dernière séance était il y a seulement 2 jours, je n'ai pas vraiment piu avancer entre les 2 séances.
J'ai consacré cette séance à faire fonctionner correctement le wifi entre le programme Java et l'Arduino (voir rapport séance 2).
Je suis finalement arrivé au programme wifi-1.ino (même dossier que ce fichier). Je transformerai ce programme en classe pour la semaine prochaine. Vous pouvez trouver la vidéo du programme fonctionnel sur YouTube, lien dans le rapport de Clara.



Quelques points à noter à propos de ce programme:

*pancar::Vector<String> listenForPoints()* est une fonction qui renvoie la liste des points envoyée par le programme Java (tableau de String pour le moment). En fait elle doit attendre de recevoir les données pour les renvoyer.
Comme expliqué dans le rapport précédent Arduino n'est pas multithread donc on ne peut pas faire de callback "à la JavaScript". Cette fonction bloque le programme tant que le téléversement n'est pas terminé. Afin d'avoir un aperçu visuel on pourrait faire clignoter une led pendant le téléversement et afficher les % sur l'interface Java.

*ESP8266.find("point:")* -> Attend de recevoir "point:", renvoie false si le délai est passé.



A propos du programme Java:

On utilise les sockets pour envoyer les données: on envoie les points sous la forme:

**point:52,63**

**point:62,73**

**point:72,83**

**point:82,93**

**point:done**

On communique sur le port TCP 8122. Le Java a quand à lui le mérite d'être multithread, donc pour ne pas bloquer l'interface utilisateur on créé un nouveau thread pour envoyer les données, c'est beaucoup plus agréable pour l'utilisateur.
Autre problème: un programme écrit en Java (bytecode) tournant sous mon PC (Intel core I5 8th Gen 8 coeurs) est beaucoup plus rapide pour envoyer les données que ne l'est l'Arduino nano pour les recevoir avec ses 2 fils RX et TX pour le relier à l'ESP8266. Il y a donc un delai entre chaque point envoyé par le socket (*Thread.sleep([...]);*).
J'ai mis un délai de 100 ms comme ça on n'a pas de souci avec la liaison par contre pour envoyer ne serait-ce que 100 points ça prend un temps considérable du point de vue de l'ergonomie c'est donc un détail qu'il faudra optimiser.



Une chose à laquelle il faut penser quand on utilise le petit module wifi ESP8266: les interférences. A la maison tout fonctionnait parfaitement mais dès que j'arrivais en cours mes appareils se déconnectaient tout le temps du wifi. La solution est la suivante: changer le canal d'émission du module.
J'ai mis le canal 11 (1 par défaut) et j'en ai profité pour changer le SSID afin de repérer **notre** module plus facilement: **pancarduino**.

Pour information ça se fait avec la commande AT suivante: *AT+CWSAP* (https://room-15.github.io/blog/2015/03/26/esp8266-at-command-reference/).

De plus il faut attendre que le module démarre avant de lui envoyer les commandes AT. Appeler la fonction *delay()* dans le setup avant les premières commandes AT.
