# python 3.9

import pygame
import serial
import time

# Initialize Pygame and the joystick
pygame.init()
pygame.joystick.init()

# Setup the serial connection to Arduino
# Make sure to replace 'COM3' with your Arduino's serial port and set the correct baud rate.
arduino = serial.Serial('COM3', 9600, timeout=1)
time.sleep(2)  # Give some time to establish the connection

# Define the control mappings
controls = {
    'base': {'positive': 'A', 'negative': 'D'},
    'elbow': {'positive': 'W', 'negative': 'S'},
    'upper_elbow': {'positive': 'K', 'negative': 'I'},
    'hand': {'positive': 'O', 'negative': 'U'}
}

# Function to send serial command
def send_command(command):
    arduino.write(command.encode())
    print(f'Sent command: {command}')
    while arduino.in_waiting == 0:
        pass
    response = arduino.readline().decode().strip()
    print(f'Arduino response: {response}')

# Main loop
try:
    joystick = pygame.joystick.Joystick(0)
    joystick.init()
    print(f'Joystick {joystick.get_name()} initialized')

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    running = False

        # Get axis values (assuming the joystick has 4 axes)
        base_movement = joystick.get_axis(0)  # Typically left stick horizontal
        elbow_movement = joystick.get_axis(1) # Typically left stick vertical
        upper_elbow_movement = joystick.get_axis(3) # Typically right stick vertical
        hand_movement = joystick.get_axis(2)  # Typically right stick horizontal

        # Check and send commands based on joystick movement
        if base_movement > 0.5:
            arduino.reset_input_buffer()
            send_command(controls['base']['positive'])
        elif base_movement < -0.5:
            arduino.reset_input_buffer()
            send_command(controls['base']['negative'])

        if elbow_movement > 0.5:
            arduino.reset_input_buffer()
            send_command(controls['elbow']['positive'])
        elif elbow_movement < -0.5:
            arduino.reset_input_buffer()
            send_command(controls['elbow']['negative'])

        if upper_elbow_movement > 0.5:
            arduino.reset_input_buffer()
            send_command(controls['upper_elbow']['positive'])
        elif upper_elbow_movement < -0.5:
            send_command(controls['upper_elbow']['negative'])

        if hand_movement > 0.5:
            arduino.reset_input_buffer()
            send_command(controls['hand']['positive'])
        elif hand_movement < -0.5:
            arduino.reset_input_buffer()
            send_command(controls['hand']['negative'])

        time.sleep(0.1)  # Small delay to control the frequency of commands

except KeyboardInterrupt:
    print("Program terminated by KeyboardInterrupt")

finally:
    arduino.close()
    pygame.quit()
    print("Program terminated")
