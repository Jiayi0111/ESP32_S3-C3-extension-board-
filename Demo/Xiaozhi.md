Great catch — thank you! You're absolutely right. The **I2S mic (audio input)** should be clearly shown in the data flow, starting from capturing the user's voice and flowing through Opus encoding before being sent to the server.

Here's the **corrected flowchart** to reflect both **audio input and output**, as well as their respective processing paths:

---

### 🔁 **Corrected System Flowchart**

```
+-----------------------+
|   Custom ESP32 Board  |
|  (Xiaozhi Firmware)   |
+-----------+-----------+
            |
   Initializes Audio, LCD, Network
            |
            v
+----------------------------+
|   Audio Subsystem         |
| +-----------------------+ |
| |  I2S MIC (Voice In)   | |---> Opus Encode --> WebSocket Send (binary)
| |  I2S Speaker (Voice Out) |<--- Opus Decode <-- WebSocket Receive (binary)
| +-----------------------+ |
+----------------------------+
            |
     AudioCodec Abstraction
            |
     Display & LED Control
            |
+----------------------------+
|  LCD UI (TTS Text, Emotion) |
|  LEDs (Status Indicator)    |
+----------------------------+
            |
    WebSocketProtocol (Client)
            |
        JSON + Audio Frames
            |
+-----------------------------+
|        Cloud Server         |
| - Accepts WebSocket        |
| - STT / LLM / TTS Engine   |
| - Sends back JSON + Audio  |
+-----------------------------+
```

---

This flowchart now accurately shows:

- **Mic input path**: I2S mic → Opus encoding → WebSocket binary stream to server
- **Speaker output path**: WebSocket binary audio frame → Opus decoding → I2S speaker
- **WebSocket JSON handling**: For `"type": "hello"`, `"tts"`, `"stt"`, `"iot"`, etc.
- **Display subsystem**: LCD/LED updated based on JSON responses

---

Let me know if you'd like this diagram turned into a **professional PNG/SVG** visual for your report, or if you'd like a breakdown of each module's source file as part of the documentation!