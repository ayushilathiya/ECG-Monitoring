#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <FirebaseESP8266.h>

const int ecgPin = A0;  // Pin connected to AD8232 OUT

// WiFi Credentials
const char* ssid = "yourssid";
const char* password = "yourpassword";

// ThingSpeak API Credentials
unsigned long channelID = yourchannelid;
const char* writeAPIKey = "your APIkey";

WiFiClient client;

// Firebase Credentials
#define FIREBASE_HOST ""  // Replace with your Firebase database URL (without https://)
#define FIREBASE_AUTH ""  // Replace with your Firebase Database Secret

FirebaseData firebaseData;
FirebaseConfig firebaseConfig;
FirebaseAuth firebaseAuth;

// Variables for R-peak detection and BPM calculation
unsigned long previousTime = 0;
bool beatDetected = false;
unsigned int bpm = 0;
unsigned long lastUploadTime = 0;
static int baseline = 0; // Baseline for dynamic threshold

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  // Initialize ThingSpeak
  ThingSpeak.begin(client);

  // Configure Firebase
  firebaseConfig.host = FIREBASE_HOST;
  firebaseConfig.signer.tokens.legacy_token = FIREBASE_AUTH;
  
  Firebase.begin(&firebaseConfig, &firebaseAuth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  int ecgValue = analogRead(ecgPin);
  unsigned long currentTime = millis();

  // Dynamic threshold-based R-peak detection
  if (ecgValue > baseline + 50 && !beatDetected) {
    beatDetected = true;
    unsigned long timeInterval = currentTime - previousTime;
    previousTime = currentTime;

    if (timeInterval > 300) {
      bpm = 60000 / timeInterval;
      Serial.print("Heartbeat detected! BPM: ");
      Serial.println(bpm);
    }
  }

  baseline = baseline * 0.9 + ecgValue * 0.1; // Update baseline
  if (ecgValue < baseline + 50) {
    beatDetected = false;
  }

  // Print ECG data for Serial Plotter (without text)
  Serial.println(ecgValue);  

  // Prepare JSON object for Firebase upload
  FirebaseJson json;
  json.set("Time", String(currentTime));
  json.set("ECG Value", String(ecgValue));

  // Upload data to ThingSpeak every 15 seconds
  if (currentTime - lastUploadTime > 15000) {
    ThingSpeak.setField(1, ecgValue);
    ThingSpeak.setField(2, (int)bpm);

    int httpResponseCode = ThingSpeak.writeFields(channelID, writeAPIKey);
    if (httpResponseCode == 200) {
      Serial.println("ECG and BPM data uploaded successfully.");
    } else {
      Serial.print("Error uploading data: ");
      Serial.println(httpResponseCode);
    }

    // Upload JSON data to Firebase Realtime Database
    if (Firebase.pushJSON(firebaseData, "/ECG_Raw_Data", json)) {
      Serial.println("Data uploaded to Firebase successfully!");
    } else {
      Serial.print("Firebase upload failed: ");
      Serial.println(firebaseData.errorReason());  // Get the error message
    }

    lastUploadTime = currentTime;
  }

  delay(10); // Small delay for better visualization
}
