//Uploaded mac address- 0x0C, 0xB8, 0x15, 0x1A, 0x74, 0x5C

#include <esp_now.h>
#include <WiFi.h>



// REPLACE WITH THE MAC Address of your receiver 
uint8_t broadcastAddress1[] = {0xC0, 0x49, 0xEF, 0x26, 0x97, 0x68};
uint8_t broadcastAddress2[] = {0x0C, 0xB8, 0x15, 0x1A, 0x8C, 0x00};

// Define variables to store incoming readings
int incomingid;
float incomingTemp;
float incomingHum;
float incomingPres;

// Variable to store if sending data was successful
String success;

//Structure example to send data
//Must match the receiver structure
typedef struct struct_message {
    int id; // must be unique for each sender board
    float temp;
    float hum;
    float pres;
} struct_message;

// Create a struct_message called BME280Readings to hold sensor readings
struct_message test;

// Create a struct_message to hold incoming sensor readings
struct_message incomingReadings;

esp_now_peer_info_t peerInfo;

// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
//  Serial.print("Packet to: ");
  // Copies the sender mac address to a string
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
//  Serial.print(macStr);
//  Serial.print(" send status:\t");
//  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

// Callback when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  Serial.print("Bytes received: ");
  Serial.println(len);
  incomingid = incomingReadings.id;
  incomingTemp = incomingReadings.temp;
  incomingHum = incomingReadings.hum;
  incomingPres = incomingReadings.pres;

  Serial.print("ID: ");
  Serial.println(incomingid);
  delay(500);
  Serial.print("Temperature: ");
  Serial.println(incomingTemp);
  delay(500);
  Serial.print("Humidity: ");
  Serial.println(incomingHum);
  delay(500);
  Serial.print("Pressure: ");
  Serial.println(incomingPres);
  delay(3000);
}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer  
  memcpy(peerInfo.peer_addr, broadcastAddress1, 6);       
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  // Add peer  
  memcpy(peerInfo.peer_addr, broadcastAddress2, 6);       
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
  delay(2000);
 
  // Set values to send
  test.id = 6;
  test.temp = random(20,40);
  test.hum = random(50,100);
  test.pres = random(0,20);

  // Send message via ESP-NOW
  esp_err_t result1 = esp_now_send(broadcastAddress1, (uint8_t *) &test, sizeof(struct_message));
   
  if (result1 == ESP_OK) {
//    Serial.println("Sent with success");
  }
  else {
//    Serial.println("Error sending the data");
  }
  delay(1000);

  // Send message via ESP-NOW
  esp_err_t result2 = esp_now_send(broadcastAddress2, (uint8_t *) &test, sizeof(struct_message));
   
  if (result2 == ESP_OK) {
//    Serial.println("Sent with success");
  }
  else {
//    Serial.println("Error sending the data");
  }
  delay(1000);

}
