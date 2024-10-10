// --c++--

// --------------------------------------------------------------
//
// Jordi Bataller i Mascarell
// 2019-07-07
//
// --------------------------------------------------------------

// https://learn.sparkfun.com/tutorials/nrf52840-development-with-arduino-and-circuitpython

// https://stackoverflow.com/questions/29246805/can-an-ibeacon-have-a-data-payload

// --------------------------------------------------------------
// --------------------------------------------------------------
#include <bluefruit.h>

#undef min // vaya tela, están definidos en bluefruit.h y  !
#undef max // colisionan con los de la biblioteca estándar

//definimos los pines para Medidor.h
#define PIN_VGAS 28
#define PIN_VREF 29

// --------------------------------------------------------------
// --------------------------------------------------------------
#include "LED.h"
#include "PuertoSerie.h"

// -------------------------------------------------------------- 
//  Espacio de nombres para variables globales de la aplicación.
// --------------------------------------------------------------
namespace Globales {
  
  // Creación del objeto LED
  LED elLED ( /* NUMERO DEL PIN LED = */ 7 );

  // Configuración de la comunicación por puerto serie
  PuertoSerie elPuerto ( /* velocidad = */ 115200 ); // 115200 o 9600 o ...

  // Serial1 en el ejemplo de Curro creo que es la conexión placa-sensor 
};

// --------------------------------------------------------------
// --------------------------------------------------------------
#include "EmisoraBLE.h"
#include "Publicador.h"
#include "Medidor.h"


// --------------------------------------------------------------
//  Globales
//  Espacio de nombres para variables globales de la aplicación.
// --------------------------------------------------------------
namespace Globales {

// Creación del objeto Publicador
  Publicador elPublicador;

// Creación del objeto Medidor
  Medidor elMedidor= Medidor(PIN_VGAS, PIN_VREF);

}; // namespace

// --------------------------------------------------------------
// Inicializa los componentes de la plaquita.
// --------------------------------------------------------------
void inicializarPlaquita () {

  // de momento nada

} // ()

// --------------------------------------------------------------
// setup()
// Configuración inicial de la aplicación.
// --------------------------------------------------------------
void setup() {

  Globales::elPuerto.esperarDisponible();

  // 
  // 
  // 
  inicializarPlaquita();

  // Suspend Loop() to save power
  // suspendLoop();

  // 
  // 
  // 
  Globales::elPublicador.encenderEmisora();

  // Globales::elPublicador.laEmisora.pruebaEmision();
  
  // 
  // 
  // 
  Globales::elMedidor.iniciarMedidor();

  // 
  // 
  // 
  esperar( 1000 );

  Globales::elPuerto.escribir( "---- setup(): fin ---- \n " );

} // setup ()

// --------------------------------------------------------------
// Función inline para controlar el LED
// --------------------------------------------------------------
inline void lucecitas() {
  using namespace Globales;

  elLED.brillar( 100 ); // 100 encendido
  esperar ( 400 ); //  100 apagado
  elLED.brillar( 100 ); // 100 encendido
  esperar ( 400 ); //  100 apagado
  Globales::elLED.brillar( 100 ); // 100 encendido
  esperar ( 400 ); //  100 apagado
  Globales::elLED.brillar( 1000 ); // 1000 encendido
  esperar ( 1000 ); //  100 apagado
} // ()

// --------------------------------------------------------------
// loop ()
// Espacio de nombres para variables relacionadas con el loop principal.
// --------------------------------------------------------------
namespace Loop {
  uint8_t cont = 0;
};

// ..............................................................
//  Bucle principal de la aplicación.
// ..............................................................
void loop () {

  using namespace Loop;
  using namespace Globales;

  cont++;

  elPuerto.escribir( "\n---- loop(): empieza " );
  elPuerto.escribir( cont );
  elPuerto.escribir( "\n" );


  lucecitas();

  // 
  // mido y publico
  // 
  // Medición y publicación de datos de gas CO2
  int valorCO2 = elMedidor.medirGas();
  
  elPublicador.publicarCO2( valorCO2, cont, 1000 );
  
  // 
  // mido y publico
  // 
  // Medición y publicación de datos de temperatura
  int valorTemperatura = elMedidor.medirTemperatura();
  
  elPublicador.publicarTemperatura( valorTemperatura, cont, 10002);

  // 
  // prueba para emitir un iBeacon y poner
  // en la carga (21 bytes = uuid 16 major 2 minor 2 txPower 1 )
  // lo que queramos (sin seguir dicho formato)
  // 
  // Al terminar la prueba hay que hacer Publicador::laEmisora privado
  // 
  char datos[16] = {'h','o','l','a','M','u','n','d','o','M','a','n','u','e','l','a'};

  elPublicador.laEmisora.emitirAnuncioIBeacon((uint8_t*) datos ,1344,0,-50);

  esperar( 2000 );

  elPublicador.laEmisora.detenerAnuncio();
  
  // 
  // 
  // 
  elPuerto.escribir( "---- loop(): acaba ** " );
  elPuerto.escribir( cont );
  elPuerto.escribir( "\n" );
  
} // loop ()
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------