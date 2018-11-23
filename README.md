## Robotics Simulator 2019

![Example GIF](example.png)

### Try it out

You can find the latest linux and win32 build in /build or at the [releases](https://github.com/Yogsther/robotics-simulator/releases). 
Make sure you have an up-to-date options.cfg file with the executable. 

*Feel free to edit the options.cfg and experiment.*

#### Build it on linux

Simply run ```g++ *.cpp``` in /src, then run the program **and** make sure options.cfg is in the same folder.

### About

There are two types of robots, normal - light loving robots (R) and light hating robots (H). There are light sources (L) and fuel stations (B).
Once a robot goes below the fuel threshold it will seek a fuel station and ignore light conditions.
When they need to fuel, the robot will stick itself to a fuel station and stay there while refueling to max capacity.

Robots can walk diagonally but they wont walk through eachother or other items.

Check out options.cfg for more information on behavior.


### About the code

#### Options.cpp

Options will read the options.cfg file. It's a custom written reader that supports comments with '#', spaces
and extra line breaks.

A new option can be added with a ```(string)OPTION_NAME: (int)VALUE (linebreak)```
Then to read it in the code, create and Options object, and use ```options.get("OPTION_NAME");```

#### Block.cpp

The map is built out of blocks, each block contains an item value, the distance to nearest fuel station and the light value

#### Map.cpp

The map class contains a matrix of blocks. One of the most important parts of Map is the bake method. 
It will calculate all distances and light values and save them, since all of those values are static.

It also has a summon feature for spawning items at random positions that prevents overlapping. 

#### Robot.cpp

The robots decide where to go next by using the evaluateMove system. All possible 8 moves (up, down, left, right and diagonal)
are evaluated and given a score. Then one with highest score is chosen. If it's tie between moves, the direction of the robot
will be prioritize. If multiple options are equally good, but the direction move is not as good, a random move from the best ones
will be chosen. 

The evaluation method takes into account: light values, if the robot has been there before (trail) and distance to fuel station (if below threshold).

Since the robots are not stored inside the map (only stations and light sources are) is a footprint system used. After every move, the robots footprint will
be removed and reapplied in the new position. This allows the robots to see other robots since they only have access to the map.


## Robotar - Systembeskrivning (not up to date)


#### Position

###### public

int x, y

Position(int x, int y) - Konstruktorn 

#### Robot

###### private: 

int fuel - Mängden bränsle i roboten

bool lightlover - Om roboten gillar ljus

Position position - X, Y för roboten

###### public: 

move(int x, int y) - Förflytta roboten ett steg, x, y kan max vara 1 och minst -1. Roboten kan gå diagonalt

refuel() - Om roboten är nära en station kan den tanka via denna metod.


#### Block
###### public: 

int light - Mängden ljus där, 0-10 där 0 är helt mörker

int item - Vad det finns för item där just då, 0-2 där 0 är tomt. 1 är ljuskälla och 2 är station

setLight(int intensity) Set the light intenisty, 1-10 int value

setItem(int item) - Set item, any int

getLight() - Get the light level from that block

getItem() - Get the item in that block


#### Map

###### private

int width

int height

Map(int width, int height) Skapa kartan med en width och height, konstruktorn

block[] mapContent - Kartan som innehåller alla block

###### public

void bake() - Baka ljuset i hela världen beroende på var alla ljuskällor befinner sig.

void putItem(int id, x, y) - Skapa ett item vid x, y. T.ex en ljuskälla, för att bygga upp världen innan man startar simuleringen 

block[] getMap() returnerar mapContent i form av en block array

block getItemAt(x, y) returnerar blocket vid x,y

block getItemAt(index) returnerar blocket vid index



#### Screen

###### private

char[] data - Information for each pixel to draw

###### public

clear() - Clear screen

draw(char character, int x, int y) - Input something in the screen data

render() - Render everything on screen, should be done once everything has been draw each frame. 
 
Screen(int width, int height) - Constructor, creates a screen and render a border with each render() call

#### main

Map map - En karta som innehåller positioner för alla stationer och ljuskällor och en ljus-karta.

Robot[] robots - En array med alla robotar i världen.

