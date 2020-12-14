#include <math.h>
#include <OneWire.h>                
#include <DallasTemperature.h>

//Aproximación de dos puntos sensor analógico
double AExperimental2 = 92.09; //Medición experimental del límite superior
double AExperimental1 = 21;  //Medición experimental del límite inferior
double AEstimado2 = 92;  //Valor real del límite superior
double AEstimado1 = 18;  //Valor real del límite inferior
double ARangoExperimental = AExperimental2 - AExperimental1;
double ARangoEstimado = AEstimado2 - AEstimado1;

//Aproximación de dos puntos sensor digital
double DExperimental2 = 91.56;  //Medición experimental del límite superior
double DExperimental1 = 22;  //Medición experimental del límite inferior
double DEstimado2 = 92;  //Valor real del límite superior
double DEstimado1 = 19.5;  //Valor real del límite inferior
double DRangoExperimental = DExperimental2 - DExperimental1;
double DRangoEstimado = DEstimado2 - DEstimado1;

//Sensor DS18B20
OneWire ourWire(7); //Se establece el pin 7 como bus OneWire
DallasTemperature sensors(&ourWire); //Se declara una variable u objeto para el sensor

//Termistor
unsigned long TiempoMedido = 0; //Tiempo medido
unsigned long PeriodoM = 30000; //Periodo de medición
int SalidaTermistor = A0; //Entrada analógica
int AR;  
double R1 = 9730; //Resistencia conocida
double RT, T, Promedio;
double a =  0.001129148, b = 0.000234125, c = 0.0000000876741; //Constantes de la ecuación de Steinhart-Hart 


void setup() 
{
  Serial.begin(9600);
  sensors.begin();   //Se inicializa el sensor DS18B20
}

void loop() 
{
  if (millis() - TiempoMedido >= PeriodoM)  
  {
    //DS18B20
    sensors.requestTemperatures();   //Se envía el comando para leer la temperatura
    float temp = sensors.getTempCByIndex(0); //Se obtiene la temperatura en ºC
    TiempoMedido = millis(); 
    temp = (temp-DExperimental1)*(DRangoEstimado/DRangoExperimental) + DEstimado1; //Valor corregido
    
    //Termistor
    AR = analogRead(SalidaTermistor);
    RT = R1 * (double)AR/(double)(1023-AR); //Resistencia del termistor a partir de la resistencia conocida y la salida analógica.
    T = 1.0 / (a + b*log(RT) + c*pow(log(RT), 3)); //Ecuación de Steinhart-Hart
    T = T - 273.15; //Kelvin a Celsius
    T = (T-AExperimental1)*(ARangoEstimado/ARangoExperimental) + AEstimado1; //Valor corregido

    //Tiempo en minutos
    Serial.print(millis()/1000.0);
    Serial.print("  \t"); 
    //Temperatura variable
    Serial.print(temp);
    Serial.print("  \t");  
    //Temperatura del medio
    Serial.print(T);
    Serial.print("\n");
  }
}
