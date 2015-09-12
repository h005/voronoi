#include "dcel.h"
#include <stdio.h>

DCEL::DCEL()
{
    face = new Face();
    vertex = new Vertex();
    edge = new Edge();
}

void DCEL::print()
{
    printf(".....edge....\n");

    Edge *p = edge->next;
    while(p)
    {
        printf("%.6x v %.6x %.6x f %.6x %.6x %.6x\n",
               p,p->origin,p->twin,p->f,p->next,p->prev);
        //if(p->origin && p->f)
        /*
         * printf("%x (%lf,%lf) %x (%lf,%lf) %x %x\n",
               p,p->origin->p.x(),p->origin->p.y(),
               p->twin,p->f->f.x(),p->f->f.y(),
               p->next,p->twin);
         *
         *
         */
        p = p->next;
    }

    printf(".....vertex...\n");
    Vertex *v = vertex->next;
    while(v)
    {
        printf("%.6x (%lf,%lf) %.6x\n",v,v->p.x(),v->p.y(),v->e);
        v = v->next;
    }
    printf(".....face...\n");
    Face *f = face->next;
    while(f)
    {
        printf("%.6x %.6x (%lf,%lf)\n",f,f->edge,f->f.x(),f->f.y());
        f = f->next;
    }
}
