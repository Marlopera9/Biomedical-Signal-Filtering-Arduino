/*
 * Práctica 2 - Instrumentación Biomédica
 * Lectura y filtrado de temperatura (NTC e-Health y TMP36)
 */

#include <eHealth.h>

// Variables del filtro de media móvil
const int numMuestras = 10;       
float lecturasTMP36[numMuestras]; 
int indice = 0;                   
float totalTMP36 = 0;             
bool primer_ciclo = true;         

// Descarte de picos parásitos (>15% de error)
const float umbral_error = 0.15; 

void setup() {
  Serial.begin(115200); 
}

void loop() {
  
  // NTC e-Health
  float temp_eHealth = eHealth.getTemperature();

  int valorDigitalA3 = analogRead(A3);
  float voltajeA3 = valorDigitalA3 * (5.0 / 1023.0); 

  // Ajuste del puente Wheatstone para RT
  float ganancia = 5.0;
  float RefTension = 3.0; 
  float Ra = 4700.0;
  float Rc = 4700.0;
  float Rb = 821.0;

  float voltage2 = voltajeA3 / ganancia; 
  float aux = (voltage2 / RefTension) + (Rb / (Rb + Ra));
  float resistenciaNTC = Rc * aux / (1.0 - aux);

  // Sensor TMP36 en A5
  int valorDigitalA5 = analogRead(A5);
  float voltajeTMP36_mV = valorDigitalA5 * (5000.0 / 1023.0); 
  float temp_TMP36_cruda = (voltajeTMP36_mV - 500.0) / 10.0; 

  // Filtro de media móvil con tolerancia
  if (primer_ciclo) {
    for (int i = 0; i < numMuestras; i++) {
      lecturasTMP36[i] = temp_TMP36_cruda;
      totalTMP36 += temp_TMP36_cruda;
    }
    primer_ciclo = false;
  }

  float media_actual = totalTMP36 / numMuestras;
  float error_relativo = 0.0;
  
  if (media_actual != 0) { 
    error_relativo = abs(temp_TMP36_cruda - media_actual) / abs(media_actual);
  }

  // Si el valor es estable, lo metemos en la ventana
  if (error_relativo <= umbral_error) {
    totalTMP36 -= lecturasTMP36[indice]; 
    lecturasTMP36[indice] = temp_TMP36_cruda;        
    totalTMP36 += lecturasTMP36[indice]; 
    
    indice++; 
    if (indice >= numMuestras) {
      indice = 0; 
    }
  }
  float temp_TMP36_filtrada = totalTMP36 / numMuestras; 

  // Salida para Serial Plotter
  Serial.print("Temp_eHealth:"); 
  Serial.print(temp_eHealth, 2); 
  Serial.print(","); 
  
  /*
  // Descomentar para debug de voltajes
  Serial.print("Voltaje_A3:"); Serial.print(voltajeA3, 2); Serial.print(",");
  Serial.print("Resistencia_NTC:"); Serial.print(resistenciaNTC, 2); Serial.print(",");
  */

  Serial.print("Temp_TMP36_Cruda:"); 
  Serial.print(temp_TMP36_cruda, 2); 
  Serial.print(",");
  
  Serial.print("Temp_TMP36_Filtrada:"); 
  Serial.println(temp_TMP36_filtrada, 2); 

  delay(100); 
}
