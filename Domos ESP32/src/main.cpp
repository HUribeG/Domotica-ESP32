#include <Arduino.h>

/**********************************************************************************
 *  TITLE: Intelli House ESP32 RainMaker
 * 
 *   Base code for the use of 
 *   Rmaker of espressif for a
 *   automated house by app
 *   and voice control.
 * 
 *   This version requires a 
 *   internet connection for the 
 *   operation of the house
 * 
 *   Created on 09/01/2023
 *   By Uribe Garcia (HG)
 *   Base on Tech StudyCell Code & Espressif example's
 *  
 **********************************************************************************/

#include "RMaker.h"
#include "WiFi.h"
#include "WiFiProv.h"

const char *service_name = "PROV_12345";
const char *pop = "1234567";

// define the Device Names
#define deviceName_1 "Cochera"
#define deviceName_2 "Exterior"
#define deviceName_3 "Cocina"
#define deviceName_4 "Sala"
#define deviceName_5 "Comedor"
#define deviceName_6 "Jardin"
#define deviceName_7 "Terraza"
#define deviceName_8 "Recamara1"
#define deviceName_9 "Recamara2"
#define deviceName_10 "Fuente"

// define the GPIO connected with Relays and switches
static uint8_t LED_COCHERA   = 23;  //D23
static uint8_t LED_EXTERIOR  = 22;  //D22
static uint8_t LED_COCINA    = 21;  //D21
static uint8_t LED_SALA      = 20;  //D20
static uint8_t LED_COMEDOR   = 19;  //D19
static uint8_t LED_JARDIN    = 18;  //D18
static uint8_t LED_TERRAZA   = 5;   //D5
static uint8_t LED_RECAMARA1 = 25;  //D25
static uint8_t LED_RECAMARA2 = 26;  //D26
static uint8_t DRIVER_BOMBA  = 16;  //D16

static uint8_t WIFILED    = 2;   //D2(Board)
static uint8_t gpio_reset = 0;   //D0(Board)

/* Variable for reading pin status*/
// Devices State 
bool cochera_state   = LOW;
bool exterior_state  = LOW;
bool cocina_state    = LOW;
bool sala_state      = LOW;
bool comedor_state   = LOW;
bool jardin_state    = LOW;
bool terraza_state   = LOW;
bool recamara1_state = LOW;
bool recamara2_state = LOW;
bool bomba_state     = LOW;

/*The framework provides some standard device types like switch, lightbulb, fan, temperature sensor. */
//LigthBulb
static LightBulb luz_cochera(deviceName_1, &LED_COCHERA);
static LightBulb luz_exterior(deviceName_2, &LED_EXTERIOR);
static LightBulb luz_cocina(deviceName_3, &LED_COCINA);
static LightBulb luz_sala(deviceName_4, &LED_SALA);
static LightBulb luz_comedor(deviceName_5, &LED_COMEDOR);
static LightBulb luz_jardin(deviceName_6, &LED_JARDIN);
static LightBulb luz_terraza(deviceName_7, &LED_TERRAZA);
static LightBulb luz_recamara1(deviceName_8, &LED_RECAMARA1);
static LightBulb luz_recamara2(deviceName_9, &luz_recamara2);

//Switch 
static Switch bomba_fuente(deviceName_10, &DRIVER_BOMBA);


void sysProvEvent(arduino_event_t *sys_event){
    switch (sys_event->event_id) {      
        case ARDUINO_EVENT_PROV_START:
#if CONFIG_IDF_TARGET_ESP32
        Serial.printf("\nProvisioning Started with name \"%s\" and PoP \"%s\" on BLE\n", service_name, pop);
        printQR(service_name, pop, "ble");
#else
        Serial.printf("\nProvisioning Started with name \"%s\" and PoP \"%s\" on SoftAP\n", service_name, pop);
        printQR(service_name, pop, "softap");
#endif        
        break;
        case ARDUINO_EVENT_WIFI_STA_CONNECTED:
        Serial.printf("\nConnected to Wi-Fi!\n");
        digitalWrite(WIFILED, true);
        break;
    }
}

