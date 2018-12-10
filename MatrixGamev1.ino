#include "LedControl.h"
#include "pitches.h"
#include "images.h"
#include "LiquidCrystal.h"

#define JOY_X A5
#define JOY_Y A4

#define MAX_PaletLength 4
#define MIN_PaletLength 2
#define MAX_Bounce 12
#define MAX_Speed 5
#define Image_Delay 100
#define Game_Delay 250

LedControl board = LedControl(12, 11, 10, 1); // pini buni
LiquidCrystal screen(2, 3, 4, 5, 6, 7); // schimba pini

bool gameStart;
bool twoPlayers;
bool ballDirectionX;  // false -> direction right & true -> direction left
bool ballDirectionY;  // false -> direction down & true -> direction up
int speedIndex;
int paletLength;
int gamePlayers;
int countBounce;
unsigned long previousTime;
unsigned long currentTime;

int ballX;
int ballY;
int player1PaletY; //left
int player2PaletY; //right
int score;

char introMessage[] = {"Welcome to   \n     PONG "};//verify messages 

void playNote(int note){
  int noteDuration = 1000 / 8;
  tone(8,  note, noteDuration);
  int pauseBetweenNotes = noteDuration * 1.30;
  delay(pauseBetweenNotes);
  noTone(8);
}

int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void playSong() {
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(8);
  }
}

void getUserImput(){
  twoPlayers = false;
}

void displayImage(const byte* image){
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
      board.setLed(0, i, j, bitRead(image[i], 7 - j)); 
}

void gameStartUp(){
  score = 0;
  speedIndex = 0;
  paletLength = MAX_PaletLength;
  player1PaletY = 2;
  player2PaletY = 2;
  
  randomSeed(analogRead(0));
  ballX = random(1, 6);
  randomSeed(analogRead(0));
  ballY = random(1, 6);
  countBounce = 0;
  
  ballDirectionX = false;
  if (ballX > 3)
    ballDirectionX = true;
    
  ballDirectionY = false;
  if (ballY > 3)
    ballDirectionY = true;
  
  draw();
  gameStart = true;
  previousTime = millis();
}

void drawPalets(){
  for (int i = 0; i < paletLength; i++){
    board.setLed(0, player1PaletY + i, 0, HIGH);
    board.setLed(0, player2PaletY + i, 7, HIGH);
  }
}

void draw(){
  board.clearDisplay(0);
  board.setLed(0, ballY, ballX, 1);
  drawPalets();
}

void gameOver(){
  gameStart = false;
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    //delay(pauseBetweenNotes);
    board.clearDisplay(0);
    delay(pauseBetweenNotes / 2);
    draw();
    delay(pauseBetweenNotes / 2);
    noTone(8);
  }
  for (int i = 0; i < IMAGES_LEN; i++){
    displayImage(IMAGES[i]);
    delay(Image_Delay);
  }
}

void setup(){
  gameStart = false;
  screen.begin(16, 2);
  board.shutdown(0, false);
  board.setIntensity(0, 2);
  board.clearDisplay(0);

  getUserImput();
  gameStartUp();
}
void gameControls(){
      //get ball new position
    if (ballDirectionX)
      ballX--;
    else
      ballX++;
    if (ballDirectionY)
      ballY--;
    else
      ballY++;
      
      //get player 1 palet location
    int pl1Y = analogRead(JOY_Y);
    //if (pl1Y < 100)
    //  player1PaletY--;
    if (pl1Y < 400)
      player1PaletY--;
    if (pl1Y > 600)
      player1PaletY++;
    //if (pl1Y > 900)
    //  player1PaletY++;
    if (player1PaletY > 8 - paletLength)
      player1PaletY = 8 - paletLength;
    if (player1PaletY < 0)
      player1PaletY = 0;

      //get player 2 palet location
    if (!twoPlayers){
      score++;
      player2PaletY = ballY;
      if (player2PaletY > 8 - paletLength)
      player2PaletY = 8 - paletLength;
    }
    
      //check end game and bounce
    if (ballX == 1){
      if (ballY < player1PaletY || ballY > player1PaletY + paletLength)
        gameOver();
      else{
        playNote(NOTE_E3);
        ballDirectionX = !ballDirectionX;
        countBounce++;
      }
    }
    if (ballX == 6){
      if (ballY < player2PaletY || ballY > player2PaletY + paletLength)
        gameOver();
      else{
        playNote(NOTE_C5);
        ballDirectionX = !ballDirectionX;
        countBounce++;
      }
    }
    if(ballY == 0 || ballY == 7)
      ballDirectionY = !ballDirectionY;
        
    if (countBounce == MAX_Bounce){
      countBounce = 0;
      if (speedIndex < MAX_Speed)
        speedIndex++;
      if (paletLength > MIN_PaletLength) 
        paletLength--;
    }

      //
    draw();
}
void loop(){
  if (gameStart){
    currentTime = millis();
    if (currentTime - previousTime > Game_Delay - speedIndex * 25){
      gameControls();
      previousTime = currentTime;
      //delay(250 - speedIndex * 25);
    }
  }
  
}
