# Servo Door Lock System

This project is a simple door lock system controlled by a servo motor, a keypad, and an LCD display. The system allows users to enter a password to unlock the door. If the entered password is correct, the servo motor rotates to open the door. If the password is incorrect, an error message is displayed, and the user is prompted to try again.

## Components Used
- Arduino Board
- 4x4 Keypad
- 16x2 LCD Display (with Adafruit LiquidCrystal library)
- Servo Motor
- Wires and Breadboard

## Libraries Required
- [Adafruit LiquidCrystal](https://github.com/adafruit/LiquidCrystal)
- [Servo](https://www.arduino.cc/en/Reference/Servo)
- [Keypad](https://playground.arduino.cc/Code/Keypad/)

## Wiring Diagram
Here is a basic outline of the wiring connections:
- **Keypad**: Connect the row and column pins of the keypad to digital pins 0-7 on the Arduino.
- **LCD Display**: Connect the LCD display using the appropriate pins defined in the `Adafruit_LiquidCrystal` library.
- **Servo Motor**: Connect the control pin of the servo motor to digital pin 12 on the Arduino.

## Code Explanation
The code for this project is written in C++ and runs on an Arduino. Below is a brief explanation of the key parts of the code:

- **Setup Function**: Initializes the servo, LCD, and displays the initial message to enter the password.
- **Loop Function**: Continuously checks for key presses and processes them based on whether the door is currently locked or unlocked.
- **zatvorene Function**: Handles input when the door is locked. It checks if the entered key is part of the password and processes the unlocking if the password is correct.
- **otvorene Function**: Handles input when the door is unlocked. It checks for the 'C' key to re-lock the door.
- **hesloJeSpravne Function**: Compares the entered password with the predefined correct password.
- **otvorDvere Function**: Unlocks the door, updates the servo position, and displays the unlocked message.
- **zatvorDvere Function**: Locks the door, resets the entered password, and updates the servo position.
- **zleHeslo Function**: Displays an error message for an incorrect password and prompts the user to try again.
- **resetHesla Function**: Resets the entered password buffer.

## Usage
1. Connect all components according to the wiring diagram.
2. Upload the provided code to your Arduino board.
3. Open the serial monitor to observe the process and interact with the system.
4. Enter the password using the keypad. The default password is `0000`.
5. Press 'D' to submit the password.
6. If the password is correct, the door will unlock. Press 'C' to lock the door again.

## Customization
- **Changing the Password**: Modify the `aktualneHeslo` array in the code to set a new password.
- **Adjusting Servo Positions**: Change the angles in `servo.write(0)` and `servo.write(90)` to adjust the locked and unlocked positions of the servo.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgements
- Adafruit Industries for the LiquidCrystal library.
- Arduino Community for the Keypad and Servo libraries.

## Contributions
Contributions, issues, and feature requests are welcome! Feel free to check the [issues page](https://github.com/yourusername/servo-door-lock-system/issues).

---

Feel free to customize this README file as per your project's specifics and needs.
