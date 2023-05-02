
```
 _   _  _________  ___________  ______ _____  ________  ___
| | | ||___  /   ||___  /_   _| |  _  \  _  ||  _  |  \/  |
| |_| |   / / /| |   / /  | |   | | | | | | || | | | .  . |
|  _  |  / / /_| |  / /   | |   | | | | | | || | | | |\/| |
| | | |./ /\___  |./ /   _| |_  | |/ /\ \_/ /\ \_/ / |  | |
\_| |_/\_/     |_/\_/    \___/  |___/  \___/  \___/\_|  |_/
 ```

# Doom on the STM32H747i-Discovery board
## Building

Building the code:
- Install STM32CubeIDE
- Open BSP/STM32CubeIDE/.project
- Build the project within the IDE

Building the USB networking utility:
- Make sure dependencies such as CMake and SDL2 are installed
- run `cmake .` and `make` in STMDoomComNetwork/


## Running

The code expects the main WAD file to be loaded in external flash at 0x91000000. Any WAD file can be used (shareware, full game, mods...), but *the networking code will only work with doom.wad (the full game)*.
Load the WAD in flash using STM32CubeProgrammer or similar.

Doom should run out-of-the-box once loaded onto the board. 
Controls are as follows:
* Wakeup button: Fire
* Center joystick button: Use
* Joystick: Move
* Fire+Use (in that order): Enter/Exit menu

Two touchscreen buttons allow toggling in and out of the automap, and cycling between weapons. 

Savegames are working, and are implemented using the external flash memory.
Audio is working as well (OPL2 emulation): simply plug a headset inside the Audio OUT port.

### Networking support
This Doom port supports networking over USB using a host-side utility.
Required steps: 
* Plug a second USB cable between a host computer and the USB OTG_HS port on the board.
* Build and run STMDoomComNetwork as follows:
	* `$ ./STMDoomComNetwork <serial_port>`
	* where <serial_port> corresponds to the virtual COM port assigned to the board.
* Reset the board to restart Doom.
* run `$ chocolate-doom.exe -server -deathmatch` on the host computer to start a server.
* Enjoy !
