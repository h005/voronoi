#include "labelview.h"

LabelView::LabelView(QWidget *parent):
    QLabel(parent)
{
    QPixmap pixmap = QPixmap(WIDTH,HEIGHT);
    pixmap.fill(Qt::red);
    this->setPixmap(pixmap);
    this->resize(WIDTH,HEIGHT);
    count = 0;
    sweepline = 1;
    beachLine = new QPointF[WIDTH];
    for(int i=0;i<WIDTH;i++)
        beachLine[i] = QPointF(i,0);
    step = 3;
}

void LabelView::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);
    QPainter *painter = new QPainter(this);
    QPen pen = QPen(Qt::white,2);
    painter->setPen(pen);
        painter->drawPoints(points,count);
    pen = QPen(Qt::green,2);
    painter->setPen(pen);
    painter->drawLine(QPoint(0,sweepline),QPointF(WIDTH,sweepline));
    pen = QPen(Qt::blue,2);
    painter->setPen(pen);
    // draw...
    painter->drawPoints(beachLine,WIDTH);
    delete painter;
}

void LabelView::setPoints()
{
    QString fileName = "E:/Qt/build-Voronoi_3-Desktop_Qt_5_4_2_MinGW_32bit-Debug/debug/voronoi.txt";
    freopen(fileName.toStdString().c_str(),"r",stdin);
    scanf("%d",&count);
    points = new QPoint[count];
    int x,y;
    for(int i=0;i<count;i++)
    {
        scanf("%d %d",&x,&y);
        points[i] = QPoint(x,y);
    }
    update();
}

void LabelView::down()
{
    sweepline = sweepline % HEIGHT;
    sweepline += step;
    setBeachLine();
    update();
}

void LabelView::up()
{
    sweepline -= step;
    while(sweepline < 0)
        sweepline += HEIGHT;
    sweepline = sweepline % HEIGHT;
    setBeachLine();
    update();
}

int LabelView::stepMore()
{
    step++;
    return step;
}

int LabelView::stepLess()
{
    step--;
    return step;
}

void LabelView::setBeachLine()
{
    for(int i=0;i<WIDTH;i++)
    {
        beachLine[i].setX(i);
        beachLine[i].setY(0);
    }
    for(int i=0;i<count;i++)
    {
        float p = sweepline - points[i].y();
        if(p <= 0)
            continue;
        for(int j=0;j<WIDTH;j++)
        {
            float y = p/2.0-(j-points[i].x())*(j-points[i].x())/2.0/p + points[i].y();
            if(y > beachLine[j].y())
                beachLine[j].setY(y);
        }
    }
}

void LabelView::mousePressEvent(QMouseEvent *e)
{
    QLabel::mousePressEvent(e);

}
