#include "csvleveldao.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

CSVLevelDAO::CSVLevelDAO(const QString &filename) : filename(filename) {}

std::vector<QString> CSVLevelDAO::parseCSVLine(const QString &line) const {
    QList<QString> list = line.split(',');
    std::vector<QString> result;
    result.reserve(list.size());
    for (const QString &str : list) {
        result.push_back(str);
    }
    return result;
}

QString CSVLevelDAO::levelToCSVString(const EditorLevel &level) const {
    QStringList fields;
    fields << level.getLevelName()
           << level.getDifficulty();

    // Serialize row hints
    QStringList rowHints;
    for (const auto &hints : level.getRowHint()) {
        rowHints << "{" + hintToString(hints) + "}";
    }
    fields << rowHints.join(' ');

    // Serialize column hints
    QStringList colHints;
    for (const auto &hints : level.getColHint()) {
        colHints << "{" + hintToString(hints) + "}";
    }
    fields << colHints.join(' ');

    return fields.join(',');
}

std::vector<int> CSVLevelDAO::parseHintString(const QString &hintString) const {
    std::vector<int> hints;
    for (const QString &hint : hintString.split(' ')) {
        hints.push_back(base36ToInt(hint));
    }
    return hints;
}

QString CSVLevelDAO::hintToString(const std::vector<int> &hint) const {
    QStringList hintStrings;
    for (int h : hint) {
        hintStrings << intToBase36(h);
    }
    return hintStrings.join(' ');
}

QString CSVLevelDAO::intToBase36(int num) const {
    const char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    QString result;
    do {
        result.prepend(digits[num % 36]);
        num /= 36;
    } while (num > 0);
    return result;
}

int CSVLevelDAO::base36ToInt(const QString &str) const {
    int result = 0;
    for (QChar c : str) {
        if (c.isDigit()) {
            result = result * 36 + (c.unicode() - '0');
        } else if (c.isLower()) {
            result = result * 36 + (c.unicode() - 'a' + 10);
        }
    }
    return result;
}

std::vector<EditorLevel> CSVLevelDAO::getAllLevels() const {
    std::vector<EditorLevel> levels;
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for reading:" << filename;
        return levels;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        auto fields = parseCSVLine(line);

        if (fields.size() >= 4) {
            QString levelName = fields[0];
            QString difficulty = fields[1];
            QString rowHintString = fields[2];
            QString colHintString = fields[3];

            std::vector<std::vector<int>> rowHints;
            std::vector<std::vector<int>> colHints;

            // Parse row hints
            rowHintString = rowHintString.mid(1, rowHintString.length() - 2); // Remove {}
            auto rowHintParts = rowHintString.split(' ');
            for (const auto &part : rowHintParts) {
                rowHints.push_back(parseHintString(part));
            }

            // Parse column hints
            colHintString = colHintString.mid(1, colHintString.length() - 2); // Remove {}
            auto colHintParts = colHintString.split(' ');
            for (const auto &part : colHintParts) {
                colHints.push_back(parseHintString(part));
            }

            EditorLevel level({}, {}, rowHints, colHints, difficulty, 0, levelName);
            levels.push_back(level);

            qDebug() << "Loaded Level:" << levelName;
            qDebug() << "Difficulty:" << difficulty;
            qDebug() << "Row Hints:" << rowHints;
            qDebug() << "Column Hints:" << colHints;
        }
    }

    file.close();
    return levels;
}

void CSVLevelDAO::insert(const EditorLevel &level) {
    QFile file(filename);

    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing:" << filename;
        return;
    }

    QTextStream out(&file);
    out << levelToCSVString(level) << "\n";

    qDebug() << "Inserted Level:" << level.getLevelName();

    file.close();
}
