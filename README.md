# Lunar Client Qt
Lunar Client Qt is a lightweight launcher for lunar client written in C++ using the Qt framework.  
  
![alt text](https://i.imgur.com/cv9SJsk.png)

## Discord
Add me on discord: nils#5281 if you have any questions or thoughts about the project. For any suggestions/issues open an issue here on the github page.

## Agents
One of the primary features of this launcher is the ability to easily attach java premain agents to your game, 
this allows you to modify the game on launch which lets you write modifications that won't break when lunar recieves an update. 
  
Here's a repository containing some useful java agents that you might want to use: https://github.com/Nilsen84/lunar-client-agents  
If you're familiar with java bytecode feel free to write your own!

## Launching without launcher
A useful feature of this launcher is the ability to with the click of a button immediately get into lunar client without the hassle every time
of having to be faced with a launcher interface. Launch Lunar Client Qt with the --nogui argument and you will be launched into lunar client using
the options you have used in the previous launch.

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
If you're on mac, you wanna start off by installing qt using brew: ```brew install qt@5```  
You also want to replace the ```cmake ..``` command with ```cmake -DCMAKE_PREFIX_PATH=/usr/local/opt/qt5/ ..```  
Besides that follow the same instructions above.

