// -*- mode: c++ -*-

// ----------------------------------------------------------
// Jordi Bataller i Mascarell
// 2019-07-17
// ----------------------------------------------------------
#ifndef SERVICIO_EMISORA_H_INCLUIDO
#define SERVICIO_EMISORA_H_INCLUIDO

// ----------------------------------------------------
// ----------------------------------------------------
#include <vector>

// ----------------------------------------------------
// @brief Pone al revés el contenido de una array en el mismo array.
// @tparam T El tipo de datos del array.
// @param p T*: El puntero al array.
// @param n int: El tamaño del array.
// @returns T*: El puntero al array con los elementos al revés.
// ----------------------------------------------------
template< typename T >
T *  alReves( T * p, int n ) {
  T aux;

  for( int i=0; i < n/2; i++ ) {
	aux = p[i];
	p[i] = p[n-i-1];
	p[n-i-1] = aux;
  }
  return p;
} // ()

// ----------------------------------------------------
// @brief Convierte una cadena de caracteres a un array de uint8_t al revés.
// @param pString const char*: El puntero a la cadena de caracteres.
// @param pUint uint8_t*: El puntero al array de uint8_t.
// @param tamMax int: El tamaño máximo del array.
// @returns uint8_t*: El puntero al array de uint8_t con los elementos al revés.
// ----------------------------------------------------
uint8_t * stringAUint8AlReves( const char * pString, uint8_t * pUint, int tamMax ) {

	int longitudString =  strlen( pString );
	int longitudCopiar = ( longitudString > tamMax ? tamMax : longitudString );
	// copio nombreServicio -> uuidServicio pero al revés
	for( int i=0; i<=longitudCopiar-1; i++ ) {
	  pUint[ tamMax-i-1 ] = pString[ i ];
	} // for

	return pUint;
} // ()

// ----------------------------------------------------------
// @class ServicioEnEmisora
// @brief Clase para manejar el servicio y las características en un emisor BLE.
// ----------------------------------------------------------
class ServicioEnEmisora {

public:


  // --------------------------------------------------------
  // --------------------------------------------------------

  // .........................................................
  // @brief Tipo de función de callback para la escritura de características.
  // @param conn_handle uint16_t: El handle de la conexión.
  // @param chr BLECharacteristic*: El puntero a la característica BLE.
  // @param data uint8_t*: El puntero a los datos.
  // @param len uint16_t: La longitud de los datos.
  // .........................................................
  using CallbackCaracteristicaEscrita = void ( uint16_t conn_handle,
											   BLECharacteristic * chr,
											   uint8_t * data, uint16_t len); 

  // .........................................................
  // @class Caracteristica
  // @brief Clase para manejar una característica BLE
  // .........................................................
  class Caracteristica {
  private:
	uint8_t uuidCaracteristica[16] = { // el uuid se copia aquí (al revés) a partir de un string-c
	  // least signficant byte, el primero
	  '0', '1', '2', '3', 
	  '4', '5', '6', '7', 
	  '8', '9', 'A', 'B', 
	  'C', 'D', 'E', 'F'
	};

	// 
	// 
	// 
	BLECharacteristic laCaracteristica;

  public:

	// .........................................................
  //@brief Constructor de la clase Caracteristica.
  // @param nombreCaracteristica_ const char*: El nombre de la característica.
	// .........................................................
	Caracteristica( const char * nombreCaracteristica_ )
	  :
	  laCaracteristica( stringAUint8AlReves( nombreCaracteristica_, &uuidCaracteristica[0], 16 ) )
	{
	  
	} // ()

	// .........................................................
  // @brief Constructor de la clase Caracteristica con propiedades y permisos.
  // @param nombreCaracteristica_ const char*: El nombre de la característica.
  // @param props uint8_t: Las propiedades de la característica.
  // @param permisoRead SecureMode_t: El permiso de lectura.
  // @param permisoWrite SecureMode_t: El permiso de escritura.
  // @param tam uint8_t: El tamaño de los datos.
	// .........................................................
	Caracteristica( const char * nombreCaracteristica_ ,
					uint8_t props,
					SecureMode_t permisoRead,
					SecureMode_t permisoWrite, 
					uint8_t tam ) 
	  :
	  Caracteristica( nombreCaracteristica_ ) // llamada al otro constructor
	{
	  (*this).asignarPropiedadesPermisosYTamanyoDatos( props, permisoRead, permisoWrite, tam );
	} // ()

  private:
	// .........................................................
	// CHR_PROPS_WRITE , CHR_PROPS_READ ,  CHR_PROPS_NOTIFY 
  // @brief Asigna las propiedades de la característica.
  // @param props uint8_t: Las propiedades de la característica
	// .........................................................
	void asignarPropiedades ( uint8_t props ) {
	  // no puedo escribir AUN si el constructor llama a esto: Serial.println( " laCaracteristica.setProperties( props ); ");
	  (*this).laCaracteristica.setProperties( props );
	} // ()

	// .........................................................
	// SecureMode_t::SECMODE_OPEN  , SecureMode_t::SECMODE_NO_ACCESS
  //  @brief Asigna los permisos de la característica.
  // @param permisoRead SecureMode_t: El permiso de lectura.
  // @param permisoWrite SecureMode_t: El permiso de escritura.
	// .........................................................
	void asignarPermisos( SecureMode_t permisoRead, SecureMode_t permisoWrite ) {
	  // no puedo escribir AUN si el constructor llama a esto: Serial.println( "laCaracteristica.setPermission( permisoRead, permisoWrite ); " );
	  (*this).laCaracteristica.setPermission( permisoRead, permisoWrite );
	} // ()

