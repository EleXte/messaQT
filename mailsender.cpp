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

