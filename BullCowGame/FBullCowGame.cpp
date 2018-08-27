/* Implementation of BullCowGame */

#pragma once
#include "stdafx.h"
#include "FBullCowGame.h"

#include <iostream>
#include <map>
#include <fstream>
#include <ctime>
#define TMap std::map // Unreal alias

/* Creating a new instance populates the word bank and resets the game */
FBullCowGame::FBullCowGame() 
{ 
	PopulateWordBank();
	Reset();
}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

/* Gets the max number of tries based on length of random word from bank */
int32 FBullCowGame::GetMaxTries() const 
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10},
											 {6,16}, {7,20}, {8,25},
											 {8,30}, {9,35}, {10,40}, 
											 {11,45}, {12,50} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

/* Parses text file, putting words inside of data member */
void FBullCowGame::PopulateWordBank()
{
	std::ifstream infile("wordbank.txt");
	FString word;

	while (infile >> word)
	{
		MyWordBank.push_back(word);
	}

	infile.close();
}

/* Chooses a new hidden word from bank and resets the tries to 1 */
void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = ChooseHiddenWord();
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;

	return;
}

/* Returns errors for invalid input */
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (GetHiddenWordLength() != Guess.length())
	{
		return EGuessStatus::Incorrect_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

/* Receives a valid guess, increments turn, and returns count */
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	
	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 MHWChar = 0; MHWChar < HiddenWordLength; MHWChar++) //loop through all letters in hidden word
	{
		for (int32 GChar = 0; GChar < HiddenWordLength; GChar++) //loop through all letters in guess
		{
			if ((MyHiddenWord[MHWChar] == Guess[GChar]) && (MHWChar == GChar))
			{
				BullCowCount.Bulls++;
			}
			else if (MyHiddenWord[MHWChar] == Guess[GChar])
			{
				BullCowCount.Cows++;
			}
		}
	}
	if (BullCowCount.Bulls == HiddenWordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

/* Checks if input is an isogram */
bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) { return true; } //treat 0 and 1 letter words as isograms

	TMap<char, bool> LetterSeen;
	for (auto Letter : Word)
	{
		Letter = tolower(Letter); //handle mixed case
		if (LetterSeen[Letter])
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}

	return true;
}

/* Checks if a word is lowercase */
bool FBullCowGame::IsLowercase(FString Word) const

{
	if (Word.length() < 1) { return true; }

	for (auto Letter : Word)
	{
		if (!islower(Letter)) { return false; }
	}

	return true;
}

/* Randomly selects a word from the bank to use as the hidden word */
FString FBullCowGame::ChooseHiddenWord()
{
	int RandomIndex = 0;
	srand(time(NULL));

	if (MyWordBank.size() > 0) 
	{ 
		RandomIndex = rand() % MyWordBank.size(); // 0 -> (Vector Size - 1)
	} 

	return MyWordBank[RandomIndex];
}