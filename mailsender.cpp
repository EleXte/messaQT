#include "mailsender.h"

MailSender::MailSender(QWidget *parent) : QWidget(parent)
{
QVBoxLayout *mainLayout = new QVBoxLayout;

mainLayout->addLayout(subHeadLayout());
mainLayout->addLayout(textAndAttachLayout());
mainLayout->addLayout(buttonSendLayout());
mainLayout->addLayout(buttonAdressLayout());

this->setLayout(mainLayout);

}

QVBoxLayout *MailSender::subHeadLayout()
{
    QVBoxLayout *tmpVlay = new QVBoxLayout;
    QHBoxLayout *tmpVlay2 = new QHBoxLayout;
    rcptToLabel = new QLabel("Recipient");
    rcptToCopyLabel = new QLabel("Copy");
    SubjectLabel = new QLabel("Subject");

    rcptToText = new QLineEdit();
    rcptToCopyText = new QLineEdit();
    SubjectText = new QLineEdit();

    rcptMenuButt = new QPushButton("Recipient Add");
    rcptMenuCopyButt = new QPushButton("Copy Add");

    tmpVlay->addWidget(rcptToLabel);
    tmpVlay->addWidget(rcptToText);

    tmpVlay->addWidget(rcptToCopyLabel);
    tmpVlay->addWidget(rcptToCopyText);

    tmpVlay->addWidget(SubjectLabel);
    tmpVlay->addWidget(SubjectText);

    tmpVlay2->addWidget(rcptMenuButt);
    tmpVlay2->addWidget(rcptMenuCopyButt);
    tmpVlay->addLayout(tmpVlay2);

    return tmpVlay;
}

QVBoxLayout *MailSender::textAndAttachLayout()
{
    QVBoxLayout *tmpVlay = new QVBoxLayout;

    textMailLabel = new QLabel("Mail Text");
    attachMailLabel = new QLabel("Attachments");
    mailText = new QTextEdit();
    attachList = new QListWidget();
    addAttachButt = new QPushButton("Add Attach");

    tmpVlay->addWidget(textMailLabel);
    tmpVlay->addWidget(mailText);

    tmpVlay->addWidget(attachMailLabel);
    tmpVlay->addWidget(attachList);

    tmpVlay->addWidget(addAttachButt);

    return tmpVlay;
}

QHBoxLayout *MailSender::buttonSendLayout()
{
    QHBoxLayout *tmpVlay = new QHBoxLayout;

    sendMailButt = new QPushButton("Send");
    closeMailButt = new QPushButton("Close");

    tmpVlay->addWidget(sendMailButt);
    tmpVlay->addWidget(closeMailButt);

    return tmpVlay;
}

QVBoxLayout *MailSender::buttonAdressLayout()
{
    QVBoxLayout *tmpVlay = new QVBoxLayout;

    return tmpVlay;

}

