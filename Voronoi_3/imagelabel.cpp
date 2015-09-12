#include "imagelabel.h"

#include <QDebug>

ImageLabel::ImageLabel(QWidget *parent) :
    QLabel(parent)
{
    this->resize(WIDTH,HEIGHT);
    image = new QPixmap(WIDTH,HEIGHT);
    image->fill(Qt::red);
    this->setPixmap(*image);
    NumPoints = 5;
    flagPoints = false;
    flagVoronoi = false;
    points = new QPointF[2000];

}

void ImageLabel::mousePressEvent(QMouseEvent *ev)
{
    QLabel::mousePressEvent(ev);
}

void ImageLabel::mouseReleaseEvent(QMouseEvent *e)
{
    QLabel::mouseReleaseEvent(e);
}

int ImageLabel::numInc()
{
    return ++ NumPoints;
}

int ImageLabel::numDec()
{
    return -- NumPoints;
}

void ImageLabel::mouseMoveEvent(QMouseEvent *e)
{
    QLabel::mouseMoveEvent(e);
}

void ImageLabel::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);
    QPainter *painter = new QPainter(this);
    if(flagPoints)
    {
//        image = new QPixmap(WIDTH,HEIGHT);
//        image->fill(Qt::red);
        this->setPixmap(*image);
        painter->setPen(QPen(Qt::white,3));
        for(int i=0;i<NumPoints;i++)
            painter->drawPoint(points[i]);
    }
    if(flagVoronoi)
    {
        painter->setPen(QPen(Qt::green,2));
        Edge *e = dcel->edge->next;
        while(e)
        {
            if(e->origin)
            {
                if(e->twin->origin)
                    painter->drawLine(e->origin->p,e->twin->origin->p);
                else
                {
                    QPointF mid = (e->f->f+e->twin->f->f)/2;
                    QPointF p1 = e->getOrigin(mid,e->origin->p,Inf);
                    painter->drawLine(e->origin->p,p1);
                }
            }
            else
            {
                if(e->twin->origin)
                {
                    QPointF mid = (e->f->f+e->twin->f->f)/2;
                    QPointF p1 = e->twin->getOrigin(mid,e->twin->origin->p,Inf);
                    painter->drawLine(p1,e->twin->origin->p);
                }
                else
                {
                    QPointF mid = (e->f->f+e->twin->f->f)/2;
                    e->getOrigin(mid,Inf);
                    painter->drawLine(e->origin->p,e->twin->origin->p);
                }
            }
            e = e->next;
        }
    }

}

void ImageLabel::setPoints()
{
    //freopen("I:\\Qt\\GetFrame\\Voronoi_3\\voronoi.txt","r",stdin);
    freopen("E:/Qt/build-Voronoi_3-Desktop_Qt_5_4_2_MinGW_32bit-Debug/debug/voronoi.txt","r",stdin);
    //scanf("%d",&NumPoints);

    double x,y;
    double xMax = -Inf,yMax = -Inf;
    double rate = 1;
    for(int i=0;i<NumPoints;i++)
    {
        scanf("%lf %lf",&x,&y);
//        xMax = xMax>x?xMax:x;
//        yMax = yMax>y?yMax:y;
        points[i] = QPointF(x,y);
    }
//    fclose(stdin);
//    if(HEIGHT*xMax>WIDTH*yMax)
//        rate = WIDTH/xMax*0.8;
//    else
//        rate = HEIGHT/yMax*0.8;
//    for(int i=0;i<NumPoints;i++)
//        points[i] = rate*points[i];

//    qDebug()<<"rate "<<rate<<endl;
//    for(int i=0;i<NumPoints;i++)
//        qDebug()<<points[i].x()<<","<<points[i].y()<<endl;

    flagPoints = true;
    flagVoronoi = false;
    update();
}

