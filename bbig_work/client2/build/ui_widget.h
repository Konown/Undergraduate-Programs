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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "pyqtgraph"

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_6;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_go;
    QFrame *frame_5;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_left;
    QPushButton *pushButton_back;
    QPushButton *pushButton_right;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *lineEdit_database;
    QPushButton *pushButton_check;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_draw;
    PlotWidget *graphicsView;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout_5;
    QTextBrowser *textBrowser_Receive;
    QPushButton *pushButton_sendMs;
    QLineEdit *lineEdit_Send;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(788, 553);
        verticalLayout = new QVBoxLayout(Widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        frame = new QFrame(Widget);
        frame->setObjectName(QStringLiteral("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(2);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        frame_6 = new QFrame(frame);
        frame_6->setObjectName(QStringLiteral("frame_6"));
        sizePolicy.setHeightForWidth(frame_6->sizePolicy().hasHeightForWidth());
        frame_6->setSizePolicy(sizePolicy);
        frame_6->setMaximumSize(QSize(16777215, 200));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_6);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_go = new QPushButton(frame_6);
        pushButton_go->setObjectName(QStringLiteral("pushButton_go"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_go->sizePolicy().hasHeightForWidth());
        pushButton_go->setSizePolicy(sizePolicy1);
        pushButton_go->setMinimumSize(QSize(250, 0));

        horizontalLayout->addWidget(pushButton_go);


        verticalLayout_3->addWidget(frame_6);

        frame_5 = new QFrame(frame);
        frame_5->setObjectName(QStringLiteral("frame_5"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_5);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButton_left = new QPushButton(frame_5);
        pushButton_left->setObjectName(QStringLiteral("pushButton_left"));

        horizontalLayout_2->addWidget(pushButton_left);

        pushButton_back = new QPushButton(frame_5);
        pushButton_back->setObjectName(QStringLiteral("pushButton_back"));

        horizontalLayout_2->addWidget(pushButton_back);

        pushButton_right = new QPushButton(frame_5);
        pushButton_right->setObjectName(QStringLiteral("pushButton_right"));

        horizontalLayout_2->addWidget(pushButton_right);


        verticalLayout_3->addWidget(frame_5);


        verticalLayout->addWidget(frame);

        frame_2 = new QFrame(Widget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(frame_2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        groupBox = new QGroupBox(frame_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout_3 = new QHBoxLayout(groupBox);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        lineEdit_database = new QLineEdit(groupBox);
        lineEdit_database->setObjectName(QStringLiteral("lineEdit_database"));

        horizontalLayout_3->addWidget(lineEdit_database);

        pushButton_check = new QPushButton(groupBox);
        pushButton_check->setObjectName(QStringLiteral("pushButton_check"));

        horizontalLayout_3->addWidget(pushButton_check);


        verticalLayout_4->addWidget(groupBox);


        verticalLayout->addWidget(frame_2);

        frame_3 = new QFrame(Widget);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(4);
        sizePolicy2.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
        frame_3->setSizePolicy(sizePolicy2);
        frame_3->setMaximumSize(QSize(16777215, 300));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame_3);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        pushButton_draw = new QPushButton(frame_3);
        pushButton_draw->setObjectName(QStringLiteral("pushButton_draw"));
        sizePolicy1.setHeightForWidth(pushButton_draw->sizePolicy().hasHeightForWidth());
        pushButton_draw->setSizePolicy(sizePolicy1);
        pushButton_draw->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_4->addWidget(pushButton_draw);

        graphicsView = new PlotWidget(frame_3);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setMaximumSize(QSize(16777215, 300));

        horizontalLayout_4->addWidget(graphicsView);


        verticalLayout->addWidget(frame_3);

        frame_4 = new QFrame(Widget);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        sizePolicy.setHeightForWidth(frame_4->sizePolicy().hasHeightForWidth());
        frame_4->setSizePolicy(sizePolicy);
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        horizontalLayout_5 = new QHBoxLayout(frame_4);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        textBrowser_Receive = new QTextBrowser(frame_4);
        textBrowser_Receive->setObjectName(QStringLiteral("textBrowser_Receive"));

        horizontalLayout_5->addWidget(textBrowser_Receive);

        pushButton_sendMs = new QPushButton(frame_4);
        pushButton_sendMs->setObjectName(QStringLiteral("pushButton_sendMs"));

        horizontalLayout_5->addWidget(pushButton_sendMs);


        verticalLayout->addWidget(frame_4);

        lineEdit_Send = new QLineEdit(Widget);
        lineEdit_Send->setObjectName(QStringLiteral("lineEdit_Send"));

        verticalLayout->addWidget(lineEdit_Send);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        pushButton_go->setText(QApplication::translate("Widget", "\345\211\215\350\277\233", 0));
        pushButton_left->setText(QApplication::translate("Widget", "\345\267\246\350\275\254", 0));
        pushButton_back->setText(QApplication::translate("Widget", "\345\220\216\351\200\200", 0));
        pushButton_right->setText(QApplication::translate("Widget", "\345\217\263\350\275\254", 0));
        groupBox->setTitle(QApplication::translate("Widget", "\346\237\245\350\257\242\345\216\206\345\217\262\344\277\241\346\201\257", 0));
        pushButton_check->setText(QApplication::translate("Widget", "\346\237\245\350\257\242", 0));
        pushButton_draw->setText(QApplication::translate("Widget", "\347\273\230\345\233\276", 0));
        pushButton_sendMs->setText(QApplication::translate("Widget", "\345\217\221\351\200\201", 0));
        lineEdit_Send->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
