#include "LedControl.h"
#include "pitches.h"
#include "images.h"
#include <LiquidCrystal.h>

#define JoyX A5
#define JoyY A4
#define PinBuzzer1 8

#define MaxPaletLength 4
#define MinPaletLength 2
#define MaxBounce 12
#define MaxSpeed 5
#define ImageDelay 100
#define GameDelay 250
#define BallDelay 250
#define PaletDelay 50
#define BounceSoundDuration 125
#define SongLength 8

LedControl board = LedControl(12, 11, 10, 1); // pini buni
LiquidCrystal screen(2, 3, 4, 5, 6, 7); // schimba pini

bool gameStart;
bool twoPlayers;
bool ballDirectionX;  // false -> direction right & true -> direction left
bool ballDirectionY;  // false -> direction down & true -> direction up
bool playNote;
bool playSong;

int speedIndex;
int paletLength;
int gamePlayers;
int countBounce;

unsigned long previousGameTime;
unsigned long previousBallTime;
unsigned long previousPaletTime;
unsigned long previousNoteTime;
unsigned long previousImageTime;
unsigned long previousSongNoteTime;
unsigned long songPause;
unsigned long currentTime;

int ballX;
int ballY;
int player1PaletY; //left
int player2PaletY; //right
int score;
int currentNote;
int currentImage = 0;

char introMessage[] = {"Welcome to   \n     PONG "};//verify messages 

void playSound(int note){
  playNote = true;
  previousNoteTime = currentTime;
  noTone(PinBuzzer1);
  tone(PinBuzzer1,  note, BounceSoundDuration);
  //
}

int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void song() {
  playSong = true;
  previousSongNoteTime = currentTime;
  int noteDuration = 1000 / noteDurations[currentNote];
  noTone(PinBuzzer1);
  tone(PinBuzzer1, melody[currentNote], noteDuration);
  songPause = noteDuration * 1.30;
  currentNote++;
}

void getUserImput(){
  twoPlayers = false;
}

void displayImage(){
  previousImageTime = currentTime;
  const byte* image = IMAGES[currentImage++];
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
      board.setLed(0, i, j, bitRead(image[i], 7 - j)); 
}

void gameStartUp(){
  score = 0;
  speedIndex = 0;
  paletLength = MaxPaletLength;
  player1PaletY = 2;
  player2PaletY = 2;
  currentNote = 0;
  currentImage = 0;
  
  randomSeed(analogRead(0));
  ballX = random(1, 6);
  randomSeed(analogRead(0));
  ballY = random(1, 6);
  countBounce = 0;
  
  playNote = false;
  ballDirectionX = false;
  if (ballX > 3)
    ballDirectionX = true;
    
  ballDirectionY = false;
  if (ballY > 3)
    ballDirectionY = true;
  
  draw();
  gameStart = true;
  playSong = false;
  previousGameTime = millis();
  previousBallTime = previousGameTime;
  previousPaletTime = previousGameTime;
  
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
  song();
  /*
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
  }*/

  /*
  for (int i = 0; i < IMAGES_LEN; i++){
    displayImage(IMAGES[i]);
    delay(ImageDelay);
  }*/
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

void ballMove(){
  if (ballDirectionX)
    ballX--;
  else
    ballX++;

  if (ballDirectionY)
    ballY--;
  else
    ballY++;
  if (!twoPlayers){
    player2PaletY = ballY;
    if (player2PaletY > 8 - paletLength)
    player2PaletY = 8 - paletLength;
  }
  if (ballX == 1){
    if (ballY < player1PaletY || ballY > player1PaletY + paletLength)
      gameOver();
    else{
      playSound(NOTE_E3);
      ballDirectionX = !ballDirectionX;
      countBounce++;
    }
  }
  if (ballX == 6){
    if (ballY < player2PaletY || ballY > player2PaletY + paletLength)
      gameOver();
    else{
      playSound(NOTE_C5);
      ballDirectionX = !ballDirectionX;
      countBounce++;
    }
  }
  if(ballY == 0 || ballY == 7)
    ballDirectionY = !ballDirectionY;
}

void validateGame(){
  
}

void paletMove(){
  int pl1Y = analogRead(JoyY);
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
    //player2PaletY = ballY;
    //if (player2PaletY > 8 - paletLength)
    //player2PaletY = 8 - paletLength;
  }
}

void dificulty(){
  if (countBounce == MaxBounce){
    countBounce = 0;
    if (speedIndex < MaxSpeed)
      speedIndex++;
    if (paletLength > MinPaletLength) 
      paletLength--;
  }
}
void gameControls(){
  if (currentTime - previousBallTime > BallDelay - speedIndex * 25){
    ballMove();
    previousBallTime = currentTime;
    draw();
  }
  if (currentTime - previousPaletTime > PaletDelay){
    paletMove();
    previousPaletTime = currentTime;
    draw();
  }
}

void sounds(){
  if (playNote)
    if (currentTime - previousNoteTime > BounceSoundDuration){
      playNote = false;
      noTone(PinBuzzer1);
    }
  if (playSong)
    if (currentTime - previousSongNoteTime > songPause){
      if (currentNote == SongLength){
        playSong = false;
        currentNote = 0;
        noTone(PinBuzzer1);
      }
      else
        song();
    }
}
void loop(){
  currentTime = millis();
  if (gameStart)
    gameControls();
  if (!gameStart && currentImage != IMAGES_LEN)
    if (currentTime - previousImageTime > ImageDelay)
      displayImage();
  sounds();
}