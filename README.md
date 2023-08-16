
# Half-Life on the STM32H747i-Discovery board
## Building

Building the code:
- Install STM32CubeIDE
- Open BSP/STM32CubeIDE/.project
- Build the project within the IDE


## Running

The game data (valve/ folder from the install folder of the steam version of the game) needs to be stored on a SD card for the code to work.

Controls are as follows:
* Wakeup button: Fire
* Center joystick button: Use
* Joystick: Move
* Fire+Use (in that order): Enter/Exit menu

Savegames are working.
Audio is working as well: simply plug a headset inside the Audio OUT port.

## Code edits

The code is based on a fork of xash3d, modified to rely on static linking only and optimized to run on the card's limited hardware.
Each modification in the code is signalled with a `<STM MOD>` comment to be easily searchable. Numerous changes were made, the most important ones relating to the software renderer and palette system to draw directly to the LCD framebuffer "racing the beam" without the need for blitting or converting color formats.
The engine code is located in BSP/STM32CubeIDE/CM7/Example/User/CM7/engine.