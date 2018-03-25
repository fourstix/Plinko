#ifndef melodies_h
#define melodies_h

//need this for the types to compile
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include "pitches.h"
/*
 * Melodies for coin pusher. Based on:
 *
 * https://github.com/electricmango/Arduino-Music-Project/blob/master/A_Theme___Tetris_with_Bass/A_Theme___Tetris_with_Bass.ino
 * By Github user electricmango under Creative Commons (CC BY-SA 4.0)
 * Sourced 20-12-15
 */
 
// Theme from Gold Diggers 1933 or We're in the Money!
const unsigned short goldDiggersTune[] PROGMEM = {
    //chorus
    NOTE_E4, NOTE_G4, NOTE_E4, NOTE_F4, NOTE_G4,
    NOTE_E4, NOTE_G4, NOTE_E4, NOTE_F4, NOTE_G4,
    REST,    NOTE_E5, NOTE_E5, NOTE_C5, 
    NOTE_D5, NOTE_C5, NOTE_D5, NOTE_C5,
    NOTE_E5, NOTE_C5, NOTE_C5, NOTE_D5, NOTE_C5,
    //chorus
    NOTE_E4, NOTE_G4, NOTE_E4, NOTE_F4, NOTE_G4,
    NOTE_E4, NOTE_G4, NOTE_E4, NOTE_F4, NOTE_G4,
    REST,    NOTE_E5, NOTE_E5, NOTE_C5, 
    NOTE_D5, NOTE_C5, NOTE_D5, NOTE_C5,
    NOTE_E5, NOTE_C5, NOTE_C5, NOTE_D5, NOTE_C5,
    //bridge
    REST,     NOTE_E5,  NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4,
    NOTE_B4,  NOTE_B4,  REST,    NOTE_C5, NOTE_A4,
    NOTE_B4,  NOTE_B4,  NOTE_C5, NOTE_B4,
    REST,     NOTE_E5,  NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4, 
    NOTE_B4,  NOTE_B4,  REST,    NOTE_B4, NOTE_B4,
    NOTE_AS4, NOTE_AS4, NOTE_A4, NOTE_A4,
    NOTE_GS4, NOTE_GS4, NOTE_G4, REST,
    //chorus
    NOTE_E4, NOTE_G4, NOTE_E4, NOTE_F4, NOTE_G4,
    NOTE_E4, NOTE_G4, NOTE_E4, NOTE_F4, NOTE_G4,
    REST,    NOTE_E5, NOTE_E5, NOTE_C5, 
    NOTE_D5, NOTE_C5, NOTE_D5, NOTE_C5,
    NOTE_E5, NOTE_C5, NOTE_C5, NOTE_D5, NOTE_C5,
    REST};

//note durations: 4 = quarter note, 8 = eighth note, etc
const byte goldDiggersTempo[] PROGMEM = {  
    //chorus
    4, 3, 8, 4, 2,
    4, 3, 8, 4, 2,
    4, 4, 3, 8, 
    4, 4, 4, 4, 
    4, 4, 4, 4, 1,
    //chorus
    4, 3, 8, 4, 2,
    4, 3, 8, 4, 2,
    4, 4, 3, 8, 
    4, 4, 4, 4, 
    4, 4, 4, 4, 1,
    //bridge
    4, 4, 8, 8, 8, 8,
    4, 4, 8, 4, 8, 
    4, 2, 4, 1,
    4, 4, 8, 8, 8, 8,
    4, 4, 8, 4, 8,
    4, 4, 4, 4,
    4, 4, 4, 4,
    //chorus
    4, 3, 8, 4, 2,
    4, 3, 8, 4, 2,
    4, 4, 3, 8, 
    4, 4, 4, 4, 
    4, 4, 4, 4, 1,
    1};
    
