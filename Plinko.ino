/* 
 * (c) Copyright 2018 by Gaston R. Williams
 * No Rights Reserved.
 *
 * This code is free, and may be freely used, copied or shared.
 *
 * This code was written for RetroBuiltGames CoinPusher kit.  It runs
 * as a continuous event loop so that the servo canmove and music can
 * play simultaneuosly without interferring with each other.
 *
 * There are  five tunes available, selected by a Music button, with a 
 * mute in between.  Pressing the Play button will move the servo.  The
 * servo will move for up to 3 seconds after the Play button is released.
 *
 * A switch inside will interrupt play if the machine is titled.
 * The machine will do nothing, but play the tilt theme, until the Clear 
 * button is pressed.
 *
 * This Coin Pusher and other arcade kits are available at:
 * www.retrobuiltgames.com
 *
 */
#include <Servo.h>

#include "melodies.h"

// define output and input pins - defines take up no space
#define TILT_PIN  2
#define MUSIC_PIN 3
#define PLAY_PIN  4
#define CLEAR_PIN 5
#define SERVO_PIN 6
#define SPKR_PIN  7
#define LED_PIN   8

// Melody constants
#define TILT_THEME    -2
#define SILENCE       -1
#define GOLD_DIGGERS        0
#define PENNIES_FROM_HEAVEN 1
#define HOT_CROSS_BUNS      2
#define POP_GOES_THE_WEASEL 3
#define PINK_FLOYD_MONEY    4

// Music button press count should include silence in between, 
// but not include tilt theme. 
// So it should be 2 times the number of songs available

#define MAX_PRESSES 10


// Simple two-state machine for playing music notes
#define PLAY_NOTE    0
#define HOLD_NOTE    1


// time for button debounce
#define DEBOUNCE_TIME 100

// time to push servos after button pressed
#define SERVO_PUSH 3000

// continuous rotation servo constants
#define SERVO_STOP 90
#define SERVO_GO   60


// variable for status of music state machine
int musicState = PLAY_NOTE;

// current time
unsigned long volatile tick = millis();

// melody variables
unsigned long  noteStamp   = tick;
unsigned short currentNote = 0;
int            tune        = 0;


// tilt variables
boolean       tilted    = false;
unsigned long tiltStamp = tick;

// music button variables
unsigned long musicButton   = tick;
int           melodyCount   = 0;
// don't allow music button to be mashed down continuously
boolean       musicButtonUp = false;

// play button variables
unsigned long playButton   = tick;
boolean       pushCoins    = false;

// create servo object to control coinPusher
Servo coinPusher; 


/*
 * One-time setup code
 */
void setup() {
  //Serial.begin(9600);
  // set up input pins
  pinMode(TILT_PIN,  INPUT_PULLUP);
  pinMode(MUSIC_PIN, INPUT_PULLUP);
  pinMode(PLAY_PIN,  INPUT_PULLUP);
  pinMode(CLEAR_PIN, INPUT_PULLUP);
  // set up output pins
  pinMode(SPKR_PIN,  OUTPUT);
  pinMode(LED_PIN,   OUTPUT);
  
  // attach servo to Arduino pin
  coinPusher.attach(SERVO_PIN);
  
  // set up interrupt and melody
  clearTilt();
}

/*
 * Main loop 
 * Note that we never call delay() so music plays continuously
 *
 */
void loop() {
  tick = millis();

  musicState = playMelody(musicState);

  if (tilted) {
    // stop any motion
    coinPusher.write(SERVO_STOP);
    
    // blink the LED to show a tilt
    blinkTilt();
    
    // check clear button
    handleClearButton();
  } else {
    handleMusicButton();
    handlePlayButton();
    handleServo();
  } // if - else titled
} // loop

/*
 * Calculate the time after an event
 *
 * unsigned long eventTimestamp - time event occurred
 * returns unsigned long - the time passed since event
 *
 * Note: The millis() function takes about 50 days to roll over, but even so
 * since the time values are unsigned long, their difference is always positive and 
 * the correct value, even if the millis() function has rolled over through zero.
 *
 */
unsigned long timeSinceEvent(unsigned long eventTimestamp) {
  tick = millis();
  
  return (tick - eventTimestamp);
}

/*
 * Interrupt handler - disable interrupt and set tilt variables
 *
 */
