import pygame

# Initialize Pygame and joystick
pygame.init()
pygame.joystick.init()

# Detect if joystick is connected
if pygame.joystick.get_count() == 0:
    print("No joystick detected!")
else:
    # Initialize the joystick
    joystick = pygame.joystick.Joystick(0)
    joystick.init()
    print(f"Joystick Name: {joystick.get_name()}")

    # Infinite loop to print button status
    try:
        while True:
            # Process Pygame events
            for event in pygame.event.get():
                if event.type == pygame.JOYBUTTONDOWN or event.type == pygame.JOYBUTTONUP:
                    # Loop through all buttons and print their status
                    for i in range(joystick.get_numbuttons()):
                        button = joystick.get_button(i)
                        print(f"Button {i}: {'Pressed' if button else 'Released'}")
            print("\n" * 5)
    except KeyboardInterrupt:
        print("Joystick monitoring stopped.")
        pygame.quit()
