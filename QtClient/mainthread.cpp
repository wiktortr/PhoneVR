#include "mainthread.h"

MainThread::MainThread() {

}

void MainThread::Connect() {
    start(QThread::HighPriority);
}

void MainThread::Disconnect() {
    log("Disconnected");
    s_connect = false;

}

void MainThread::log(QString msg) {
    if(logs == nullptr)
        return;
    logs->setText(logs->text() + msg + "\n");
}

void MainThread::run() {

    socket = new QUdpSocket();
    socket->connectToHost("192.168.1.13", 27015, QIODevice::ReadWrite);

    packet_message s_msg;
    s_msg.message = 4;
    if(socket->write((char*)&s_msg, sizeof(packet_message)) != -1){
        log("Send request to connet");

        qint64 start_time = QDateTime::currentMSecsSinceEpoch();
        for(;;){
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

            packet_sync sync;
            for(;;) {
                if(socket->read((char*)&sync, sizeof(packet_sync)) != -1 && sync.check()){
                    s_msg.message = 2;
                    if(socket->write((char*)&s_msg, sizeof(packet_message)) != -1){
                        log("Sync server");
                        break;
                    }
                }
            }

            //renderer->data0 = new uchar[sync.size];

            packet_data data0;
            uint32_t index, i;
            while (s_connect) {
                if(socket->read((char*)&data0, sizeof(packet_data)) != -1 && data0.check()){
                    index = data0.num_of_packet * 64000;
                    for (i = 0; i < 64000; ++i){
                        if(index + i > sync.size)
                            break;
                        renderer->data0[index + i] = data0.data[i];
                    }
                }
            }

        }
        else{
            log("Can't connect to server");
        }



    }
    else{
        log("Can't send request to connect");
    }

}
