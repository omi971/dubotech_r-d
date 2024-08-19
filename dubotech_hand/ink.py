'''
To control the arm with
Joystick Button
Single Press
'''
import pygame
import serial
import time


# Update Variables before work
com_port = "COM3"
baud_rate = 9600

# Initialize the joystick and serial port
pygame.init()
pygame.joystick.init()

joystick = pygame.joystick.Joystick(0)
joystick.init()

# Setup the serial connection (replace 'COM4' with the appropriate port for your Arduino)
ser = serial.Serial(com_port, baud_rate)
time.sleep(2)  # Allow time for the serial connection to establish

# Initialize the value to be sent to the Arduino
current_value = 1

# Define the button mappings
button_x = 2  # X button (Gripper )
button_y = 3  # B button (Gripper )

button_b = 1  # A button (Up Jabe)
button_a = 0  # A button (Down Jabe)

left = 4 # LB Button (Left Turn)
right = 5 # RB Button (Right Turn)

l_stick_in = 6 # Start Button CW
r_stick_in = 7 # Back Button CCW

# Function to send the current value to the Arduino
def send_value(value):
    ser.reset_input_buffer()  # Termianl stuck er solve
    ser.write(f"{value}\n".encode())
    print(f"Sent value: {value}")
    ser.flush()  # Ensure all data is sent before proceeding

# Main loop
running = True
while running:
    pygame.event.pump()  # Process event queue

    # Check if the Y button is pressed
    # ------------------ Up Jabe ----------------
    if joystick.get_button(button_y):
        if current_value < 10:
            current_value += 1
            send_value(current_value)
            time.sleep(0.1)  # Add a small delay to avoid sending values too quickly
            print("------------------ Up Jabe ----------------")
    
    # ------------------ Down Jabe ----------------
    elif joystick.get_button(button_a):
        if current_value > 1:
            current_value -= 1
            send_value(current_value)
            time.sleep(0.1)  # Add a small delay to avoid sending values too quickly
            print("------------------ Down Jabe ----------------")

    # Check if the X button is pressed
    # Gripper 
    elif joystick.get_button(button_x):
        send_value(13)
        time.sleep(0.1)  # Add a small delay to avoid sending values too quickly
        print("------------------ Gripper Open ----------------")

    
    # Check if the A button is pressed
    # Gripper 
    elif joystick.get_button(button_b):
        send_value(12)
        time.sleep(0.1)  # Add a small delay to avoid sending values too quickly
        print("------------------ Gripper Close ----------------")

    # Check if the LB button is pressed
    # Left Movement
    elif joystick.get_button(left):
        send_value(15)
        time.sleep(0.1)  # Add a small delay to avoid sending values too quickly
        print("------------------ Left Jabe ----------------")

    
    # Check if the RB button is pressed
    # Left Movement
    elif joystick.get_button(right):
        send_value(16)
        time.sleep(0.1)  # Add a small delay to avoid sending values too quickly
        print("------------------ Right Jabe ----------------")

    
    # Gripper Twist (CW)
    # Start Button
    elif joystick.get_button(l_stick_in):
        send_value(17)
        time.sleep(0.1)  # Add a small delay to avoid sending values too quickly
        print("------------------ Gripper Twist (CW) ----------------")

    
    # Gripper Twist (CCW)
    # Back Button
    elif joystick.get_button(r_stick_in):
        send_value(18)
        time.sleep(0.1)  # Add a small delay to avoid sending values too quickly
        print("------------------ Gripper Twist (CCW) ----------------")

    # Check if the joystick is disconnected or exit button pressed
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

# Cleanup
pygame.quit()
ser.close()
