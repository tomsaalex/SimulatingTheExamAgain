/********************************************************************************
** Form generated from reading UI file 'ExamTime.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXAMTIME_H
#define UI_EXAMTIME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExamTimeClass
{
public:

    void setupUi(QWidget *ExamTimeClass)
    {
        if (ExamTimeClass->objectName().isEmpty())
            ExamTimeClass->setObjectName(QString::fromUtf8("ExamTimeClass"));
        ExamTimeClass->resize(600, 400);

        retranslateUi(ExamTimeClass);

        QMetaObject::connectSlotsByName(ExamTimeClass);
    } // setupUi

    void retranslateUi(QWidget *ExamTimeClass)
    {
        ExamTimeClass->setWindowTitle(QCoreApplication::translate("ExamTimeClass", "ExamTime", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ExamTimeClass: public Ui_ExamTimeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXAMTIME_H