	// .........................................................
  //  @brief Asigna el tamaño de los datos de la característica.
  // @param tam uint8_t: El tamaño de los datos.
	// .........................................................
	void asignarTamanyoDatos( uint8_t tam ) {
	  // no puedo escribir AUN si el constructor llama a esto: Serial.print( " (*this).laCaracteristica.setFixedLen( tam = " );
	  // no puedo escribir AUN si el constructor llama a esto: Serial.println( tam );
	  // (*this).laCaracteristica.setFixedLen( tam );
	  (*this).laCaracteristica.setMaxLen( tam );
	} // ()

  public:
	// .........................................................
  // @brief Asigna las propiedades, permisos y tamaño de los datos de la característica.
  // @param props uint8_t: Las propiedades de la característica.
  // @param permisoRead SecureMode_t: El permiso de lectura.
  // @param permisoWrite SecureMode_t: El permiso de escritura.
  // @param tam uint8_t: El tamaño de los datos.
	// .........................................................
	void asignarPropiedadesPermisosYTamanyoDatos( uint8_t props,
												 SecureMode_t permisoRead,
												 SecureMode_t permisoWrite, 
												 uint8_t tam ) {
	  asignarPropiedades( props );
	  asignarPermisos( permisoRead, permisoWrite );
	  asignarTamanyoDatos( tam );
	} // ()
												 

	// .........................................................
  // @brief Escribe datos en la característica.
  // @param str const char*: Cadena de caracteres a escribir.
  // @returns uint16_t: Número de bytes escritos.
	// .........................................................
	uint16_t escribirDatos( const char * str ) {
	  // Serial.print( " return (*this).laCaracteristica.write( str  = " );
	  // Serial.println( str );

	  uint16_t r = (*this).laCaracteristica.write( str );

	  // Serial.print( ">>>Escritos " ); Serial.print( r ); Serial.println( " bytes con write() " );

	  return r;
	} // ()

	// .........................................................
  // @brief Notifica datos de la característica.
  // @param str const char*: Cadena de caracteres a notificar.
  // @returns uint16_t: Número de bytes notificados.
	// .........................................................
	uint16_t notificarDatos( const char * str ) {
	  
	  uint16_t r = laCaracteristica.notify( &str[0] );

	  return r;
	} //  ()

	// .........................................................
  // @brief Instala un callback para cuando la característica sea escrita.
  // @param cb CallbackCaracteristicaEscrita: Callback a instalar..
	// .........................................................
	void instalarCallbackCaracteristicaEscrita( CallbackCaracteristicaEscrita cb ) {
	  (*this).laCaracteristica.setWriteCallback( cb );
	} // ()

	// .........................................................
  //  @brief Activa la característica.
	// .........................................................
	void activar() {
	  err_t error = (*this).laCaracteristica.begin();
	  Globales::elPuerto.escribir(  " (*this).laCaracteristica.begin(); error = " );
	  Globales::elPuerto.escribir(  error );
	} // ()

  }; // class Caracteristica
  
  // --------------------------------------------------------
  // --------------------------------------------------------
private:
  
  uint8_t uuidServicio[16] = { // el uuid se copia aquí (al revés) a partir de un string-c
	// least signficant byte, el primero
	'0', '1', '2', '3', 
	'4', '5', '6', '7', 
	'8', '9', 'A', 'B', 
	'C', 'D', 'E', 'F'
  };

  //
  //
  //
  BLEService elServicio;

  //
  //
  //
  std::vector< Caracteristica * > lasCaracteristicas;

public:
  
  // .........................................................
  // @brief Constructor de la clase ServicioEnEmisora.
  // @param nombreServicio_ const char*: Nombre del servicio.
  // .........................................................
  ServicioEnEmisora( const char * nombreServicio_ )
	:
	elServicio( stringAUint8AlReves( nombreServicio_, &uuidServicio[0], 16 ) )
  {
	
  } // ()
  
  // .........................................................
  // @brief Escribe el UUID del servicio en el puerto serie.
  // .........................................................
  void escribeUUID() {
	Serial.println ( "**********" );
	for (int i=0; i<= 15; i++) {
	  Serial.print( (char) uuidServicio[i] );
	}
	Serial.println ( "\n**********" );
  } // ()

  // .........................................................
  // @brief Añade una característica al servicio.
  // @param car Caracteristica&: Referencia a la característica a añadir.
  // .........................................................
  void anyadirCaracteristica( Caracteristica & car ) {
	(*this).lasCaracteristicas.push_back( & car );
  } // ()

  // .........................................................
  // @brief Activa el servicio y sus características.
  // .........................................................
  void activarServicio( ) {
	// entiendo que al llegar aquí ya ha sido configurado
	// todo: características y servicio

	err_t error = (*this).elServicio.begin();
	Serial.print( " (*this).elServicio.begin(); error = " );
	Serial.println( error );

	for( auto pCar : (*this).lasCaracteristicas ) {
	  (*pCar).activar();
	} // for

  } // ()

  // .........................................................
  // @brief Conversión de tipo a BLEService.
  // @returns BLEService&: Referencia al servicio BLE.
  // .........................................................
  operator BLEService&() {
	// "conversión de tipo": si pongo esta clase en un sitio donde necesitan un BLEService
	return elServicio;
  } // ()
	
}; // class

#endif

// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------

