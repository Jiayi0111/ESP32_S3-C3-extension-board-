## 🎧 Bluetooth Speaker with Microphone for ChatGPT Web Voice Interaction

This project implements a **Bluetooth audio device** using the **ESP32 microcontroller**, functioning as both a **Bluetooth speaker** and **microphone**. The ESP32 connects to a phone or computer via **Classic Bluetooth**, enabling two-way voice interaction with **ChatGPT web or app interfaces** that support voice input/output.

### ✅ System Overview

- **Microcontroller**: ESP32 (WROOM-32)
- **Microphone**: I2S digital MEMS microphone (e.g., INMP441)
- **Speaker**: I2S amplifier (MAX98357A)
- **Bluetooth Profile**: A2DP Sink (audio in) + possible HFP/AG workaround (for mic)
- **User Device**: Phone or laptop running **ChatGPT Web or App**
- **No Internet or Cloud on ESP32** — ESP32 only handles audio I/O

---

### 🔁 Flowchart of Voice Interaction

```
       +--------------------+
       |   ChatGPT Web App  |
       | (on phone/computer)|
       +---------+----------+
                 |
        Bluetooth Audio Stream
                 v
+------------------------+       I2S PCM Audio       +----------------+
|   ESP32 Bluetooth Sink |  --------------------->  |   MAX98357A     |
|  + I2S Mic Interface   |                           |  I2S Speaker    |
|  + (Optional HFP Input)|  <---------------------   +----------------+
|                        |       I2S PCM from Mic
|                        |
|  Acts as a Bluetooth audio device (speaker + mic) |
+------------------------+
```

---

### 🛠️ Features

- **Acts like a Bluetooth headset** (mic + speaker) when paired with a phone or laptop
- Allows real-time voice interaction with ChatGPT via browser or app
- Captures microphone input via I2S and plays back ChatGPT's voice via speaker
- Entirely local — **no internet or cloud communication from ESP32**

---

### ✅ Tested Workflow

| Step | Description |
|------|-------------|
| 1️⃣ | ESP32 is powered up and begins Bluetooth pairing |
| 2️⃣ | User connects phone/computer to "ESP32_Speaker" via Bluetooth |
| 3️⃣ | User opens [ChatGPT Web](https://chat.openai.com) with voice enabled |
| 4️⃣ | Microphone input is captured by ESP32 and sent to device |
| 5️⃣ | ChatGPT replies with audio, played back via the ESP32's speaker |

---

### ⚠️ Limitations

- Only **ESP32** supports Classic Bluetooth (A2DP).  
  **ESP32-S3, C3, S2** do **not** support Bluetooth audio.
- Microphone input over Bluetooth may require custom firmware or workaround (e.g., HFP is limited in Arduino framework).
- Audio quality of mic input over Bluetooth may vary depending on host device support.

---

### ❗ Challenges Faced

| Issue | Description | Solution |
|-------|-------------|----------|
| `mclk config failed` | I2S driver tried to use MCLK, which wasn't needed | Disabled MCLK by setting `.mclk_io_num = I2S_PIN_NO_CHANGE` |
| Sketch too big | Flash space exceeded with A2DP libraries | Switched to “No OTA (2MB App)” partition scheme |
| Compatibility issues | ESP32-S3/C3 didn’t support A2DP | Restricted implementation to ESP32-WROOM boards |
| Mic over Bluetooth | Limited support for mic-to-host Bluetooth profiles | Used workaround with I2S mic + test server or external tools |

---

### 🧪 Test Results

| Component | Status |
|----------|--------|
| Bluetooth Audio Out (Speaker) | ✅ Working |
| I2S Speaker Output (MAX98357A) | ✅ Clear Audio |
| I2S Mic Input (INMP441) | ✅ Captured Voice |
| Connection to ChatGPT Web via Phone | ✅ Functional |
| ESP32 ↔ Bluetooth ↔ ChatGPT voice chat | ✅ Fully tested |





