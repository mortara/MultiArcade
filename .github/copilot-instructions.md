# Copilot Instructions for MultiArcade

## Project Overview

MultiArcade is an ESP32-based arcade console featuring multiple classic games (Pong, Asteroids, Space Invaders, Breakout, Cannon, Lunar Lander) controlled via rotary encoders/paddles with fire buttons, displayed on a TFT screen.

## Technology Stack

- **Platform**: ESP32 (espressif32)
- **Framework**: Arduino
- **Build System**: PlatformIO
- **Display**: TFT_eSPI library
- **Key Dependencies**:
  - pmCommonLib (custom library from mortara/pmCommonLib.git)
  - TFT_eSPI (Bodmer/TFT_eSPI.git)
  - ESP32Encoder (madhephaestus/ESP32Encoder.git)

## Build and Development

### Building the Project
```bash
pio run
```

### Uploading to Device
```bash
pio run --target upload
```

### Serial Monitor
```bash
pio device monitor
```
The serial monitor runs at 115200 baud rate.

### TFT_eSPI Configuration
The TFT_eSPI library requires custom configuration. Configuration files are stored in `include/TFT_eSPI_Config/`. To configure the library, add this line to `TFT_eSPI/User_Setup_Select.h`:
```cpp
#include <../../../../include/TFT_eSPI_Config/User_Setup.h>
```

## Code Structure

### Directory Layout
- `src/` - Main source code
  - `main.cpp` / `main.h` - Entry points with setup() and loop()
  - `general/` - Core game framework classes
    - `Game.hpp` - Base game interface
    - `GameWorld.cpp/hpp` - Game world management
    - `GameObject.cpp/hpp` - Base game object class
    - `manager.cpp/hpp` - Game manager for switching between games
    - `menu.cpp/hpp` - Menu system
    - `vector2DF.cpp/hpp` - 2D vector math
    - `config.h` - Hardware pin definitions and constants
  - `Input/` - Input handling (rotary encoders, joystick)
  - `sound/` - Sound/buzzer functionality
  - Game directories: `Pong/`, `Asteroids/`, `spaceinvaders/`, `breakout/`, `cannon/`, `lunarlander/`
- `include/` - Header files and library configurations
- `lib/` - Local library dependencies (excluded from git)

### Key Files
- `platformio.ini` - PlatformIO project configuration
- `src/general/config.h` - Hardware configuration (pin assignments, colors, constants)

## Coding Conventions

### Style Guidelines
- Use C++ for Arduino framework
- Keep code simple and straightforward (per project philosophy: "not overcomplicate the code")
- Use `.cpp` and `.hpp` for C++ files
- Use `.h` for C header files

### Hardware Constants
- Pin definitions are in `src/general/config.h`
- Color constants: `DEFAULT_TEXT_COLOR`, `DEFAULT_BG_COLOR`, `DEFAULT_FG_COLOR`, etc.
- Buzzer pin: GPIO 22
- Player 1 controls: CLK1=17, DT1=16, SW1=5, SW1_2=21
- Player 2 controls: CLK2=25, DT2=26, SW2=27, SW2_2=14

### Common Patterns
- Screen is accessed via `TFT_eSPI*` pointer (typically named `_tft` or `_screen`)
- Use `pmCommonLib` for common functionality
- Games inherit from base `Game` class
- Game objects typically use `GameWorld` for management
- Vector math uses `Vector2DF` class for 2D float vectors

### Serial Commands
The main loop responds to serial commands:
- 'r' - Restart ESP32
- 'i' - Display WiFi info

## Testing

There are currently no automated tests in this project. Manual testing is done via:
1. Building the project
2. Uploading to ESP32 hardware
3. Testing games and controls on the physical device

## Common Tasks

### Adding a New Game
1. Create a new directory under `src/` for the game
2. Implement game class inheriting from `Game.hpp`
3. Add game to the manager in `src/general/manager.cpp`
4. Update menu system if needed

### Modifying Display Code
- Use TFT_eSPI library functions
- Remember to call `startWrite()` and `endWrite()` for efficient drawing
- Use color constants from `config.h`
- Common methods: `fillRect()`, `drawString()`, `setTextColor()`, `pushColor()`

### Hardware Changes
- Update pin definitions in `src/general/config.h`
- Ensure changes are compatible with ESP32 GPIO capabilities

## Important Notes

- This is a hardware project - changes should be tested on actual ESP32 hardware
- The TFT_eSPI library configuration is critical and stored outside the library directory
- Build flags include `PMCOMMONNOMQTT=true` and `PMCOMMONNOWEBSERIAL=true` to disable certain pmCommonLib features
- The board uses LittleFS filesystem
- Upload speed is set to 921600 baud for faster uploads
