/* Console executable that makes use of the BullCow class.
 * Acts as the view in the MVC pattern, responsible for userr interaction.
 * For game logic see FBullCowGame.cpp
 */

#include "stdafx.h"
#include "FBullCowGame.h"

#include <iostream>
#include <string>

using FText = std::string; //Unreal alias substitution
using int32 = int;         //Unreal alias substitution

void PrintIntro();
void PlayGame();
FText GetGuess();
bool AskToPlayAgain();

FBullCowGame BCGame;

int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain == true);

	return 0;
}

void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?" << std::endl;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	
	// TODO change from FOR to WHILE loop once we are validating tries
	for (int32 i = 0; i < MaxTries; i++)
	{
		FText Guess = GetGuess(); //TODO make loop checking for valid guesses

		//submit valid guess to game
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ".  Cows = " << BullCowCount.Cows << std::endl;
		std::cout << std::endl;
	}
}

FText GetGuess()
{
	int32 CurrentTry = BCGame.GetCurrentTry();
	std::cout << "Enter your guess: ";
	FText Guess = "";
	std::getline(std::cin, Guess);

	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n): ";
	FText Response = "";
	std::getline(std::cin, Response);

	return(Response[0] == 'y' || Response[0] == 'Y');
}