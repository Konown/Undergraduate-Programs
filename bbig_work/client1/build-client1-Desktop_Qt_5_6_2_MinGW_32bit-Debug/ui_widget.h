/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *lineEdit_users;
    QSpacerItem *horizontalSpacer;
    QLabel *label_3;
    QLineEdit *lineEdit_login_password;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButto_login_close;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_login_enter;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout_3;
    QFrame *frame_5;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_9;
    QLabel *label_7;
    QLabel *label_8;
    QFrame *frame_6;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_4;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(546, 494);
        verticalLayout = new QVBoxLayout(Widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        frame = new QFrame(Widget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_2->addWidget(label);


        verticalLayout->addWidget(frame);

        frame_2 = new QFrame(Widget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(frame_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        lineEdit_users = new QLineEdit(frame_2);
        lineEdit_users->setObjectName(QStringLiteral("lineEdit_users"));

        horizontalLayout->addWidget(lineEdit_users);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_3 = new QLabel(frame_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        lineEdit_login_password = new QLineEdit(frame_2);
        lineEdit_login_password->setObjectName(QStringLiteral("lineEdit_login_password"));

        horizontalLayout->addWidget(lineEdit_login_password);


        verticalLayout->addWidget(frame_2);

        frame_3 = new QFrame(Widget);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_3);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButto_login_close = new QPushButton(frame_3);
        pushButto_login_close->setObjectName(QStringLiteral("pushButto_login_close"));

        horizontalLayout_2->addWidget(pushButto_login_close);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pushButton_login_enter = new QPushButton(frame_3);
        pushButton_login_enter->setObjectName(QStringLiteral("pushButton_login_enter"));

        horizontalLayout_2->addWidget(pushButton_login_enter);


        verticalLayout->addWidget(frame_3);

        frame_4 = new QFrame(Widget);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_4);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        frame_5 = new QFrame(frame_4);
        frame_5->setObjectName(QStringLiteral("frame_5"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(frame_5);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_5 = new QLabel(frame_5);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout_4->addWidget(label_5);

        label_6 = new QLabel(frame_5);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout_4->addWidget(label_6);

        label_9 = new QLabel(frame_5);
        label_9->setObjectName(QStringLiteral("label_9"));

        verticalLayout_4->addWidget(label_9);

        label_7 = new QLabel(frame_5);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout_4->addWidget(label_7);

        label_8 = new QLabel(frame_5);
        label_8->setObjectName(QStringLiteral("label_8"));

        verticalLayout_4->addWidget(label_8);


        horizontalLayout_3->addWidget(frame_5);

        frame_6 = new QFrame(frame_4);
        frame_6->setObjectName(QStringLiteral("frame_6"));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame_6);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_4 = new QLabel(frame_6);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/CJLU_logo.png")));

        verticalLayout_3->addWidget(label_4);


        horizontalLayout_3->addWidget(frame_6);


        verticalLayout->addWidget(frame_4);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        label->setText(QApplication::translate("Widget", "<html><head/><body><p align=\"center\"><span style=\" font-size:18pt; font-weight:600;\">\347\231\273\345\275\225\347\225\214\351\235\242</span></p></body></html>", 0));
        label_2->setText(QApplication::translate("Widget", "\347\224\250\346\210\267\345\220\215", 0));
        label_3->setText(QApplication::translate("Widget", "\345\257\206\347\240\201", 0));
        pushButto_login_close->setText(QApplication::translate("Widget", "\345\205\263\351\227\255", 0));
        pushButton_login_enter->setText(QApplication::translate("Widget", "\347\231\273\345\275\225", 0));
        label_5->setText(QApplication::translate("Widget", "\351\231\210\346\265\267\345\250\201     2000110310", 0));
        label_6->setText(QApplication::translate("Widget", "\344\271\224\346\243\256     ", 0));
        label_9->setText(QApplication::translate("Widget", "TextLabel", 0));
        label_7->setText(QApplication::translate("Widget", "TextLabel", 0));
        label_8->setText(QApplication::translate("Widget", "TextLabel", 0));
        label_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
