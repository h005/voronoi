#ifndef LABELVIEW_H
#define LABELVIEW_H

#include <QLabel>
#include <QPainter>
#include <QPen>
#include <QImage>
#include <QPoint>
#include <QPointF>

#define WIDTH 600
#define HEIGHT 400

class LabelView : public QLabel
{
    Q_OBJECT
public:
    LabelView(QWidget *parent = 0);

    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);

    void setPoints();
    void down();
    void up();
    int stepMore();
    int stepLess();
private:
    void setBeachLine();
private:
    QPoint *points;
    QPointF *beachLine;
    QImage image;
    int count;
    int step;
    int sweepline;

};

#endif // LABELVIEW_H
