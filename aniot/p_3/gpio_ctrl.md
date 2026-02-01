# Controladores GPIO

Los controladores de GPIO (*General Purpose Input-Ouput*)  permiten controlar ciertos pines de nuestro dispositivo para usarlos  como entrada (por ejemplo, para conectar un botón) o salida (por ejemplo para conectar un LED) o con funciones *especiales* (que forme parte de un bus serie, por ejemplo). 

El SoC ESP32 que usamos proporciona 40 GPIO *pads* (el SoC no tiene pines propiamente dichos, sino conectores, normalmente de superfície, que se deminan *pad*). El módulo WROOM-32 que usamos expone 38 de ellos, que son accesibles a  traves de los pines (los conectores físicos a ambos lados de la placa)  que incorpora nuestra placa DevKitC.

En la siguiente figura se muestra la disposición de los pines en la placa ESP32-DevKitC que usamos en nuestras prácticas: 

![pinout](https://miot-rpi.github.io/practicas/ANIOT/P2/img/esp32-devkitC-v4-pinout.png)

En [la web](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/hw-reference/esp32/get-started-devkitc.html) de Espressif se pueden encontrar más detalles de la placa.

Como se indica en la documentación de [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/gpio.html), algunos de esos pines tiene un propósito específico. Por ejemplo,  GPIO6-11 y 16-17 no deben usarse porque están internamente conectados a  la memoria SPI flash. También nos indica que los pines del canal 2 del  ADC (ADC2) NO deben usarse mientras se utiliza Wi-Fi.  Es muy  conveniente leer todas las restricciones para evitar problemas en  nuestros desarrollos.

### API de ESP-IDF

La documentación muestra también la API que ofrece ESP-IDF para  configurar los pines (entrada o salida, uso de pull-up/pull-down)  establecer un valor lógico (0 ó 1)en un pin (previamente configurado  como salida) o leer el valor lógico de un pin (configurado como  entrada).

El siguiente código, [extraído del ejemplo de GPIO proporcionado en la distribución ESP-IDF](https://github.com/espressif/esp-idf/tree/master/examples/peripherals/gpio/generic_gpio), muestra cómo configurar los pines GPIO18 y GPIO19 como salida. 

Observa cómo se construye la máscara de bits `GPIO_OUTPUT_PIN_SEL` para indicar a `gpio_config()` qué pines se configuran.

```c
#define GPIO_OUTPUT_IO_0 18
#define GPIO_OUTPUT_IO_1 19
#define GPIO_OUTPUT_PIN_SEL ((1ULL<<GPIO_OUTPUT_IO_0) | (1ULL<<GPIO_OUTPUT_IO_1))
gpio_config_t io_conf;
io_conf.intr_type = GPIO_PIN_INTR_DISABLE; 
io_conf.mode = GPIO_MODE_OUTPUT; 
io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL; 
io_conf.pull_down_en = 0; 
io_conf.pull_up_en = 0; 
gpio_config(&io_conf);
```

Posteriormente, podemos establecer el valor lógico de la salida con una llamada similar a `gpio_set_level(GPIO_OUTPUT_IO_1, valor);`, siendo `valor` igual a 0 ó 1.

De forma similar el siguiente código configura los pines 4 y 5 como entrada:

```c
    #define GPIO_INPUT_IO_0 4
    #define GPIO_INPUT_IO_1 5
    #define GPIO_INPUT_PIN_SEL ((1ULL<<GPIO_INPUT_IO_0) | (1ULL<<GPIO_INPUT_IO_1))
    gpio_config_t io_conf;  
    io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
    io_conf.mode = GPIO_MODE_INPUT;
    gpio_config(&io_conf);
```

Posteriormente, podremos leer el valor lógico de esos pines con una llamada a `gpio_get_level()`.

Busca información

En relación al código anterior: en la configuración anterior, los  pines de entrada deben muestrearse periódicamente para conocer su  estado. Investiga cómo configurar los pines como entrada de modo que  generen una interrupción cuando se produce un flanco (subida, bajado o  ambos).

## Ejercicio final

Completa este ejercicio después de haber resuelto los anteriores.  Recuerda que, en todo caso, no es necesario entregar esta práctica.

Tareas

Partiendo del ejemplo *Blink* (usando el denominado *LED_STRIP* en GPIO 2, no como la usamos el primer día), crea una applicación que:

- Incluya el componente `shtc3` en tu proyecto.
- Muestree la temperatura cada segundo utilizando un *timer*.
- Muestre el progreso de la temperatura en el LED programable de la  placa. Si la temperatura es inferior a 20 grados, estará apagado. Por  cada grado que suba la temperatura, se modificará el color/intensidad  del LED.
  - Para variar el color/intensidad, sólo debes cambiar los 3 últimos argumentos de la llamada `led_strip_set_pixel()` del código de ejemplo. 
- Se programará un segundo timer que mostrará por pantalla (puerto  serie) la última medida de temperatura realizada cada 10 segundos. 
- [Opcional] Configura el GPIO 9, al que está conectado el botón BOOT, para que genere interrupciones cuando soltemos el botón. ¿Qué valor  lógico se lee del GPIO 9 con el botón pulsado?. Consulta [la documentación de GPIO](https://docs.espressif.com/projects/esp-idf/en/v5.3.1/esp32/api-reference/peripherals/gpio.html) y el [ejemplo de GPIO genérico](https://github.com/espressif/esp-idf/tree/v5.3.1/examples/peripherals/gpio/generic_gpio) para entender cómo configurar un GPIO como entrada por interrupciones.
- [Opcional] En lugar de usar el componente `shtc3` descargado, busca un componente similar en el **ESPRegistry** y configura el proyecto para usar dicho componente. 