#ifndef CSVLEVELDAO_H
#define CSVLEVELDAO_H

#include "leveldao.h"
#include "editorlevel.h"
#include <QString>
#include <vector>

class CSVLevelDAO : public LevelDAO {
public:
    explicit CSVLevelDAO(const QString &filename);
    std::vector<EditorLevel> getAllLevels() const override;
    void insert(const EditorLevel &level) override;
    QString generateUniqueLevelName(const QString &baseName) const;
    bool levelNameExists(const QString &levelName) const;

private:
    QString filename;

    std::vector<QString> parseCSVLine(const QString &line) const;
    QString levelToCSVString(const EditorLevel &level) const;
    std::vector<int> parseHintString(const QString &hintString) const;
    QString hintToString(const std::vector<int> &hint) const;
    QString intToBase36(int num) const;
    int base36ToInt(const QString &str) const;
};

#endif // CSVLEVELDAO_H
