#include <esp_now.h>
#include <WiFi.h>

// REPLACE WITH YOUR ESP RECEIVER'S MAC ADDRESS
uint8_t broadcastAddress1[] = {0x0C, 0xB8, 0x15, 0x1A, 0x8C, 0x00};
uint8_t broadcastAddress2[] = {0xC0, 0x49, 0xEF, 0x26, 0x97, 0x68};
uint8_t broadcastAddress3[] = {0x0C, 0xB8, 0x15, 0x1A, 0x74, 0x5C};
uint8_t broadcastAddress4[] = {0xC0, 0x49, 0xEF, 0x1D, 0xE8, 0x58};
uint8_t broadcastAddress5[] = {0x0C, 0xB8, 0x15, 0x1A, 0x82, 0xC8};
uint8_t broadcastAddress6[] = {0x0C, 0xB8, 0x15, 0x1A, 0x91, 0x1C};
uint8_t broadcastAddress7[] = {0x0C, 0xB8, 0x15, 0x1A, 0x5C, 0x00};
uint8_t broadcastAddress8[] = {0x0C, 0xB8, 0x15, 0x1A, 0x8C, 0x9C};
uint8_t broadcastAddress9[] = {0x0C, 0xB8, 0x15, 0x1A, 0x8C, 0x68};

typedef struct test_struct {
  int x;
  int y;
} test_struct;

test_struct test;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  Serial.print("Packet to: ");
  // Copies the sender mac address to a string
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
  Serial.print(" send status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {
  Serial.begin(115200);
 
  WiFi.mode(WIFI_STA);
 
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  esp_now_register_send_cb(OnDataSent);
   
  // register peer
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  // register first peer  
  memcpy(peerInfo.peer_addr, broadcastAddress1, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  // register second peer  
//  memcpy(peerInfo.peer_addr, broadcastAddress2, 6);
//  if (esp_now_add_peer(&peerInfo) != ESP_OK){
//    Serial.println("Failed to add peer");
//    return;
//  }
//  /// register third peer
//  memcpy(peerInfo.peer_addr, broadcastAddress3, 6);
//  if (esp_now_add_peer(&peerInfo) != ESP_OK){
//    Serial.println("Failed to add peer");
//    return;
//  }
//    // register fourth peer  
//  memcpy(peerInfo.peer_addr, broadcastAddress4, 6);
//  if (esp_now_add_peer(&peerInfo) != ESP_OK){
//    Serial.println("Failed to add peer");
//    return;
//  }
//  // register fifth peer  
//  memcpy(peerInfo.peer_addr, broadcastAddress5, 6);
//  if (esp_now_add_peer(&peerInfo) != ESP_OK){
//    Serial.println("Failed to add peer");
//    return;
//  }
//  // register sixth peer
//  memcpy(peerInfo.peer_addr, broadcastAddress6, 6);
//  if (esp_now_add_peer(&peerInfo) != ESP_OK){
//    Serial.println("Failed to add peer");
//    return;
//  }
//    // register seventh peer  
//  memcpy(peerInfo.peer_addr, broadcastAddress7, 6);
//  if (esp_now_add_peer(&peerInfo) != ESP_OK){
//    Serial.println("Failed to add peer");
//    return;
//  }
//  // register eighth peer  
//  memcpy(peerInfo.peer_addr, broadcastAddress8, 6);
//  if (esp_now_add_peer(&peerInfo) != ESP_OK){
//    Serial.println("Failed to add peer");
//    return;
//  }
//  /// register ninth peer
//  memcpy(peerInfo.peer_addr, broadcastAddress9, 6);
//  if (esp_now_add_peer(&peerInfo) != ESP_OK){
//    Serial.println("Failed to add peer");
//    return;
//  }
}
 
void loop() {
  test.x = random(20,40);
//  test.y = random(0,20);
 
  esp_err_t result1 = esp_now_send(broadcastAddress1, (uint8_t *) &test, sizeof(test_struct));
   
  if (result1 == ESP_OK) {
//    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(2000);

//  esp_err_t result2 = esp_now_send(broadcastAddress2, (uint8_t *) &test, sizeof(test_struct));
//   
//  if (result2 == ESP_OK) {
////    Serial.println("Sent with success");
//  }
//  else {
//    Serial.println("Error sending the data");
//  }
//  delay(2000);
//
//  esp_err_t result3 = esp_now_send(broadcastAddress3, (uint8_t *) &test, sizeof(test_struct));
//   
//  if (result3 == ESP_OK) {
////    Serial.println("Sent with success");
//  }
//  else {
//    Serial.println("Error sending the data");
//  }
//  delay(2000);
//  
//  esp_err_t result4 = esp_now_send(broadcastAddress4, (uint8_t *) &test, sizeof(test_struct));
//   
//  if (result4 == ESP_OK) {
////    Serial.println("Sent with success");
//  }
//  else {
//    Serial.println("Error sending the data");
//  }
//  delay(2000);
//
//  esp_err_t result5 = esp_now_send(broadcastAddress5, (uint8_t *) &test, sizeof(test_struct));
//   
//  if (result5 == ESP_OK) {
////    Serial.println("Sent with success");
//  }
//  else {
//    Serial.println("Error sending the data");
//  }
//  delay(2000);
//
//  esp_err_t result6 = esp_now_send(broadcastAddress6, (uint8_t *) &test, sizeof(test_struct));
//   
//  if (result6 == ESP_OK) {
////    Serial.println("Sent with success");
//  }
//  else {
//    Serial.println("Error sending the data");
//  }
//  delay(2000);
//  
//  esp_err_t result7 = esp_now_send(broadcastAddress7, (uint8_t *) &test, sizeof(test_struct));
//   
//  if (result7 == ESP_OK) {
////    Serial.println("Sent with success");
//  }
//  else {
//    Serial.println("Error sending the data");
//  }
//  delay(2000);
//
//  esp_err_t result8 = esp_now_send(broadcastAddress8, (uint8_t *) &test, sizeof(test_struct));
//   
//  if (result8 == ESP_OK) {
////    Serial.println("Sent with success");
//  }
//  else {
//    Serial.println("Error sending the data");
//  }
//  delay(2000);
//
//  esp_err_t result9 = esp_now_send(broadcastAddress9, (uint8_t *) &test, sizeof(test_struct));
//   
//  if (result9 == ESP_OK) {
////    Serial.println("Sent with success");
//  }
//  else {
//    Serial.println("Error sending the data");
//  }
//  delay(2000);
}
