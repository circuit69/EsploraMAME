/* Modified to work with the standard MAME emulator
    by Joel Krueger 12-9-2013
*/

#include <Esplora.h>
boolean buttonStates[8];

/*
  This array holds the names of the buttons being read.
  Later in the sketch, you'll use these names with
  the method Esplora.readButton(x), where x
  is one of these buttons.
 */
const byte buttons[] = {
  JOYSTICK_DOWN,
  JOYSTICK_LEFT,
  JOYSTICK_UP,
  JOYSTICK_RIGHT,
  SWITCH_RIGHT, // fire
  SWITCH_LEFT, // bend
  SWITCH_UP, // nitro
  SWITCH_DOWN, // look back
};

/*
  This array tells what keystroke to send to the PC when a
  button is pressed.
  If you look at this array and the above one, you can see that
  the "cursor down" keystroke is sent when the joystick is moved
  down, the "cursor up" keystroke when the joystick is moved up
  and so on.
*/
const char keystrokes[] = {
  KEY_DOWN_ARROW,
  KEY_LEFT_ARROW,
  KEY_UP_ARROW,
  KEY_RIGHT_ARROW,
  KEY_LEFT_CTRL,
  KEY_LEFT_ALT,
  ' ',
  KEY_LEFT_SHIFT
};

/*
  This is code is run only at startup, to initialize the
  virtual USB keyboard.
*/
void setup() {
  Keyboard.begin();
}

/*
  After setup() is finished, this code is run continuously.
  Here we continuously check if something happened with the
  buttons.
*/
void loop() { 
  
  // Iterate through all the buttons:
  for (byte thisButton=0; thisButton<8; thisButton++) {
    boolean lastState = buttonStates[thisButton];
    boolean newState = Esplora.readButton(buttons[thisButton]);
    if (lastState != newState) { // Something changed!
      /* 
        The Keyboard library allows you to "press" and "release" the
        keys as two distinct actions. These actions can be
        linked to the buttons we're handling.
       */
      if (newState == PRESSED) {
        Keyboard.press(keystrokes[thisButton]);
      }
      else if (newState == RELEASED) {
        Keyboard.release(keystrokes[thisButton]);
      }
    }

    // Store the new button state, so you can sense a difference later:
    buttonStates[thisButton] = newState;
  }
  
  /*
    Wait a little bit (50ms) between a check and another.
    When a mechanical switch is pressed or released, the
    contacts may bounce very rapidly. If the check is done too
    fast, these bounces may be confused as multiple presses and
    may lead to unexpected behaviour.
   */
  delay(50);
}