void ImageLabel::voronoi()
{
    sitequeue = new SiteQueue();
    eventqueue = new EventQueue();
    beachline = new BeachLine();
    dcel = new DCEL();

    for(int i=0;i<NumPoints;i++)
        sitequeue->insert(points[i]);

    while(!sitequeue->empty())
    {
        if(eventqueue->empty())
        {
            SiteQueue *tmp = sitequeue->pop();
            handleSiteEvent(tmp,eventqueue,beachline,dcel);
            //handle site event()
            //printf(".....1.5\n");
        }
        else
        {
            QPointF ps = sitequeue->getTopPoint();
            QPointF pc = eventqueue->getTopPoint();
            bool tmpbool = ps.y()==pc.y()?
                        ps.x()<pc.x():
                        ps.y()<pc.y();
            if(tmpbool)
            {
                SiteQueue *tmp = sitequeue->pop();
                handleSiteEvent(tmp,eventqueue,beachline,dcel);
                //handle site event();
            }
            else
            {
                EventQueue *tmp = eventqueue->pop();
                handleCircleEvent(sitequeue,eventqueue,beachline,dcel,tmp->beachline);
                //handle circle event();
            }
        }
        //printf(".....2\n");
    }
    //printf(".....3\n");
    while(!eventqueue->empty())
    {
        EventQueue *tmp = eventqueue->pop();
        handleCircleEvent(sitequeue,eventqueue,beachline,dcel,tmp->beachline);
        //handle circle event();
        //printf(".....4\n");
    }
    flagVoronoi = true;
    update();
}

void ImageLabel::handleSiteEvent(SiteQueue *tmp,
                                 EventQueue *eventqueue,
                                 BeachLine *beachline,
                                 DCEL *dcel)
{
    if(beachline->empty())
    {
        //printf("handleSiteEvent...1\n");
        beachline->insert(tmp->p);
        return;
    }
    BeachLine *upon = beachline->search(tmp->p);
    if(upon->circleEvent)
    {
        eventqueue->del(upon->circleEvent);
        upon->circleEvent = NULL;
    }
    //printf("handleSiteEvent...2\n");
    BeachLine *b1 = upon->insert(tmp->p);
    //printf("handleSiteEvent...2.1\n");
    BeachLine *b2 = b1->insert(upon->p);
    //printf("handleSiteEvent...2.2\n");
    //if exist the face then return the pointer
    //else insert the new face and return
    Face *f1 = dcel->face->insert(b1->p);
    //printf("handleSiteEvent...2.3\n");
    Face *f2 = dcel->face->insert(b2->p);
    //printf("handleSiteEvent...2.4\n");
    Edge *e1 = dcel->edge->insert(f1);
    //printf("handleSiteEvent...2.5\n");
    Edge *e2 = dcel->edge->insert(f2);
    //printf("handleSiteEvent...2.6\n");
    e1->twin = e2;
    e2->twin = e1;


    QPointF *c1 = beachline->checkCircleL(upon->prev,upon,b1);
    if(c1)
    {
        //printf("(%lf,%lf)\n",c1->x(),c1->y());
        QPointF *p1 = getLowestPoint(c1,b1);
        EventQueue *ce1 = eventqueue->insert(c1,p1,upon);
        upon->circleEvent = ce1;
        //printf("handleSiteEvent...4\n");
    }
    /*
    upon = upon->prev;

    while(upon && upon->prev && (upon->prev->p.y()==upon->p.y()))
    {
        c1 = beachline->checkCircleL(upon->prev,upon,b1);
        if(c1)
        {
//            printf("(%lf,%lf)\n",c1->x(),c1->y());
            QPointF *p1 = getLowestPoint(c1,b1);
            EventQueue *ce1 = eventqueue->insert(c1,p1,upon);
            upon->circleEvent = ce1;
            //printf("handleSiteEvent...4\n");
        }
        upon = upon->prev;
    }
    */
    QPointF *c2 = beachline->checkCircleR(b1,b2,b2->next);
    if(c2)
    {
        //printf("(%lf,%lf)\n",c2->x(),c2->y());
        QPointF *p2 = getLowestPoint(c2,b2);
        EventQueue *ce2 = eventqueue->insert(c2,p2,b2);
        b2->circleEvent = ce2;
        //printf("handleSiteEvent...5\n");
    }
    /*
    b2 = b2->next;

    while(b2 && b2->next && (b2->next->p.y()==b2->p.y()))
    {
        QPointF *c2 = beachline->checkCircleR(b1,b2,b2->next);
        if(c2)
        {
            //printf("(%lf,%lf)\n",c2->x(),c2->y());
            QPointF *p2 = getLowestPoint(c2,b2);
            EventQueue *ce2 = eventqueue->insert(c2,p2,b2);
            b2->circleEvent = ce2;
            //printf("handleSiteEvent...5\n");
        }
        b2 = b2->next;
    }
    */
}

