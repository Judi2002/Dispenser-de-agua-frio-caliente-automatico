#include <OneWire.h>

#include <OneWire.h>                
#include <DallasTemperature.h>
#define Pin 2     
#define Pinn 3                 
OneWire ourWire1(Pin);
OneWire ourWire2(Pinn);               
DallasTemperature sensor1(&ourWire1);
DallasTemperature sensor2(&ourWire2);

void setup() {
delay(1000);
Serial.begin(9600);
sensor1.begin(); 
sensor2.begin();                    
}
 
void loop() {
sensor1.requestTemperatures();    
sensor2.requestTemperatures();   
Serial.print(sensor1.getTempCByIndex(0)); 
Serial.println(" sensor 1");
Serial.print(sensor2.getTempCByIndex(1)); 
Serial.println(" sensor 2 \n");
 
delay(1000);                         
}
