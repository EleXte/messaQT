#include "xmlviewer.hpp"

XMLViewer::XMLViewer(QObject * parent) : QObject(parent) {
	
}

XMLViewer::~XMLViewer() {
	
}

QDomDocument XMLViewer::createXMLFile(QString adress)
{
	QFile XMLFile;
	QDomDocument MLP;
	QDomElement docElm = MLP.createElement("baseDate");
	MLP.appendChild(docElm);
	//MLP.createElement("message");
	//MLP.appendChild(docElm);
	//QTextStream out(&XMLFile);
	//MLP.save(out, 1);
	return MLP;
}

void XMLViewer::getXMLFile(QString fileName)
{
	QDomDocument domDoc;
	QFile        file(fileName);

	if (file.open(QIODevice::ReadOnly)) {
		if (domDoc.setContent(&file)) {
			QDomElement domElement = domDoc.documentElement();
//            loadXMLFile(fileName);
		}
		file.close();
	}

    return;
}

//QDomDocument XMLViewer::loadXMLFile(QString fileName)
//{
//	QDomNode domNode = domNode.firstChild();
//	QDomDocument domDoc;
//	QFile        file(fileName);
//
//	if (file.open(QIODevice::ReadOnly)) {
//		if (domDoc.setContent(&file)) {
//			QDomElement domElement = domDoc.documentElement();
//			while (!domNode.isNull()) {
//				if (domNode.isElement())
//				{
//					QDomElement domElement = domNode.toElement();
//				}
//				//loadXMLFile(domNode);
//				domNode = domNode.nextSibling();
//			}
//		}
//		file.close();
//	}
//
//	return domDoc;
//}

void XMLViewer::saveXMLFile()
{
	QDomDocument m_domDocLog;
	QDomDocument m_domElLog;
	QDomDocument domNode;
//	int m_iLenFileDataBase;
	// Пополнение архива
	m_domElLog.appendChild(domNode);
	int iLenLog = m_domDocLog.toString().length();
	if (iLenLog ) //> m_iLenFileDataBase)
	{
		QString strNameV = QDir::currentPath() + tr("/data");
		QDir dir(strNameV);
		// Удаляем предыдущую коприю
		bool b = dir.remove(tr("Архив1.xml"));
		// Переводим текущий архив в хранилище 1
		b = dir.rename(tr("Архив.xml"), tr("Архив1.xml"));
		// Сохраняем новый архив
		QFile file("data/Архив.xml");
		// Откроем выбранный файл для записи
		if (!file.open(QFile::WriteOnly | QFile::Text))
		{
			QMessageBox::warning(NULL, tr("Параметры связи приложений"),
				tr("Нет возможности открыть файл\n"
					"для записи архива"));
			return;
		}
		// Величина отступа в дереве
		const int IndentSize = 2;
		// Создание текстового потока для записи
		QTextStream out(&file);
		//Вариант записи
		m_domDocLog.save(out, IndentSize);
	}
}

void XMLViewer::checkXMLFile(QString adress)
{
	QFile file(adress);
	QDate curDay(QDate::currentDate());
	QDateTime filetime = QFileInfo(file).created();
	if (filetime.date() == curDay)
	{
		QTime checkTime = QDateTime::currentDateTime().time();
		checkTime.addSecs(-900);
		if (filetime.time() > checkTime)
		{
			return;
		}
	}
	else
	{
		file.remove();
	}
}

void XMLViewer::savePaketToXML(QString nameXML, QDomNode node)
{
	//проверяем устарел ли файл
	
	QDomDocument Arhiv;
	QFile file(nameXML);
	if (!file.exists())
	{
		Arhiv = createXMLFile(nameXML);
		qDebug() << Arhiv.toString();
	}
	else 
	{
		Arhiv.setContent(&file);
		qDebug() << Arhiv.toString();
	}
	QDomNode domDoc;
	//Подготавливаем для формирования нового архива
	QDomElement root = Arhiv.documentElement();
	//QString idioma = QDateTime::currentDateTime().toString();
	//QDomElement domElem = Arhiv.createElement(idioma);
	//Arhiv.appendChild(domElem);
	QDomNode needName;
	//Arhiv = loadXMLFile();
	//Arhiv.nextSiblingElement();
	QDomNode lost;
	lost = root.lastChild();
	//qDebug() << lost.toText();
	root.insertAfter(node, lost);
	//root.appendChild(node);
	Arhiv.appendChild(root);
	//Проверяем открываеться ли файл и урезаем его до нуля
	//if (!file.open(QIODevice::Truncate))
	//{
	//	QMessageBox::warning(NULL, tr("Параметры связи приложений"),
	//		tr("Нет возможности открыть файл\n"
	//			"для записи архива"));
	//	return;
	//}
	//file.close();
	// Откроем выбранный файл для записи
//	if (file.open(QIODevice::WriteOnly)) {
	file.open(QIODevice::Truncate);
	file.close();
	file.open(QIODevice::WriteOnly);
		QTextStream(&file) << Arhiv.toString();
		file.close();
	//}
}