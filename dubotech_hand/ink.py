import pygame
import serial
import time


# Update Variables before work
com_port = "COM4"
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
button_y = 3  # Y button
button_a = 0  # A button
button_x = 2  # X button
button_b = 1  # B button

# Function to send the current value to the Arduino
def send_value(value):
    ser.write(f"{value}\n".encode())
    print(f"Sent value: {value}")
    ser.flush()  # Ensure all data is sent before proceeding

# Main loop
running = True
while running:
    pygame.event.pump()  # Process event queue

    # Check if the Y button is pressed
    if joystick.get_button(button_y):
        if current_value < 10:
            current_value += 1
            send_value(current_value)
            time.sleep(0.1)  # Add a small delay to avoid sending values too quickly

    # Check if the A button is pressed
    elif joystick.get_button(button_a):
        if current_value > 1:
            current_value -= 1
            send_value(current_value)
            time.sleep(0.1)  # Add a small delay to avoid sending values too quickly

    # Check if the X button is pressed
    elif joystick.get_button(button_x):
        send_value(13)
        time.sleep(0.1)  # Add a small delay to avoid sending values too quickly

    # Check if the B button is pressed
    elif joystick.get_button(button_b):
        send_value(12)
        time.sleep(0.1)  # Add a small delay to avoid sending values too quickly

    # Check if the joystick is disconnected or exit button pressed
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

# Cleanup
pygame.quit()
ser.close()
