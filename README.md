# `hack-art` Interactive Art Wall

An interactive wall that requires 2 Arduino UNOs to control the logic.
### Master Arduino logic
 * Controls the skyline and landmark LEDs
 * Outputs a signal to control Lyft sign via relay switch (on/off)
 * Outputs a signal to control car lights (via another Arduino)
### Behavior:
 * any 1 button pressed: Lyft logo lights up
 * any 2 buttons pressed: Lyft logo, cars
 * any 3 buttons pressed: Lyft logo, cars, skyline
 * all 4 buttons pressed: Lyft logo, cars, skyline cycles through rainbow color, and foreground landmarks light up
