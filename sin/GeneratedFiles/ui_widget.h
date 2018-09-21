/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetClass
{
public:
    QPushButton *pushButton1;
    QPushButton *pushButton2;
    QPushButton *pushButton3;

    void setupUi(QWidget *WidgetClass)
    {
        if (WidgetClass->objectName().isEmpty())
            WidgetClass->setObjectName(QStringLiteral("WidgetClass"));
        WidgetClass->resize(800, 461);
        pushButton1 = new QPushButton(WidgetClass);
        pushButton1->setObjectName(QStringLiteral("pushButton1"));
        pushButton1->setGeometry(QRect(200, 260, 93, 28));
        pushButton2 = new QPushButton(WidgetClass);
        pushButton2->setObjectName(QStringLiteral("pushButton2"));
        pushButton2->setGeometry(QRect(350, 260, 93, 28));
        pushButton3 = new QPushButton(WidgetClass);
        pushButton3->setObjectName(QStringLiteral("pushButton3"));
        pushButton3->setGeometry(QRect(510, 260, 93, 28));

        retranslateUi(WidgetClass);
        QObject::connect(pushButton1, SIGNAL(clicked()), WidgetClass, SLOT(ChangeSinOffset()));
        QObject::connect(pushButton2, SIGNAL(clicked()), WidgetClass, SLOT(ChangeAmplitude()));
        QObject::connect(pushButton3, SIGNAL(clicked()), WidgetClass, SLOT(ChangeCycle()));

        QMetaObject::connectSlotsByName(WidgetClass);
    } // setupUi

    void retranslateUi(QWidget *WidgetClass)
    {
        WidgetClass->setWindowTitle(QApplication::translate("WidgetClass", "Widget", Q_NULLPTR));
        pushButton1->setText(QApplication::translate("WidgetClass", "\345\201\217\347\247\273\351\207\217", Q_NULLPTR));
        pushButton2->setText(QApplication::translate("WidgetClass", "\346\214\257\345\271\205", Q_NULLPTR));
        pushButton3->setText(QApplication::translate("WidgetClass", "\345\221\250\346\234\237", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class WidgetClass: public Ui_WidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
