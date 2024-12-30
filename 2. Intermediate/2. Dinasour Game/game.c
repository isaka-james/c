#include <stdio.h>
#include <unistd.h>  // For usleep()
#include <termios.h> // For capturing key presses without Enter
#include <fcntl.h>   // For non-blocking I/O

#define WIDTH 20
#define HEIGHT 20
#define GROUND (HEIGHT - 1)
#define DINO_CHAR '~'     // Dinosaur represented
#define OBSTACLE_CHAR '#' // Obstacle represented

// Flow per second (FPS)
#define FPS 60  // x FPS means updating the screen every 100 ms

// Obstacle speed (number of positions moved per second)
#define OBSTACLE_SPEED 3 // The obstacle moves x position per second

// Function to initialize the game board (static view, no movement)
void initialize_board(char board[HEIGHT][WIDTH]) {
    // Clear the board and set the ground
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == GROUND) {
                board[i][j] = '-';  // Ground
            } else {
                board[i][j] = ' ';  // Empty space
            }
        }
    }

    // Place the dinosaur on the left
    board[GROUND - 1][2] = DINO_CHAR;  // Dinosaur at position (2, HEIGHT-1)
}

// Function to print the game board with the ground at the bottom
void print_board(char board[HEIGHT][WIDTH], int score, int jump_count) {
    // Print the board excluding the ground, since it's static
    for (int i = 0; i < HEIGHT - 1; i++) {  // Exclude the last row (ground)
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }

    // Print the ground (always at the bottom)
    for (int j = 0; j < WIDTH; j++) {
        printf("-");
    }

    // Print static score at the bottom
    printf("\nScore: %d\n", score);

    // Print jump count at the bottom
    printf("Jumps: %d\n", jump_count);
}

// Function to capture keypress without requiring Enter (Up Arrow detection)
int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);  // Disable buffering and echoing
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();  // Get the keypress (non-blocking)
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  // Restore terminal settings
    fcntl(STDIN_FILENO, F_SETFL, oldf);  // Restore file descriptor flags

    if(ch != EOF) {  // If a key was pressed
        return ch;
    }

    return -1;  // No key pressed
}

// Main function
int main() {
    char board[HEIGHT][WIDTH];
    int jump_count = 0;  // Jump count (number of times up key is pressed)
    int obstacle_position = WIDTH - 2;  // Start obstacle near the right side
    int counter = 0;
    int score = 0;

    // Initialize the static board with dinosaur
    initialize_board(board);

    // Loop to simulate obstacle moving right to left
    int obstacle_move_counter = 0;  // Counter to track obstacle movement at a fixed speed
    while (1) {  // Infinite loop for continuous update
        // Check for keypresses (for jumps) without blocking the game loop
        int ch = kbhit();
        if (ch == 65) {  // Up arrow key in ANSI escape codes (65 is the up arrow key code)
            jump_count++;  // Increment jump count when up arrow is pressed
        }

        // Move the obstacle based on the speed and time (independent of FPS)
        obstacle_move_counter++;
        if (obstacle_move_counter >= FPS / OBSTACLE_SPEED) {  // Check if it's time to move the obstacle
            board[GROUND - 1][obstacle_position] = ' '; // Clear previous obstacle position
            obstacle_position--;  // Move the obstacle to the left
            if (obstacle_position < 0) { // If the obstacle reaches the left edge
                obstacle_position = WIDTH - 2; // Reset
		score+=100;
            }
            board[GROUND - 1][obstacle_position] = OBSTACLE_CHAR; // Place the new obstacle
            obstacle_move_counter = 0;  // Reset the counter after moving the obstacle
        }

        // Redraw the game board
        print_board(board,score, jump_count);

        // Control the FPS
        usleep(1000000 / FPS);  // Delay in microseconds (1 second / FPS)
        
        // Clear the screen without clearing the entire terminal window
        printf("\033[H\033[J"); // ANSI escape code to clear the screen
    }

    return 0;
}

