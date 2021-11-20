//
// Created by nils on 11/20/21.
//

#include "classpathpage.h"

ClasspathPage::ClasspathPage(QWidget *parent) : ConfigurationPage(parent) {
}


QString ClasspathPage::title() {
    return QStringLiteral("Classpath & Agents");
}

QIcon ClasspathPage::icon() {
    return QIcon(":/res/icons/agent.svg");
}

void ClasspathPage::save(QJsonObject &jsonObject) {

}

void ClasspathPage::load(const QJsonObject &jsonObject) {

}
