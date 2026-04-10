```markdown
# ESP32 Dasai Mochi Clone 👾

<p align="center">
  <img src="https://via.placeholder.com/800x200.png?text=ESP32+Dasai+Mochi+Clone" alt="Project Banner">
</p>

## 📖 Introduction
This repository contains the source code for an **ESP32-based clone of the Dasai Mochi** companion. The project utilizes an ESP32 microcontroller to drive a 0.96" TFT display, rendering retro-style pixel animations and GIF frames directly on your dashboard or desk. 

## ✨ Features
* **Smooth Animation Rendering:** Plays high frame-rate image sequences directly from C-header arrays (`frame_00xxx.h`).
* **Compact & Portable:** Perfect for car dashboards, PC setups, or IoT projects.
* **Easy Customization:** Replace existing frames with your own custom GIFs easily.
* **PlatformIO Ready:** Neatly structured for fast compilation and flashing.

## 🛠 Hardware Requirements
* **Microcontroller:** ESP32-S3 (Configured for `esp32-s3-devkitc-1` in `platformio.ini`)
* **Display:** 0.96" TFT Display (ST7735S driver, 8-pin SPI)
* **Jumper Wires & Breadboard**

## 🔌 Wiring Guide
Connect the 8-pin ZJY096TFT ST7735S Display to your ESP32-S3 as follows:

| TFT Pin | Function | ESP32-S3 Pin | Notes |
| :---: | :--- | :--- | :--- |
| 1 | GND | GND | Ground |
| 2 | VCC | 3.3V | Power |
| 3 | SCL / SCK | GPIO 17 | SPI Clock |
| 4 | SDA / MOSI| GPIO 16 | SPI Data Input |
| 5 | RES / RST | GPIO 4 | Reset |
| 6 | DC / RS | GPIO 5 | Data/Command |
| 7 | CS | GPIO 6 | Chip Select |
| 8 | BLK / LED | 3.3V | Backlight (Connect to 3.3V for full brightness) |

*(Note: Please double-check your specific board's pinout and adjust the definitions in `src/main.cpp` if necessary).*

## 🚀 Getting Started

### 1. Prerequisites
* Install [Visual Studio Code](https://code.visualstudio.com/).
* Install the [PlatformIO IDE Extension](https://platformio.org/) for VS Code.

### 2. Installation
1. Clone this repository to your local machine:
   ```bash
   git clone [https://github.com/your-username/esp32-dasai-mochi.git](https://github.com/your-username/esp32-dasai-mochi.git)
   ```
2. Open the project folder in VS Code.
3. PlatformIO will automatically read the `platformio.ini` file and install the necessary dependencies and frameworks.

### 3. Build and Flash
1. Connect your ESP32-S3 to your PC via USB.
2. Click the **Upload** button (the right arrow icon `→`) on the PlatformIO status bar at the bottom.
3. Wait for the build and upload process to finish. The screen should light up and start displaying the animations!

## 🎨 Adding Custom Animations
Want to add your own GIFs? 
1. Extract your `.gif` file into individual image frames using an online tool or Python script.
2. Convert those frames into C-style hex arrays (`.h` files).
3. Place the newly generated `frame_00xxx.h` files into the `src/frames/` directory.
4. Include them in `src/all_frames.h` and recompile.

## 🤝 Contributing
Contributions, bug reports, and feature requests are always welcome! Feel free to check the issues page or submit a Pull Request.

## 📝 License
This project is for educational and personal use. "Dasai" and "Mochi" are trademarks of their respective owners. This repository is an open-source, fan-made hardware clone.
```
