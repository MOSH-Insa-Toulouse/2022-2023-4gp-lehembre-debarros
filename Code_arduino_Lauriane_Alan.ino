
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Adafruit_SSD1306.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////
#define nombreDePixelsEnLargeur 128         // Taille de l'écran OLED, en pixel, au niveau de sa largeur
#define nombreDePixelsEnHauteur 64          // Taille de l'écran OLED, en pixel, au niveau de sa hauteur
#define brocheResetOLED         -1          // Reset de l'OLED partagé avec l'Arduino (d'où la valeur à -1, et non un numéro de pin)
#define adresseI2CecranOLED     0x3C  
#define encoder0PinA  2  //CLK Output A Do not use other pin for clock as we are using interrupt
#define encoder0PinB  4  //DT Output B
#define Switch 5 // Switch connection if available
#define MCP_NOP 0b00000000
#define MCP_WRITE 0b00010001
#define MCP_SHTDWN 0b00100001
#define txPin 8   //Broche 11 en tant que RX, TX du HC-05
#define rxPin 9   //Broche 10 en tant que TX, RX du HC-05
#define baudrate 9600
////////////////////////////////////////////////////////////////////////////////////////////////////////

const int ssMCPin = 10; // Define the slave select for the digital pot
volatile unsigned int encoder0Pos = 0; //Valeur de position de l'encodeur rotatoire
int in_menu = 0; //Booleen permettant de switch entre menu et fonctionnalités
int last_pos_encodeur = 0; //Dernière position de l'encodeur rotatoire, pour savoir si la position a changé depuis le dernier tour de boucle
int pos_menu = 1; //Position dans le menu 
float R2 = 5*196.08; //Valeur de R2, initialisée à environ 980 
float sensorfelix = 0.0; //Valeur de tension du flexsensor 
int buttonState;   // lecture actuelle du pin d'entrée du bouton poussoir
int lastButtonState = 0; //Dernière valeur de l'entrée du bouton poussoir
long lastDebounceTime = 0; // the last time the output pin was toggled
long debounceDelay = 10;    // temps de debouncing 


Adafruit_SSD1306 ecranOLED(nombreDePixelsEnLargeur, nombreDePixelsEnHauteur, &Wire, brocheResetOLED); //definition de l'OLED 
SoftwareSerial mySerial(rxPin ,txPin); //Definition du software serial pour le bluetooth 

//SPIWrite est une fonction qui sera appelee pour ecrire des valeurs sur le potentiometre digital 
void SPIWrite(uint8_t cmd, uint8_t data, uint8_t ssPin) // SPI write the command and data to the MCP IC connected to the ssPin
{
  SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0)); //https://www.arduino.cc/en/Reference/SPISettings
  digitalWrite(ssPin, LOW); // SS pin low to select chip
  SPI.transfer(cmd);        // Send command code
  SPI.transfer(data);       // Send associated value
  digitalWrite(ssPin, HIGH);// SS pin high to de-select chip
  SPI.endTransaction();
}

//---------------------------------------------------------------------------------------


void setup() {

//Setup des pins de l'encodeur rotatoire et de l'interrupt ------------------------------
  pinMode(encoder0PinA, INPUT);  
  digitalWrite(encoder0PinA, HIGH);       // turn on pullup resistor
  pinMode(encoder0PinB, INPUT); 
  digitalWrite(encoder0PinB, HIGH);       // turn on pullup resistor
  attachInterrupt(0, doEncoder, RISING); // encoder pin on interrupt 0 - pin2
//---------------------------------------------------------------------------------------

//Setup de l'ecran OLED ------------------------------------------------------------------------------------
      if(!ecranOLED.begin(SSD1306_SWITCHCAPVCC, adresseI2CecranOLED))
    while(1);                               // Arrêt du programme (boucle infinie) si échec d'initialisation
    boolean bCouleurInverse = false;
    ecranOLED.clearDisplay();  // Effaçage de l'intégralité du buffer de l'ecran 
    ecranOLED.setTextSize(1);  // Taille de la police d'ecriture
    ecranOLED.setCursor(0,30 ); //Position initiale du curseur 
    ecranOLED.setTextColor(SSD1306_WHITE, SSD1306_BLACK); //Couleur d'ecriture initiale             
//----------------------------------------------------------------------------------------------------------
  

//Setup des pins serie et debut de communication sur les differents ports 
  // initialize serial communication at 9600 bits per second:
  Serial.begin(baudrate);
  pinMode(rxPin,INPUT);
  pinMode(txPin,OUTPUT);
  pinMode (ssMCPin, OUTPUT); //select pin output
  digitalWrite(ssMCPin, HIGH); //SPI chip disabled
  SPI.begin();  
  mySerial.begin(baudrate);
//------------------------------------------------------------------------

}


