/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QSplitter *splitter;
    QLabel *titre;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_7;
    QSplitter *splitter_2;
    QLabel *label_5;
    QComboBox *preset;
    QSplitter *splitter_3;
    QLabel *label_10;
    QLineEdit *Name;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_5;
    QLineEdit *port;
    QLineEdit *baudrate;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QLabel *label_4;
    QVBoxLayout *verticalLayout_4;
    QLineEdit *khigh;
    QLineEdit *klow;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_6;
    QLineEdit *mininterval;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_9;
    QLabel *label_8;
    QLabel *label_7;
    QVBoxLayout *verticalLayout_6;
    QLineEdit *bplow;
    QLineEdit *bphigh;
    QLineEdit *bporder;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *save;
    QPushButton *deleteButton;
    QPushButton *lunchButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(329, 448);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName("splitter");
        splitter->setGeometry(QRect(40, 20, 251, 411));
        splitter->setOrientation(Qt::Orientation::Vertical);
        splitter->setHandleWidth(11);
        titre = new QLabel(splitter);
        titre->setObjectName("titre");
        QFont font;
        font.setFamilies({QString::fromUtf8("System")});
        font.setPointSize(23);
        font.setBold(true);
        titre->setFont(font);
        titre->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        titre->setFrameShape(QFrame::Shape::Box);
        titre->setFrameShadow(QFrame::Shadow::Raised);
        titre->setLineWidth(2);
        titre->setMidLineWidth(0);
        titre->setTextFormat(Qt::TextFormat::AutoText);
        titre->setAlignment(Qt::AlignmentFlag::AlignCenter);
        titre->setWordWrap(false);
        titre->setMargin(0);
        titre->setIndent(1);
        splitter->addWidget(titre);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName("layoutWidget");
        verticalLayout_8 = new QVBoxLayout(layoutWidget);
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        splitter_2 = new QSplitter(layoutWidget);
        splitter_2->setObjectName("splitter_2");
        splitter_2->setOrientation(Qt::Orientation::Horizontal);
        label_5 = new QLabel(splitter_2);
        label_5->setObjectName("label_5");
        splitter_2->addWidget(label_5);
        preset = new QComboBox(splitter_2);
        preset->setObjectName("preset");
        splitter_2->addWidget(preset);

        verticalLayout_7->addWidget(splitter_2);

        splitter_3 = new QSplitter(layoutWidget);
        splitter_3->setObjectName("splitter_3");
        splitter_3->setOrientation(Qt::Orientation::Horizontal);
        label_10 = new QLabel(splitter_3);
        label_10->setObjectName("label_10");
        splitter_3->addWidget(label_10);
        Name = new QLineEdit(splitter_3);
        Name->setObjectName("Name");
        splitter_3->addWidget(Name);

        verticalLayout_7->addWidget(splitter_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(layoutWidget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        port = new QLineEdit(layoutWidget);
        port->setObjectName("port");

        verticalLayout_5->addWidget(port);

        baudrate = new QLineEdit(layoutWidget);
        baudrate->setObjectName("baudrate");

        verticalLayout_5->addWidget(baudrate);


        horizontalLayout_2->addLayout(verticalLayout_5);


        verticalLayout_7->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName("label_3");

        verticalLayout_2->addWidget(label_3);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName("label_4");

        verticalLayout_2->addWidget(label_4);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        khigh = new QLineEdit(layoutWidget);
        khigh->setObjectName("khigh");

        verticalLayout_4->addWidget(khigh);

        klow = new QLineEdit(layoutWidget);
        klow->setObjectName("klow");

        verticalLayout_4->addWidget(klow);


        horizontalLayout->addLayout(verticalLayout_4);


        verticalLayout_7->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName("label_6");

        horizontalLayout_3->addWidget(label_6);

        mininterval = new QLineEdit(layoutWidget);
        mininterval->setObjectName("mininterval");

        horizontalLayout_3->addWidget(mininterval);


        verticalLayout_7->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName("label_9");

        verticalLayout_3->addWidget(label_9);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName("label_8");

        verticalLayout_3->addWidget(label_8);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName("label_7");

        verticalLayout_3->addWidget(label_7);


        horizontalLayout_4->addLayout(verticalLayout_3);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        bplow = new QLineEdit(layoutWidget);
        bplow->setObjectName("bplow");

        verticalLayout_6->addWidget(bplow);

        bphigh = new QLineEdit(layoutWidget);
        bphigh->setObjectName("bphigh");

        verticalLayout_6->addWidget(bphigh);

        bporder = new QLineEdit(layoutWidget);
        bporder->setObjectName("bporder");

        verticalLayout_6->addWidget(bporder);


        horizontalLayout_4->addLayout(verticalLayout_6);


        verticalLayout_7->addLayout(horizontalLayout_4);


        verticalLayout_8->addLayout(verticalLayout_7);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(15);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, -1, -1, -1);
        save = new QPushButton(layoutWidget);
        save->setObjectName("save");

        horizontalLayout_5->addWidget(save);

        deleteButton = new QPushButton(layoutWidget);
        deleteButton->setObjectName("deleteButton");

        horizontalLayout_5->addWidget(deleteButton);

        lunchButton = new QPushButton(layoutWidget);
        lunchButton->setObjectName("lunchButton");

        horizontalLayout_5->addWidget(lunchButton);


        verticalLayout_8->addLayout(horizontalLayout_5);

        splitter->addWidget(layoutWidget);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        titre->setText(QCoreApplication::translate("MainWindow", "app beat", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "select preset", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "--port", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "--baudrate", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "--k-high", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "--k-low", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "--min-interval", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "--bp-low", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "--bp-high", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "--bp-order", nullptr));
        save->setText(QCoreApplication::translate("MainWindow", "save", nullptr));
        deleteButton->setText(QCoreApplication::translate("MainWindow", "delete", nullptr));
        lunchButton->setText(QCoreApplication::translate("MainWindow", "lunch", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
