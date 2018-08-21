#pragma once
#include <string>

using FString = std::string; //Unreal alias substitution
using int32 = int;           //Unreal alias substitution

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

class FBullCowGame {
public:
	FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool CheckGuessValidity(FString) const;
	bool IsGameWon() const;

	void Reset();
	FBullCowCount SubmitGuess(FString Guess);

private:
	int32 MyCurrentTry;
	int32 MyMaxTries;
	bool IsIsogram();
	FString MyHiddenWord;
};