void loop() {

  int i_R2 = 5; //Initialisation de la position du wiper dans le pot. digital

  //Code des 3 fonctionnalités qui s'executent en dehors du menu principal selon la valeur de pos_menu 
  if (not in_menu){ //Si on n'est pas dans le menu alors... 
     
      if(pos_menu == 1){ //Si pos_menu vaut 1 on rentre dans la fonctionnalité reglage du gain, en choisissant R2, la resistance serie sur la borne V- de l'ampli-op
        i_R2 = 0; //On passe le wiper a 0 
        buttonState = 0; //On force l'etat actuel du bouton poussoir a 0, car il n'est pas re-lu et vaut toujours 1 en sortant du menu 
        delay(100); //Delai pour la stabilite 

        while(!buttonState){ //Tant que le bouton poussoir n'a pas ete presse 
            //Serial.println("on passe ici"); //Pour debugguer :) 
            if (last_pos_encodeur != encoder0Pos) { //Si la position de l'encodeur rotatoire a change <=> il a tourne alors... 
                          if(i_R2 < 255){ //Si la position du wiper vaut 254 ou moins, on l'incremente de 1 
                            i_R2++;
                          }
                          else{ //Si elle vaut deja 255, alors elle repasse a 0 
                            i_R2 = 0; 
                          }
                          last_pos_encodeur = encoder0Pos; //Changement de la derniere position de l'encodeur, pour le prochain tour de boucle 
                          
              }
            //Affiche sur l'ecran oled de la valeur de R2 a chaque tour de boucle 
            ecranOLED.clearDisplay(); //Clear de l'ecran 
            ecranOLED.setCursor(0, 30); 
            ecranOLED.print("R2 vaut ");
            ecranOLED.print(i_R2*196.08);
            ecranOLED.display();
            ecranOLED.setCursor(0, 30); 
            //-------------------------------------------------------------------
            
            buttonState = Bouton(&lastButtonState, &lastDebounceTime); //Lecture du bouton poussoir, a l'aide d'une fonction dediee 

        }
        //Une fois qu'on sort de la boucle de reglage de R2 
        R2 = (float)i_R2*196.08;
        delay(300); //Delai pour stabilite 
        SPIWrite(MCP_WRITE, i_R2, ssMCPin); //ecriture de R2 dans le pot. digital 
        in_menu = 1; //On retourne dans le menu
       }
       
      else if(pos_menu == 2){ //Si pos_menu == 2, alors on passe dans la fonctionnalite lecture de Rgraphite et envoi par Bluetooth sur l'appli

        int sensorValue = analogRead(A0); //Lecture tension de sortie de l'ampli-op 
        //Serial.println(sensorValue); //Pour observer sur ordinateur la tension, si necessaire 
        float tension_graphite = (float)sensorValue * 5.0/1023.0; //Conversion valeur ADC vers tension en volts 
        float Rc = ((100000.0*(100000.0+R2)*4.2968)/(R2*tension_graphite)) - 10000.0 - 100000.0; //Calcul de Rgraphite avec la fonction de transfert du circuit

        //Affichage de Rgraphite sur l'ecran oled         
        ecranOLED.clearDisplay();
        ecranOLED.setCursor(0, 30);
        ecranOLED.print("Rgraph vaut :");
        ecranOLED.println(Rc);
        ecranOLED.display();
        ecranOLED.setCursor(0, 30);
        //---------------------------------------

        //Envoi de la valeur en sortie d'ADC vers l'application via le module bluetooth HC-05 
        uint8_t sensorBT = sensorValue/4; //Variable permettant de cantonner la valeur sur un byte car synchronisation du transfert de donnee sur plusieurs octets 
        //tres difficile avec l'application android et le module bluetooth, engendre des bugs. On perd un facteur 4 de resolution sur l'appli (20mV au lieu de 5)
        mySerial.write(sensorBT); //Envoi par bluetooth en serial 
        delay(100); //Delai car le transfert de donnee prend du temps + stabilite 
        
         //Si l'encodeur rotatoire a tourne depuis le dernier tour de boucle, on revient dans le menu 
        if (last_pos_encodeur != encoder0Pos) {
              in_menu = 1; 
              last_pos_encodeur = encoder0Pos; 
            }
        //--------------------------------------------------------------------------------------------
      }

      else if (pos_menu ==  3){ //Fonctionnalite lecture de la resistance du flex sensor 
      //Serial.println("Nous sommes dans le case 3"); //Pour debug 

        int felixsensor = analogRead(A1);
        float sensorfelix = (39000.0*4.2968)/(4.2968 - (float)felixsensor*(5.0/1023.0));

        //Affichage OLED ---------------
        ecranOLED.clearDisplay();
        ecranOLED.setCursor(0, 30);
        ecranOLED.print("Rflex vaut :");
        ecranOLED.println(sensorfelix);
        ecranOLED.display();
        ecranOLED.setCursor(0, 30);
        //-------------------------------

        delay(100);
        
        //Retour menu si l'encodeur rotatoire tourne 
        if (last_pos_encodeur != encoder0Pos) {
              in_menu = 1; 
              last_pos_encodeur = encoder0Pos; 
            }
        //------------------------------------------
      }
      else{
        Serial.println("Il y a eu un bug, déso"); //Exception si pos_menu se prend un rayon cosmique et prend une valeur impossible :) 
      }

  }
  else { //Programme du menu 
  
    //Serial.println("Nous sommes dans le menu");  //Pour debug 

    //Affichage du menu, la ligne correspondant a la fonction selectionnee par pos_menu est en surbrillance 
    ecranOLED.clearDisplay();
    ecranOLED.setCursor(0, 10);
    
    if (pos_menu == 1){ecranOLED.setTextColor(SSD1306_BLACK, SSD1306_WHITE);} 
    ecranOLED.print("Parametrer R2\n");
    if (pos_menu == 1){ecranOLED.setTextColor(SSD1306_WHITE, SSD1306_BLACK);}

    if (pos_menu == 2){ecranOLED.setTextColor(SSD1306_BLACK, SSD1306_WHITE);}
    ecranOLED.print("Observer Rgraph\n");
    if (pos_menu == 2){ecranOLED.setTextColor(SSD1306_WHITE, SSD1306_BLACK);}
    
    if (pos_menu == 3){ecranOLED.setTextColor(SSD1306_BLACK, SSD1306_WHITE);}
    ecranOLED.print("Observer Rflex");
    if (pos_menu == 3){ecranOLED.setTextColor(SSD1306_WHITE, SSD1306_BLACK);}

    ecranOLED.display();

    //-----------------------------------------------------------------------------------------------------

    // Serial.println("Le bouton est a:"); //Pour debug 
    // Serial.println(buttonState);
  
    //Code de selection de la fonctionnalite 
     if (last_pos_encodeur != encoder0Pos) { //Si l'encodeur rotatoire tourne, pos_menu est incremente entre 1 et 3, puis repasse a 1 
               last_pos_encodeur = encoder0Pos; 
               if(pos_menu<3){
                 pos_menu++;
                 }
               else{
                 pos_menu=1;
                 }
              
       }

    buttonState = Bouton(&lastButtonState, &lastDebounceTime); //Lecture du bouton poussoir 
    if(buttonState){ //Si le bouton est appuye alors on sort du menu, pos_menu ne change pas donc on entre dans la bonne fonctionnalite 
      in_menu = 0;
    }
    delay(50); //Pour la stabilite 
  }
  

}


