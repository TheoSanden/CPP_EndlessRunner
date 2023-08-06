// Fill out your copyright notice in the Description page of Project Settings.


#include "HighscoreSaveGame.h"

TArray<int> UHighscoreSaveGame::TryInsertScore(FSaveValues Score1, FSaveValues Score2)
{
	Scores.Add(Score1);
	Scores.Add(Score2);
	Scores.Sort([](const FSaveValues HS1, const FSaveValues HS2) {return HS1 > HS2;});

	if(Scores.Num() > HighScoreArrayMaxSize)
	{
		for(int i = HighScoreArrayMaxSize-1; i < Scores.Num(); i++)
		{
			Scores.RemoveAt(i);
		}
	}

	TArray<int> IndexLocations = {-1,-1};

	for(int i = 0; i < Scores.Num(); i++)
	{
		if(Score1 == Scores[i])
		{
			IndexLocations[0] = i;
		}
		if (Score2 == Scores[i])
		{
			IndexLocations[1] = i;
		}
	}
	return IndexLocations;
}