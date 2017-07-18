#ifndef EARTHWORMZMQWORKER_H
#define EARTHWORMZMQWORKER_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QSettings>

#include <zmq.hpp>

class EarthWormZMQWorker : public QThread
{
    Q_OBJECT;

public:
    EarthWormZMQWorker(QObject* parent = Q_NULLPTR) : QThread{parent} {}   // Initalize in run

signals:
    void ReceivedHypoMessage(QString message);

private:
    void run() override;

    // *** Members
private:
    // No initialization here, only in run()
    zmq::context_t * context {};
    zmq::socket_t * subscriber {};

};

#endif // EARTHWORMZMQWORKER_H