// Pennies from Heaven
const unsigned short penniesFromHeavenTune[] PROGMEM = {
  // chorus
  NOTE_C5, NOTE_C5, NOTE_C5, NOTE_B4, NOTE_D5, NOTE_D5, NOTE_B4,
  NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_G4, REST,
  // chorus
  NOTE_C5, NOTE_C5, NOTE_C5, NOTE_B4, NOTE_D5, NOTE_D5, NOTE_B4,
  NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_G4, REST,
  // bridge
  REST,    NOTE_E4, NOTE_G4, NOTE_AS4, 
  NOTE_D5, NOTE_D5, NOTE_C5, NOTE_AS4,
  REST,    NOTE_A4, NOTE_A4, NOTE_GS4, NOTE_A4,
  REST,    NOTE_FS4, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_E5, NOTE_D5, NOTE_C5,
  REST,    NOTE_B4,  NOTE_D5, REST,    NOTE_F4, NOTE_A4,  
  // finale
  NOTE_C5, NOTE_C5, NOTE_C5, NOTE_B4, NOTE_D5, NOTE_D5, NOTE_B4,
  NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_G4, REST,
  NOTE_C5, NOTE_C5, NOTE_C5, NOTE_B4, NOTE_D5, NOTE_D5, NOTE_C5,
  NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_D5,
  REST,    NOTE_F4, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_DS5,
  NOTE_D5, NOTE_D5, NOTE_D5, NOTE_CS5, NOTE_C5, NOTE_B4,
  NOTE_B4, NOTE_AS4, NOTE_A4, NOTE_F4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_C5, 
  NOTE_D5, NOTE_E5, NOTE_C5, REST}; 
 
  
//note durations: 4 = quarter note, 8 = eighth note, etc
const byte penniesFromHeavenTempo[] PROGMEM = {
  // chorus
  4, 4, 4, 4, 4, 4, 2,
  8, 8, 8, 3, 2, 2,
  // chorus
  4, 4, 4, 4, 4, 4, 2,
  8, 8, 8, 3, 2, 2,
  // bridge
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4, 1,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 8, 8, 4, 1,
  // finale
  4, 4, 4, 4, 4, 4, 2,
  8, 8, 8, 3, 2, 2,
  4, 4, 4, 4, 4, 4, 2,
  8, 8, 8, 3, 1,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 8, 8, 8, 2,
  8, 8, 6, 6, 6, 6, 6, 6,
  2, 2, 1, 1};
  
// Hot Cross Buns Nursery Rhyme
const unsigned short hotCrossBunsTune[] PROGMEM = {   
  NOTE_B4, NOTE_A4, NOTE_G4,
  NOTE_B4, NOTE_A4, NOTE_G4,
  NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4,
  NOTE_B4, NOTE_A4, NOTE_G4,
  REST};
  
//note durations: 4 = quarter note, 8 = eighth note, etc
const byte hotCrossBunsTempo[] PROGMEM = {  
  4, 4, 2,
  4, 4, 2,
  8, 8, 8, 8, 8, 8, 8, 8,
  4, 4, 2,
  1};  

  // Pop Goes the Weasel
const unsigned short popGoesTheWeaselTune[] PROGMEM = {
  NOTE_G4, NOTE_C5, NOTE_C5, NOTE_D5, NOTE_D5,
  NOTE_E5, NOTE_G5, NOTE_E5, NOTE_C5, NOTE_G4,
  NOTE_C5, NOTE_C5, NOTE_D5, NOTE_F5, NOTE_E5, NOTE_C5, NOTE_G4,
  NOTE_C5, NOTE_C5, NOTE_D5, NOTE_D5, NOTE_E5, NOTE_G5, NOTE_E5, NOTE_C5,
  NOTE_A5, NOTE_D5, NOTE_F5, NOTE_E5, NOTE_C5, REST,
  NOTE_G5, NOTE_C6, NOTE_C6, NOTE_A5, NOTE_C6, NOTE_B5, NOTE_D6, NOTE_B5, NOTE_G5,
  NOTE_G5, NOTE_C6, NOTE_C6, NOTE_A5, NOTE_C6, NOTE_B5, NOTE_G5,
  NOTE_F5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6,
  NOTE_A5, NOTE_D5, NOTE_F5, NOTE_E5, NOTE_C5, REST};

