#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QPainter>
#include <QWidget>
#include <QTimer>
#include <QFont>

#include <QDateTime>

class RenderArea : public QWidget{
    Q_OBJECT

public:
    explicit RenderArea(QWidget *parent = nullptr);

    double fps = 0;

    QColor color;

    uint32_t data_size;
    uchar* data0;



signals:

public slots:

    void MyUpdate(){
        update();
        color = QColor(0 ,0, 0);
    }

private:
    QImage* image;
    QTimer* timer;
    qint64 a_t = QDateTime::currentMSecsSinceEpoch(), p_t = 0;
    void paintEvent(QPaintEvent*);


};


#endif // RENDERAREA_H
