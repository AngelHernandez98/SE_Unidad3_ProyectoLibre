#include <dth.h>// Libreria del Sensor DHT11
#include <LiquidCrystal_I2C.h> // Libreria de la Pantalla
LiquidCrystal_I2C lcd(0x27, 16, 2); // Define Modelo de Pantalla
dth DTH; // Para usar Sensor
#define DHT11_PIN 3 // Pin a usar
long lecturaP;
// Variables para almacenar los valores obtenidos por el Sensor
int humedad;
int temperatura;
int TempActivacion = 0 // Temperatura a la que se activa el Relay

// Proyecto
void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  pinMode(4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  lecturaPotenciometro();
  lecturaDHT11;
  WriteLCD();

  //Se activa el Relay
  if(TempActivacion > temperatura && TempActivacion - temperatura > 1){
    digitalWrite(4, HIGH);
  }
  //Se desactiva el Relay
  if(TempActivacion < temperatura){
    digitalWrite(4, LOW);
  }
  delay(1000);
  }

}

void lecturaDHT11(){
  DHT.readll(DHT11_PIN);
  temperatura = DHT.temperature;
  humedad = DHT.humidity;
}

void lecturaPotenciometro(){
  lecturaP = analogRead(A0); //Se lee el potenciometro
  TempActivacion = map(lecturaP, 0, 1023, 0, 50);
}

void WriteLDC(){
  ldc.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("T:"));
  lcd.print(temperatura);
  lcd.print(F("C:"));
  lcd.print(F("H:"));
  lcd.print(humedad)
  lcd.print(F("%"));
  lcd.setCursor(0, 1);
  lcd.print(F("Se activa a: "));
  lcd.print(TempActivacion);
  lcd.print(F("C"));
}
