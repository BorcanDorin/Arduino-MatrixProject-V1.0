#include "LedControl.h"
#include "pitches.h"
#include "images.h"
#include <LiquidCrystal.h>

#pragma region definingArea

#define Joy1X A5
#define Joy1Y A4
#define Joy2X A3
#define Joy2Y A2
#define ScreenPWN 9
#define ScreenBackLight 13
#define PinBuzzer1 12

#define Adress 0
#define BoardWidth 8
#define BoardHeight 8
#define MatrixSize 8
#define MaxPaletLength 4
#define MinPaletLength 2
#define MaxBounce 12
#define MaxSpeedIndex 5
#define SpeedFactor 25
#define ImageDelay 100
#define GameDelay 250
#define BallDelay 250
#define PaletDelay 100
#define BounceSoundDuration 125
#define SongLength 8
#define MenuDelay 250

LedControl board = LedControl(8, 11, 10, 1); // pini buni
LiquidCrystal screen(2, 3, 4, 5, 6, 7); // pini buni

bool gameStart;
bool twoPlayers;
bool ballDirectionX;  // false -> direction right & true -> direction left
bool ballDirectionY;  // false -> direction down & true -> direction up
bool playNote;
bool playSong;
bool stats;
bool menuDisplay;
bool menuPosition;

int speedIndex;
int paletLength;
int gamePlayers;
int countBounce;
int highScore;

unsigned long previousGameTime;
unsigned long previousBallTime;
unsigned long previousPaletTime;
unsigned long previousNoteTime;
unsigned long previousImageTime;
unsigned long previousSongNoteTime;
unsigned long songPause;
unsigned long previousMenuTime;
unsigned long currentTime;

int ballX;
int ballY;
int player1PaletY; //left
int player2PaletY; //right
int scoreCount;
int currentNote;
int currentImage = 0;

char introMessage1[] = {"Welcome to  "};
char introMessage2[] = {"        PONG "};
char player1Win[] = {"Player 1 wins!!"};
char player2Win[] = {"Player 2 wins!!"};
char happy[] = {"^_^"};
char connector[] = {" - "};
char scoreString[] = {"Your score: "};
char highScoreString[] = {"HighScore: "};
char newHighScore[] = {"NEW HIGHSCORE!!"};
char menuCursor[] = {">"};
char startGame[] = {"Play game ->"};
char playersOne[] = {"Players: 1"};
char playersTwo[] = {"Players: 2"};

int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

#pragma endregion

#pragma region soundsFunctions

void playSound(int note){
  playNote = true;
  previousNoteTime = currentTime;
  noTone(PinBuzzer1);
  tone(PinBuzzer1,  note, BounceSoundDuration);
}

void song() {
  playSong = true;
  previousSongNoteTime = currentTime;
  int noteDuration = 1000 / noteDurations[currentNote];
  noTone(PinBuzzer1);
  tone(PinBuzzer1, melody[currentNote], noteDuration);
  songPause = noteDuration * 1.30;
  currentNote++;
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

#pragma endregion

#pragma region drawFunctions

void displayImage(int matrixNo){
  previousImageTime = currentTime;
  const byte* image = IMAGES[currentImage++];
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
      board.setLed(matrixNo, i, j, bitRead(image[i], 7 - j)); 
}

void drawPalets(){
  for (int i = 0; i < paletLength; i++){
    board.setLed((player1PaletY + i) / MatrixSize, player1PaletY + i, 0, HIGH);
    board.setLed((player1PaletY + i) / MatrixSize, player2PaletY + i, BoardWidth - 1, HIGH);
  }
}

void draw(){
  for(int i = 0; i < BoardHeight / MatrixSize; i++)
    board.clearDisplay(0);
  board.setLed(ballY / MatrixSize, ballY, ballX, 1);
  drawPalets();
}

#pragma endregion

#pragma region game

#pragma region objectsMove

void ballMove(){
  if (ballDirectionX)
    ballX--;
  else
    ballX++;

  if (ballDirectionY)
    ballY--;
  else
    ballY++;
  //this code is for one player mode in order to keep playing with the PC
  if (!twoPlayers){
    player2PaletY = ballY;
    if (player2PaletY > BoardHeight - paletLength)
    player2PaletY = BoardHeight - paletLength;
  }
  //end of one player mode palet move 
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
      score();
      ballDirectionX = !ballDirectionX;
      countBounce++;
    }
  }
  if(ballY == 0 || ballY == BoardHeight - 1)
    ballDirectionY = !ballDirectionY;
}

void score(){
  scoreCount++;
  screen.clear();
  screen.setCursor(0, 0);
  screen.print(scoreString);
  screen.print(scoreCount);
}

void paletMove(){
  //player one palet move 
  int pl1Y = analogRead(Joy1Y);
  if (pl1Y < 400)
    player1PaletY--;
  if (pl1Y > 600)
    player1PaletY++;
  if (player1PaletY > BoardHeight - paletLength)
    player1PaletY = BoardHeight - paletLength;
  if (player1PaletY < 0)
    player1PaletY = 0;

  //player two palet move
  if (twoPlayers){
    int pl2Y = analogRead(Joy2Y);
    if (pl2Y < 400)
      player2PaletY--;
    if (pl2Y > 600)
      player2PaletY++;
    if (player2PaletY > BoardHeight - paletLength)
      player2PaletY = BoardHeight - paletLength;
    if (player2PaletY < 0)
      player2PaletY = 0;
    
  }
}
#pragma endregion

