#pragma once

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
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //instance used across all plays

int main()
{
	bool bPlayAgain = false;
	BCGame.PopulateWordBank();

	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain == true);

	return 0;
}

void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ "                 << std::endl;
	std::cout << "          (o o)        (o o) "                << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ "      << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ "       << std::endl;
	std::cout << " *  |-,--- |              |------|  * "       << std::endl;
	std::cout << "    ^      ^              ^      ^ "          << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;

	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	
	// loop asking for guesses while the game is NOT won and still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ".  Cows = " << BullCowCount.Cows << std::endl << std::endl;
	}

	PrintGameSummary();
}

FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status; //invalid by default

	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Incorrect_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n" << std::endl;
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram.\n" << std::endl;
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter a lowercase word.\n" << std::endl;
			break;
		default:
			Status = EGuessStatus::OK;
		}
	} while (Status != EGuessStatus::OK);
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (y/n): ";
	FText Response = "";
	std::getline(std::cin, Response);

	return(Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN!" << std::endl;
	}
	else
	{
		std::cout << "Better luck next time!" << std::endl;
	}
}