#include "csvscoredao.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

CSVScoreDAO::CSVScoreDAO(const QString &filename) : filename(filename) {}

std::vector<Score> CSVScoreDAO::getAllScores() const
{
    std::vector<Score> scores;
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for reading:" << filename;
        return scores;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');

        if (fields.size() == 4) {
            Score score(fields[0].toInt(),
                        fields[1],
                        static_cast<qint64>(fields[2].toLongLong()),
                        fields[3]);
            scores.push_back(score);
        }
    }

    file.close();
    return scores;
}

void CSVScoreDAO::insert(const Score& score) {
    QFile file(filename);

    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing:" << filename;
        return;
    }

    QTextStream out(&file);
    out << score.getScoreId() << ","
        << score.getUserName() << ","
        << score.getCompletionTime() << ","
        << score.getLevelDifficulty() << "\n";

    qDebug() << "Inserted Scores: " << score.printScore();

    file.close();
}

int CSVScoreDAO::getNextScoreId() const
{
    int maxId = 0;
    std::vector<Score> scores = getAllScores();
    for (const Score &score : scores) {
        maxId = std::max(maxId, score.getScoreId());
    }
    return maxId + 1;
}

qint64 CSVScoreDAO::getMinTimeForUser(const QString &username) const
{
    QFile file(filename);
    qint64 lowestTime = std::numeric_limits<int>::max();

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for reading:" << filename;
        return lowestTime;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');

        if (fields.size() == 4 && fields[1] == username) {
            int completionTime = fields[2].toInt();
            if (completionTime < lowestTime) {
                lowestTime = completionTime;
            }
        }
    }

    file.close();
    return (lowestTime == std::numeric_limits<int>::max()) ? 0 : lowestTime;
}

int CSVScoreDAO::getCountLevelForUser(const QString &username) const
{
    QFile file(filename);
    int count = 0;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for reading:" << filename;
        return count;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');

        if (fields.size() == 4 && fields[1] == username) {
            count++;
        }
    }

    file.close();
    return count;
}
