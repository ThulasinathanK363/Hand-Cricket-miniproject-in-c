#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function prototypes
int playerBatting(int target);
int computerBatting(int target);
void singlePlayerMode();
void multiplayerMode();
void tournamentMode();

int toss();

int main() {
    int choice;

    printf("Welcome to Hand Cricket!\n");

    srand(time(0)); // Seed for random number generation

    do {
        printf("\nChoose a mode:\n");
        printf("1. Single Player\n2. Multiplayer\n3. Tournament\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: singlePlayerMode(); break;
            case 2: multiplayerMode(); break;
            case 3: tournamentMode(); break;
            case 4: printf("Exiting game. Goodbye!\n"); break;
            default: printf("Invalid choice! Please try again.\n");
        }

        if (choice != 4) {
            char playAgain;
            printf("\nDo you want to play again? (y/n): ");
            getchar(); // Consume newline character
            scanf("%c", &playAgain);

            if (playAgain == 'n' || playAgain == 'N') {
                printf("Thank you for playing! Goodbye!\n");
                break;
            }
        }
    } while (choice != 4);

    return 0;
}

// Toss function
int toss() {
    int playerChoice, playerNum, computerNum, sum;

    printf("\nToss Time! Choose:\n1. Odd\n2. Even\nEnter your choice: ");
    scanf("%d", &playerChoice);

    printf("Enter your number (1-6): ");
    scanf("%d", &playerNum);

    computerNum = (rand() % 6) + 1; // Random number for computer
    printf("Computer chose: %d\n", computerNum);

    sum = playerNum + computerNum;

    if ((sum % 2 == 0 && playerChoice == 2) || (sum % 2 == 1 && playerChoice == 1)) {
        printf("You won the toss!\n");
        return 1; // Player wins toss
    } else {
        printf("Computer won the toss!\n");
        return 0; // Computer wins toss
    }
}

// Single-player mode
void singlePlayerMode() {
    int playerScore, computerScore;

    printf("\nSingle Player Mode\n");

    int tossResult = toss();
    if (tossResult == 1) { // Player wins toss
        int choice;
        printf("\nWhat do you want to do?\n1. Bat First\n2. Bowl First\nEnter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("\nYou chose to bat first!\n");
            playerScore = playerBatting(-1);
            printf("Your Total Score: %d\n", playerScore);

            printf("\nComputer's turn to chase!\n");
            computerScore = computerBatting(playerScore);
            printf("Computer's Total Score: %d\n", computerScore);
        } else if (choice == 2) {
            printf("\nYou chose to bowl first!\n");
            computerScore = computerBatting(-1);
            printf("Computer's Total Score: %d\n", computerScore);

            printf("\nYour turn to chase!\n");
            playerScore = playerBatting(computerScore);
            printf("Your Total Score: %d\n", playerScore);
        } else {
            printf("Invalid choice. Returning to main menu.\n");
            return;
        }
    } else { // Computer wins toss
        int choice = (rand() % 2) + 1; // Computer decides randomly
        if (choice == 1) {
            printf("\nComputer chose to bat first!\n");
            computerScore = computerBatting(-1);
            printf("Computer's Total Score: %d\n", computerScore);

            printf("\nYour turn to chase!\n");
            playerScore = playerBatting(computerScore);
            printf("Your Total Score: %d\n", playerScore);
        } else {
            printf("\nComputer chose to bowl first!\n");
            playerScore = playerBatting(-1);
            printf("Your Total Score: %d\n", playerScore);

            printf("\nComputer's turn to chase!\n");
            computerScore = computerBatting(playerScore);
            printf("Computer's Total Score: %d\n", computerScore);
        }
    }

    // Determine the winner
    if (playerScore > computerScore) {
        printf("\nYou Win!\n");
    } else if (playerScore < computerScore) {
        printf("\nComputer Wins!\n");
    } else {
        printf("\nIt's a Tie!\n");
    }
}

