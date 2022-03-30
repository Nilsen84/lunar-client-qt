# Lunar Client Qt
Lunar Client Qt is a lightweight, cross-platform and open sourced launcher for Lunar Client written in C++ using the Qt framework.  
  
![Lunar Client Qt](https://i.imgur.com/owcLWNV.png)

## Discord
Add me on Discord (nils#5281) if you have any questions or thoughts about the project. For any suggestions/issues open an issue here on the github page.

## Agents
One of the primary features of this launcher is the ability to easily attach Java premain agents to your game, 
this allows you to modify the game on launch, which lets you write modifications that won't break when Lunar Client recieves an update. 
  
Here's a repository containing some useful Java agents that you might want to use: https://github.com/Nilsen84/lunar-client-agents  
If you're familiar with java bytecode, feel free to write your own!

## Build instructions
Make sure you have Qt 5.15+ and CMake 3.16+ installed. 
```
git clone https://github.com/Nilsen84/lunar-client-qt.git
cd lunar-client-qt
mkdir build && cd build
cmake ..
make
```

**NOTE**  
If you're on MacOS, you wanna start off by installing Qt using [Brew](https://brew.sh/): ```brew install qt@5```  
You also want to replace the `cmake ..` command with `cmake -DCMAKE_PREFIX_PATH=/usr/local/opt/qt5/ ..`  
Besides that follow the same instructions above.

