#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

// display the current game state
void displayGameState(const std::string& guessedWord, int attemptsLeft, const std::vector<char>& wrongGuesses) {
    std::cout << "\nWord: " << guessedWord;
    std::cout << "\nAttempts left: " << attemptsLeft;
    std::cout << "\nWrong guesses: ";
    for (char ch : wrongGuesses) {
        std::cout << ch << ' ';
    }
    std::cout << std::endl;
}

//check if the player has won
bool isGameWon(const std::string& guessedWord, const std::string& secretWord) {
    return guessedWord == secretWord;
}

// check if the game is over
bool isGameOver(int attemptsLeft) {
    return attemptsLeft <= 0;
}

int main() {
    // List of possible words
    std::vector<std::string> words = {"computer", "programming", "hangman", "code", "algorithm"};

    // Seed for random number generator
    std::srand(static_cast<unsigned int>(std::time(0)));

    // Select a random word
    std::string secretWord = words[std::rand() % words.size()];
    std::string guessedWord(secretWord.size(), '_');
    int attemptsLeft = 6;
    std::vector<char> wrongGuesses;

    // loop game
    while (!isGameWon(guessedWord, secretWord) && !isGameOver(attemptsLeft)) {
        displayGameState(guessedWord, attemptsLeft, wrongGuesses);

        char guess;
        std::cout << "Enter a letter: ";
        std::cin >> guess;

        // if the guessed letter is in the secret word
        bool correctGuess = false;
        for (size_t i = 0; i < secretWord.size(); i++) {
            if (secretWord[i] == guess && guessedWord[i] == '_') {
                guessedWord[i] = guess; // Reveal the letter
                correctGuess = true;
            }
        }

        // If guess incorrect, reduce attempts and store the guess
        if (!correctGuess) {
            attemptsLeft--;
            wrongGuesses.push_back(guess);
        }
    }

    // Display final game state
    displayGameState(guessedWord, attemptsLeft, wrongGuesses);

    // Win or lose message
    if (isGameWon(guessedWord, secretWord)) {
        std::cout << "Congratulations! You guessed the word: " << secretWord << std::endl;
    } else {
        std::cout << "Sorry, you lost. The word was: " << secretWord << std::endl;
    }

    return 0;
}
