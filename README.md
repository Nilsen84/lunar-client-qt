# Lunar Client Qt
Lunar Client Qt is a lightweight launcher for lunar client written in c++ using the qt framework  
  
![alt text](https://i.imgur.com/7j3YGQ5.png)

## Agents
One of the primary features of this launcher is the ability to easily attach java premain agents to your game, 
this allows you to modify the game on launch which lets you write modifications that won't break when lunar recieves an update. 
  
Here's a repository containing some useful java agents that you might want to use: https://github.com/Nilsen84/lunar-client-agents  
If you're familiar with java bytecode feel free to write your own!

## Build instructions
Make sure you have Qt 5.15+ and CMake 3.16+ installed. 
```
git clone https://github.com/Nilsen84/lunar-client-qt.git
cd lunar-client-qt
mkdir build && cd build
cmake ..
make
```

