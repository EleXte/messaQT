#include "cltransudp.h"

clTransUDP::clTransUDP(QString path, QThread *parent) : QThread(parent)
{
	//newcon();
	startUDPsok();
	startUDPsokAns();
	init_crc_table();

	settings = new QSettings(QDir::currentPath() + "/config/network.conf", QSettings::IniFormat);
	settings->setIniCodec("UTF-8");
	adress = settings->value("network/server/main/").toString();
	port = settings->value("network/server/portUDP/").toInt();
	PACET_SIZE = settings->value("network/server/PACKET_SIZE/").toInt();
	numbOfPak = settings->value("network/server/puckNumber/").toInt();

	prerapeToSendFile(path);
}

void clTransUDP::lauch()
{
	//newcon();
	//startUDPsok();
	//startUDPsokAns();
	//prerapeToSendFile(QString filePath);
}

void clTransUDP::prerapeToSendFile(QString filePath)
{
	QString fName;
	file = new QFile(filePath);
	if (file->open(QFile::ReadOnly))
	{
		fileSize = file->bytesAvailable();
		ProgressBar->setMaximum(fileSize);
		fName = file->fileName();
		fName = fName.remove(0, fName.lastIndexOf("/") + 1);
	}
	sendFileInf(TYPE_HEAD, fName.toLocal8Bit(), adress, port);
	nextSend();
}

void clTransUDP::nextSend()
{
	QByteArray sendInfo;
	for (int i = 0; i < 10; i++)
	{
		sendInfo = transmitData.mid((quint64(PACET_SIZE)*i), quint64(PACET_SIZE));
		inDataSize += sendInfo.length();
		sendFileInf(TYPE_FILE, sendInfo, adress, port);
		ProgressBar->setValue(inDataSize);
		if (inDataSize >= fileSize)
		{
			sendFileInf(TYPE_LASTPAK, getCRC32(transmitData).toLocal8Bit(), adress, port); //завершаем передачу
			qDebug() << QString::fromUtf8("Last paket send");
			return;
		}
	}
	sendFileInf(TYPE_CHKSUM, getCRC32(transmitData).toLocal8Bit(), adress, port);
}

void clTransUDP::sendFileInf(quint8 type, QByteArray sendInfo, QHostAddress &adress, quint16 &port)
{
	QByteArray data;
	QDataStream out(&data, QIODevice::WriteOnly);
	out << quint8(type);
	if (type == TYPE_FILE)
	{
		out << sendInfo;
		qDebug() << QString::fromUtf8("FILE");
	}
	if (type == TYPE_MESSAGE)
	{
		out << sendInfo;
		/**/
		qDebug() << QString::fromUtf8("MSG");
	}
	if (type == TYPE_ANSWER || type == TYPE_CHKSUM || type == TYPE_LASTPAK || type == TYPE_ABORT)
	{
		qDebug() << QString::fromUtf8("Send");
		out << sendInfo;
	}
	if (type == TYPE_HEAD)
	{
		qDebug() << QString::fromUtf8("HEAD");
		out << sendInfo;
		out << fileSize;
		out << PACET_SIZE;
	}

	//Send data
	qserver->writeDatagram(data, adress, port);
	qserver->waitForBytesWritten();
}

void clTransUDP::readTransaction(QByteArray data)
{
	/*
	DATA READ
	*/
	// data.resize(qserver->pendingDatagramSize());
	QDataStream in(&data, QIODevice::ReadOnly);
	QByteArray sendInfo;
	quint8 type;
	in >> type;
	if (type == TYPE_FILE)
	{
		qDebug() << QString::fromUtf8("FILE_IN");
		in >> sendInfo;
		transmitData += sendInfo;
		return;
	}
	if (type == TYPE_MESSAGE)
	{
		qDebug() << QString::fromUtf8("MSG_IN");
		QByteArray message;
		in >> message;
		//textinfo->append("Text:" + message);
		sendInfo.append(successA);
		sendFileInf(TYPE_ANSWER, sendInfo, adress, port);
		return;
	}
	if (type == TYPE_CHKSUM)
	{
		QString ctrlSum; //Control Sum
		in >> ctrlSum;
		port = 6660;
		qDebug() << QString::fromUtf8("CHKSUM_IN");
		//Check control sum of get information
		if (ctrlSum == getCRC32(transmitData))
		{
			//file->open(QFile::Append);
			file->write(transmitData);
			inDataSize += transmitData.length();
			sendInfo.append(trueA);
		}
		else
		{
			qDebug() << QString::fromUtf8("CHKSUM_False");
			sendInfo.append(falseA);
		}
		transmitData = NULL;
		sendFileInf(TYPE_ANSWER, sendInfo, adress, port);
		return;
	}
	if (type == TYPE_HEAD)
	{
		qDebug() << QString::fromUtf8("HEAD_IN");
		QString fName;
		in >> fName;
		in >> fileSize;
		in >> PACET_SIZE;
		if (fName != "")
		{
			qDebug() << "Head false";
			return;
		}
		file = new QFile(fName);
		if (file->exists())
		{
			fName.insert(fName.lastIndexOf("."), "(" + QDateTime::currentDateTime().toString() + ")");
			file->setFileName(fName);
		}
		file->open(QFile::Append);
		return;
	}
	if (type == TYPE_LASTPAK)
	{
		/*^-^*/
		QString ctrlSum; //Control Sum
		in >> ctrlSum;
		port = 6660;
		qDebug() << QString::fromUtf8("LASTPAK_IN");
		//Check control sum of get information
		if (ctrlSum == getCRC32(transmitData))
		{
			file->write(transmitData);
			file->close();
			globalToNULL();
			stopUDPsok();
			qDebug() << QString::fromUtf8("Last paket save");
			sendInfo.append(scsEnd);
			sendFileInf(TYPE_ANSWER, sendInfo, adress, port);
			terminate();
			return;
		}
		else
		{
			sendInfo.append(falseA);
			transmitData = NULL;
			sendFileInf(TYPE_ANSWER, sendInfo, adress, port);
			return;
		}
	}
	if (type == TYPE_ABORT)
	{
		/*O-O*/
		return;
	}

}

