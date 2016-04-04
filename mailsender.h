#ifndef MAILSENDER_H
#define MAILSENDER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QDir>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QListWidget>

#include <QDebug>

class MailSender : public QWidget
{
    Q_OBJECT
public:
    explicit MailSender(QWidget *parent = 0);

signals:

public slots:

private:
    QVBoxLayout *subHeadLayout();
    QVBoxLayout *textAndAttachLayout();
    QHBoxLayout *buttonSendLayout();
    QVBoxLayout *buttonAdressLayout();

	QLabel *rcptToLabel;
	QLabel *rcptToCopyLabel;
	QLabel *SubjectLabel;
	QLabel *textMailLabel;
	QLabel *attachMailLabel;

	QLineEdit *rcptToText;
	QLineEdit *rcptToCopyText;
	QLineEdit *SubjectText;

	QTextEdit *mailText;
	QListWidget *attachList;

	QPushButton *sendMailButt;
	QPushButton *closeMailButt;
	QPushButton *rcptMenuButt;
	QPushButton *rcptMenuCopyButt;
	QPushButton *addAttachButt;

};

#endif // MAILSENDER_H
