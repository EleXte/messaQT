#include "windowConfig.h"
#include <mainwindow.h>

windowConfig::windowConfig(QWidget *parent) : QWidget(parent)
{
	this->resize(450, 700);

	settings = new QSettings(QDir::currentPath() + "/config/network.conf", QSettings::IniFormat);
	settings->setIniCodec("UTF-8");

	connect(this, SIGNAL(CDCONF_network()), this, SLOT(createDefaultCONF_network()));
	connect(this, SIGNAL(LoadConf()), this, SLOT(loadCONF_net()));

	if (!QFile::exists("config/network.conf")) { emit CDCONF_network(); }
	qDebug() << QDir::currentPath();

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(createButtLayout());
	mainLayout->addStretch(3);
	mainLayout->addLayout(createEditBox());
	mainLayout->addStretch(1);
	mainLayout->addLayout(createMailBox());
	mainLayout->addStretch(5);

	this->setLayout(mainLayout);


	

	//QTimer::singleShot(1000, this, SLOT(loadCONF()));
	emit LoadConf();
	
}

void windowConfig::createDefaultCONF_network()
{
	QDir dir;
	if (!dir.exists("config"))
	{
		dir.mkdir("config");
	}
	//Default ini adress

	settings->beginGroup("network");
	settings->setValue("server/type/", "UDP");
	settings->setValue("server/check/", "CRC32"); 
	settings->setValue("server/main/", "192.168.1.101");
	settings->setValue("server/portUDP/", "6661");
	settings->setValue("server/portTCP/", "6661");
	settings->setValue("server/PACKET_SIZE/", "4000");
	settings->setValue("server/puckNumber/", "10");
	settings->endGroup();
	settings->beginGroup("mail");
	settings->setValue("SMTP port", "25");
	settings->setValue("POP3-IMAP port", "110");
	settings->endGroup();
	settings->beginGroup("getIP");
	settings->setValue("countIP/", "5");
	settings->setValue("port/", "6666");
	settings->setValue("insideIP/main1/", "192.168.137.129:33333");
	settings->setValue("insideIP/main2/", "130.216.0.104:33333");
	settings->setValue("insideIP/main3/", "130.216.0.105:33333");
	settings->setValue("insideIP/main4/", "130.216.0.105:33332");
	settings->setValue("insideIP/main5/", "192.168.137.1:33332");
	settings->endGroup();
	settings->sync();
	emit LoadConf();
}

void windowConfig::loadCONF_net()
{
	//QSettings conf;
	//int microInd = settings->value("getIP/countIP/").toInt();
	//for (int i = 1; i <= microInd; i++)
	//{
	//	QString mainName = "getIP/insideIP/main" + QString::number(i) + "/";
	//	QString ip = settings->value(mainName).toString();
	//	//listConnections->addItem(ip);
	//}
	typeTransferText->setCurrentText(settings->value("network/server/type/").toString());
	typeChkSumText->setCurrentText(settings->value("network/server/check/").toString());
	IPServerText->setText(settings->value("network/server/main/").toString());
	portUDPText->setValue(settings->value("network/server/portUDP/").toInt());
	portTCPText->setValue(settings->value("network/server/portTCP/").toInt());
	pakSizeText->setValue(settings->value("network/server/PACKET_SIZE").toInt());
	pucketNumText->setValue(settings->value("network/server/puckNumber").toInt());
	sentMailPortText->setValue(settings->value("mail/SMTP port").toInt());
	giveMailPortText->setValue(settings->value("mail/POP3-IMAP port").toInt());

	return;
}

void windowConfig::saveCONF_net()
{
	settings->setValue("network/server/type/", typeTransferText->currentText());
	settings->setValue("network/server/check/", typeChkSumText->currentText());
	settings->setValue("network/server/main/", IPServerText->text());
	settings->setValue("network/server/portUDP/", portUDPText->value());
	settings->setValue("network/server/portTCP/", portTCPText->value());
	settings->setValue("network/server/PACKET_SIZE/", pakSizeText->value());
	settings->setValue("network/server/puckNumber/", pucketNumText->value());
	settings->setValue("mail/SMTP port", sentMailPortText->value());
	settings->setValue("mail/POP3-IMAP port", giveMailPortText->value());

	settings->sync();

}

QHBoxLayout * windowConfig::createButtLayout()
{

	saveConfButton = new QPushButton(tr("&Save"));
	cancelConfButton = new QPushButton(tr("&Chancel"));
	DefaultConfButton = new QPushButton(tr("&Deafult"));
	quitButton = new QPushButton(tr("&Quit"));

	QHBoxLayout *buttonLayout = new QHBoxLayout;
	//buttonLayout->addWidget();
	buttonLayout->addStretch(1);
	buttonLayout->addWidget(saveConfButton);
	buttonLayout->addWidget(cancelConfButton);
	buttonLayout->addStretch(2);
	buttonLayout->addWidget(DefaultConfButton);
	buttonLayout->addWidget(quitButton);
	buttonLayout->addStretch(1);

	connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(DefaultConfButton, SIGNAL(clicked()), this, SLOT(createDefaultCONF_network()));
	connect(saveConfButton, SIGNAL(clicked()), this, SLOT(saveCONF_net()));
	connect(cancelConfButton, SIGNAL(clicked()), this, SLOT(loadCONF_net()));

	return buttonLayout;
}

