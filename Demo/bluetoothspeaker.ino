

//INMP441  
// Omnidirectional Microphone with Bottom Port and I2S Digital Output 
// https://invensense.tdk.com/wp-content/uploads/2015/02/INMP441.pdf

#include <Arduino.h>
#include "AudioTools.h"
#include "BluetoothA2DPSink.h"

// I2S OUTPUT (to speaker)
#define I2S_LRC   27   // WS / LRCLK
#define I2S_BCLK  25   // BCLK
#define I2S_DIN   32   // DIN / Data

// I2S INPUT (from INMP441 mic)
#define MIC_LRC   26   // WS / LRCLK
#define MIC_BCLK  22   // BCLK
#define MIC_DOUT  33   // Data from mic

// I2S output stream for speaker
I2SStream i2s_out;

// I2S input stream for mic
I2SStream i2s_in; // Changed from AudioInI2S to I2SStream

// Bluetooth sink
BluetoothA2DPSink a2dp_sink(i2s_out);

void setup() {
  Serial.begin(115200);

  // === OUTPUT CONFIG ===
  auto out_cfg = i2s_out.defaultConfig();
  out_cfg.pin_bck = I2S_BCLK;
  out_cfg.pin_ws = I2S_LRC;
  out_cfg.pin_data = I2S_DIN;
  out_cfg.is_master = true;
  i2s_out.begin(out_cfg);

  // === INPUT CONFIG ===
  auto in_cfg = i2s_in.defaultConfig();
  in_cfg.pin_bck = MIC_BCLK;
  in_cfg.pin_ws = MIC_LRC;
  in_cfg.pin_data = MIC_DOUT;
  in_cfg.sample_rate = 16000;        // or 44100
  in_cfg.bits_per_sample = 32;       // INMP441 outputs 24-bit left-justified
  in_cfg.channels = 1;               // mono
  in_cfg.is_master = true;           // ESP32 generates clock signals
  in_cfg.rx_tx_mode = RX_MODE;       // Input mode
  i2s_in.begin(in_cfg);

  // Start Bluetooth audio output
  a2dp_sink.set_volume(64);
  a2dp_sink.start("ESPEAKER");

  Serial.println("Setup complete.");
}

void loop() {
  // Read mic input
  int32_t buffer[256];
  int bytesRead = i2s_in.readBytes((uint8_t*)buffer, sizeof(buffer));
  if (bytesRead > 0) {
    Serial.println("Mic data available");
    // Process mic data here
    
    /* 
     * You can add processing here, like:
     * - Sound detection
     * - Audio analysis
     * - Forward audio to Bluetooth (would need to add BT source capability)
     */
  }

  delay(10);
}