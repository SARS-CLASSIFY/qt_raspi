/********************************************************************************
** Form generated from reading UI file 'fix.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIX_H
#define UI_FIX_H

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

class Ui_fix
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QLabel *bar1;
    QLabel *word2;
    QLabel *label_img;

    void setupUi(QWidget *fix)
    {
        if (fix->objectName().isEmpty())
            fix->setObjectName(QStringLiteral("fix"));
        fix->resize(603, 427);
        gridLayout = new QGridLayout(fix);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox = new QGroupBox(fix);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        bar1 = new QLabel(groupBox);
        bar1->setObjectName(QStringLiteral("bar1"));
        bar1->setGeometry(QRect(0, 100, 594, 15));
        word2 = new QLabel(groupBox);
        word2->setObjectName(QStringLiteral("word2"));
        word2->setGeometry(QRect(120, 10, 331, 71));
        word2->setFrameShadow(QFrame::Raised);
        word2->setAlignment(Qt::AlignCenter);
        label_img = new QLabel(groupBox);
        label_img->setObjectName(QStringLiteral("label_img"));
        label_img->setGeometry(QRect(50, 140, 231, 241));
        label_img->setAcceptDrops(true);
        label_img->setAutoFillBackground(true);
        label_img->setWordWrap(false);

        gridLayout->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(fix);

        QMetaObject::connectSlotsByName(fix);
    } // setupUi

    void retranslateUi(QWidget *fix)
    {
        fix->setWindowTitle(QApplication::translate("fix", "Form", Q_NULLPTR));
        groupBox->setTitle(QString());
        bar1->setText(QString());
        word2->setText(QApplication::translate("fix", "\344\270\252\344\272\272\347\233\270\345\206\214", Q_NULLPTR));
        label_img->setText(QApplication::translate("fix", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class fix: public Ui_fix {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIX_H
