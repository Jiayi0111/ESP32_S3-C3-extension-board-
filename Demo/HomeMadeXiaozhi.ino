#include <WiFi.h>
#include <WebSocketsClient.h>
#include <driver/i2s.h>

// WiFi credentials
const char* ssid = "GOODLUCK";
const char* password = "luckylucky";

// Server details
const char* serverHost = "192.168.50.62";
const int serverPort = 3000;
const char* serverPath = "/audio";

WebSocketsClient webSocket;

// I2S speaker output pins
#define I2S_LRC   27   // WS / LRCLK
#define I2S_BCLK  25   // BCLK
#define I2S_DIN   32   // DIN

// I2S mic input pins (INMP441)
#define MIC_LRC   26
#define MIC_BCLK  22
#define MIC_DOUT  33

// Task handles for dual-core operation
TaskHandle_t micTaskHandle = NULL;
TaskHandle_t speakerTaskHandle = NULL;

// Control flags
volatile bool isConnected = false;
volatile bool isListening = false;
volatile bool isSpeaking = false;

// Buffer for audio data
uint8_t audioBuffer[512];
SemaphoreHandle_t audioBufferMutex;

void setupWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void i2sSpeakerSetup() {
  const i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
    .sample_rate = 32000,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 8,
    .dma_buf_len = 64,
    .use_apll = false,
    .tx_desc_auto_clear = true
  };

  const i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_BCLK,
    .ws_io_num = I2S_LRC,
    .data_out_num = I2S_DIN,
    .data_in_num = I2S_PIN_NO_CHANGE
  };

  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &pin_config);
  i2s_zero_dma_buffer(I2S_NUM_0);
  
  Serial.println("Speaker I2S initialized on I2S_NUM_0");
}

void i2sMicSetup() {
  const i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 16000,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 8,
    .dma_buf_len = 64,
    .use_apll = false
  };

  const i2s_pin_config_t pin_config = {
    .bck_io_num = MIC_BCLK,
    .ws_io_num = MIC_LRC,
    .data_out_num = I2S_PIN_NO_CHANGE,
    .data_in_num = MIC_DOUT
  };

  i2s_driver_install(I2S_NUM_1, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_1, &pin_config);
  i2s_zero_dma_buffer(I2S_NUM_1);
  
  Serial.println("Microphone I2S initialized on I2S_NUM_1");
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WebSocket connected!");
      isConnected = true;
      webSocket.sendTXT("ESP32 client connected");
      break;

    case WStype_DISCONNECTED:
      Serial.println("WebSocket disconnected");
      isConnected = false;
      isListening = false;
      isSpeaking = false;
      break;

    case WStype_TEXT:
      Serial.printf("Received text: %s\n", payload);
      
      // Control messages
      if (strcmp((char*)payload, "START_LISTENING") == 0) {
        Serial.println("Starting to listen");
        isListening = true;
        isSpeaking = false;
      } else if (strcmp((char*)payload, "STOP_LISTENING") == 0) {
        Serial.println("Stopping listening");
        isListening = false;
      } else if (strcmp((char*)payload, "START_SPEAKING") == 0) {
        Serial.println("Server is sending audio");
        isListening = false;
        isSpeaking = true;
      } else if (strcmp((char*)payload, "STOP_SPEAKING") == 0) {
        Serial.println("Server stopped sending audio");
        isSpeaking = false;
      }
      break;

    case WStype_BIN:
      // Audio data received, use in speaker task
      if (isSpeaking && length > 0) {
        // Take semaphore to safely update shared buffer
        if (xSemaphoreTake(audioBufferMutex, portMAX_DELAY)) {
          // Copy received data to buffer (up to buffer size)
          size_t copySize = min(length, sizeof(audioBuffer));
          memcpy(audioBuffer, payload, copySize);
          
          // Release semaphore
          xSemaphoreGive(audioBufferMutex);
          
          // Debug info
          static uint32_t packetCount = 0;
          if (++packetCount % 50 == 0) {
            Serial.printf("Received audio packet #%d, size: %d bytes\n", packetCount, length);
          }
        }
      }
      break;

    default:
      break;
  }
}

