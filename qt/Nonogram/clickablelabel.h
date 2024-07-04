#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QString>

class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget *parent = nullptr);
    void setImagePath(const QString &path);
    QString getImagePath() const;

signals:
    void clicked(const QString &imagePath);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QString imagePath;
};

#endif // CLICKABLELABEL_H
