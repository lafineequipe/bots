#ifndef FEEDER_H
#define FEEDER_H

#include <QDebug>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QObject>
#include <QNetworkReply>
#include <QNetworkRequest>

class Feeder : public QObject
{
    Q_OBJECT
public:
    explicit Feeder(QString, int limit = 15, QObject *parent = 0);

    void setName(const QString& name) { Name = name; }
    const QString& getName() const { return Name; }

    void setLimit(int limit) { Limit = limit; }
    int getLimit() const { return Limit; }

private:
    QString Name;
    int Limit;

signals:

public slots:
    void onFinished(QNetworkReply* reply);
};

#endif // FEEDER_H
