# 2022-2023-4gp-lehembre-debarros

## SOMMAIRE 

1. Etapes de fabrication
2. Présentation du capteur graphite 
3. Simulations sous LtSpice
4. Circuit électronique
5. Eléments nécessaires au projet
6. Elaboration du shield sous KiCAD
7. Programme Arduino
8. Application Android
9. Banc de test
10. Datasheet 

# 1. Etapes de fabrication

- Création du circuit et simulations sous LtSpice
- Implémentation du circuit sous KiCAD et élaboration du PCB 
- Fabrication du PCB
- Percage de la plaquette et soudure des composants 
- Elaboration du code Arduino
- Création de l'application d'interfacage sous MIT - app inventor
- Caractérisation du capteur

# 2. Présentation du capteur graphite 

Le capteur est basé sur l'effet tunnel quantique entre les particules de graphite déposées par le crayon. 
Pour plus d'informations, vous pouvez vous renseigner grâce au lien suivant : [Informations supplémentaires](https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-lehembre-debarros/blob/d776b440ef20fb4f5e64abb67d3f56df1f3a449e/++Publi%20Pencil%20Drawn%20Strain%20Gauges-srep03812.pdf)

Dimensions : 

<img width="305" alt="image" src="https://user-images.githubusercontent.com/123983006/233673780-bb326a95-9697-457d-ab55-849565c78948.png">

Utilisation d'un crayon HB pour le grain.

# 3. Simulations sous LtSpice

![image](https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-lehembre-debarros/assets/123983006/37055e73-0361-40ae-8ce9-98f88d7cde84)
𝑅_𝐶=((𝑅_3+𝑅_2 ) 𝑅_1 𝑉_𝐶𝐶)/(𝑅_2 𝑉_𝐴𝐷𝐶 )−𝑅_5−𝑅_1

Etude et dimensionnement du gain et des capacités afin d’obtenir un signal exploitable en simulant le circuit

# 4. Circuit électronique 

Schéma de l'amplificateur de signal :
 
![image](https://user-images.githubusercontent.com/123983006/233670098-0d6b56d7-fcdb-4a46-a134-9d60f6946954.png)

Modules supplémentaires et leur connexions : 

![image](https://user-images.githubusercontent.com/123983006/233670651-80eaf7b7-4b44-4b1c-9065-9e1a6c9549bc.png)

Connection des pins entre le PCB et la carte Arduino

![image](https://user-images.githubusercontent.com/123983006/233671289-94eeec8e-3fbc-4118-b84e-bf61e8f388fc.png)


# 5. Eléments nécessaires au projet 

-	Arduino Uno
-	Module Bluetooth HC05
-	Amplificateur LTC1050 
-	I2C Ecran OLED Joy-it SBC-OLED01
-	Encodeur rotatoire avec boutton poussoir (Joy-it KY-040) 
-	Spectrasymbol 005 21 Flex Sensor
-	MCP41050 SPI Potentiomètre Digital 

# 6. Elaboration du PCB sous KiCAD

Représentation du PCB avec le circuit implémenté : 

![image](https://user-images.githubusercontent.com/123983006/233671496-8657108f-28f1-4707-b5d3-a29620d68c3c.png)

Empruntes des autres composants : 

![image](https://user-images.githubusercontent.com/123983006/233671934-35ba265f-30e9-4f8b-8c31-10f8902c15b0.png)

# 7. Programme Arduino

Ci-après, le code Arduino utilisé : [Code Arduino](https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-lehembre-debarros/blob/07b504035136efd2108f1f7b01446d1b1bee7c57/Code_arduino_Lauriane_Alan.ino)

# 8. Application Android

L'APK est disponible à cette adresse : [APK](https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-lehembre-debarros/blob/c0ea48ad6c8dff68e6e4c520c7baa0256ce2a0f2/Capteur_Graphite_Final.apk)

# 9. Banc de test

Pour calibrer notre capteur, nous avons utilisé le banc de test mis à notre disposition. 

<img width="307" alt="image" src="https://user-images.githubusercontent.com/123983006/233672885-3f3f39ab-638e-4f1a-a48f-ac6c1df0d200.png">

Nous avons ainsi obtenu les variations relatives suivantes en tension et en compression : 
<img width="404" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-lehembre-debarros/assets/123983006/24f43f09-9aa6-4fed-8fac-2e13231a1648"> <img width="403" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-lehembre-debarros/assets/123983006/742519d9-3b41-48de-ba39-d683817fa632">

Notre capteur dispose ainsi d'une sensibilité de 0,675 GΩ/% en compression et 0,2GΩ/% en tension.

Cette sensibilité correspond au coefficient de la pente de la variation relative par rapport à la déformation. 
La déformation se calcule à l'aide de la formule suivante : 
![image](https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-lehembre-debarros/assets/123983006/510dfadf-7ff9-4c82-80cb-fb1e97add056)

Avec e l'épaisseur du papier utilisé et R le rayon de la courbe. Dans notre cas, e = 0,16mm. 

# 10. Datasheet

La datasheet est disponible en suivante le lien ci-après : [Datasheet](https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-lehembre-debarros/blob/970a85952978378579259352fa356e7eba29f6f5/Datasheet%20-%20Capteur.pdf)




