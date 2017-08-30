# `hack-art` Interactive Art Wall

An interactive wall that requires 2 Arduino UNOs to control the logic.

![Screenshot](preview.jpg?raw=true "Hack Art Sign")
### Master Arduino logic
 * Controls the skyline and landmark LEDs
 * Outputs a signal to control Lyft sign via relay switch (on/off)
 * Outputs a signal to control car lights (via another Arduino)
### Secondary Arduino logic
(This Arduino is used because we ran out of PWM pins on the first Arduino)
 * Receives signal from Master to turn car lights on or off
### Behavior:
 * any 1 button pressed: Lyft logo lights up
 * any 2 buttons pressed: Lyft logo, cars
 * any 3 buttons pressed: Lyft logo, cars, skyline
 * all 4 buttons pressed: Lyft logo, cars, skyline cycles through rainbow color, and foreground landmarks light up
