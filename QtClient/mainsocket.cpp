#include "mainsocket.h"

MainSocket::MainSocket(QObject *parent) : QObject(parent) {
    socket = new QUdpSocket(this);
    main_thread = new SocketThread();
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

void MainSocket::log(QString msg){
    if(logs != nullptr)
        logs->setText(logs->text() + msg + "\n");
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

void MainSocket::Connect() {
    socket->connectToHost("192.168.1.13", 27015, QIODevice::ReadWrite);

    packet_message s_msg;
    s_msg.message = 4;
    if(socket->write((char*)&s_msg, sizeof(packet_message)) != -1){
        log("Send request to connet");

        qint64 start_time = QDateTime::currentMSecsSinceEpoch();
        for(;;){
            renderer->fps = 100;
            if(socket->read((char*)&s_msg, sizeof(packet_message)) != -1){
                if(s_msg.check() && s_msg.message == 2){
                    s_connect = true;
                    break;
                }
            }

            if(QDateTime::currentMSecsSinceEpoch() - start_time > 3000)
                break;
        }



        if(s_connect){
            log("Connected to server\nStart main Thread");
            main_thread->s_connect = &s_connect;
            main_thread->socket = socket;
            main_thread->logs = logs;
            main_thread->renderer = renderer;
            main_thread->start(QThread::HighPriority);
        }
        else{
            log("Can't connect to server");
        }



    }
    else{
        log("Can't send request to connect");
    }


}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

void MainSocket::Disconnect() {
    s_connect = false;
    packet_message s_msg;
    s_msg.message = 5;
    socket->write((char*)&s_msg, sizeof(packet_message));
    log("Disconnect");
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

void SocketThread::run() {
    packet_sync last_sync, sync;
    packet_data* last_data,* data;


    while((*s_connect)){

        if(socket->read((char*)&sync, sizeof(packet_sync)) != -1 && sync.check()){
            renderer->fps = 100;
//            p_t = a_t;
//            a_t = QDateTime::currentMSecsSinceEpoch();
//            renderer->fps = a_t - p_t;

//            data = new packet_data[sync.num_of_packets];
//            log("recive: " + QString::number(sync.num_of_packets) + "  size: " + QString::number(sync.size));
//            for (int i = 0; i < sync.num_of_packets; ++i) {
//                if(socket->read((char*)&data[i], sizeof(packet_data)) != -1 && data[i].check()){
//                    log("recive: " + QString::number(i) + "  size: " + QString::number(data[i].size));
//                }
//            }
        }

    }
}
