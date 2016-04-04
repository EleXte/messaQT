#ifndef WINDOWCONFIG_H
#define WINDOWCONFIG_H

#include <QWidget>
#include <QSettings>
#include <QDebug>
#include <qsettings.h>
#include <qmessagebox.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QDir>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QTimer>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>


//class QPushButton;
//class QTextEdit;

class windowConfig : public QWidget
{
    Q_OBJECT
public:
    explicit windowConfig(QWidget *parent = 0);

   
	
	
	QSettings *settings;

signals:
void CDCONF_network();
void LoadConf();

	public slots :
void createDefaultCONF_network();			//Create default network config
void createDefaultCONF_system();			//Create default system config
void loadCONF_net();						//Load config file
void saveCONF_net();						//Save config

private:
	QHBoxLayout *createButtLayout();
	QVBoxLayout *createEditBox();
	QVBoxLayout *createMailBox();

	QComboBox *typeTransferText;
	QComboBox *typeChkSumText;
	QLineEdit *IPServerText;

	QSpinBox *portUDPText;
	QSpinBox *portTCPText;
	QSpinBox *pakSizeText;
	QSpinBox *pucketNumText;
	QSpinBox *sentMailPortText;
	QSpinBox *giveMailPortText;
	QLabel *networkConfigLabel;
	QLabel *mailConfigLabel;

	QLabel *portUDPLabel;
	QLabel *portTCPLabel;
	QLabel *pakSizeLabel;
	QLabel *pucketNumLabel;
	QLabel *IPServerLabel;
	QLabel *typeTransferLabel;
	QLabel *typeChkSumLabel;
	QLabel *sentMailPortLabel;
	QLabel *giveMailPortLabel;
	QPushButton *saveConfButton;
	QPushButton *cancelConfButton;
	QPushButton *DefaultConfButton;
	QPushButton *quitButton;

};

#endif // WINDOWCONFIG_H