QVBoxLayout * windowConfig::createEditBox()
{
	typeTransferText = new QComboBox;
	typeTransferText->addItem("UDP", QVariant(QString()));
	//typeTransferText->insertSeparator(2);
	typeTransferText->addItem("TCP", QVariant(QString()));

	typeChkSumText = new QComboBox;
	typeChkSumText->addItem("MD5", QVariant(QString()));
	//typeTransferText->insertSeparator(2);
	typeChkSumText->addItem("CRC32", QVariant(QString()));
	IPServerText = new QLineEdit;

	portUDPText = new QSpinBox;
	portUDPText->setRange(1024, 65535);
	portTCPText = new QSpinBox;
	portTCPText->setRange(1024, 65535);
	pakSizeText = new QSpinBox;
	pakSizeText->setRange(100, 8000);
	pucketNumText = new QSpinBox;
	pucketNumText->setRange(1, 30);
	networkConfigLabel = new QLabel(tr("Server configuration"));
	typeTransferLabel = new QLabel(tr("Transfer type:"));
	IPServerLabel = new QLabel(tr("Server IP:"));
	typeChkSumLabel = new QLabel(tr("Check metod:"));
	portUDPLabel = new QLabel(tr("UDP port:"));
	portTCPLabel = new QLabel(tr("TCP port:"));
	pakSizeLabel = new QLabel(tr("Packet size:"));
	pucketNumLabel = new QLabel(tr("Number of packet:"));

	QHBoxLayout  *editLayout = new QHBoxLayout;

	QVBoxLayout  *editLabelLayout = new QVBoxLayout;
	editLabelLayout->addWidget(typeTransferLabel);
	editLabelLayout->addWidget(typeChkSumLabel);
	editLabelLayout->addWidget(IPServerLabel);
	editLabelLayout->addWidget(portUDPLabel);
	editLabelLayout->addWidget(portTCPLabel);
	editLabelLayout->addWidget(pakSizeLabel);
	editLabelLayout->addWidget(pucketNumLabel);
	QVBoxLayout  *editTextLayout = new QVBoxLayout;
	editTextLayout->addWidget(typeTransferText);
	editTextLayout->addWidget(typeChkSumText);
	editTextLayout->addWidget(IPServerText);
	editTextLayout->addWidget(portUDPText);
	editTextLayout->addWidget(portTCPText);
	editTextLayout->addWidget(pakSizeText);
	editTextLayout->addWidget(pucketNumText);
	editLayout->addStretch(1);
	editLayout->addLayout(editLabelLayout);
	editLayout->addStretch(2);
	editLayout->addLayout(editTextLayout);
	editLayout->addStretch(1);

	QHBoxLayout  *microSerLabel = new QHBoxLayout;
	microSerLabel->addStretch(1);
	microSerLabel->addWidget(networkConfigLabel);
	microSerLabel->addStretch(1);

	QVBoxLayout  *mainConfigLay = new QVBoxLayout;
	mainConfigLay->addLayout(microSerLabel);
	mainConfigLay->addLayout(editLayout);


	return mainConfigLay;
}

QVBoxLayout * windowConfig::createMailBox()
{
	sentMailPortText = new QSpinBox;
	sentMailPortText->setRange(1, 80000);
	giveMailPortText = new QSpinBox;
	giveMailPortText->setRange(1, 80000);

	mailConfigLabel = new QLabel(tr("Mail configuration"));
	sentMailPortLabel = new QLabel(tr("Send mail port:"));
	giveMailPortLabel = new QLabel(tr("Give mail port:"));

	QHBoxLayout  *editLayout = new QHBoxLayout;

	QVBoxLayout  *editLabelLayout = new QVBoxLayout;
	editLabelLayout->addWidget(sentMailPortLabel);
	editLabelLayout->addWidget(giveMailPortLabel);

	QVBoxLayout  *editTextLayout = new QVBoxLayout;
	editTextLayout->addWidget(sentMailPortText);
	editTextLayout->addWidget(giveMailPortText);


	QHBoxLayout  *microSerLabel = new QHBoxLayout;
	microSerLabel->addStretch(1);
	microSerLabel->addWidget(mailConfigLabel);
	microSerLabel->addStretch(1);

	editLayout->addStretch(1);
	editLayout->addLayout(editLabelLayout);
	editLayout->addStretch(2);
	editLayout->addLayout(editTextLayout);
	editLayout->addStretch(1);

	QVBoxLayout  *mainConfigLay = new QVBoxLayout;
	mainConfigLay->addLayout(microSerLabel);
	mainConfigLay->addLayout(editLayout);

	return mainConfigLay;
}

void windowConfig::createDefaultCONF_system()
{

}
