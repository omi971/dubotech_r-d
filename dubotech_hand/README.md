### Description



## The system has two function
* Manual Joystick Control
* inverse kinematics control
  * it has 10 steps (0 to 1)
  * currently working code (top to bottom)
  * we have to make the servo work now

### For python side 
python version using: python 3.10

## Install dependencies
install pygame and serial
```bash
pip install pygame
pip install serial
# or serial or pyserial confused?? ask
pip install pyserial
```
### Python Code Functionality
* ink.py (This File controls the code with joystick single tap)
* here we are using buttons
  * button_x = 2  # X button (Gripper )
  * button_y = 3  # B button (Gripper )
  * button_b = 1  # A button (Up Jabe)
  * button_a = 0  # A button (Down Jabe)
  * left = 4 # LB Button (Left Turn)
  * right = 5 # RB Button (Right Turn)
  * l_stick_in = 6 # Start Button CW
  * r_stick_in = 7 # Back Button CCW



### For Arduino Side
* install adafruit library from arduino ide 'manage library menu'