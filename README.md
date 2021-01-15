# dht11-sensor-to-grafana
PoC - Equipe 5 : SoftSanT

Pour pouvoir relancer le projet, il faut se munir de quelques capteurs et modules:
	- dht11 capteurs de température et d'humidité
	- esp-01S (basé sur l'esp8266) module wifi
	- une module alimentation pour breadboard/arduino (de préférence du 3.3V)
	
Nous utiliserons l'IDE d'Arduino afin de programmer nos différetns composants.

## Libraries
 Contient toutes  les librairies nécessaires à l'emploie du code sur l'IDE Arduino
 
## DHT_mqtt3
 Conetient le code .ino

## Running_sc
 Quelques screeshots des divers paramètres et processeur à éxécuter pour le bon fonctionnement de l'ingestion des données
 
## scripts
 Script à utiliser sur le processeur nifi ECMA scripts pour transformer les données reçues sous un format Json en un format accepté par InfluxDB
 
## Docker-files
  Les différents docker-compose.yaml utilisés pour notre démonstration technique
  
## Scheme
 Schéma des branchements à effectuer pour faire fonctionner les différents composants.
 Afin d'assurer le bon fonctionnement du téléverseemnt du code vers l'ESP-01s, il faut utiliser le flash mode.
 Pour recevoir les données, il faut utiliser le boot mode.
 
 Le bouton poussoir permet de "reset" et de basculer de mode après les bon branchements effectués.