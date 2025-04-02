//simple bluetooth speaker
// Hat SPK2 speaker https://docs.m5stack.com/en/hat/Hat-SPK2
// MAX98357A PCM Class D Amplifier with Class AB Performance
// Supports I2S and 8-Channel TDM Data
// https://www.analog.com/en/products/MAX98357A.html


#include <Arduino.h>
#include "AudioTools.h"
#include "BluetoothA2DPSink.h"

// I2S Pin Definitions
#define I2S_LRC   27   // WS / LRCLK
#define I2S_BCLK  25   // BCLK
#define I2S_DIN   32   // DIN / Data

// I2S and Bluetooth sink
I2SStream i2s;
BluetoothA2DPSink a2dp_sink(i2s);

void setup() {
  Serial.begin(115200);

  // Configure I2S pins
  auto cfg = i2s.defaultConfig();
  cfg.pin_bck = I2S_BCLK;
  cfg.pin_ws = I2S_LRC;
  cfg.pin_data = I2S_DIN;
  i2s.begin(cfg);

  // Start Bluetooth sink
  a2dp_sink.start("ESPEAKER");  // Bluetooth name
  a2dp_sink.set_volume(64);     // Set initial volume (0–127)
}

void loop() {
  // Nothing to do here, Bluetooth audio is handled internally
}


