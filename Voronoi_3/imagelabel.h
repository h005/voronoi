#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QLabel>
#include <QPainter>
#include <QPen>
#include <math.h>

#include "sitequeue.h"
#include "eventqueue.h"
#include "beachline.h"
#include "edge.h"
#include "dcel.h"
#include "face.h"
#include "vertex.h"

#define WIDTH 900
#define HEIGHT 800
#define Inf 1000000

class QPixmap;

class ImageLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ImageLabel(QWidget *parent = 0);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    int numInc();
    int numDec();

    void setPoints();
    void voronoi();


signals:

public slots:

private:

    SiteQueue *sitequeue;
    EventQueue *eventqueue;
    BeachLine *beachline;
    DCEL *dcel;
    QPixmap *image;
    QPointF *points;
    int NumPoints;
    bool flagPoints;
    bool flagVoronoi;

    void handleSiteEvent(SiteQueue *tmp,
                              EventQueue *eventqueue,
                              BeachLine *beachline,
                              DCEL *dcel
                              );

    void handleCircleEvent(SiteQueue *sitequeue,
                           EventQueue *eventqueue,
                           BeachLine *beachline,
                           DCEL *dcel,
                           BeachLine *bl
                           );
    QPointF* getLowestPoint(QPointF *c,BeachLine *bl);

};

#endif // IMAGELABEL_H
