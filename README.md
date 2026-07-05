# Procesado y Filtrado de Señales Biomédicas (Arduino)

Este repositorio contiene el código de adquisición y acondicionamiento digital desarrollado para la captura de temperatura corporal. 

El objetivo de este proyecto práctico fue resolver las discrepancias y el ruido inherente a la lectura de sensores físicos usando el termistor NTC de la plataforma e-Health y el sensor integrado TMP36 y utilizando microcontroladores. 

## Aspectos a comentar
* **Calibración Hardware/Software:** Implementación de la lectura de un Puente de Wheatstone para el termistor NTC, logrando un error relativo mínimo (0.51%) frente a mediciones de multímetro de alta precisión.
* **Procesamiento de Señal:** Desarrollo en C++ de un filtro digital de media móvil con validación por error relativo.
* **Tolerancia al Ruido:** El algoritmo descarta variaciones anómalas que superen un 15% de desviación respecto a la media, eliminando eficazmente los picos parásitos ambientales o del conversor ADC sin perder latencia en la lectura.

Este trabajo previo aporta la base para diseñar algoritmos que identifiquen datos falsos o anomalías médicas en el mismo dispositivo de medición.