// Task running on Core 0: Microphone capture
void microphoneTask(void *pvParameters) {
  Serial.print("Microphone task running on core ");
  Serial.println(xPortGetCoreID());
  
  // Buffer for microphone data
  uint8_t micBuffer[320];
  
  // Give the system some time to stabilize
  delay(500);
  
  for (;;) {
    if (isConnected && isListening) {
      size_t bytesRead = 0;
      
      // Read from microphone
      esp_err_t result = i2s_read(I2S_NUM_1, micBuffer, sizeof(micBuffer), &bytesRead, 20 / portTICK_PERIOD_MS);
      
      if (result == ESP_OK && bytesRead > 0) {
        // Send audio data to server
        webSocket.sendBIN(micBuffer, bytesRead);
        
        // Debugging (occasional)
        static uint32_t micPackets = 0;
        if (++micPackets % 100 == 0) {
          Serial.printf("Mic: Sent packet #%d, %d bytes\n", micPackets, bytesRead);
        }
      }
    }
    // Small delay to prevent task starvation
    vTaskDelay(5 / portTICK_PERIOD_MS);
  }
}

// Task running on Core 1: Speaker output
void speakerTask(void *pvParameters) {
  Serial.print("Speaker task running on core ");
  Serial.println(xPortGetCoreID());
  
  // Local buffer for speaker data
  uint8_t speakerBuffer[512];
  size_t bufferSize = 0;
  
  for (;;) {
    if (isConnected && isSpeaking) {
      // Take semaphore to safely read from shared buffer
      if (xSemaphoreTake(audioBufferMutex, portMAX_DELAY)) {
        // Copy data from shared buffer to local buffer
        memcpy(speakerBuffer, audioBuffer, sizeof(audioBuffer));
        bufferSize = sizeof(audioBuffer);
        
        // Release semaphore
        xSemaphoreGive(audioBufferMutex);
        
        // Play audio through speaker
        if (bufferSize > 0) {
          size_t bytes_written = 0;
          i2s_write(I2S_NUM_0, speakerBuffer, bufferSize, &bytes_written, 20 / portTICK_PERIOD_MS);
          
          // Debug occasional output
          static uint32_t speakerPackets = 0;
          if (++speakerPackets % 100 == 0) {
            Serial.printf("Speaker: Played packet #%d, %d bytes\n", speakerPackets, bytes_written);
          }
        }
      }
    }
    // Small delay to prevent task starvation
    vTaskDelay(5 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("\nESP32 WebSocket Audio Client Starting (Dual-Core Version)");
  
  // Create mutex for shared buffer
  audioBufferMutex = xSemaphoreCreateMutex();
  
  // Setup connections
  setupWiFi();
  i2sSpeakerSetup();
  i2sMicSetup();
  
  // Setup WebSocket
  webSocket.begin(serverHost, serverPort, serverPath);
  webSocket.onEvent(webSocketEvent);
  webSocket.setReconnectInterval(3000);
  
  // Create tasks for dual-core processing
  xTaskCreatePinnedToCore(
    microphoneTask,     // Task function
    "MicrophoneTask",   // Name
    8192,               // Stack size
    NULL,               // Parameters
    1,                  // Priority
    &micTaskHandle,     // Task handle
    0                   // Run on Core 0
  );
  
  xTaskCreatePinnedToCore(
    speakerTask,        // Task function
    "SpeakerTask",      // Name
    8192,               // Stack size
    NULL,               // Parameters
    1,                  // Priority
    &speakerTaskHandle, // Task handle
    1                   // Run on Core 1
  );
  
  Serial.println("Tasks created. System ready.");
}

void loop() {
  // Main loop just handles WebSocket events and keeps connection alive
  webSocket.loop();
  
  // Report status periodically
  static unsigned long lastStatus = 0;
  if (millis() - lastStatus > 10000) {  // Every 10 seconds
    Serial.printf("Status: Connected=%d, Listening=%d, Speaking=%d\n", 
                 isConnected, isListening, isSpeaking);
    lastStatus = millis();
  }
}