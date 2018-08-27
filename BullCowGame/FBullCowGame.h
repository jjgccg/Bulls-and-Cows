#pragma once

/* Defines members and functionality of BullCowGame class */

#include <string>
#include <vector>

using FString = std::string; //Unreal alias substitution
using int32 = int;           //Unreal alias substitution

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Incorrect_Length,
	Not_Lowercase
};

class FBullCowGame {
public:
	FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	EGuessStatus CheckGuessValidity(FString Guess) const;
	bool IsGameWon() const;

	void PopulateWordBank();
	void Reset();
	FBullCowCount SubmitValidGuess(FString Guess);

private:
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;
	std::vector<FString> MyWordBank;

	bool IsIsogram(FString Word) const;
	bool IsLowercase(FString Word) const;
	FString ChooseHiddenWord();
};