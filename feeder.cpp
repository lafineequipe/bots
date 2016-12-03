#include "feeder.h"

Feeder::Feeder(QString name, int limit, QObject *parent) : QObject(parent)
{
    this->setLimit(limit);
    this->setName(name);

    QNetworkAccessManager *nam = new QNetworkAccessManager(this);

    connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinished(QNetworkReply*)));


    QString url = "http://ichart.finance.yahoo.com/table.csv?s="
            + this->getName() + "&a=12&b=3&c=2015&d=12&e=2&f=2016&g=d&ignore=.csv&f=sopl1";

    QNetworkRequest request = QNetworkRequest(QUrl(url));
    request.setRawHeader("Content-Type", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    nam->get(request);
}

void Feeder::onFinished(QNetworkReply* reply){
    QString text = reply->readAll();
    QStringList lines = text.split('\n');

    lines.removeFirst(); // rm header

    for(int index = 0; index < lines.size(); ++index) {
        if (index >= this->getLimit())
            return;

        auto columns = lines[index].split(',');
        auto date = columns[0];
        auto close = columns[4];

        qDebug() << date + " " + close;
    }

    /*if(reply->error() == QNetworkReply::NoError)
        qDebug() << QObject::tr(reply->readAll());
    else
        qDebug() << reply->errorString();*/
}
