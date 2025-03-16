# Arduino Micro Projects

## Notas

En caso de tener ESP-WROOVER-32, instalar el ``CP210x Universal Windows Driver`` desde:

`https://www.silabs.com/developer-tools/usb-to-uart-bridge-vcp-drivers?tab=downloads`

La compatibilidad es importante, abrir Administrador de dispositivos y verificar la conectividad del módulo.

## Instalación de Arduino

[Descargar Arduino IDE](https://www.arduino.cc/en/software)

1. Después de instalar Arduino IDE, añadir los drivers.
2. Ir a `Archivo` -> `Preferencias` -> **URLs adicionales del gestor de placas**.
3. Insertar los siguientes enlaces en el campo correspondiente:
   - `https://dl.espressif.com/dl/package_esp32_index.json`
   - `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`

## Instalar la placa correspondiente en `Gestor de placas`

1. En este caso escribimos esp32 o .

2. Instalar ambos gestores de los resultados de búsqueda.

## Seleccionar placa correspondiente ==>

- Para ESP-WROOM-32: `ESP32 Dev Module`

- Para ESP-WROOVER-E: `ESP32 Wroover Module`
