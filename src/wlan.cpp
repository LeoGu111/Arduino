#include "wlan.h"

// versucht sich im WLan anzumelden
void connectToWiFi()
{
    WiFi.begin(ssid, password);
    Serial.print("Verbindung zum WLAN...");

    for (int i = 0; i < 15; i++)
    {
        if (WiFi.status() != WL_CONNECTED)
        {
            delay(1000);
            Serial.print(".");
        }
        else
        {
            Serial.println("\nVerbunden! IP-Adresse: " + WiFi.localIP().toString());
            return;
        }
    }
    Serial.println("\nWlanverbindung fehlgeschlagen");
    startAccessPoint();
}
// Startet einen AP
void startAccessPoint()
{
    WiFi.softAP("ESP32-AP", "Passwort123");
    Serial.println("ESP32 erstellt ein eigenes WLAN. SSID: ESP32-AP, Passwort: Passwort123");
    Serial.println("IP-Adresse im AP-Modus: " + WiFi.softAPIP().toString());
}

void changeWiFiCredentials(const char *newSSID, const char *newPassword)
{
    WiFi.disconnect();
    delay(1000);
    WiFi.begin(newSSID, newPassword);
    Serial.println("Verbindung zum neuen WLAN wird hergestellt...");
}
// Startet einen Webserver
void webserverstart()
{
    // Route to handle requests and provide HTML page with array values
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              {
    String html = "<html><body><h1>Array values:</h1><ul>";
    for (size_t i = 0; i < sizeof(TimerArray) / sizeof(TimerArray[0]); i++) {
      html += "<li>" + String((long)TimerArray[i]) + "</li>";
    }
    html += "</ul></body></html>";
    request->send(200, "text/html", html); });

    // Start server
    server.begin();
}