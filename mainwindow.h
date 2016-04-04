#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <x86intrin.h>
#include <QMainWindow>
#include <QWidget>
#include <QString>
#include <QStringList>
#include <QtNetwork>
#include <QDebug>
#include <QListView>
#include <qdatetime.h>
#include <qinputdialog.h>
#include <QListWidget>
#include <QFile>
#include <QFileDialog>
#include <qsettings.h>
#include <qdatetime.h> 
#include <qtimer.h>
#include <QMenu>
#include <QMenuBar>
#include <qmessagebox.h>
#include <cltransudp.h>
#include <windowConfig.h>

class QLabel;
class QPushButton;
class QLineEdit;
class QTextEdit;
class QListWidget;
class QProgressBar;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QMainWindow *parent = 0);
    ~MainWindow();

	QSettings *settings;
	QSettings *stngNetwork;
	void createDefaultCONF();			//Восстановление базового конфиг файла
	QTimer* ptimer;
	windowConfig *WindowCongif;

private slots:
    void on_SendButton_clicked();
    void slotConnected();
    void on_AddButton_clicked();
	void AdrListClick();		
	void FileDialog();						//Выбираем файл для передачи
	void slot_NetworkConfig();
	
private:
	/*--Создаем меню--*/
	void createMenus();
	void createActions();
	void createStatusBar();
	QHBoxLayout * createButtonLoyat();
	/*--Создали меню--*/
   

	QHostAddress adress;
	qint16 ports;

	void readHost(QHostAddress &host, qint16 &port);
	void globalToNULL();									//Очистка вссех переменных

	qint64 PACET_SIZE;										//Размер передаваемых блоков
	QString fName;											//имя принимаемого файла
	QFile *file;											//Весь файл

	/*--Элементы окна--*/
	QLabel *statusLabel;
	QPushButton *quitButton;
	QPushButton *sendButton;
	QPushButton *sendDataButton;
	QLineEdit *adresLine;
	QLineEdit *lineSend;
	QLabel *lineprogres;
	QTextEdit *textinfo;
	QListWidget *listConnections;
	QProgressBar *progres;
	/*--конец--*/

	/*--Переменные меню--*/
	QMenu *systMenu;
	QMenu *confMenu;
	QMenu *mailMenu;
	QMenu *fileMenu;
	QMenu *chatMenu;
    QAction *connectAct; //
    QAction *exitAct; //
    QAction *sysConfAct; //
    QAction *netConfAct; //
    QAction *mailConfAct; //
    QAction *adrBookAct; //
	QAction *sendMailAct;
    QAction *sendAct; //
    QAction *aboutQtAct; //
	/*--конец Переменные меню--*/

};

#endif // MAINWINDOW_H