void getUserImput(){
  
  twoPlayers = true;
}

void gameStartUp(){
  scoreCount = 0;
  speedIndex = 0;
  paletLength = MaxPaletLength;
  player1PaletY = (BoardHeight - paletLength) / 2;
  player2PaletY = (BoardHeight - paletLength) / 2;
  currentNote = 0;
  currentImage = 0;
  
  randomSeed(analogRead(0));
  ballX = random(1, BoardWidth - 2);
  randomSeed(analogRead(0));
  ballY = random(1, BoardHeight - 2);
  countBounce = 0;
  
  playNote = false;
  ballDirectionX = false;
  if (ballX > (BoardWidth - 1) / 2)
    ballDirectionX = true;
    
  ballDirectionY = false;
  if (ballY > (BoardWidth - 1) / 2)
    ballDirectionY = true;
  
  draw();
  stats = false;
  gameStart = true;
  playSong = false;
  previousGameTime = millis();
  previousBallTime = previousGameTime;
  previousPaletTime = previousGameTime;
}

void gameOver(){
  gameStart = false;
  displayGameStats();
  song();
}

void displayGameStats(){
  if (!stats){
    stats = true;
    screen.clear();
    screen.setCursor(0, 0); 
    if(twoPlayers){
      if (ballX < (BoardWidth - 1) / 2) 
        screen.print(player2Win);
      else
        screen.print(player1Win);
    }
    else{
      if (scoreCount > highScore){
        highScore = scoreCount;
        screen.print(newHighScore);
        screen.setCursor(0, 1);
        screen.print(happy); 
        screen.print(connector);
        screen.print(scoreCount);
        screen.print(connector);  
        screen.print(happy); 
      }
      else{
        screen.print(highScoreString);
        screen.print(highScore);
        screen.setCursor(0, 1);
        screen.print(scoreString);
        screen.print(scoreCount);
      }
    }
  }
}

void dificulty(){
  if (countBounce == MaxBounce){
    countBounce = 0;
    if (speedIndex < MaxSpeedIndex)
      speedIndex++;
    if (paletLength > MinPaletLength) 
      paletLength--;
  }
}

void gameControls(){
  if (currentTime - previousBallTime > BallDelay - speedIndex * SpeedFactor){
    ballMove();
    if(!twoPlayers)
      dificulty();
    previousBallTime = currentTime;
    draw();
  }
  if (currentTime - previousPaletTime > PaletDelay){
    paletMove();
    previousPaletTime = currentTime;
    draw();
  }
}

#pragma endregion

void menu(){
  if (currentTime - previousMenuTime > MenuDelay){
    int valY = analogRead(Joy1Y);
    if (valY > 600 || valY < 400){
      menuPosition = !menuPosition;
      playSound(NOTE_CS7);
    }
    int valX = analogRead(Joy1X);
    if (valX > 600 || valX < 400){
        if (menuPosition){
          menuDisplay = !menuDisplay;
          gameStartUp();
        }
        else{
          playSound(NOTE_CS8);
          twoPlayers = !twoPlayers;
        }
    }
    //display menu items
    screen.clear();
    if (menuPosition){
      screen.setCursor(0, 0);
      screen.print(menuCursor);
    }
    
    screen.setCursor(1, 0);
    screen.print(startGame);
    if (!menuPosition){
      screen.setCursor(0, 1);
      screen.print(menuCursor);
    }
    screen.setCursor(1, 1);
    if (!twoPlayers)
      screen.print(playersOne);
    else
      screen.print(playersTwo);
    previousMenuTime = currentTime;
  }
}

void setup(){
  gameStart = false;
  screen.begin(16, 2);
  screen.clear();
  pinMode(ScreenPWN, OUTPUT);
  pinMode(ScreenBackLight, OUTPUT);
  digitalWrite(ScreenBackLight, HIGH);
  analogWrite(ScreenPWN, 150);
  screen.setCursor(0, 0);
  screen.print(introMessage1);
  delay(1000);
  screen.setCursor(0, 1);
  screen.print(introMessage2);
  delay(1000);
  for(int i = 0; i < BoardHeight / MatrixSize; i++){
    board.shutdown(i, false);
    board.setIntensity(i, 5);
    board.clearDisplay(i);
  }
  highScore = 0;
  menuDisplay = true;
  playSong = false;
  twoPlayers = false;
  previousMenuTime = millis();
  menuPosition = true;
}

void loop(){
  currentTime = millis();
  if(menuDisplay)
    menu();
  else{
    if (gameStart)
      gameControls();
    if (!gameStart && currentImage != IMAGES_LEN)
      if (currentTime - previousImageTime > ImageDelay)
        displayImage(0);
    if (currentImage == IMAGES_LEN)
      menuDisplay = !menuDisplay;
  }
  sounds();
  
  
}