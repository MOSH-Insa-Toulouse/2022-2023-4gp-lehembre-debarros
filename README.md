# 2022-2023-4gp-lehembre-debarros

## SOMMAIRE 

1. Etapes de fabrication
2. Présentation du capteur graphite 
3. Circuit électronique
4. Eléments nécessaires au projet
5. Elaboration du shield sous KiCAD
6. Programme Arduino
7. Application Android
8. Banc de test
9. Datasheet 

# 1. Etapes de fabrication

- Création du circuit et simulations sous LtSpice
- Implémentation du circuit sous KiCAD et élaboration du PCB 
- Fabrication du PCB
- Percage de la plaquette et soudure des composants 
- Elaboration du code Arduino
- Création de l'application d'interfacage sous MIT - app inventor
- Caractérisation du capteur

# 2. Présentation du capteur graphite 



# 3. Circuit électronique 

Schéma de l'amplificateur de signal :
 
![image](https://user-images.githubusercontent.com/123983006/233670098-0d6b56d7-fcdb-4a46-a134-9d60f6946954.png)

Modules supplémentaires et leur connexions : 

![image](https://user-images.githubusercontent.com/123983006/233670651-80eaf7b7-4b44-4b1c-9065-9e1a6c9549bc.png)

Connection des pins entre le PCB et la carte Arduino

![image](https://user-images.githubusercontent.com/123983006/233671289-94eeec8e-3fbc-4118-b84e-bf61e8f388fc.png)


# 4. Eléments nécessaires au projet 

-	Arduino Uno
-	Module Bluetooth HC05
-	Amplificateur LTC1050 
-	I2C Ecran OLED Joy-it SBC-OLED01
-	Encodeur rotatoire avec boutton poussoir (Joy-it KY-040) 
-	Spectrasymbol 005 21 Flex Sensor
-	MCP41050 SPI Potentiomètre Digital 

# 5. Elaboration du PCB sous KiCAD

Représentation du PCB avec le circuit implémenté : 

![image](https://user-images.githubusercontent.com/123983006/233671496-8657108f-28f1-4707-b5d3-a29620d68c3c.png)

Empruntes des autres composants : 

![image](https://user-images.githubusercontent.com/123983006/233671934-35ba265f-30e9-4f8b-8c31-10f8902c15b0.png)

# 6. Programme Arduino

Ci-après, le code Arduino utilisé : [Code Arduino](https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-lehembre-debarros/blob/07b504035136efd2108f1f7b01446d1b1bee7c57/Code_arduino_Lauriane_Alan.ino)

# 7. Application Android

# 8. Banc de test

Pour calibrer notre capteur, nous avons utilisé le banc de test mis à notre disposition. Voici ses particularités et 

# 9. Datasheet

La datasheet est disponible en suivante le lien ci-après : [Datasheet](https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-lehembre-debarros/blob/970a85952978378579259352fa356e7eba29f6f5/Datasheet%20-%20Capteur.pdf)




