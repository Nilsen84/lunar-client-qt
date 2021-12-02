//
// Created by nils on 12/2/21.
//

#ifndef LUNAR_CLIENT_QT_FILECHOOSER_H
#define LUNAR_CLIENT_QT_FILECHOOSER_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class FileChooser : public QWidget {
Q_OBJECT
public:
    explicit FileChooser(QWidget* parent = nullptr);

    QString getPath();
    void setPath(const QString& path);
private:
    QLineEdit* pathEdit;
};


#endif //LUNAR_CLIENT_QT_FILECHOOSER_H
