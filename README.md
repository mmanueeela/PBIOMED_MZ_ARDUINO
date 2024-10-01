# 🌳 PBIOMED_MZ_ARDUINO
El siguiente repositorio contiene los ficheros correspondiente a la parte de Arduino del proyecto 3A (Proyecto Aplicaciones de Biometría y Medio Ambiente). Incluye un programa principal llamado **Emison_Datos_Arduino.ino** y distintas bibliotecas creadas por Jordi Bataller i Mascarell: **EmisoraBLE.h**, **Medidor.h**, **Publicador.h**, **PuertoSerie.h** y **ServicioEnEmisora.h**.
# 🔎 Descripción del problema que el proyecto resuelve
Este proyecto implementa un sistema para medir y transmitir datos ambientales, como CO2 y temperatura, utilizando una placa con Bluetooth Low Energy (BLE). Los datos se envían de forma inalámbrica a dispositivos cercanos, y también permite emitir mensajes personalizados usando la tecnología iBeacon. Además, incluye optimización para ahorrar energía y notificaciones visuales mediante un LED.
# 📁 Contenido del Repositorio
_HolaMundoIBeacon.ino_: El archivo principal del programa de Arduino.

📚 Bibliotecas

_EmisoraBLE.h_: Biblioteca para gestionar la emisión de datos a través de Bluetooth Low Energy (BLE).

_Medidor.h_: Biblioteca que proporciona funciones de medición de datos.

_Publicador.h:_ Biblioteca para publicar datos a través de una interfaz específica.

_PuertoSerie.h_: Biblioteca para la comunicación serie.

_ServicioEnEmisora.h_: Biblioteca que define un servicio específico en la emisora.

# 🖲️ Placa Arduino
Antes de cargar y ejecutar el programa de Arduino, asegúrate de tener una placa SparkFun Pro nRF52840 Mini. Puedes encontrar más información sobre esta placa en la página oficial de SparkFun Pro nRF52840 Mini.

# 🖥️ Requisitos Previos
Antes de cargar y ejecutar el programa de Arduino, asegúrate de tener los siguientes requisitos previos instalados:

- Arduino IDE: Descarga e instala el entorno de desarrollo Arduino IDE en tu ordenador.

# ⚠️ Cómo Utilizar el Proyecto
1. Descarga la carpeta Emision_Datos_Arduino del repositorio que se encuentra en la carpeta src.

2. Abre el archivo Emision_Datos_Arduino.ino en el entorno de desarrollo de Arduino.

3. Conecta tu placa SparkFun Pro nRF52840 Mini a tu computadora usando un cable USB.

4. En el entorno de Arduino, elige el modelo de tu placa desde la opción "Herramientas".

5. Haz clic en el ícono de verificación para compilar el código.

6. Para cargar el programa en tu placa, presiona el botón de carga.

7. Mira la salida del programa en el monitor serie del entorno de Arduino para realizar la depuración.

# ©️ Autor 
Manuela Zazzaro - @mmanueeela 
