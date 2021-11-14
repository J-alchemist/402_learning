/********************************************************************************
** Form generated from reading UI file 'clientfiletcp.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTFILETCP_H
#define UI_CLIENTFILETCP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClientFileTcp
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QLineEdit *lineEditIP;
    QLabel *label_2;
    QLineEdit *lineEditPort;
    QPushButton *buttonConnect;
    QLabel *label_4;
    QProgressBar *progressBar;
    QTextEdit *textEdit;

    void setupUi(QWidget *ClientFileTcp)
    {
        if (ClientFileTcp->objectName().isEmpty())
            ClientFileTcp->setObjectName(QStringLiteral("ClientFileTcp"));
        ClientFileTcp->resize(400, 300);
        gridLayout = new QGridLayout(ClientFileTcp);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer = new QSpacerItem(136, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 2);

        label_3 = new QLabel(ClientFileTcp);
        label_3->setObjectName(QStringLiteral("label_3"));
        QFont font;
        font.setFamily(QStringLiteral("Algerian"));
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(158, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 3, 1, 2);

        label = new QLabel(ClientFileTcp);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        lineEditIP = new QLineEdit(ClientFileTcp);
        lineEditIP->setObjectName(QStringLiteral("lineEditIP"));

        gridLayout->addWidget(lineEditIP, 1, 1, 1, 3);

        label_2 = new QLabel(ClientFileTcp);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        lineEditPort = new QLineEdit(ClientFileTcp);
        lineEditPort->setObjectName(QStringLiteral("lineEditPort"));

        gridLayout->addWidget(lineEditPort, 2, 1, 1, 3);

        buttonConnect = new QPushButton(ClientFileTcp);
        buttonConnect->setObjectName(QStringLiteral("buttonConnect"));

        gridLayout->addWidget(buttonConnect, 2, 4, 1, 1);

        label_4 = new QLabel(ClientFileTcp);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        progressBar = new QProgressBar(ClientFileTcp);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(24);

        gridLayout->addWidget(progressBar, 3, 1, 1, 4);

        textEdit = new QTextEdit(ClientFileTcp);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        gridLayout->addWidget(textEdit, 4, 0, 1, 5);


        retranslateUi(ClientFileTcp);

        QMetaObject::connectSlotsByName(ClientFileTcp);
    } // setupUi

    void retranslateUi(QWidget *ClientFileTcp)
    {
        ClientFileTcp->setWindowTitle(QApplication::translate("ClientFileTcp", "Form", Q_NULLPTR));
        label_3->setText(QApplication::translate("ClientFileTcp", "\345\256\242\346\210\267\347\253\257", Q_NULLPTR));
        label->setText(QApplication::translate("ClientFileTcp", "\346\234\215\345\212\241\345\231\250ip\357\274\232", Q_NULLPTR));
        lineEditIP->setText(QApplication::translate("ClientFileTcp", "127.0.0.1", Q_NULLPTR));
        label_2->setText(QApplication::translate("ClientFileTcp", "\346\234\215\345\212\241\345\231\250\347\253\257\345\217\243\357\274\232", Q_NULLPTR));
        lineEditPort->setText(QApplication::translate("ClientFileTcp", "8080", Q_NULLPTR));
        buttonConnect->setText(QApplication::translate("ClientFileTcp", "connect", Q_NULLPTR));
        label_4->setText(QApplication::translate("ClientFileTcp", "\346\216\245\346\224\266\350\277\233\345\272\246\357\274\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ClientFileTcp: public Ui_ClientFileTcp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTFILETCP_H
