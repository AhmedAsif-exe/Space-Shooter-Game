#pragma once
#include <iostream> // Move to .cpp
#include <string>
#include "Vector.h"
#include "Coordinates.h"
#include <string>
#include <cstring>

struct Score
{
	int score = 0;
	char playername[52] = {'\0'};
};

class ScoreManager
{
	static const int numScores = 10;
	Score scores[numScores];
	Score currentScore;
	static ScoreManager* instance;

	void sorting();
	int lowestEntry();
	ScoreManager() = default;
	void WriteToFile(std::string filePath);
public:
	void AddToScore(int amount);
	Score* GetCurrentScore();
	Score* GetScores();
	std::string getName() const;
	void setName(std::string name);
	static ScoreManager* GetInstance();


	void ReadFromFile(std::string filePath);
	void resetState();
	void entry();
	void insert(int idx);

	void writecurrentscoretofile(std::string filename);
};