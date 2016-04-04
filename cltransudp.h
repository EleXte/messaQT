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

	QUdpSocket *qserver;				//������ ������� ��������
	QUdpSocket *qserverAn;				//������ ������� ������ ������
	QMap<int, QUdpSocket *> Socets;

	void startUDPsok();					//������ ������� ��������
	void stopUDPsok();					//���������� ������� ��������
	void startUDPsokAns();				//������ ������� ��� ������ ������
	void stopUDPsokAns();				//���������� ������� ������ ������

	int sokUDP_status;					//������ ������� ��������
	int sokUDPAn_status;				//������ ������� ������ ������
	QHostAddress adress;				//IP ����� ����������
	quint16 port;						//Port to send information
	quint16 numbOfPak;					//Number of paket in 1 send cycle
	quint64 PACET_SIZE;					//������ ������������ ������
	quint64 inDataSize;					//����������� ������ ���������/������������� �����
	quint64 fileSize;					//������ ������ ������������/������������� �����
	QByteArray transmitData;			//transmitted data or data to transmit
	QFile *file;						//���� ����

signals:

	public slots :
	void readAnswer();                      //��������� ������
	void readTransaction(QByteArray);		//��������� ����� � ���������
	void lauch();                           //������ ������� ������ ��������

private:

	QSettings *settings;
	void newcon();                                                                                  //��������� ����������� �� ���� � �����
	void sendFileInf(quint8 TYPE_BlackMessa, QByteArray info, QHostAddress &host, quint16 &port);	//���������������� ��������
	void prerapeToSendFile(QString filePath);               										//���������� � ��������
	void sendMessage(QString msg);                                                                  //�������� ���������� ���������
	void globalToNULL();																			//������� ����� ����������
	void nextSend();																				//�������� ���������� ������
	QString getMD5(QByteArray &info);                                                               //������� ��������� ����������� �����

	//crc check
	quint32 crc_table[256];
	QMap<int, quint32> instances;
	QString getCRC32(QByteArray &data);
	void init_crc_table();

	//������ ������
	enum answerType { trueA = 1, falseA = 2, successA = 3, scsEnd = 4 };
	//���� �������
	enum sendType { TYPE_MESSAGE = 0, TYPE_FILE = 1, TYPE_ANSWER = 2, TYPE_CHKSUM = 7, TYPE_HEAD = 9, TYPE_LASTPAK = 20, TYPE_ABORT = 99 };

	QProgressBar* ProgressBar;
};

#endif // CLTRANSUDP_H