void write_callback(Device *device, Param *param, const param_val_t val, void *priv_data, write_ctx_t *ctx){

  const char *device_name = device->getDeviceName();
  const char *param_name = param->getParamName();

  if(strcmp(device_name, deviceName_1) == 0) {

    Serial.printf("LightBulb = %s\n", val.val.b? "true" : "false");

    if(strcmp(param_name, "Power") == 0) {
      Serial.printf("Received value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
      cochera_state = val.val.b;
      (cochera_state == false)? digitalWrite(LED_COCHERA, HIGH) : digitalWrite(LED_COCHERA, LOW);
      param->updateAndReport(val);
    }

  }
  else if(strcmp(device_name, deviceName_2) == 0) {
      
      Serial.printf("Lightbulb value = %s\n", val.val.b? "true" : "false");  

      if(strcmp(param_name, "Power") == 0) {
        Serial.printf("Received value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
        exterior_state = val.val.b;
        (exterior_state == false) ? digitalWrite(LED_EXTERIOR, HIGH) : digitalWrite(LED_EXTERIOR, LOW);
        param->updateAndReport(val);
      }
  
    }
  else if(strcmp(device_name, deviceName_3) == 0) {
      
      Serial.printf("Lightbulb value = %s\n", val.val.b? "true" : "false");  

      if(strcmp(param_name, "Power") == 0) {
        Serial.printf("Received value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
        cocina_state = val.val.b;
        (cochera_state == false) ? digitalWrite(LED_COCINA, HIGH) : digitalWrite(LED_COCINA, LOW);
        param->updateAndReport(val);
      }
  
    }
  else if(strcmp(device_name, deviceName_4) == 0) {
      
      Serial.printf("Lightbulb value = %s\n", val.val.b? "true" : "false");  

      if(strcmp(param_name, "Power") == 0) {
        Serial.printf("Received value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
        sala_state = val.val.b;
        (sala_state == false) ? digitalWrite(LED_SALA, HIGH) : digitalWrite(LED_SALA, LOW);
        param->updateAndReport(val);
      }
  
    }
  else if(strcmp(device_name, deviceName_5) == 0) {
      
      Serial.printf("Lightbulb value = %s\n", val.val.b? "true" : "false");  

      if(strcmp(param_name, "Power") == 0) {
        Serial.printf("Received value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
        comedor_state = val.val.b;
        (comedor_state == false) ? digitalWrite(LED_COMEDOR, HIGH) : digitalWrite(LED_COMEDOR, LOW);
        param->updateAndReport(val);
      }
  
    }
  else if(strcmp(device_name, deviceName_6) == 0) {
      
      Serial.printf("Lightbulb value = %s\n", val.val.b? "true" : "false");  

      if(strcmp(param_name, "Power") == 0) {
        Serial.printf("Received value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
        jardin_state = val.val.b;
        (jardin_state == false) ? digitalWrite(LED_JARDIN, HIGH) : digitalWrite(LED_JARDIN, LOW);
        param->updateAndReport(val);
      }
  
    }
  else if(strcmp(device_name, deviceName_7) == 0) {
      
      Serial.printf("Lightbulb value = %s\n", val.val.b? "true" : "false");  

      if(strcmp(param_name, "Power") == 0) {
        Serial.printf("Received value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
        terraza_state = val.val.b;
        (terraza_state == false) ? digitalWrite(LED_TERRAZA, HIGH) : digitalWrite(LED_TERRAZA, LOW);
        param->updateAndReport(val);
      }
  
    }
  else if(strcmp(device_name, deviceName_8) == 0) {
      
      Serial.printf("Lightbulb value = %s\n", val.val.b? "true" : "false");  

      if(strcmp(param_name, "Power") == 0) {
        Serial.printf("Received value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
        recamara1_state = val.val.b;
        (recamara2_state == false) ? digitalWrite(LED_RECAMARA1, HIGH) : digitalWrite(LED_RECAMARA1, LOW);
        param->updateAndReport(val);
      }
  
    }
  else if(strcmp(device_name, deviceName_9) == 0) {
      
      Serial.printf("Lightbulb value = %s\n", val.val.b? "true" : "false");  

      if(strcmp(param_name, "Power") == 0) {
        Serial.printf("Received value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
        recamara2_state = val.val.b;
        (recamara2_state == false) ? digitalWrite(LED_RECAMARA2, HIGH) : digitalWrite(LED_RECAMARA2, LOW);
        param->updateAndReport(val);
      }
  
    }
    else if(strcmp(device_name, deviceName_10) == 0) {
      
      Serial.printf("Switch value = %s\n", val.val.b? "true" : "false");  

      if(strcmp(param_name, "Power") == 0) {
        Serial.printf("Received value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
        bomba_state = val.val.b;
        (bomba_state == false) ? digitalWrite(DRIVER_BOMBA, HIGH) : digitalWrite(DRIVER_BOMBA, LOW);
        param->updateAndReport(val);
      }
  
    }

    
}  

void setup(){

  uint32_t chipId = 0;
  
  Serial.begin(115200);
  
  // Set the Relays GPIOs as output mode
  pinMode(LED_COCHERA,  OUTPUT);
  pinMode(LED_EXTERIOR, OUTPUT);
  pinMode(LED_SALA,     OUTPUT);
  pinMode(LED_COMEDOR,  OUTPUT);
  pinMode(LED_JARDIN,   OUTPUT);
  pinMode(LED_TERRAZA,  OUTPUT);
  pinMode(LED_RECAMARA1,OUTPUT);
  pinMode(LED_RECAMARA2,OUTPUT);
  pinMode(DRIVER_BOMBA, OUTPUT);
  pinMode(WIFILED,      OUTPUT);
  
  // Configure the input GPIOs
   pinMode(gpio_reset, INPUT);

  // Write to the GPIOs the default state on booting
  digitalWrite(LED_COCHERA,  LOW);
  digitalWrite(LED_EXTERIOR, LOW);
  digitalWrite(LED_SALA,     LOW);
  digitalWrite(LED_COMEDOR,  LOW);
  digitalWrite(LED_JARDIN,   LOW);
  digitalWrite(LED_TERRAZA,  LOW);
  digitalWrite(LED_RECAMARA1,LOW);
  digitalWrite(LED_RECAMARA2,LOW);
  digitalWrite(DRIVER_BOMBA, LOW);
  digitalWrite(WIFILED,      LOW);
  

  Node my_node;    
  my_node = RMaker.initNode("ESP32_House");

  //Standard Lightbulb device
  luz_cochera.addCb(write_callback);
  luz_exterior.addCb(write_callback);
  luz_cocina.addCb(write_callback);
  luz_sala.addCb(write_callback);
  luz_comedor.addCb(write_callback);
  luz_jardin.addCb(write_callback);
  luz_terraza.addCb(write_callback);
  luz_recamara1.addCb(write_callback);
  luz_recamara2.addCb(write_callback);
  
  //Standard Switch device
  bomba_fuente.addCb(write_callback);

  //Add switch device to the node   
  my_node.addDevice(luz_cochera);
  my_node.addDevice(luz_exterior);
  my_node.addDevice(luz_cocina);
  my_node.addDevice(luz_sala);
  my_node.addDevice(luz_comedor);
  my_node.addDevice(luz_jardin);
  my_node.addDevice(luz_terraza);
  my_node.addDevice(luz_recamara1);
  my_node.addDevice(luz_recamara2);
  my_node.addDevice(bomba_fuente);
  

  //This is optional 
  RMaker.enableOTA(OTA_USING_PARAMS);
  //If you want to enable scheduling, set time zone for your region using setTimeZone(). 
  //The list of available values are provided here https://rainmaker.espressif.com/docs/time-service.html
  // RMaker.setTimeZone("Asia/Shanghai");
  // Alternatively, enable the Timezone service and let the phone apps set the appropriate timezone
  RMaker.enableTZService();
  RMaker.enableSchedule();

  //Service Name
  for(int i=0; i<17; i=i+8) {
    chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
  }

  Serial.printf("\nChip ID:  %d Service Name: %s\n", chipId, service_name);

  Serial.printf("\nStarting ESP-RainMaker\n");
  RMaker.start();

  WiFi.onEvent(sysProvEvent);
#if CONFIG_IDF_TARGET_ESP32
    WiFiProv.beginProvision(WIFI_PROV_SCHEME_BLE, WIFI_PROV_SCHEME_HANDLER_FREE_BTDM, WIFI_PROV_SECURITY_1, pop, service_name);
#else
    WiFiProv.beginProvision(WIFI_PROV_SCHEME_SOFTAP, WIFI_PROV_SCHEME_HANDLER_NONE, WIFI_PROV_SECURITY_1, pop, service_name);
#endif

  luz_cochera.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, false);
  luz_exterior.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, false);
  luz_cocina.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, false);
  luz_sala.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, false);
  luz_comedor.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, false);
  luz_jardin.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, false);
  luz_terraza.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, false);
  luz_recamara1.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, false);
  luz_recamara2.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, false);
  bomba_fuente.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, false);
  
}

void loop(){
    // Read GPIO0 (external button to reset device
    if(digitalRead(gpio_reset) == LOW) { //Push button pressed
        Serial.printf("Reset Button Pressed!\n");
        // Key debounce handling
        delay(100);
        int startTime = millis();
        while(digitalRead(gpio_reset) == LOW) delay(50);
        int endTime = millis();

        if ((endTime - startTime) > 10000) {
          // If key pressed for more than 10secs, reset all
          Serial.printf("Reset to factory.\n");
          RMakerFactoryReset(2);
        } else if ((endTime - startTime) > 3000) {
          Serial.printf("Reset Wi-Fi.\n");
          // If key pressed for more than 3secs, but less than 10, reset Wi-Fi
          RMakerWiFiReset(2);
        }
    }
    delay(100);

    if (WiFi.status() != WL_CONNECTED)
    {
      //Serial.println("WiFi Not Connected");
      digitalWrite(WIFILED, false);
    }
    else
    {
      //Serial.println("WiFi Connected");
      digitalWrite(WIFILED, true);
    }

    
}
