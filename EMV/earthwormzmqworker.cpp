#include "earthwormzmqworker.h"

void EarthWormZMQWorker::run()
{
    QSettings qsettings;

    QString IP = qsettings.value("EW/IP", "Error").toString();
    QString Port = qsettings.value("EW/Port", "Error").toString();
    QString URL = QString("tcp://") + IP + QString(":") + Port;

    qDebug() << URL << endl;

    context = new zmq::context_t(1);
    subscriber = new zmq::socket_t(*context, ZMQ_SUB);

    try {
        qDebug() << URL.toLatin1().data() << endl;
        subscriber->connect(URL.toLatin1().data());
    }
    catch (const zmq::error_t& error) {
        QString errorMessage(error.what());
        qDebug() << errorMessage << endl;
    }

    //  Subscribe to export zmq
    const char *filter = "EW_ZMQ:";
    subscriber->setsockopt(ZMQ_SUBSCRIBE, filter, strlen (filter));

    while (true) {
        zmq::message_t update;

        subscriber->recv(&update);
        qDebug() << "Retured from Subscriber.recv()\n";

        QString message = QString::fromLatin1(static_cast<char*>(update.data()), update.size());

        qDebug() << message << endl;

        if (!message.contains("<DIAGNOSTIC>"))
            emit ReceivedHypoMessage(message);

//        QThread::msleep(10);
    }

    delete context;

}

