# Smart-Home
A smart home using two microcontrollers (atmega32)

The first atmega32 is responsible for taking the inputs from the user (Keypad) and show the results in the LCD
there are two modes at the smart home:
- Admin Mode: makes the the user able to
1.  Switch on and OFF LEDs at three rooms (ROOM_1, ROOM_2, and ROOM_3) -> (three green leds).
2.  Control two fans whether to turn them ON or OFF (FAN_1 & FAN_2) -> (two DC motors controlled by motor driver L293D).
3.  Check the state of the Garage (UltraSonic to check the distance).
4.  Change the Password of Admin mode or Guest mode.
- Guest mode : the user is only able to switch ON or OFF the LEDs
note: if the program is powered for the first time, the user will be asked to Set the Password for both Admin and Guest mode. 
