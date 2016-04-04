#include "mainwindow.h"
#include <QtWidgets>
#include "xmlviewer.hpp"

MainWindow::MainWindow(QMainWindow *parent) :
	QMainWindow(parent)
// ,   ui(new Ui::MainWindow)
{
//    ui->setupUi(this);
	
	this->resize(540, 960);
	
  statusLabel = new QLabel();
  statusLabel->setWordWrap(true);
  adresLine = new QLineEdit(tr(""));
  lineSend = new QLineEdit();
  lineprogres = new QLabel(tr("0/0"));
  textinfo = new QTextEdit;
  progres = new QProgressBar();

  listConnections = new QListWidget;
  if (!QFile::exists("settings.conf")) { /*createDefaultCONF(); */}
  settings = new QSettings(QDir::currentPath() + "/config/network.conf", QSettings::IniFormat);
  settings->setIniCodec("UTF-8");
  QString IP;
  QString PORT;
  IP = settings->value("network/server/main/").toString();
  PORT = settings->value("network/server/portUDP/").toString();
  adresLine->setText(IP+":"+PORT);
  PACET_SIZE = settings->value("network/server/PACKET_SIZE/").toInt();

  QHBoxLayout *adresLayout = new QHBoxLayout;
  adresLayout->addWidget(adresLine,70);

  QHBoxLayout *progresLayout = new QHBoxLayout;
  progresLayout->addWidget(progres, 87);
  progresLayout->addWidget(lineprogres, 13);

  QVBoxLayout *mainLayout = new QVBoxLayout;

  mainLayout->addLayout(progresLayout);
  mainLayout->addWidget(statusLabel);
  mainLayout->addLayout(adresLayout);
  mainLayout->addLayout(createButtonLoyat());

  mainLayout->addWidget(textinfo);

  mainLayout->addWidget(lineSend);
  mainLayout->addWidget(listConnections);
  

  QWidget *allWidgets = new QWidget;

  allWidgets->setLayout(mainLayout);

  setCentralWidget(allWidgets);
  createActions();
  createMenus();
  createStatusBar();

  setWindowTitle(tr("Messenger"));

  //QTimer* ptimer = new QTimer(this);
 
  //connect(ptimer, SIGNAL(timeout()), SLOT(slotTimerAnswer()));

  connect(listConnections, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(AdrListClick()));
  
}

MainWindow::~MainWindow()
{
//  delete ui;
}

void MainWindow::AdrListClick()
{
	//listConnections->setCurrentRow(2);
    //int nowItem = listConnections->currentItem;
   const QListWidgetItem* texting = listConnections->currentItem();
	adresLine->setText(texting->text());
}

void MainWindow::globalToNULL()
{
    fName = "";

}

void MainWindow::on_SendButton_clicked()
{
  on_AddButton_clicked();
if (listConnections->count ()!=-1)
  {
   //if( serverAn_status == 0){ startServerAnswer();}
   // sendMessage(lineSend->text());
  }
}

void MainWindow::readHost(QHostAddress &host, qint16 &port)
{
		if (!QFile::exists(QDir::currentPath() + "/config/network.conf")) {}// createDefaultCONF();}

		host = stngNetwork->value("network/serverIP/").toString();
		port = stngNetwork->value("network/serverPort/").toInt() - 1;

		adress = host;
		PACET_SIZE = stngNetwork->value("network/server/PACKET_SIZE/").toInt();
}

//void MainWindow::readHost(QHostAddress &host, qint16 &port)
//{
//	MainWindow config;
//	if (!QFile::exists("data base/config/network.conf")) {}// createDefaultCONF();}
//
//	host = config.stngNetwork->value("network/serverIP/").toString();
//	port = config.stngNetwork->value("network/serverPort/").toInt() - 1;
//
//	adress = host;
//	PACET_SIZE = config.stngNetwork->value("network/server/PACKET_SIZE/").toInt();
//}

void MainWindow::slotConnected()
{
    qDebug() << "Received the connected() signal";
}

void MainWindow::on_AddButton_clicked()
{
	//QHostAddress adr;
 //   qint16 host;
 //  readHost(adresLine->text () ,adr, host);
 //   qDebug() <<adr;
 //  qDebug() <<host;

}

//void MainWindow::on_listConnections_itemActivated(QListWidgetItem *item)
//{
// qsoket =  Socets[item->text().toInt()];
//// qsoket->open(QIODevice::ReadWrite);
//qDebug()<< qsoket->errorString();
//qDebug()<< qsoket->isOpen();
//qDebug()<< qsoket->isReadable();
//qDebug()<< qsoket->isSequential();
//qDebug()<< qsoket->isValid();
//qDebug()<< qsoket->isWritable();
//
//}

void MainWindow::FileDialog()
{
	fName = QFileDialog::getOpenFileName(this, QObject::tr("Open"), QString(),
		QObject::tr("All Files (*)")); //диалоговое окно выбора файла
	if (fName.isEmpty())
	{
		return;
}


    }

