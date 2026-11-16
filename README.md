# LDR-Auto-Brightness
Arduino project that uses an LDR sensor to automatically control LED brightness using analog input and PWM output.

## 🔌 Circuit Diagram

A concise ASCII circuit diagram is included in the repository:

📁 `circuits/diagram.txt` — contains the LDR voltage divider and LED PWM wiring.

Refer to that file for the complete wiring layout and notes before assembling the circuit.

## 🛠 Hardware Used

| Component | Quantity | Purpose |
|-----------|----------|---------|
| LDR (Light Dependent Resistor) | 1 | Ambient light sensor (voltage divider) |
| 10kΩ resistor | 1 | Fixed resistor for voltage divider |
| LED (any standard LED) | 1 | Visual output (brightness control) |
| 220Ω resistor | 1 | Current-limiting resistor for LED |
| Arduino Uno / Nano | 1 | Microcontroller (analog read + PWM) |
| Jumper wires & breadboard | — | Wiring and prototyping |
| USB cable / power supply | 1 | Power & serial debug |

## 🔧 Wiring & Pin Map

- **LDR voltage divider**
  - LDR → top leg → +5V
  - Bottom leg → 10kΩ resistor → GND
  - Divider midpoint → **A0** (Arduino analog input)

- **LED**
  - Arduino **D9** (PWM) → 220Ω resistor → LED anode
  - LED cathode → GND

- **Power & Ground**
  - Connect Arduino GND to the negative rail of the breadboard.
  - Ensure common ground between sensor and Arduino.

Pin summary:
- `A0` = LDR divider output  
- `D9` = LED PWM output  
- `5V` = VCC for divider  
- `GND` = common ground

## ▶️ How to Run — Quick Start

1. Wire the circuit according to `circuits/diagram.txt` and the Wiring & Pin Map above.
2. Open `src/auto_brightness.ino` in the Arduino IDE.
3. Select the correct board (Uno/Nano) and COM port.
4. Upload the sketch.
5. Open Serial Monitor at **9600 baud** to view real-time sensor and brightness values.

Expected behavior:
- In bright ambient light the LED dims.
- In low light/dark the LED becomes brighter.

## ✅ Testing & Calibration

- Use the Serial Monitor to view `LDR` and `Brightness` values while adjusting ambient light.
- If LED response is too sensitive or too slow, tweak `delay(100)` or apply a simple smoothing filter:
  - Example: apply exponential smoothing on `sensorValue` before mapping.
- Recommended calibration:
  1. Note `sensorValue` in bright daylight and in low indoor light.
  2. Adjust the `map()` parameters or add conditional thresholds in the code for finer control.

Example smoothing snippet (optional):
```cpp
// low-pass filter example
static float smooth = 0;
smooth = 0.85 * smooth + 0.15 * sensorValue;
int smoothBrightness = map((int)smooth, 0, 1023, 255, 0);
analogWrite(ledPin, smoothBrightness);

For sensor reconnects or recalibration, call `brightnessFilter.reset()`. The next sample initializes immediately; subsequent samples retain the configured smoothing factor. Host test: `c++ -std=c++11 tests/brightness_filter_reset_test.cpp -o /tmp/brightness-reset && /tmp/brightness-reset`.
