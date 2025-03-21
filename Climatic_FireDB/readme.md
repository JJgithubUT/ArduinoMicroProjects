# Proyecto ESP32 con Sensor DHT y Firebase

Este proyecto utiliza un **ESP32 Wrover-E** para leer la temperatura con un sensor **DHT22** y subir los datos a **Firebase Realtime Database**.

## 🚀 Requisitos

- **Placa ESP32 Wrover-E**.
- **Sensor DHT22**.
- **Arduino IDE** (versión 1.8.13 o superior recomendada).
- Conexión WiFi para subir datos a Firebase.

---

## 🛠️ Instalación

### 1. **Configurar Arduino IDE para ESP32**

1. Abre **Arduino IDE**.
2. Ve a **Archivo > Preferencias**.
3. En el campo `URL Adicionales de Gestor de Tarjetas`, agrega la siguiente URL: ``https://dl.espressif.com/dl/package_esp32_index.json``
4. Ve a **Herramientas > Placa > Gestor de Tarjetas**.
5. Busca `esp32` e instala el paquete oficial de Espressif.
6. En **Herramientas > Placa**, selecciona **ESP32 Wrover Module**.

---

### 2. **Instalar Librerías Necesarias**

Para instalar las librerías requeridas, sigue estos pasos:

#### a. Librería para el sensor DHT

1. Ve a **Herramientas > Administrar bibliotecas**.
2. Busca `DHT sensor library`.
3. Instala la librería `DHT sensor library for ESPx by beegee_tokyo`.

#### b. Librería para WiFi

Ya viene incluida en el núcleo del ESP32, por lo que no necesitas instalar nada adicional.

#### c. Librería para Firebase

1. Ve a **Herramientas > Administrar bibliotecas**.
2. Busca `Firebase ESP32 Client`.
3. Instala la librería `Firebase ESP32 Client by Mobizt`.

---

## ⚙️ Configuración

1. Edita las credenciales de WiFi en el código:

- define WIFI_SSID "Tu_Red_WiFi"
- define WIFI_PASSWORD "Tu_Contraseña_WiFi"
- define FIREBASE_HOST "<https://tu-database.firebaseio.com>"
- define FIREBASE_AUTH "Tu_Token"
