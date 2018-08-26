#pragma once

/* Implementation of BullCowGame */

#include "stdafx.h"
#include "FBullCowGame.h"

#include <iostream>
#include <map>
#define TMap std::map // Unreal alias

FBullCowGame::FBullCowGame() { Reset();}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;

	return;
}

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

// receives a valid guess, increments turn, and returns count
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

bool FBullCowGame::IsLowercase(FString Word) const
{
	if (Word.length() < 1) { return true; }

	for (auto Letter : Word)
	{
		if (!islower(Letter)) { return false; }
	}

	return true;
}