void ImageLabel::handleCircleEvent(SiteQueue *sitequeue,
                                   EventQueue *eventqueue,
                                   BeachLine *beachline,
                                   DCEL *dcel,
                                   BeachLine *bl)
{
    eventqueue->del(bl->prev->circleEvent);
    //printf("handleSiteEvent...2.1\n");
    eventqueue->del(bl->next->circleEvent);
    //printf("handleSiteEvent...2.2\n");
    Vertex *v = dcel->vertex->insert(bl->circleEvent->getCenter());
    Face *f1 = dcel->face->insert(bl->prev->p);
    Face *f2 = dcel->face->insert(bl->next->p);
    Edge *e1 = dcel->edge->insert(f1);
    Edge *e2 = dcel->edge->insert(f2);
    e1->twin = e2;
    e2->twin = e1;
    e2->setOrigin(v);
    //printf("handleSiteEvent...2.3\n");
    dcel->edge->setOrigin(f1->f,bl->p,v);
    //printf("handleSiteEvent...2.4\n");
    dcel->edge->setOrigin(bl->p,f2->f,v);
    //printf("handleSiteEvent...2.5\n");
    v->setIncidentEdge(e2);
    if(bl->prev->p == QPointF(2.785,4.2176) &&
       bl->next->p == QPointF(6.3236,8.0028) &&
       bl->next->next->p == QPointF(5.4688,9.1574))
        printf("for debug...\n");


    //printf("handleSiteEvent...2.6\n");
    BeachLine *b1 = bl->prev;
    BeachLine *b2 = bl->next;
    QPointF *c1 = beachline->checkCircleL(b1->prev,b1,b2);
    if(c1)
    {
//        printf("(%lf,%lf)\n",c1->x(),c1->y());
        QPointF *p1 = getLowestPoint(c1,b1);
        EventQueue *ce1 = eventqueue->insert(c1,p1,b1);
        b1->circleEvent = ce1;
    }
    /*
    b1 = b1->prev;

    while(b1 && b1->prev && (b1->prev->p.y()==b1->p.y()))
    {
        c1 = beachline->checkCircleL(b1->prev,b1,b2);
        if(c1)
        {
//            printf("(%lf,%lf)\n",c1->x(),c1->y());
            QPointF *p1 = getLowestPoint(c1,b1);
            EventQueue *ce1 = eventqueue->insert(c1,p1,b1);
            b1->circleEvent = ce1;
        }
        b1 = b1->prev;
    }
    */
    b1 = bl->next;
    b2 = bl->prev;
    QPointF *c2 = beachline->checkCircleR(b2,b1,b1->next);
    if(c2)
    {
//        printf("(%lf,%lf)\n",c2->x(),c2->y());
        QPointF *p2 = getLowestPoint(c2,b1);
        EventQueue *ce2 = eventqueue->insert(c2,p2,b1);
        b1->circleEvent = ce2;
    }
    /*
    b1 = b1->next;
    while(b1 && b1->next && (b1->next->p.y()==b1->p.y()))
    {
        c2 = beachline->checkCircleR(b2,b1,b1->next);
        if(c2)
        {
            QPointF *p2 = getLowestPoint(c2,b1);
            EventQueue *ce2 = eventqueue->insert(c2,p2,b1);
            b1->circleEvent = ce2;
        }
        b1 = b1->next;
    }
    */


    beachline->del(bl);
}

QPointF* ImageLabel::getLowestPoint(QPointF *c,BeachLine *bl)
{
    QPointF *p1;
    double rr = c->dotProduct(*c-bl->p,*c-bl->p);
    double y = c->y()+sqrt(rr);
    p1 = new QPointF(c->x(),y);
    return p1;
}