void tilt () {
  detachInterrupt(digitalPinToInterrupt(TILT_PIN));
  
  // Serial.println("Interrupt triggered!");
  tilted = true;  
  tiltStamp = millis();
  setMelody();
}

/*
 * Clear flags and set interrupt
 *
 */
void clearTilt() {
  tilted = false;
  // turn off blinking light
  digitalWrite(LED_PIN, LOW); 
  // Serial.println("Interrupt reset!");
  attachInterrupt(digitalPinToInterrupt(TILT_PIN), tilt, LOW);
  // clear buttons
  resetButtons();
  setMelody();
}

/*
 * Stop the music and reset to the next tune
 */
void setMelody() {
  // stop the music
  noTone(SPKR_PIN);
  
  // set to the new tune
  setTune();
   
  // set to play from beginning of melody
  currentNote = 0; 
  musicState = PLAY_NOTE;
  
  // set the note timestamp
  tick = millis();
  noteStamp = tick;
} // setMelody

/*
 * Play a note based on the event state machine based on time.
 * int state = current state of machine
 * returns int - the next state for the machine.
 *
 */
int playMelody(int state) {
  // Stay in current state as default
  int nextState = state;
  if(tune == SILENCE) {
   // just do nothing until melody chages
  } else {
    unsigned int noteDuration  = getNoteDuration();
    unsigned int noteFrequency = getNoteFrequency();

    // start playing the initial note one time only, after a reset
    if (state == PLAY_NOTE) {
      tone(SPKR_PIN, noteFrequency, noteDuration);
      nextState = HOLD_NOTE;
    } else if (state == HOLD_NOTE) {  
      if (timeSinceEvent(noteStamp) > (noteDuration * 1.3)) {
         // play next note
         noTone(SPKR_PIN);
         nextNote();
         nextState = PLAY_NOTE;
      } // if noteDuration * 1.3
    }// if - else if (state)
  } // if - else silence
  return nextState;
} // playMelody

 /*
  * Set all the timestamp variables to the current time
  */
 void resetButtons() {
   tick = millis();
   // reset button pressed time stamps for debouncing
   musicButton = tick;
   playButton  = tick;
   // reset button flags
   musicButtonUp = false;
   pushCoins     = false;
 } // resetButtons
 
 /* 
  * Set the current tune to play based on presses of Music button.
  * Every other press mutes the music.
  */
void setTune() {
  
   if (tilted) {
     // if we are tilted always play the tilt theme
     tune = TILT_THEME;
   } else if ( melodyCount % 2 == 1) {
     // every odd button press mutes the music
     tune = SILENCE;
   } else {
     // otherwise the tune is half of the number of button presses
     tune = melodyCount / 2;
   }
 } // setTune
 
 /*
  * Get the size of the current melody
  */
 int tuneSize(int melody) {
   int size = 0;
   
   if (tilted) {
     // if we are tilted always play the tilt theme
     size = (sizeof(tiltTune) / 2);
   } else if (melody == GOLD_DIGGERS) {
     size = sizeof(goldDiggersTune) / 2;
   } else if (melody == PENNIES_FROM_HEAVEN) {
     size = sizeof(penniesFromHeavenTune) / 2;
   } else if (melody == HOT_CROSS_BUNS) {
     size = sizeof(hotCrossBunsTune) / 2;
   } else if (melody == POP_GOES_THE_WEASEL) {
     size = sizeof(popGoesTheWeaselTune) / 2;
   } else if (melody == PINK_FLOYD_MONEY) {
     size = sizeof(moneyTune) / 2;
   }else {
     // otherwise silence
     size = 0;
   }
 return size;
 }

 
 /*
  * Change the current note to play the next note in the melody
  */
 void nextNote() {
   tick = millis();
   noteStamp = tick;
   currentNote++;
   if (currentNote >= tuneSize(tune)) {
       currentNote = 0;
   } // if currentNote >= size of tune 
 } // nextNote
 
/*
 * Get duration for the current musical note
 *
 * returns unsigned int duration of current note
 */
