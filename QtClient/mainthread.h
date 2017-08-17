#ifndef MAINTHREAD_H
#define MAINTHREAD_H

#include <QLabel>
#include <QThread>
#include <QDateTime>
#include "renderarea.h"
#include <QtNetwork/QUdpSocket>

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

class MainThread : public QThread {

public:
    MainThread();
    RenderArea* renderer;
    QLabel* logs;

    void Connect();
    void Disconnect();

private:

    void log(QString msg);
    void run() override;

    QUdpSocket* socket;
    bool s_connect = false;



};

#endif // MAINTHREAD_H
