/********************************************************************************
** Form generated from reading UI file 'music.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MUSIC_H
#define UI_MUSIC_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_music
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QLabel *bar1;

    void setupUi(QWidget *music)
    {
        if (music->objectName().isEmpty())
            music->setObjectName(QStringLiteral("music"));
        music->resize(603, 427);
        gridLayout = new QGridLayout(music);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox = new QGroupBox(music);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        bar1 = new QLabel(groupBox);
        bar1->setObjectName(QStringLiteral("bar1"));
        bar1->setGeometry(QRect(0, 100, 594, 15));

        gridLayout->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(music);

        QMetaObject::connectSlotsByName(music);
    } // setupUi

    void retranslateUi(QWidget *music)
    {
        music->setWindowTitle(QApplication::translate("music", "Form", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("music", "music", Q_NULLPTR));
        bar1->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class music: public Ui_music {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUSIC_H
