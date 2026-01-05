# MultiArcade

A retro arcade gaming console built with ESP32, featuring classic arcade games controlled with a rotary encoder and buttons.

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## 🎮 Features

MultiArcade brings classic arcade gaming to an ESP32 microcontroller with a TFT display. The console includes **8 playable games**:

- **Asteroids** - Navigate your ship through an asteroid field
- **Pong** - Classic paddle game (1 or 2 player modes)
- **Breakout** - Break all the blocks with your ball
- **Space Invaders** - Defend against waves of alien invaders
- **Lunar Lander** - Carefully land your spacecraft
- **Cannon** - Artillery physics-based game
- **Tempest** - Tube shooter action

All games feature:
- Smooth vector-style graphics
- Sound effects via piezo buzzer
- Score tracking and level progression
- Responsive rotary encoder controls

## 🔧 Hardware Requirements

### Core Components
- **ESP32** development board
- **TFT Display** (160x128 compatible with TFT_eSPI library)
- **Rotary Encoder** with push button (debounced recommended)
- **Piezo Buzzer** for sound effects
- **2 Fire Buttons** (optional, depending on game)

### Wiring

![Wiring Diagram](https://github.com/mortara/MultiArcade/blob/main/wiring_breadboard.png)

See `wiring.fzz` for the complete Fritzing schematic.

> **Note:** While a debounced rotary encoder is recommended for best performance, the console may work without debouncing.

## 💾 Software Setup

### Prerequisites

- [PlatformIO](https://platformio.org/) - Development environment
- [TFT_eSPI Library](https://github.com/Bodmer/TFT_eSPI) by Bodmer - Display driver

### Installation

1. Clone this repository:
   ```bash
   git clone https://github.com/mortara/MultiArcade.git
   cd MultiArcade
   ```

2. Configure the TFT_eSPI library for your specific display (edit `User_Setup.h` in the library folder)

3. Open the project in PlatformIO (VS Code recommended)

4. Build and upload to your ESP32:
   ```bash
   pio run --target upload
   ```

### Configuration

The main configuration can be found in `src/general/config.h`. You may need to adjust:
- Pin assignments for your rotary encoder
- Display settings
- Sound settings

## 🎯 Usage

1. Power on the ESP32
2. Use the rotary encoder to navigate the game menu
3. Press the fire button to select a game
4. In-game controls:
   - **Rotate encoder** - Move left/right or aim
   - **Button 1** - Fire/shoot
   - **Button 2** - Secondary action (game-dependent)

### Serial Commands

While connected via USB, you can use these serial commands:
- `r` - Restart the ESP32
- `i` - Display WiFi/system information

## 📁 Project Structure

```
MultiArcade/
├── src/
│   ├── Asteroids/       # Asteroids game implementation
│   ├── Pong/            # Pong game (1P and 2P)
│   ├── breakout/        # Breakout game
│   ├── spaceinvaders/   # Space Invaders game
│   ├── lunarlander/     # Lunar Lander game
│   ├── cannon/          # Cannon artillery game
│   ├── tempest/         # Tempest tube shooter
│   ├── general/         # Core game engine and manager
│   ├── input/           # Input handling (rotary encoder, joystick)
│   ├── sound/           # Sound/buzzer management
│   └── main.cpp         # Main entry point
├── platformio.ini       # PlatformIO configuration
├── wiring.fzz          # Fritzing wiring diagram
└── README.md
```

## 🛠️ Development

This project uses a simple game engine architecture:
- `Game` - Base class for all games
- `GameObject` - Base class for game entities
- `GameWorld` - Physics and collision management
- `Manager` - Game state and menu management

The code intentionally avoids over-engineering to keep things simple and readable. Feel free to extend it with your own games!

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🔗 Links

- **Homepage:** [mortara.org](https://www.mortara.org/allgemein/selbstbau-spielkonsole-mit-esp32/)
- **TFT_eSPI Library:** [github.com/Bodmer/TFT_eSPI](https://github.com/Bodmer/TFT_eSPI)

## 🙏 Acknowledgments

- Bodmer for the excellent TFT_eSPI library
- Classic arcade games that inspired this project

---

**Note:** This is a hobby project. The code prioritizes simplicity and fun over production-quality standards!