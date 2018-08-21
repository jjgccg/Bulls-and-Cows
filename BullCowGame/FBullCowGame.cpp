#include "stdafx.h"
#include "FBullCowGame.h"

#include <iostream>

FBullCowGame::FBullCowGame() { Reset();}

int32 FBullCowGame::GetMaxTries() const {return MyMaxTries;}
int32 FBullCowGame::GetCurrentTry() const {return MyCurrentTry;}

int32 FBullCowGame::GetHiddenWordLength() const {return MyHiddenWord.length();}

void FBullCowGame::Reset()
{
	constexpr int MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";

	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;

	return;
}

bool FBullCowGame::IsGameWon() const
{
	return false;
}

bool FBullCowGame::CheckGuessValidity(FString) const
{
	return false;
}

// receives a valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	//increment return number
	MyCurrentTry++;
	//setup a return variable
	FBullCowCount BullCowCount;
	
	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 MHWChar = 0; MHWChar < HiddenWordLength; MHWChar++)
	{
		for (int32 GChar = 0; GChar < HiddenWordLength; GChar++)
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

	//loop through all letters in the guess
	//compare letters against the hidden word
	return BullCowCount;
}

bool FBullCowGame::IsIsogram()
{
	return false;
}