void MainWindow::slot_NetworkConfig()
{
	WindowCongif = new windowConfig();
	//connect(WindowCongif, SIGNAL(LoadConf()), this, SLOT(AdrListClick()));
	WindowCongif->show();
}


void MainWindow::createActions()
{
	connectAct = new QAction(tr("&Connect"), this);
	//connectAct->setShortcuts(QKeySequence::New);
	connectAct->setStatusTip(tr("Connectiing to host"));
	connect(connectAct, SIGNAL(triggered()), this, SLOT(newFile()));

	sendAct = new QAction(tr("&Send..."), this);
	//sendAct->setShortcuts(QKeySequence::Open);
	sendAct->setStatusTip(tr("Send select information. And dont asking how!"));
	connect(sendAct, SIGNAL(triggered()), this, SLOT(FileDialog()));

	adrBookAct = new QAction(tr("&Adressbook"), this);
	//adrBookAct->setShortcuts(QKeySequence::Save);
	adrBookAct->setStatusTip(tr("Open ROAD TO THE HELL"));
	connect(adrBookAct, SIGNAL(triggered()), this, SLOT(save()));

	netConfAct = new QAction(tr("Network &Config..."), this);
	//netConfAct->setShortcuts(QKeySequence::SaveAs);
	netConfAct->setStatusTip(tr("Change network setting"));
	connect(netConfAct, SIGNAL(triggered()), this, SLOT(slot_NetworkConfig()));

	exitAct = new QAction(tr("E&xit"), this);
	exitAct->setShortcuts(QKeySequence::Quit);
	exitAct->setStatusTip(tr("You realy need tip for this? REALY?!"));
	connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

	sysConfAct = new QAction(tr("Program &Config..."), this);
	//sysConfAct->setShortcuts(QKeySequence::Cut);
	sysConfAct->setStatusTip(tr("Change program setting"));
	connect(sysConfAct, SIGNAL(triggered()), this, SLOT(cut()));

	mailConfAct = new QAction(tr("Mail &Config..."), this);
	//mailConfAct->setShortcuts(QKeySequence::Copy);
	mailConfAct->setStatusTip(tr("This is all to config, understand?"));
	connect(mailConfAct, SIGNAL(triggered()), this, SLOT(copy()));

	sendMailAct = new QAction(tr("&New mail"), this);
	//sendMailAct->setShortcuts(QKeySequence::Paste);
	sendMailAct->setStatusTip("First time want sand mail? F*ing virgin..");
	connect(sendMailAct, SIGNAL(triggered()), this, SLOT(copy()));

	/*aboutAct = new QAction(tr("&About"), this);
	aboutAct->setStatusTip(tr("Show the application's About box"));
	connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));*/

	aboutQtAct = new QAction(tr("About &Qt"), this);
	aboutQtAct->setStatusTip(tr("Show for what we want this f*uk 'Qt'"));
	connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
    systMenu = menuBar()->addMenu(tr("&Prog"));
	systMenu->addAction(connectAct);
	systMenu->addSeparator();
	systMenu->addAction(exitAct);
	systMenu->addSeparator();
	systMenu->addAction(aboutQtAct);
	//systMenu->addAction(openAct);
	//fileMenu->addAction(saveAct);
	//fileMenu->addAction(saveAsAct);
	//fileMenu->addSeparator();

    confMenu = menuBar()->addMenu(tr("&Conf"));
	confMenu->addAction(sysConfAct);
	confMenu->addAction(netConfAct);
	confMenu->addAction(mailConfAct);

	confMenu->addSeparator();

    mailMenu = menuBar()->addMenu(tr("Mail"));
	mailMenu->addAction(adrBookAct);
	mailMenu->addAction(sendMailAct);

	chatMenu = menuBar()->addMenu(tr("Chat"));
	chatMenu->addAction(sendAct);
}

void MainWindow::createStatusBar()
{
	statusBar()->showMessage(tr("Ready"));
}

QHBoxLayout * MainWindow::createButtonLoyat()
{
	sendButton = new QPushButton(tr("&Send"));
	sendDataButton = new QPushButton(tr("&SendData"));
	quitButton = new QPushButton(tr("&Quit"));

	QHBoxLayout *buttonLayout = new QHBoxLayout;
	buttonLayout->addStretch(1);
	buttonLayout->addWidget(sendButton);
	buttonLayout->addStretch(1);
	buttonLayout->addWidget(sendDataButton);
	buttonLayout->addStretch(1);
	buttonLayout->addWidget(quitButton);
	buttonLayout->addStretch(1);

	connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(sendButton, SIGNAL(clicked()), this, SLOT(on_SendButton_clicked()));
	connect(sendDataButton, SIGNAL(clicked()), this, SLOT(FileDialog()));

	return buttonLayout;
}
