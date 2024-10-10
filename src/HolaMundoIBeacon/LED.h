// -*- mode: c++ -*-

#ifndef LED_H_INCLUIDO
#define LED_H_INCLUIDO

// ----------------------------------------------------------
// Jordi Bataller i Mascarell
// 2019-07-07
// ----------------------------------------------------------

// ----------------------------------------------------------
// @brief Espera un tiempo específico.
// @param tiempo Tiempo en milisegundos que la función debe esperar.
// ----------------------------------------------------------
void esperar (long tiempo) {
  delay (tiempo);
}

// ----------------------------------------------------------
// Clase para controlar un LED.
// ----------------------------------------------------------
class LED {
private:
  int numeroLED; ///< Número del pin del LED
  bool encendido; ///< Estado del LED (encendido o apagado).
public:

  // .........................................................
  // @brief Constructor de la clase LED.
  // @param numero Número del pin del LED.
  // .........................................................
  LED (int numero)
	: numeroLED (numero), encendido(false)
  {
	pinMode(numeroLED, OUTPUT);
	apagar ();
  }

  // .........................................................
  // @brief Enciende el LED
  // .........................................................
  void encender () {
	digitalWrite(numeroLED, HIGH); 
	encendido = true;
  }

  // .........................................................
  // @brief Apaga el LED.
  // .........................................................
  void apagar () {
	  digitalWrite(numeroLED, LOW);
	  encendido = false;
  }

  // .........................................................
  // @brief Alterna el estado del LED
  // .........................................................
  void alternar () {
	if (encendido) {
	  apagar();
	} else {
	  encender ();
	}
  } // ()

  // .........................................................
  // @brief Hace que el LED brille durante un tiempo específico.
  // @param tiempo Tiempo en milisegundos que el LED debe brillar.
  // .........................................................
  void brillar (long tiempo) {
	encender ();
	esperar(tiempo); 
	apagar ();
  }
}; // class

// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
#endif