unsigned int getNoteDuration() {
  unsigned int duration = 0;
  
  if (tilted) {
     // if we are tilted always play the tilt theme
    duration = 1000 / pgm_read_byte_near(tiltTempo + currentNote);
  } else if (tune == GOLD_DIGGERS) {
    duration = 1000 / pgm_read_byte_near(goldDiggersTempo + currentNote);
  } else if (tune == PENNIES_FROM_HEAVEN) {
    duration = 1000 / pgm_read_byte_near(penniesFromHeavenTempo + currentNote);
  } else if (tune == HOT_CROSS_BUNS) {
    duration = 1000 / pgm_read_byte_near(hotCrossBunsTempo + currentNote);
  } else if (tune == POP_GOES_THE_WEASEL) {
    duration = 1000 / pgm_read_byte_near(popGoesTheWeaselTempo + currentNote);
  } else if (tune == PINK_FLOYD_MONEY) {
    duration = 1000 / pgm_read_byte_near(moneyTempo + currentNote);
  } // if - else if titled
    
  return duration;
}

/*
 * Get the frequency of the current musical note
 *
 * returns unsigned int frequency of note
 */
unsigned int getNoteFrequency() {
  unsigned int frequency = 0;
  
  if (tilted) {
    // if we are tilted always play the tilt theme
    frequency = pgm_read_word_near(tiltTune + currentNote);
  } else if (tune == GOLD_DIGGERS) {
    frequency = pgm_read_word_near(goldDiggersTune + currentNote);
  } else if (tune == PENNIES_FROM_HEAVEN) {
    frequency = pgm_read_word_near(penniesFromHeavenTune + currentNote);
  } else if (tune == HOT_CROSS_BUNS) {
    frequency = pgm_read_word_near(hotCrossBunsTune + currentNote);
  } else if (tune == POP_GOES_THE_WEASEL) {
    frequency = pgm_read_word_near(popGoesTheWeaselTune + currentNote);
  } else if (tune == PINK_FLOYD_MONEY) {
    frequency = pgm_read_word_near(moneyTune + currentNote);
  } // if - else if tilted
  return frequency;
}

/*
 * Ignore a push button for a brief time after it was pressed.
 * This allows the contacts to settle and prevents false reads.
 *
 * Returns boolean - true when okay to read button again.
 */
boolean debounce(unsigned long buttonEvent) {
  tick = millis();
  return (tick - buttonEvent) > DEBOUNCE_TIME;
}

/*
 * Check to see of the music button has been pushed and released,
 * and change the tune accordingly.  This doesn't allow the button
 * to be held continuously.
 */
void handleMusicButton() {
  if (debounce(musicButton)) {
      if(musicButtonUp && (digitalRead(MUSIC_PIN) == LOW) ) {
        musicButtonUp = false;
        tick = millis();
        musicButton = tick;
        melodyCount++;
        melodyCount = melodyCount % MAX_PRESSES;
        setMelody(); 
        // else wait until button released
       } else if (digitalRead(MUSIC_PIN) == HIGH){
         musicButtonUp = true;
       } // if - else if digitalRead(MUSIC_PIN)
     } // if debounce(musicButton)
} // handleMusicButton

/*
 * Check the clear button. This is a one shot button press, so there's
 * no debouncing and no checking to see if the button is being held.
 *
 */
void handleClearButton() { 
  if (digitalRead(CLEAR_PIN) == LOW) {
     clearTilt();
     } // digitalRead(CLEAR_PIN)
} // handleClearButton

/* 
 * Check the play button.  If this button is held, the play time is 
 * extended until after the button is released.  So the button is
 * debounced but there is no verification the button is released.
 *
 */
void handlePlayButton() {
  if (debounce(playButton)) {
      if(digitalRead(PLAY_PIN) == LOW) {
        tick = millis();
        playButton = tick;
        pushCoins = true;
      } // if digitalRead(PLAY_PIN)
  } // debounce(playButton)
} // handlePlayButton 

/*
 * Move or stop the servo and show status on LED
 */
void handleServo() {
  if(pushCoins) {
    if(timeSinceEvent(playButton) < SERVO_PUSH) {
      coinPusher.write(SERVO_GO);
      digitalWrite(LED_PIN, HIGH);
    } else {
      pushCoins = false;
      coinPusher.write(SERVO_STOP);
      digitalWrite(LED_PIN, LOW);
    } // if - else timeSinceEvent(playButton)
  } else {
      coinPusher.write(SERVO_STOP);
      digitalWrite(LED_PIN, LOW);
  } // if - else pushCoins
} // handleServo

/*
 * Flash the Tilt LED on and off
 */
void blinkTilt() {
  int blinkTime = timeSinceEvent(tiltStamp) % 1000;
  
  if (blinkTime < 500) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}

