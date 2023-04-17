const int cdwn = 5; //c = calor 
const int cup = 6;
const int fdwn =7; //f = frio
const int fup = 8; 
const int led2 = 12;
int cdeseado = 30;
int fdeseado = 16;
int estado_cdwn = 0;
int estado_cup = 0;
int estado_fdwn = 0;
int estado_fup = 0;

void setup() {
  Serial.begin (9600);
  pinMode(cdwn,INPUT);
  pinMode(cup,INPUT);
  pinMode(fdwn,INPUT);
  pinMode(fup,INPUT); 
  pinMode(led,OUTPUT);
}

void loop() {
  estado_cdwn = digitalRead(cdwn);
  estado_cup = digitalRead(cup);
  estado_fdwn = digitalRead(fdwn);
  estado_fup = digitalRead(fup);
  Serial.print("El frio deseado es:");
  Serial.println(fdeseado);
  Serial.print("El calor deseado es:");
  Serial.println(cdeseado);
  
  if(estado_cdwn == HIGH){
    cdeseado = cdeseado - 1;
    Serial.print("El frio deseado es:");
    Serial.println(fdeseado);
    Serial.print("El calor deseado es:");
    Serial.println(cdeseado);
    digitalWrite(led2, HIGH);
    delay(500);
    digitalWrite(led2, LOW);
  }
  if(estado_cup == HIGH){
    cdeseado = cdeseado + 1;
    Serial.print("El frio deseado es:");
    Serial.println(fdeseado);
    Serial.print("El calor deseado es:");
    Serial.println(cdeseado);
    digitalWrite(led2, HIGH);
    delay(500);
    digitalWrite(led2, LOW);
  }
  if(estado_fdwn == HIGH){
    fdeseado = fdeseado - 1;
    Serial.print("El frio deseado es:");
    Serial.println(fdeseado);
    Serial.print("El calor deseado es:");
    Serial.println(cdeseado);
    digitalWrite(led2, HIGH);
    delay(500);
    digitalWrite(led2, LOW);
  }
  if(estado_fup == HIGH){
    fdeseado = fdeseado + 1;
    Serial.print("El frio deseado es:");
    Serial.println(fdeseado);
    Serial.print("El calor deseado es:");
    Serial.println(cdeseado);
    digitalWrite(led2, HIGH);
    delay(500);
    digitalWrite(led2, LOW);
  }
  Serial.println();
  delay(1000);
}
