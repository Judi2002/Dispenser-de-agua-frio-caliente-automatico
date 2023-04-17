#include <infrarrojo.h>
infrarrojo estado(13);
infrarrojo estado1(12);
int valorIR = 0;
int valorIR1 = 0;
int led = 11;
int led_estado = 0;
int led1 = 10;
int led_estado1 = 0;

void setup() {
pinMode(led,OUTPUT);
pinMode(led1,OUTPUT);
Serial.begin(9600);
}

void loop() {
Serial.print("\n leyendo estado sensor 1: \n");
Serial.print(estado.lectura(valorIR));
led_estado = estado.lectura(valorIR);
Serial.print("\n leyendo estado sensor 2: \n");
Serial.print(estado1.lectura(valorIR1));
led_estado1 = estado1.lectura(valorIR1);
if(led_estado == 1)
  {
  digitalWrite(led,LOW);
  }
else
  {
  digitalWrite(led,HIGH);
  }
if(led_estado1 == 1)
  {
  digitalWrite(led1,LOW);
  }
else
  {
  digitalWrite(led1,HIGH);
  }
delay(100);
}
