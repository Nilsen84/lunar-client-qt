#ifndef LUNAR_CLIENT_QT_HELPERSPAGE_H
#define LUNAR_CLIENT_QT_HELPERSPAGE_H

#include <QListWidget>

#include "configurationpage.h"

class HelpersPage : public ConfigurationPage {
Q_OBJECT
public:
    explicit HelpersPage(Config& config, QWidget* parent = nullptr);

    QString title() override;
    QIcon icon() override;

    void apply() override;
    void load() override;
private:
    void addHelper(const QString& path, bool select = false);

    QStringList getHelpers();
private:
    QListWidget* helpers;
};


#endif //LUNAR_CLIENT_QT_HELPERSPAGE_H
