#include <math.h>

int i = 0; //Iteraciones
unsigned long TiempoA = 0;  //Tiempo inicial
unsigned long TiempoB; //Tiempo final
const unsigned long PM = 5000; //Periodo de medición
int SalidaTermistor = A0; //Entrada digital
int AR;  
double R1 = 9730; //Resistencia conocida
double RT, T, Promedio;
double a = 0.001129148, b = 0.000234125, c =  0.0000000876741; //Constantes de la ecuación de Steinhart-Hart 


void setup() 
{
  Serial.begin(9600);
  TiempoA = millis();
}

void loop() 
{
  TiempoB = millis();  
  if (TiempoB - TiempoA >= PM)  
  {
    i++;
    AR = analogRead(SalidaTermistor);
    RT = R1 * (double)AR/(double)(1023-AR); //Resistencia del termistor a partir de la resistencia conocida y la salida analógica.
    T = 1.0 / (a + b*log(RT) + c*pow(log(RT), 3)); //Ecuación de Steinhart-Hart
    T = T - 273.15; //Kelvin a Celsius
    Promedio += T; //Registra la suma de todas las temperaturas medidas 
    TiempoA = TiempoB; //
    if (millis() >= 20000)  //Selecciona el número de medidas a partir del cual calcular el promedio
    {
      Promedio = Promedio/(double)i; 
      Serial.print("Tiempo: ");
      Serial.print(millis()/1000.0);
      Serial.print("\t");
      Serial.print("Temperatura: "); 
      Serial.print(T);
      Serial.println(" °C\t");
      Serial.print("Promedio: "); 
      Serial.print(Promedio);
      Serial.println(" C\n");
    }
    else
    {
      Serial.print("Tiempo: ");
      Serial.print(millis()/1000.0);
      Serial.print("\t");  
      Serial.print("Temperatura: "); 
      Serial.print(T);
      Serial.println(" °C\n");
     }
  }
}
