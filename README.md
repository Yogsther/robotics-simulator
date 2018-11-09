## Robotar - Systembeskrivning


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

