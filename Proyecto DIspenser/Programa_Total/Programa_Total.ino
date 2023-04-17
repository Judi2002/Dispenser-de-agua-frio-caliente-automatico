#include <LiquidCrystal_I2C.h>
#include <infrarrojo.h>  //Pines usados: 2-3-4-5-6-7-8-9-12-13
#include <OneWire.h>     //Pines libres: 0-1-10-11           
#include <DallasTemperature.h> /*Programado: Infrarrojo-Temperaturas-Teclado-Caudal-Controladores-Display */
const int STF = 2;      //Sensor Temperatura Frio  
const int STC = 3;     //Sensor Temperatura Caliente
const int REV1 = A2;  //Rele electrovalvula 1    
const int REV = A3;  //Rele electrovalvula 0
const int cdwn = 5; //c = calor 
const int cup = 6;
const int fdwn =7; //f = frio
const int fup = 8; 
const int ledcf = 9; //Led por cambios de config  
const int sensorPin = 4; //Caudalimetro
const int RRE = A0; //Rele Resistencia Electrica
const int RCP = A1; //Rele Celda Peltier       
OneWire ourWire1(STF); 
OneWire ourWire2(STC);               
DallasTemperature sensor1(&ourWire1);
DallasTemperature sensor2(&ourWire2);
infrarrojo estado(13);
infrarrojo estado1(12);
int valorIR = 0;
int valorIR1 = 0;
int REV_estado = 0;
int REV_estado1 = 0;
int cdeseado = 30;
int fdeseado = 16;
int estado_cdwn = 0;
int estado_cup = 0;
int estado_fdwn = 0;
int estado_fup = 0;
int valors1 = 0;
int valors2 = 0;
const int measureInterval = 2500;
volatile int pulseConter;
const float factorK = 7.5;
float volume = 0;
long t0 = 0;
LiquidCrystal_I2C lcd(0x27,20,4);

void ISRCountPulse()
{
   pulseConter++;
}
 
float GetFrequency()
{
   pulseConter = 0;
   interrupts();
   delay(measureInterval);
   noInterrupts();
   return (float)pulseConter * 1000 / measureInterval;
}
 
void SumVolume(float dV)
{
   volume += dV / 60 * (millis() - t0) / 1000.0;
   t0 = millis();
}

void setup() {
pinMode(REV,OUTPUT);
pinMode(REV1,OUTPUT);
pinMode(cdwn,INPUT);
pinMode(cup,INPUT);
pinMode(fdwn,INPUT);
pinMode(fup,INPUT); 
pinMode(ledcf,OUTPUT);
pinMode(RRE,OUTPUT);
pinMode(RCP,OUTPUT);
sensor1.begin(); 
sensor2.begin(); 
attachInterrupt(digitalPinToInterrupt(sensorPin), ISRCountPulse, RISING);
t0 = millis();
Serial.begin(9600);
}

void loop() {
sensor1.requestTemperatures();    
sensor2.requestTemperatures();   
valors1=digitalRead(sensor1.getTempCByIndex(0));
valors2=digitalRead(sensor2.getTempCByIndex(1)); //hacer el calculo 
  lcd.init();                     
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Temp fria");
  lcd.print(sensor1.getTempCByIndex(0));
  lcd.setCursor(0,1);
  lcd.print("Temp caliente");
  lcd.print(sensor2.getTempCByIndex(1));
  lcd.setCursor(0,2);
  lcd.print("Agua consumida en el");
  lcd.setCursor(0,3);
  lcd.print("dia:");
if(valors1 > fdeseado){
  analogWrite(RCP, HIGH);
}else{
  analogWrite(RCP, LOW);
}
if(valors2 < cdeseado){
  analogWrite(RRE, HIGH);
}else{
  analogWrite(RRE, LOW);
}
estado_cdwn = digitalRead(cdwn);
estado_cup = digitalRead(cup);
estado_fdwn = digitalRead(fdwn);
estado_fup = digitalRead(fup);

float frequency = GetFrequency(); //fr en hz
float flow_Lmin = frequency / factorK; // calcular caudal L/min
SumVolume(flow_Lmin);

lcd.setCursor(4,4);
lcd.print(" (L/min)\tConsumo:");

REV_estado = estado.lectura(valorIR);
REV_estado1 = estado1.lectura(valorIR1);

if(estado_cdwn == HIGH){
  cdeseado = cdeseado - 1;
  lcd.setCursor(0,2);
  lcd.print("El calor deseado es:");
  lcd.print(cdeseado);
  digitalWrite(ledcf, HIGH);
  delay(500);
  digitalWrite(ledcf, LOW);
}
if(estado_cup == HIGH){
  cdeseado = cdeseado + 1;
  lcd.setCursor(0,2);
  lcd.print("El calor deseado es:");
  lcd.print(cdeseado);
  digitalWrite(ledcf, HIGH);
  delay(500);
  digitalWrite(ledcf, LOW);
}
if(estado_fdwn == HIGH){
  fdeseado = fdeseado - 1;
  lcd.setCursor(0,1);
  lcd.print("El frio deseado es:");
  lcd.print(fdeseado);
  digitalWrite(ledcf, HIGH);
  delay(500);
  digitalWrite(ledcf, LOW);
}
if(estado_fup == HIGH){
  fdeseado = fdeseado + 1;
  lcd.setCursor(0,1);
  lcd.print("El frio deseado es:");
  lcd.print(fdeseado);
  digitalWrite(ledcf, HIGH);
  delay(500);
  digitalWrite(ledcf, LOW);
}

if(REV_estado == 1)
  {
  digitalWrite(REV,HIGH);
  }
else
  {
  digitalWrite(REV,LOW);
  }
if(REV_estado1 == 1)
  {
  digitalWrite(REV1,HIGH);
  }
else
  {
  digitalWrite(REV1,LOW);
  }
delay(1000);
}
