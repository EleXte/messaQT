#pragma once
#include <QObject>
#include <QFile>
#include <QDir>
#include <QDomNode>
#include <QDebug>
#include <QMessageBox>
#include <qdatetime.h>

class XMLViewer : public QObject {
	Q_OBJECT

public:
	XMLViewer(QObject * parent = Q_NULLPTR);
	~XMLViewer();
	//QDomDocument loadXMLFile(QString fileName); //Загрузка XML файла
	void saveXMLFile(); //Сохранение XML файла
	void checkXMLFile(QString adress); //Проверка XML файла
    void getXMLFile(QString fileName); //Получение XML файла
	void savePaketToXML(QString nameXML, QDomNode node); //Сохранение пакета в файл XML
	QDomDocument createXMLFile(QString adress);

private:
    //const QDomNode& node;
};
