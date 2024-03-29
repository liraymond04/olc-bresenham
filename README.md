# olc-bresenham

Implementation of [Bresenham's line algorithm](http://members.chello.at/~easyfilter/bresenham.html) for plotting curves.

Project using javidx9's [olcPixelGameEngine](https://github.com/OneLoneCoder/olcPixelGameEngine)

## Controls

| Button | Action |
| ----------- | ----------- |
| Escape | Quit |
| Left arrow | Previous curve |
| Right arrow | Next curve |
| Left click | Plot point |
| Backspace | Clear points |

## Building

Building is based on Moros1138's [pge-template-project](https://github.com/Moros1138/pge-template-project) CMake files

### Arch Linux

Install the required packages with the following command

`sudo pacman -Sy base-devel cmake git libpng mesa`

Generate project makefiles with CMake

`cmake .`

And build the project

`make`

### Windows

Install a C++ compiler like [MinGW](https://sourceforge.net/projects/mingw/)

Generate project makefiles with CMake

`cmake . -G "MinGW Makefiles"`

And build the project

`mingw32-make`