//Fonction qui gere l'interrupt de l'encodeur rotatoire et incremente ou decremente sa position selon l'etat du pin encoder0PinB 
void doEncoder() {
  if (digitalRead(encoder0PinB)==HIGH) {
    encoder0Pos++;
  } else {
    encoder0Pos--;
  }
}
//-------------------------------------------------------------------------------------------------------------------------------

//Fonction de lecture du bouton poussoir, avec debouncing pour eviter les flickerings et mauvaises lectures 
int Bouton(int * LBS, long * LBT) { //On passe par des pointeurs pour pouvoir modifier des variables passees en entree de la fonction 
    int Bout_state = 0; 
    int reading = analogRead(A3); //On utilise une entree analogique car la tension du bouton ne suffit pas a declencher un haut niveau logique en entree digitale
      if(reading > 10){ //Lorsque le bouton n'est pas appuye on a un niveau de tension d'environ 1V 
        reading = 0; 
      }
      else{
        reading = 1; 
      }
 

      // check to see if you just pressed the button
      // (i.e. the input went from LOW to HIGH),  and youve waited
      // long enough since the last press to ignore any noise:  
      // If the switch changed, due to noise or pressing:
      if (reading != *LBS) { //Si la valeur de lecture a change (bruit ou intentionnel)
       
        *LBT = millis();  // reset du timer de deboucing 

      }
    
      if ((millis() - *LBT) > debounceDelay)
      {
        // whatever the reading is at, it's been there for longer
        // than the debounce delay, so take it as the actual current state:
        Bout_state = reading;
      }

    *LBS = reading; 
    //  Serial.print("state = ");
    //  Serial.println(reading);
     
    //Serial.println(Bout_state); //Pour debug
    return Bout_state;   

}

//---------------------------------------------------------------------------------
                                        //FIN DU CODE, Merci pour votre attention// 



