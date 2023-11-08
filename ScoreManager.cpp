#include "ScoreManager.h"

#include <cstring> // Include for strcpy_s()

ScoreManager* ScoreManager::instance = nullptr;

void ScoreManager::AddToScore(int amount)
{
    currentScore.score += amount;
 
}

Score* ScoreManager::GetCurrentScore()
{
    return &currentScore;
}

Score* ScoreManager::GetScores()
{
    return scores;
}

std::string ScoreManager::getName() const
{
    return currentScore.playername;
}

void ScoreManager::setName(std::string name)
{
    strcpy_s(currentScore.playername, name.c_str());

}

ScoreManager* ScoreManager::GetInstance()
{
    if (!instance)
        instance = new ScoreManager();

    return instance;
}

void ScoreManager::WriteToFile(std::string filePath)
{
    FILE* file;
    fopen_s(&file, filePath.c_str(), "wb");
    if (file)
    {
        fwrite(scores, sizeof(Score) * numScores, 1, file);
        fclose(file);
    }
}

void ScoreManager::ReadFromFile(std::string filePath)
{
    FILE* file;
    fopen_s(&file, filePath.c_str(), "rb");
    if (file)
    {
        fread(scores, sizeof(Score) * numScores, 1, file);
        fclose(file);
    }
}

void ScoreManager::resetState()
{
    for (int i = 0; i < numScores; i++)
        currentScore.playername[i] = '\0';
    currentScore.score = 0;
}
void ScoreManager::entry()
{

    sorting();
    int temp = lowestEntry();
    if (temp != -1)
    insert(temp);

    WriteToFile("ScoreBoard.dat");
    resetState();
}
void ScoreManager::sorting()
{
    for (int i = 0; i < numScores; i++)
    {
        for (int j = 0; j < numScores - 1; j++)
        {
            if (scores[j].score < scores[j + 1].score)
            {
                Score temp = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = temp;
            }
        }
    }
}

int ScoreManager::lowestEntry()
{   
    for (int i = 0; i < numScores; i++)   
        if (currentScore.score > scores[i].score)
            return i;
    
    return -1;
    
}
void ScoreManager::insert(int idx)
{
    for (int i = numScores - 2; i >= idx; i--)
        scores[i + 1] = scores[i];
    scores[idx] = currentScore;    

}
void ScoreManager::writecurrentscoretofile(std::string filename)
{
    FILE* file;
    fopen_s(&file, filename.c_str(), "wb");
    if (file)
    {
        fwrite(&currentScore, sizeof(int), 1, file);
        fclose(file);
    }
}
