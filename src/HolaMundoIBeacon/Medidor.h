// -- mode: c++ --
#ifndef MEDIDOR_H_INCLUIDO
#define MEDIDOR_H_INCLUIDO

#include <Arduino.h> // Incluir la librería de Arduino para funciones como analogRead, pinMode, etc.

// ------------------------------------------------------
// Clase Medidor para medir gas y temperatura
// ------------------------------------------------------
class Medidor {

private:
    uint8_t pinVref;    // Pin para referencia de voltaje
    uint8_t pinVgas;    // Pin para leer el voltaje del gas
    double ppmOzono;    // Partes por millón de Ozono (O3)
    float vref;         // Voltaje de referencia
    float vgas;         // Voltaje del gas

    // Función para convertir valor digital a voltios
    float digToVolt(int Vin) { 
        return ((Vin * 3.3) / 1024);
    }

public:

    //Contructor vacio
    Medidor(){

    }

    // Constructor
    Medidor(uint8_t pinVgas, uint8_t pinVref)
        : pinVref(pinVref), pinVgas(pinVgas), ppmOzono(0), vref(0), vgas(0) {
    }

    // Inicializa el medidor configurando los pines
    void iniciarMedidor() {
        vgas = 0;
        vref = 0;
        ppmOzono = 0;
        pinMode(pinVref, INPUT);
        pinMode(pinVgas, INPUT);
    }

    // Mide el gas y devuelve el valor de ppm de ozono
    double medirGas() {
        int Agas = analogRead(pinVgas);
        int Aref = analogRead(pinVref);

        vgas = digToVolt(Agas);
        vref = digToVolt(Aref);

        // Constante de conversión basada en la especificación del sensor
        const double M = -41.96 * 499 * (0.000001);

        int ppm10 = (int) ( (double) ppmOzono * 100);

       
       double res = ((1 / M) * (vgas - vref));
        // Si el resultado es negativo, devuelve 0
        ppmOzono = res > 0 ? res : 0; 
        
        Serial.print("M:");
        Serial.println(M);
        Serial.print("Vgas: ");
        Serial.println(vgas);
        Serial.print("Vref: ");
        Serial.println(vref);
        Serial.print("PPM OZONO ");
        Serial.println(ppmOzono);
        Serial.print("PPMx10 OZONO ");
        Serial.println(ppm10);

        return ppmOzono;
    }

    // Función de ejemplo para medir la temperatura
    int medirTemperatura() {
        return -12; // Ejemplo, cambiar según el sensor de temperatura
    }

}; // class Medidor

#endif // MEDIDOR_H_INCLUIDO