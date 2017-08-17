#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent) : QWidget(parent){
    //qDebug() << ;

    this->setGeometry(0, 0, 800, 600);
    QPalette pal = palette();

    // set black background
    pal.setColor(QPalette::Background, Qt::black);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    this->show();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(MyUpdate()));
    timer->start(1000/120);

    this->data0 = new uchar[800 * 600];
    memset(data0,0,800*600);
    image = new QImage(data0,800,600,QImage::Format_Grayscale8);

}

void RenderArea::paintEvent(QPaintEvent *) {
    p_t = a_t;
    a_t = QDateTime::currentMSecsSinceEpoch();
    if(a_t - p_t == 0)
        fps = 1000;
    else
        fps = 1000 / (a_t - p_t);


    QPainter painter(this);

    painter.drawPixmap(0,0,800,600,QPixmap::fromImage(QImage(data0, 800, 600, QImage::Format_Grayscale8)));

    QFont font = painter.font() ;

    font.setPointSize(20);

    painter.setFont(font);
    painter.setPen(QColor(0,255,0));
    painter.drawText(size().width()-70, 30, QString::number(fps));

    painter.end();
}
