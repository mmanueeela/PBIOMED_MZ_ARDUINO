
// -*- mode: c++ -*-

// ----------------------------------------------------------
// Jordi Bataller i Mascarell
// 2019-07-07
// ----------------------------------------------------------

#ifndef PUERTO_SERIE_H_INCLUIDO
#define PUERTO_SERIE_H_INCLUIDO

// ----------------------------------------------------------
// Clase para manejar la comunicación por puerto serie.
// ----------------------------------------------------------
class PuertoSerie  {

public:
  // .........................................................
  // Constructor de la clase PuertoSerie.
  // .........................................................
  PuertoSerie (long baudios) {
	Serial.begin( baudios );
	// mejor no poner esto aquí: while ( !Serial ) delay(10);   
  } // ()

  // .........................................................
  // Espera un tiempo para asegurar que el puerto serie esté disponible.
  // .........................................................
  void esperarDisponible() {

	delay(10);   

  } // ()

  // .........................................................
  // Escribe un mensaje a través del puerto serie.
  // T El tipo de datos del mensaje a escribir.
  // mensaje T: El mensaje a enviar por el puerto serie.
  // .........................................................
  template<typename T>
  void escribir (T mensaje) {
	Serial.print( mensaje );
  } // ()
  
}; // class PuertoSerie

// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
#endif
