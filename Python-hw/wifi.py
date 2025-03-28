import network
import time

ssid = "UTT-Directores P"
password = "D1r3ct0r3$%@"

def conectar_wifi():
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    wlan.connect(ssid, password)
    print(f"Conectándose a la red WiFi: {ssid}")

    timeout = 10  # Tiempo límite en segundos
    start = time.time()

    while not wlan.isconnected():
        if time.time() - start > timeout:
            print("No se pudo conectar al WiFi")
            return False
        time.sleep(1)
        print(".", end="")
    print("\n¡WiFi conectado!")
    print("Dirección IP:", wlan.ifconfig()[0])
    return True

conectar_wifi()