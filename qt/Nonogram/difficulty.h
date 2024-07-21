#ifndef DIFFICULTY_H
#define DIFFICULTY_H

#include <QString>

enum class Difficulty {
    Easy = 5,
    Normal = 10,
    Hard = 15,
    Extreme = 20,
    Hell = 30,
    Custom = 0
};

inline QString difficultyToString(Difficulty difficulty) {
    switch (difficulty) {
    case Difficulty::Easy: return "Easy";
    case Difficulty::Normal: return "Normal";
    case Difficulty::Hard: return "Hard";
    case Difficulty::Extreme: return "Extreme";
    case Difficulty::Hell: return "Hell";
    case Difficulty::Custom: return "Custom";
    default: return "Unknown";
    }
}

inline Difficulty stringToDifficulty(const QString &difficultyStr) {
    if (difficultyStr == "Easy") return Difficulty::Easy;
    if (difficultyStr == "Normal") return Difficulty::Normal;
    if (difficultyStr == "Hard") return Difficulty::Hard;
    if (difficultyStr == "Extreme") return Difficulty::Extreme;
    if (difficultyStr == "Hell") return Difficulty::Hell;
    if (difficultyStr == "Custom") return Difficulty::Custom;
    return Difficulty::Custom; // Default to Custom if no match
}

#endif // DIFFICULTY_H
