const byte IMAGES[][8] = {
{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
},{
  B00000000,
  B00000000,
  B00000001,
  B00000001,
  B00000001,
  B00000000,
  B00000000,
  B00000000
},{
  B00000000,
  B00000001,
  B00000011,
  B00000011,
  B00000011,
  B00000001,
  B00000000,
  B00000000
},{
  B00000001,
  B00000011,
  B00000110,
  B00000110,
  B00000110,
  B00000011,
  B00000001,
  B00000000
},{
  B00000011,
  B00000110,
  B00001100,
  B00001100,
  B00001100,
  B00000110,
  B00000011,
  B00000000
},{
  B00000111,
  B00001100,
  B00011000,
  B00011000,
  B00011001,
  B00001100,
  B00000111,
  B00000000
},{
  B00001111,
  B00011001,
  B00110000,
  B00110000,
  B00110011,
  B00011001,
  B00001111,
  B00000000
},{
  B00011110,
  B00110011,
  B01100000,
  B01100000,
  B01100111,
  B00110011,
  B00011111,
  B00000000
},{
  B00111100,
  B01100110,
  B11000000,
  B11000000,
  B11001110,
  B01100110,
  B00111110,
  B00000000
},{
  B01111000,
  B11001100,
  B10000000,
  B10000000,
  B10011100,
  B11001101,
  B01111100,
  B00000000
},{
  B11110000,
  B10011000,
  B00000001,
  B00000000,
  B00111001,
  B10011011,
  B11111001,
  B00000000
},{
  B11100000,
  B00110000,
  B00000011,
  B00000000,
  B01110011,
  B00110110,
  B11110011,
  B00000000
},{
  B11000000,
  B01100000,
  B00000111,
  B00000000,
  B11100111,
  B01101100,
  B11100111,
  B00000000
},{
  B10000000,
  B11000000,
  B00001111,
  B00000001,
  B11001111,
  B11011001,
  B11001110,
  B00000000
},{
  B00000000,
  B10000000,
  B00011110,
  B00000011,
  B10011111,
  B10110011,
  B10011101,
  B00000000
},{
  B00000000,
  B00000000,
  B00111100,
  B00000110,
  B00111110,
  B01100110,
  B00111011,
  B00000000
},{
  B00000000,
  B00000000,
  B01111000,
  B00001100,
  B01111100,
  B11001100,
  B01110110,
  B00000000
},{
  B00000000,
  B00000000,
  B11110001,
  B00011001,
  B11111001,
  B10011001,
  B11101101,
  B00000000
},{
  B00000000,
  B00000000,
  B11100011,
  B00110011,
  B11110011,
  B00110011,
  B11011011,
  B00000000
},{
  B00000000,
  B00000000,
  B11000110,
  B01100111,
  B11100111,
  B01100110,
  B10110110,
  B00000000
},{
  B00000000,
  B00000000,
  B10001100,
  B11001111,
  B11001111,
  B11001101,
  B01101100,
  B00000000
},{
  B00000000,
  B00000000,
  B00011001,
  B10011111,
  B10011111,
  B10011010,
  B11011000,
  B00000000
},{
  B00000000,
  B00000000,
  B00110011,
  B00111111,
  B00111111,
  B00110101,
  B10110001,
  B00000000
},{
  B00000000,
  B00000000,
  B01100110,
  B01111111,
  B01111111,
  B01101011,
  B01100011,
  B00000000
},{
  B00000000,
  B00000000,
  B11001100,
  B11111110,
  B11111110,
  B11010110,
  B11000110,
  B00000000
},{
  B00000000,
  B00000000,
  B10011000,
  B11111101,
  B11111101,
  B10101101,
  B10001100,
  B00000000
},{
  B00000000,
  B00000000,
  B00110001,
  B11111011,
  B11111011,
  B01011011,
  B00011001,
  B00000000
},{
  B00000000,
  B00000000,
  B01100011,
  B11110110,
  B11110111,
  B10110110,
  B00110011,
  B00000000
},{
  B00000000,
  B00000000,
  B11000111,
  B11101100,
  B11101111,
  B01101100,
  B01100111,
  B00000000
},{
  B00000000,
  B00000000,
  B10001111,
  B11011001,
  B11011111,
  B11011000,
  B11001111,
  B00000000
},{
  B00000000,
  B00000000,
  B00011110,
  B10110011,
  B10111111,
  B10110000,
  B10011110,
  B00000000
},{
  B00000000,
  B00000000,
  B00111100,
  B01100110,
  B01111110,
  B01100000,
  B00111100,
  B00000000
},{
  B00000000,
  B00000000,
  B01111000,
  B11001100,
  B11111100,
  B11000000,
  B01111000,
  B00000000
},{
  B00000000,
  B00000000,
  B11110000,
  B10011000,
  B11111000,
  B10000000,
  B11110000,
  B00000000
},{
  B00000000,
  B00000000,
  B11100000,
  B00110000,
  B11110000,
  B00000000,
  B11100000,
  B00000000
},{
  B00000000,
  B00000000,
  B11000000,
  B01100000,
  B11100000,
  B00000000,
  B11000000,
  B00000000
},{
  B00000000,
  B00000000,
  B10000000,
  B11000000,
  B11000000,
  B00000000,
  B10000000,
  B00000000
},{
  B00000000,
  B00000000,
  B00000000,
  B10000000,
  B10000000,
  B00000000,
  B00000000,
  B00000000
},{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
},{
  B00000000,
  B00000000,
  B00000000,
  B00000001,
  B00000001,
  B00000001,
  B00000000,
  B00000000
},{
  B00000000,
  B00000000,
  B00000001,
  B00000011,
  B00000011,
  B00000011,
  B00000001,
  B00000000
},{
  B00000000,
  B00000000,
  B00000011,
  B00000110,
  B00000110,
  B00000110,
  B00000011,
  B00000000
},{
  B00000000,
  B00000000,
  B00000111,
  B00001100,
  B00001100,
  B00001100,
  B00000111,
  B00000000
},{
  B00000000,
  B00000000,
  B00001111,
  B00011001,
  B00011001,
  B00011001,
  B00001111,
  B00000000
},{
  B00000000,
  B00000000,
  B00011110,
  B00110011,
  B00110011,
  B00110011,
  B00011110,
  B00000000
},{
  B00000000,
  B00000000,
  B00111100,
  B01100110,
  B01100110,
  B01100110,
  B00111100,
  B00000000
},{
  B00000000,
  B00000000,
  B01111000,
  B11001100,
  B11001100,
  B11001100,
  B01111000,
  B00000000
},{
  B00000000,
  B00000000,
  B11110001,
  B10011001,
  B10011001,
  B10011000,
  B11110000,
  B00000000
},{
  B00000000,
  B00000000,
  B11100011,
  B00110011,
  B00110011,
  B00110001,
  B11100000,
  B00000000
},{
  B00000000,
  B00000000,
  B11000110,
  B01100110,
  B01100110,
  B01100011,
  B11000001,
  B00000000
},{
  B00000000,
  B00000000,
  B10001100,
  B11001100,
  B11001100,
  B11000111,
  B10000011,
  B00000000
},{
  B00000000,
  B00000000,
  B00011001,
  B10011001,
  B10011001,
  B10001111,
  B00000110,
  B00000000
},{
  B00000000,
  B00000000,
  B00110011,
  B00110011,
  B00110011,
  B00011110,
  B00001100,
  B00000000
},{
  B00000000,
  B00000000,
  B01100110,
  B01100110,
  B01100110,
  B00111100,
  B00011000,
  B00000000
},{
  B00000000,
  B00000000,
  B11001100,
  B11001100,
  B11001100,
  B01111000,
  B00110000,
  B00000000
},{
  B00000000,
  B00000000,
  B10011000,
  B10011001,
  B10011001,
  B11110001,
  B01100000,
  B00000000
},{
  B00000000,
  B00000000,
  B00110001,
  B00110011,
  B00110011,
  B11100011,
  B11000001,
  B00000000
},{
  B00000000,
  B00000000,
  B01100011,
  B01100110,
  B01100111,
  B11000110,
  B10000011,
  B00000000
},{
  B00000000,
  B00000000,
  B11000111,
  B11001100,
  B11001111,
  B10001100,
  B00000111,
  B00000000
},{
  B00000000,
  B00000000,
  B10001111,
  B10011001,
  B10011111,
  B00011000,
  B00001111,
  B00000000
},{
  B00000000,
  B00000000,
  B00011110,
  B00110011,
  B00111111,
  B00110000,
  B00011110,
  B00000000
},{
  B00000000,
  B00000000,
  B00111100,
  B01100110,
  B01111110,
  B01100000,
  B00111100,
  B00000000
},{
  B00000000,
  B00000000,
  B01111000,
  B11001100,
  B11111100,
  B11000000,
  B01111000,
  B00000000
},{
  B00000000,
  B00000000,
  B11110001,
  B10011000,
  B11111000,
  B10000000,
  B11110001,
  B00000000
},{
  B00000000,
  B00000000,
  B11100011,
  B00110001,
  B11110001,
  B00000001,
  B11100011,
  B00000000
},{
  B00000000,
  B00000000,
  B11000110,
  B01100011,
  B11100011,
  B00000011,
  B11000111,
  B00000000
},{
  B00000000,
  B00000000,
  B10001101,
  B11000111,
  B11000110,
  B00000110,
  B10001111,
  B00000000
},{
  B00000000,
  B00000000,
  B00011011,
  B10001110,
  B10001100,
  B00001100,
  B00011110,
  B00000000
},{
  B00000000,
  B00000000,
  B00110111,
  B00011101,
  B00011001,
  B00011000,
  B00111100,
  B00000000
},{
  B00000000,
  B00000000,
  B01101110,
  B00111011,
  B00110011,
  B00110000,
  B01111000,
  B00000000
},{
  B00000000,
  B00000000,
  B11011100,
  B01110110,
  B01100110,
  B01100000,
  B11110000,
  B00000000
}};
const int IMAGES_LEN = sizeof(IMAGES)/8;