//note durations: 4 = quarter note, 8 = eighth note, etc
const byte popGoesTheWeaselTempo[] PROGMEM = { 
 8, 4, 8, 4, 8,
 8, 8, 8, 4, 8,
 4, 8, 4, 8, 3, 4, 8,
 4, 8, 4, 8, 8, 8, 8, 3,
 3, 4, 8, 3, 4, 8,
 8, 4, 8, 4, 8, 8, 8, 8, 4,
 8, 4, 8, 4, 8, 3, 3,
 4, 8, 4, 8, 4, 8, 4,
 3, 4, 8, 3, 4, 1};
 
  //Money by Pink Floyd
const unsigned short moneyTune[] PROGMEM = {
  //intro 
  NOTE_B2,  REST,    NOTE_B3, NOTE_FS3, NOTE_B2, REST,
  NOTE_FS2, NOTE_A2, NOTE_B2, NOTE_B2,  NOTE_D3, REST,
  NOTE_B2,  REST,    NOTE_B3, NOTE_FS3, NOTE_B2, REST,
  NOTE_FS2, NOTE_A2, NOTE_B2, NOTE_B2,  NOTE_D3, REST,
  //verse 1
  NOTE_FS5, NOTE_FS5, REST, NOTE_A4, NOTE_D5, NOTE_D5, 
  NOTE_A4, NOTE_B4, REST, REST,
  NOTE_B4, NOTE_D5, NOTE_D5, NOTE_B4, NOTE_D5, NOTE_B4, NOTE_FS4, NOTE_A4, NOTE_A4,
  NOTE_E5, NOTE_B4, NOTE_A4, REST, REST, 
  //verse 2
  NOTE_FS5, NOTE_FS5, REST, NOTE_D5, NOTE_D5,
  NOTE_A4, NOTE_B4, REST, REST,
  NOTE_D5, NOTE_B4, NOTE_D5, NOTE_FS4, NOTE_A4, NOTE_B4, 
  NOTE_E5, NOTE_B4, NOTE_A4, REST, REST,
  //coda
  NOTE_FS5, NOTE_FS5, NOTE_FS5, NOTE_CS5,
  NOTE_FS4, NOTE_A4,  NOTE_CS5, NOTE_FS5, NOTE_F5,
  NOTE_E5,  NOTE_E4,  NOTE_E4,  NOTE_G4, 
  NOTE_A4,  NOTE_B4,  NOTE_E5,  
  NOTE_D5,  NOTE_A4,  REST,     REST};
  
//note durations: 4 = quarter note, 8 = eighth note, etc
const byte moneyTempo[] PROGMEM = {
  //intro
  8, 8, 6, 12, 8, 8,
  4, 4, 6, 12, 8, 8,
  8, 8, 6, 12, 8, 8,
  4, 4, 6, 12, 8, 8,
  //verse 1
  8, 6, 2, 16, 12, 16,
  4, 8, 1, 4,
  16, 12, 16, 4, 4, 4, 4, 12, 16,
  3, 16, 6, 4, 1,
  //verse 2
  8, 6, 2, 12, 16,
  4, 8, 1, 4,
  4, 4, 4, 4, 4, 4,
  3, 16, 6, 4, 1,
  //coda
  4, 4, 12, 16,
  4, 4, 4, 4, 4,
  12, 16, 4, 4,
  4, 4, 3, 
  8, 4, 4, 1};

//Price Is Right dum da dum dah whaaa... loser tune
const unsigned short tiltTune[] PROGMEM = {
   NOTE_C4, NOTE_D3,  NOTE_C3,  NOTE_G3, 
   NOTE_B2, NOTE_AS2, NOTE_A2,  NOTE_GS2, NOTE_G2,  NOTE_FS2, 
   NOTE_F2, NOTE_E2,  NOTE_DS2, NOTE_D2,  NOTE_CS2, NOTE_C2,
   NOTE_B1, REST,     REST,     REST};

//note durations: 4 = quarter note, 8 = eighth note, etc
const byte tiltTempo[] PROGMEM = { 
   8, 4, 4, 2,
   2,  16, 16, 16, 16, 16,
   16, 16, 16, 16, 16, 16,
   1, 1, 1, 1}; 

#endif
