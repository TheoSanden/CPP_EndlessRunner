// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "HighscoreSaveGame.generated.h"


/**
 * 
 */

USTRUCT()
struct FSaveValues
{
	GENERATED_BODY()

	//UPROPERTY()
	FString name;
	//UPROPERTY()
	int score;
	FSaveValues()
	{
		name = FString("");
		Hash = FCrc::MemCrc32(this, sizeof(this));
	}
	FSaveValues(FString p_name, int p_score)
	{
		name = p_name;
		score = p_score;
		Hash = FCrc::MemCrc32(this, sizeof(this));
	}

	FORCEINLINE bool operator>(const FSaveValues& Other) const
	{
		return (score > Other.score);
	}
	FORCEINLINE bool operator<(const FSaveValues& Other) const
	{
		return (score < Other.score);
	}
	FORCEINLINE bool operator==(const FSaveValues& Other) const
	{
		return (Other.Hash == Hash);
	}

private:
	uint32 Hash;
};


UCLASS()
class ENDLESSRUNNER_API UHighscoreSaveGame : public USaveGame
{
	GENERATED_BODY()

	const int HighScoreArrayMaxSize = 10;
public:
	//Returns the indicies in which the Highscores were Placed, returns -1 for no highscore
	TArray<int> TryInsertScore(FSaveValues Score1, FSaveValues Score2);
	UPROPERTY()
	TArray<FSaveValues> Scores;
};
