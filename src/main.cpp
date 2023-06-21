#include "main.h"
#include <WiFiManager.h>

unsigned long _lastWifiUpdate = millis();
bool ota_running = false;
WiFiManager wifiManager;

void start_ota()
{
    ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else {  // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
    });
    ArduinoOTA.onEnd([]() {
      Serial.println("\nEnd");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) {
        Serial.println("Auth Failed");
      } else if (error == OTA_BEGIN_ERROR) {
        Serial.println("Begin Failed");
      } else if (error == OTA_CONNECT_ERROR) {
        Serial.println("Connect Failed");
      } else if (error == OTA_RECEIVE_ERROR) {
        Serial.println("Receive Failed");
      } else if (error == OTA_END_ERROR) {
        Serial.println("End Failed");
      }
    });
    ArduinoOTA.begin();
    Serial.println("OTA started");
    ota_running = true;
}



void loop() {
  // put your main code here, to run repeatedly:
    //delay(_delay);
    unsigned long now = millis();
    _loopCount++;
    if(_loopCount == 500 && _screen != NULL)
    {
        
        float duration = (float)(now - _loopStart) / (float)500.0;
        //Serial.print(duration);
        _screen->setTextColor(DEFAULT_TEXT_COLOR, DEFAULT_BG_COLOR, true);
        _screen->drawString("loop: " + String(duration) + "ms", 10, 113 , 1);
        _loopCount = 0;
        _loopStart = now;
    }

    if(now - _lastWifiUpdate > 300)
    {
      if(ota_running)
        ArduinoOTA.handle();
      else
      {
        if(WiFi.isConnected())
          start_ota();
      }
      wifiManager.process();
      _lastWifiUpdate = now;
    }
    _mgr.Loop();
    
}

void saveWifiCallback(){
  Serial.println("[CALLBACK] saveCallback fired");
      delay(2000);
}

void configPortalTimeoutCallback(){
  Serial.println("[CALLBACK] configPortalTimeoutCallback fired");
      delay(2000);
}

void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());

  Serial.println(myWiFiManager->getConfigPortalSSID());
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Starting up...");
  _mgr = Manager();
  _screen = _mgr.Setup();
  _loopStart = millis();

  WiFi.mode(WIFI_STA);
  WiFi.setHostname("ESP32Arcade");
  wifiManager.setConfigPortalBlocking(false);
  wifiManager.setConnectTimeout(20);

  std::vector<const char *> menu = { "wifi", "restart", "exit" };  // Added by me...
  wifiManager.setMenu(menu);
  
  if(wifiManager.autoConnect("AutoConnectAP"))
  {
    Serial.println("WIFI Connected");
  }
  Serial.println("Startup complete!");
}