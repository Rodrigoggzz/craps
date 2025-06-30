#include <iostream>
#include <random>
#include <limits>


int rollDie() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 6);
    return dist(gen);
}


int rollDice() {
    int die1 = rollDie();
    int die2 = rollDie();
    std::cout << "Rolled: " << die1 << " + " << die2 << " = " << (die1 + die2) << "\n";
    return die1 + die2;
}


int getValidatedBet(int maxBet) {
    int bet;
    while (true) {
        std::cout << "Enter your bet (You have $" << maxBet << "): $";
        std::cin >> bet;

        if (std::cin.fail() || bet <= 0 || bet > maxBet) {
            std::cin.clear(); // clear error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid bet. Please enter a value between $1 and $" << maxBet << ".\n";
        }
        else {
            return bet;
        }
    }
}

int main() {
    int balance = 50;
    char playAgain;

    std::cout << "Welcome to Craps! You start with $50.\n";

    do {
        if (balance <= 0) {
            std::cout << "You're out of money! Game over.\n";
            break;
        }

        int bet = getValidatedBet(balance);

        std::cout << "Rolling dice...\n";
        int sum = rollDice();

        if (sum == 7 || sum == 11) {
            std::cout << "You win!\n";
            balance += bet;
        }
        else if (sum == 2 || sum == 3 || sum == 12) {
            std::cout << "Craps! You lose.\n";
            balance -= bet;
        }
        else {
            int point = sum;
            std::cout << "Point is set to: " << point << "\n";

            bool rolling = true;
            while (rolling) {
                std::cout << "Rolling again...\n";
                sum = rollDice();

                if (sum == point) {
                    std::cout << "You hit the point! You win!\n";
                    balance += bet;
                    rolling = false;
                }
                else if (sum == 7) {
                    std::cout << "You rolled a 7. You lose.\n";
                    balance -= bet;
                    rolling = false;
                }
            }
        }

        std::cout << "Your current balance: $" << balance << "\n";

        if (balance > 0) {
            std::cout << "Do you want to play again? (Y/N): ";
            std::cin >> playAgain;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            break;
        }

    } while (playAgain == 'Y' || playAgain == 'y');

    std::cout << "Thanks for playing! Your final worth: $" << balance << "\n";
    return 0;
}
