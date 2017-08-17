#ifndef MAINSOCKET_H
#define MAINSOCKET_H

#include <QLabel>
#include <QThread>
#include <QObject>
#include <QDateTime>
#include <QtNetwork/QUdpSocket>

#include "renderarea.h"

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

struct packet_message {
    char start = -1;
    uint32_t message = 0;
    char end = 1;

    bool check() {
        if (start == -1 && end == 1 && message > 0)
            return true;
        return false;
    }
};

struct packet_sync{
    char start = -1;
    uint32_t size = 0;
    uint32_t num_of_packets = 0;
    char end = 1;

    bool check() {
        if (start == -1 && end == 1 && size > 0 && num_of_packets > 0)
            return true;
        return false;
    }
};

struct packet_data{
    char start = -1;
    uint32_t size = 0;
    uint32_t num_of_packet = 0;
    uint32_t num_of_packets = 0;
    char data[64000];
    char end = 1;

    bool check() {
        if (start == -1 && end == 1 && size > 0 && num_of_packets > 0)
            return true;
        return false;
    }
};

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//


class SocketThread : public QThread{

public:
    bool* s_connect;
    QUdpSocket* socket;
    QLabel* logs;
    RenderArea* renderer;

private:
    void log(QString msg){
        logs->setText(logs->text() + msg + "\n");
    }

    void run() override;

};


// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//


class MainSocket : public QObject {
    Q_OBJECT

public:
    explicit MainSocket(QObject *parent = nullptr);

    void Connect();
    void Disconnect();

    QLabel* logs;
    RenderArea* renderer;

signals:

public slots:

private:

    bool s_connect = false;
    SocketThread* main_thread;
    QUdpSocket* socket;


    void log(QString msg);

};

#endif // MAINSOCKET_H
