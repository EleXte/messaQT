#ifndef CLTRANSUDP_H
#define CLTRANSUDP_H

#include <QObject>
#include <QThread>
#include <QtNetwork>
#include <qudpsocket.h>
#include <QDebug>
#include <QFile>
#include <QProgressBar>

class clTransUDP : public QThread
{
	Q_OBJECT
public:
	explicit clTransUDP(QString path, QThread *parent = 0);

	QUdpSocket *qserver;				//Статус сервера передачи
	QUdpSocket *qserverAn;				//Статус сервера приема ответа
	QMap<int, QUdpSocket *> Socets;

	void startUDPsok();					//Запуск сервера передачи
	void stopUDPsok();					//Выключение сервера передачи
	void startUDPsokAns();				//запуск сервера для приема ответа
	void stopUDPsokAns();				//Выключение сервера приема ответа

	int sokUDP_status;					//Статус сервера передачи
	int sokUDPAn_status;				//Статус сервера приема ответа
	QHostAddress adress;				//IP адрес получателя
	quint16 port;						//Port to send information
	quint16 numbOfPak;					//Number of paket in 1 send cycle
	quint64 PACET_SIZE;					//Размер передаваемых блоков
	quint64 inDataSize;					//Фактический размер принятого/отправленного файла
	quint64 fileSize;					//Полный размер принимаемого/отправляемого файла
	QByteArray transmitData;			//transmitted data or data to transmit
	QFile *file;						//Весь файл

signals:

	public slots :
	void readAnswer();                      //получение ответа
	void readTransaction(QByteArray);		//получение файла с проверкой
	void lauch();                           //Запуск функций начала передачи

private:

	QSettings *settings;
	void newcon();                                                                                  //Проверяем подключение на порт и адрес
	void sendFileInf(quint8 TYPE_BlackMessa, QByteArray info, QHostAddress &host, quint16 &port);	//Непосредственная отправка
	void prerapeToSendFile(QString filePath);               										//Подготовка к отправке
	void sendMessage(QString msg);                                                                  //Отправка текстового сообщения
	void globalToNULL();																			//Очистка вссех переменных
	void nextSend();																				//Отправка следующего набора
	QString getMD5(QByteArray &info);                                                               //Функция получения контрольной суммы

	//crc check
	quint32 crc_table[256];
	QMap<int, quint32> instances;
	QString getCRC32(QByteArray &data);
	void init_crc_table();

	//СТАТУС ОТВЕТА
	enum answerType { trueA = 1, falseA = 2, successA = 3, scsEnd = 4 };
	//ТИПЫ ПЕРЕДАЧ
	enum sendType { TYPE_MESSAGE = 0, TYPE_FILE = 1, TYPE_ANSWER = 2, TYPE_CHKSUM = 7, TYPE_HEAD = 9, TYPE_LASTPAK = 20, TYPE_ABORT = 99 };

	QProgressBar* ProgressBar;
};

#endif // CLTRANSUDP_H
