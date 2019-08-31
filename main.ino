 
 /*
  * 
  * 30.12.2018
  * 
  * This project developt by Cetin KAYA and Gamze YILMAZ
  * 
  * Kocaeli University
  * 
  * contact@cetinkaya.co
  * 
  * cetinkaya.co
*/
#include<Keypad.h>
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>

// RFID SPI pins config
/* -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */

#define RST_PIN         5       // RFID Reset Pin
#define SS_PIN          53      // RFID SDA Pin
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
Servo SolarPanel; // Identifying servos
Servo Door;
Servo Water;
const byte ROWS = 4; // Keypad rows and collums 
const byte COLS = 4; 
char hexaKeys[ROWS][COLS] = { 
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {36,34,32,30}; // Keypad rows and collums pins
byte colPins[COLS] = {37,35,33,31}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
#define ROW_1 46
#define ROW_2 42
#define ROW_3 40
#define ROW_4 48
#define ROW_5 39
#define ROW_6 47
#define ROW_7 45
#define ROW_8 39

#define COL_1 44
#define COL_2 41
#define COL_3 A8
#define COL_4 A9
#define COL_5 A10
#define COL_6 A11
#define COL_7 A12
#define COL_8 A13

const byte rows[] = 
{
  
    ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8
    
};
const byte col[] = 
{
  
  COL_1,COL_2, COL_3, COL_4, COL_5, COL_6, COL_7, COL_8
  
};

// "1" is off "0" is on

byte ALL[] = {B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111};

byte EX[] = {B00000000,B00010000,B00010000,B00010000,B00010000,B00000000,B00010000,B00000000};

byte TRIANGLE[] =  {B11101111,B11010111,B10111011,B00000001,B11111111,B11111111,B11111111,B11111111};

byte SQUARE[] =  {00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000};

byte CIRCLE[] =  {B11000111,B10111011,B01111101,B01111101,B01111101,B10111011,B11000111,B11111111};

byte HEXAGON[] =  {B11111111,B11111001,B11110110,B11110110,B11111001,B11111111,B11111111,B11111111};

byte TRAPAZOID[] =  {B11111111,B11111011,B11111001,B11111010,B11111010,B11111010,B11111001,B11111011};

byte RECTANGLE[] =  {B11111111,B0000000,B01111110,B01111110,B01111110,B01111110,B00000000,B11111111};

float timeCount = 0;
int val,x,j=0,m=0;
String password[4] = {};
int val2;
int PanelLeft, PanelRight, PanelMiddle;
int RefValue = 200;

void setup() 
{
  SPI.begin();           // Init SPI bus
  mfrc522.PCD_Init();    // Init MFRC522
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
   
  Serial.begin(115200);  // Open serial port
  SolarPanel.attach(9);
  Door.attach(6);
  Water.attach(11);
   
  for (byte i = 33; i <= 53; i++)
  pinMode(i, OUTPUT);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A8, OUTPUT);
  pinMode(A9, OUTPUT);
  pinMode(A10, OUTPUT);
  pinMode(A11, OUTPUT);
  pinMode(A12, OUTPUT);
  pinMode(A13, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(A6, OUTPUT);
  pinMode(A7, INPUT);
}

void loop() 
{
  
 int CNY70Value = analogRead(A7);
 
 if(CNY70Value > 900) // Detects white color
  {
    Serial.println("white");
  }
  PanelLeft = analogRead(A0);
  PanelMiddle = analogRead(A1);
  PanelRight = analogRead(A2);
  
  if(PanelLeft > PanelRight & PanelLeft > PanelMiddle)
  {
    Serial.println("left");
    delay(50);
  }
  
  if (PanelMiddle > PanelLeft & PanelMiddle >PanelRight)
  {
    Serial.println("middle");
    delay(50);
  }
  
  if(PanelRight > PanelMiddle & PanelRight > PanelLeft)
  {
    Serial.println("right");
    delay(50);
  }
   
  if(x==1)
  {
    drawScreen(TRIANGLE);
  }
  if(x==2)
  {
    drawScreen(SQUARE);
  }
  if(x==3)
  {
    drawScreen(CIRCLE);
  }
  if(x==4)
  {
    drawScreen(RECTANGLE);
  }
    
char customKey = customKeypad.getKey();
  {
  if (customKey)
  {
    password[j] = customKey;
    j++;
  }
  if(j == 4) 
  {
    Serial.print("sifre ");
  for(int i = 0; i < 4; i++) 
  {
    Serial.print(password[i]);
  }
    Serial.println("");
    j=0;
  }
  if (Serial.available() > 0) {
                // read the incoming byte:
             // String incoming_data = Serial.readString();
    val = Serial.parseInt();
    
  if(val == 1)
  {
    x=1;
  }
  
  if(val== 2)
  {
    x=2;                 
  }
  
  if(val== 3)
  {
    x=3;          
  }
  
  if(val== 4)
  {
    x=4;             
  }
  
  if(val == 5)
  {
    SolarPanel.write(180);
  }

  if(val == 90)
  {
    SolarPanel.write(90);
  }
  
  if(val == 180)
  {
    SolarPanel.write(0);
  }
  
  if(val == 6)
  {
    digitalWrite(A3,HIGH);
    digitalWrite(A4,LOW);
    digitalWrite(A5,LOW);
    digitalWrite(A6,LOW);
  }
  
  if(val == 7)
  {
    digitalWrite(A4,HIGH);
    digitalWrite(A3,LOW);
    digitalWrite(A5,LOW);
    digitalWrite(A6,LOW);
  }
  
  if(val == 8)
  {
    digitalWrite(A5,HIGH);
    digitalWrite(A3,LOW);
    digitalWrite(A4,LOW);
    digitalWrite(A6,LOW);
  }
  
  if(val == 9)
  {
    digitalWrite(A6,HIGH);
    digitalWrite(A4,LOW);
    digitalWrite(A5,LOW);
    digitalWrite(A3,LOW);
  }
  if(val >182 & val< 340 )
  {
    Door.write(360-val);
  }
  
  if(val >340 )
  {
    if(val==360)
    {
      Water.write(-540+val);
      
  }
  delay(200);
  }
  
  if(val==540)
    Water.write(-540+val+180);
  }
  }
                
  if ( !mfrc522.PICC_IsNewCardPresent()) 
  {
    
    return ;
  }
  
  // Select one of the cards
  if ( !mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  String content= "";
  byte letter;
  
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  content.toUpperCase();
  if (content.substring(1) == "CA CD 01 10") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("lala");
  }
  
  if (content.substring(1) == "15 3F D2 65") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("po");
  }
 
  

}
 void  drawScreen(byte buffer2[])
 { 
   // Turn on each row in series
    for (byte i = 0; i < 8; i++)        // count next row
     {
        digitalWrite(rows[i], HIGH);    //initiate whole row
        for (byte a = 0; a < 8; a++)    // count next row
        {
          // if You set (~buffer2[i] >> a) then You will have positive
          digitalWrite(col[a], (buffer2[i] >> a) & 0x01); // initiate whole column
          
          delayMicroseconds(100);       // uncoment deley for diferent speed of display
          //delayMicroseconds(1000);
          //delay(10);
          //delay(100);
          
          digitalWrite(col[a], 1);      // reset whole column
        }
        digitalWrite(rows[i], LOW);     // reset whole row
        // otherwise last row will intersect with next row
    }
}