void clTransUDP::readAnswer()
{
	QByteArray data;
	QDataStream in(&data, QIODevice::ReadOnly);
	data.resize(qserverAn->pendingDatagramSize());
	QHostAddress *address = new QHostAddress();
	qserverAn->readDatagram(data.data(), data.size(), address);
	quint8 type;
	in >> type;
	if (type == TYPE_ANSWER) {
		uint answCcode; //Code of successful transation
		in >> answCcode;
		switch (answCcode)
		{
		case trueA:
		{
			qDebug() << "Answer: true";
			if (file == NULL) { return; }
			if (inDataSize > 0) { file->seek(inDataSize); }
			transmitData = file->read(quint64(PACET_SIZE * 10));
			nextSend();
			break;
		}
		case falseA:
		{
			qDebug() << "Answer: false";
			inDataSize = inDataSize - transmitData.length();
			ProgressBar->setValue(inDataSize);
			file->seek(inDataSize);
			nextSend();
			break;
		}
		case successA:
		{
			qDebug() << "Answer: success";
			stopUDPsokAns();
			break;
		}
		case scsEnd:
		{
			qDebug() << "Answer: scsEnd";
			file->close();		//ty-ty
			ProgressBar->setValue(inDataSize);
			globalToNULL();		//ty-ty
			break;
		}
		}
		return;
	}
}

void clTransUDP::globalToNULL()
{
	fileSize = 0;
	inDataSize = 0;
	transmitData = NULL;
	file = NULL;

}

QString clTransUDP::getMD5(QByteArray &info)
{
	QString sum = QString(QCryptographicHash::hash((info), QCryptographicHash::Md5).toHex());
	return sum;
}

QString clTransUDP::getCRC32(QByteArray &data)
{
	quint32 crc;
	char buffer[16000];
	int len, i, k;
	QByteArray tempor;
	uint s;
	s = 16000;

	crc = 0xFFFFFFFFUL;

	for (k = 0; k < ceil(data.size() / s); k++)
	{
		tempor = data.mid((qint64(s)*k), qint64(s));
		len = tempor.size();
		memcpy(buffer, tempor.data(), len);
		for (i = 0; i < len; i++)
			crc = crc_table[(crc ^ buffer[i]) & 0xFF] ^ (crc >> 8);
	}
	QString sum;
	sum += (crc ^ 0xFFFFFFFFUL);
	return sum;
}

void clTransUDP::init_crc_table()
{
	quint32 crc;
	// initialize CRC table
	for (int i = 0; i < 256; i++)
	{
		crc = i;
		for (int j = 0; j < 8; j++)
			crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;
		crc_table[i] = crc;
	}
}

void clTransUDP::startUDPsok()
{
	qserver = new QUdpSocket(this);
	connect(qserver, SIGNAL(readyRead()), this, SLOT(readTransaction()));
	if (!qserver->bind(port, QUdpSocket::ShareAddress) && sokUDP_status == 0) {
		qDebug() << QObject::tr("Unable to start the server: %1.").arg(qserver->errorString());
	}
	else {
		sokUDP_status = 1;
		qDebug() << QString::fromUtf8("Server start successfull.");
	}
}

void clTransUDP::startUDPsokAns()
{
	qserverAn = new QUdpSocket(this);
	connect(qserverAn, SIGNAL(readyRead()), this, SLOT(readAnswer()));
	if (!qserverAn->bind(6660, QUdpSocket::ShareAddress) && sokUDPAn_status == 0) {
		qDebug() << QObject::tr("Unable to start the server: %1.").arg(qserverAn->errorString());
	}
	else {
		sokUDPAn_status = 1;
		qDebug() << QString::fromUtf8("Answer server start successfull.");
	}
}

void clTransUDP::stopUDPsok()
{
	if (sokUDP_status == 1)
	{
		foreach(int i, Socets.keys())
		{
			QTextStream os(Socets[i]);
			os.setAutoDetectUnicode(true);
			os << QDateTime::currentDateTime().toString() << "\n";
			Socets[i]->close();
			Socets.remove(i);
		}
		qserver->close();
		qDebug() << QString::fromUtf8("Send server stop success.");
		sokUDP_status = 0;
	}
}

void clTransUDP::stopUDPsokAns()
{
	if (sokUDPAn_status == 1)
	{
		foreach(int i, Socets.keys())
		{
			QTextStream os(Socets[i]);
			os.setAutoDetectUnicode(true);
			os << QDateTime::currentDateTime().toString() << "\n";
			Socets[i]->close();
			Socets.remove(i);
		}
		qserverAn->close();
		qDebug() << QString::fromUtf8("Answer server stop success.");
		sokUDPAn_status = 0;
	}
}