// Multiplayer mode
void multiplayerMode() {
    int player1Score, player2Score;

    printf("\nMultiplayer Mode\n");
    printf("Player 1's turn to bat:\n");
    player1Score = playerBatting(-1);
    printf("Player 1's Total Score: %d\n", player1Score);

    printf("\nPlayer 2's turn to chase:\n");
    player2Score = playerBatting(player1Score);
    printf("Player 2's Total Score: %d\n", player2Score);

    // Determine the winner
    if (player1Score > player2Score) {
        printf("\nPlayer 1 Wins!\n");
    } else if (player1Score < player2Score) {
        printf("\nPlayer 2 Wins!\n");
    } else {
        printf("\nIt's a Tie!\n");
    }
}

// Tournament mode
void tournamentMode() {
    int rounds, player1Wins = 0, player2Wins = 0;

    printf("\nTournament Mode\n");
    printf("Enter number of matches: ");
    scanf("%d", &rounds);

    for (int i = 1; i <= rounds; i++) {
        printf("\nMatch %d\n", i);

        int player1Score, player2Score;

        printf("Player 1's turn to bat:\n");
        player1Score = playerBatting(-1);
        printf("Player 1's Total Score: %d\n", player1Score);

        printf("\nPlayer 2's turn to chase:\n");
        player2Score = playerBatting(player1Score);
        printf("Player 2's Total Score: %d\n", player2Score);

        // Determine match winner
        if (player1Score > player2Score) {
            printf("\nPlayer 1 Wins Match %d!\n", i);
            player1Wins++;
        } else if (player1Score < player2Score) {
            printf("\nPlayer 2 Wins Match %d!\n", i);
            player2Wins++;
        } else {
            printf("\nMatch %d is a Tie!\n", i);
        }
    }

    // Determine tournament winner
    printf("\nTournament Results:\n");
    printf("Player 1 Wins: %d\n", player1Wins);
    printf("Player 2 Wins: %d\n", player2Wins);

    if (player1Wins > player2Wins) {
        printf("\nPlayer 1 is the Tournament Champion!\n");
    } else if (player1Wins < player2Wins) {
        printf("\nPlayer 2 is the Tournament Champion!\n");
    } else {
        printf("\nThe Tournament is a Tie!\n");
    }
}

// Player batting function
int playerBatting(int target) {
    int score = 0, playerRun, computerRun;

    while (1) {
        printf("Enter your run (1-6): ");
        scanf("%d", &playerRun);

        if (playerRun < 1 || playerRun > 6) {
            printf("Invalid input! Please enter a number between 1 and 6.\n");
            continue;
        }

        computerRun = (rand() % 6) + 1; // Random number between 1 and 6
        printf("Computer played: %d\n", computerRun);

        if (playerRun == computerRun) {
            printf("Out! Total Score: %d\n", score);
            break;
        } else {
            score += playerRun;
            printf("Current Score: %d\n", score);
            if (target != -1 && score > target) {
                printf("You Win! Total Score: %d\n", score);
                break;
            }
        }
    }

    return score;
}

// Computer batting function
int computerBatting(int target) {
    int score = 0, playerRun, computerRun;

    while (1) {
        printf("Enter your run to bowl (1-6): ");
        scanf("%d", &playerRun);

        if (playerRun < 1 || playerRun > 6) {
            printf("Invalid input! Please enter a number between 1 and 6.\n");
            continue;
        }

        computerRun = (rand() % 6) + 1; // Random number between 1 and 6
        printf("Computer played: %d\n", computerRun);

        if (playerRun == computerRun) {
            printf("Out! Computer's Total Score: %d\n", score);
            break;
        } else {
            score += computerRun;
            printf("Computer's Current Score: %d\n", score);
            if (target != -1 && score > target) {
                printf("Computer Wins! Total Score: %d\n", score);
                break;
            }
        }
    }

    return score;
}
