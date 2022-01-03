<h1 align="center">Asteroids C++</h1>
<h6 align="center">Written in C++ using SDL2</h6>

<p align="center">
  <img width="543" alt="asteroids-logo" src="https://user-images.githubusercontent.com/81219815/146649608-eb616daf-bb2c-4589-8cab-2718d94c022d.png">
</p>


## Usage
This application is a fun weekend project that aims to be a simple recreation of Space Invaders. The structure of the project is
broken into components with the intention for easy project expansion.

#### Application Specifications
- C++ version 11
- sdl2 version 2.0.18
- CMake version 3.21
- Apple clang version 13.0.0
- macOS Monterey version 12.1


#### Setup

###### Clone the repository
```
git clone https://github.com/BrandonJernigan/Asteroids_Cpp.git
```
###### Ensure that you have SDL2
```js
// Ensure that you have the base sdl2 library installed
```
Refer to this [link](https://www.libsdl.org/download-2.0.php) to download for your operating system.
###### Edit the fonts path in the source code
```c++
// Menu.cpp
// Add the absolute path to the fonts directory
14 TTF_Font *font = TTF_OpenFont("<YOUR ABSOLUTE PATH HERE>/EncodeSansCondensed-Regular.ttf", 24);
```
```c++
// Score.cpp
// Add the absolute path to the fonts directory
10 TTF_Font *font = TTF_OpenFont("<YOUR ABSOLUTE PATH HERE>/EncodeSansCondensed-Regular.ttf", 24);
```
