#animation of Cigarrete Smokers Problem
import pygame
import random
import time

def main():
    

    # Initialize Pygame
    pygame.init()

    # Set up the display
    width, height = 800, 600
    screen = pygame.display.set_mode((width, height))
    pygame.display.set_caption("Cigarette Smokers Problem Animation")

    # Define colors
    WHITE = (255, 255, 255)
    BLACK = (0, 0, 0)
    RED = (255, 0, 0)
    GREEN = (0, 255, 0)
    BLUE = (0, 0, 255)

    # Define positions for the smokers and the table
    smoker_positions = [(100, 300), (350, 300), (600, 300)]
    table_position = (400, 200)

    # Load images for smokers and items
    smoker_image = pygame.Surface((50, 50))
    smoker_image.fill(BLUE)
    
    item_images = {
        "tobacco": pygame.Surface((30, 30)),
        "paper": pygame.Surface((30, 30)),
        "matches": pygame.Surface((30, 30))
    }
    
    item_images["tobacco"].fill(RED)
    item_images["paper"].fill(GREEN)
    item_images["matches"].fill(BLACK)

    # Function to draw the scene
    def draw_scene(items_on_table):
        screen.fill(WHITE)
        
        # Draw smokers
        for pos in smoker_positions:
            screen.blit(smoker_image, pos)
        
        # Draw items on the table
        for i, item in enumerate(items_on_table):
            if item:
                screen.blit(item_images[item], (table_position[0] + i * 40 - 20, table_position[1]))

        pygame.display.flip()

    # Main loop
    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        # Randomly select two items to place on the table
        items = ["tobacco", "paper", "matches"]
        selected_items = random.sample(items, 2)

        draw_scene(selected_items)

        time.sleep(2)  # Wait for a while before next iteration


if __name__ == "__main__":
    main()