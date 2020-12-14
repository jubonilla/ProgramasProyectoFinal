#include <OneWire.h>                
#include <DallasTemperature.h>
 
OneWire ourWire(7);                //Se establece el pin 7 como bus OneWire
 
DallasTemperature sensors(&ourWire); //Se declara una variable u objeto para el sensor

void setup() 
{
Serial.begin(9600);
sensors.begin();   //Se inicia el sensor
}
 
void loop() 
{
sensors.requestTemperatures();   //Se envía el comando para leer la temperatura
float temp= sensors.getTempCByIndex(0); //Se obtiene la temperatura en ºC

Serial.print("Temperatura= ");
Serial.print(temp);
Serial.println(" C");
delay(5000);                     
}
