// -- mode: c++ --

// --------------------------------------------------------------
// Jordi Bataller i Mascarell
// --------------------------------------------------------------

#ifndef PUBLICADOR_H_INCLUIDO
#define PUBLICADOR_H_INCLUIDO

// --------------------------------------------------------------
// Clase que se encarga de publicar mediciones a través de anuncios iBeacon.
// --------------------------------------------------------------
class Publicador {

  // ............................................................
  // ............................................................
private:

  uint8_t beaconUUID[16] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

  // ............................................................
  // ............................................................
public:
  EmisoraBLE laEmisora {
	"ManuelaZazzaro", //  nombre emisora
	  0x004c, // fabricanteID (Apple)
	  4 // txPower
	  };
  
  const int RSSI = -53; // por poner algo, de momento no lo uso

  // ............................................................
  // ............................................................
public:

  // ............................................................
  // @enum MedicionesID
  // @brief Enum para identificar tipos de mediciones.
  // ............................................................
  enum MedicionesID  {
	CO2 = 11,
	TEMPERATURA = 12,
	RUIDO = 13
  };

  // --------------------------------------------------------------
  // @brief Constructor de la clase Publicador.
  // --------------------------------------------------------------

  Publicador( ) {
	// ATENCION: no hacerlo aquí. (*this).laEmisora.encenderEmisora();
	// Pondremos un método para llamarlo desde el setup() más tarde
  } // ()

  // ............................................................
  // @brief Enciende la emisora para empezar a emitir anuncios.
  // ............................................................
  void encenderEmisora() {
	(*this).laEmisora.encenderEmisora();
  } // ()

  // ............................................................
  // @brief Publica una medición de CO2 a través de un anuncio iBeacon.
  // @param valorCO2 double: Valor de CO2 a publicar.
  // @param contador uint8_t: Contador para identificar la medición.
  // @param tiempoEspera long: Tiempo de espera en milisegundos antes de detener el anuncio.
  // ............................................................
  void publicarCO2( double valorCO2, uint8_t contador, long tiempoEspera ) {

	//
	// 1. empezamos anuncio
	//
	uint16_t major = (uint16_t) (valorCO2 * 10);
	(*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID, major, valorCO2, (*this).RSSI);
  
  /*
	Globales::elPuerto.escribir( "   publicarCO2(): valor=" );
	Globales::elPuerto.escribir( valorCO2 );
	Globales::elPuerto.escribir( "   contador=" );
	Globales::elPuerto.escribir( contador );
	Globales::elPuerto.escribir( "   todo="  );
	Globales::elPuerto.escribir( major );
	Globales::elPuerto.escribir( "\n" );
	*/

	//
	// 2. esperamos el tiempo que nos digan
	//
	esperar( tiempoEspera );

	//
	// 3. paramos anuncio
	//
	(*this).laEmisora.detenerAnuncio();
  } // ()

  // ............................................................
  // @brief Publica una medición de temperatura a través de un anuncio iBeacon.
  // @param valorTemperatura int16_t: Valor de temperatura a publicar.
  // @param contador uint8_t: Contador para identificar la medición.
  // @param tiempoEspera long: Tiempo de espera en milisegundos antes de detener el anuncio.
  // ............................................................
  void publicarTemperatura( int16_t valorTemperatura, uint8_t contador, long tiempoEspera ) {

	uint16_t major = (MedicionesID::TEMPERATURA << 8) + contador;
	(*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID, major, valorTemperatura, (*this).RSSI);
	
  esperar( tiempoEspera );
  
  (*this).laEmisora.detenerAnuncio();
  } // ()
	
}; // class

// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
#endif