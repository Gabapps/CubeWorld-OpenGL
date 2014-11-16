#ifndef MOTEURPHYSIQUE_H_INCLUDED
#define MOTEURPHYSIQUE_H_INCLUDED

#include "Person.h"
#include "Map.h"

#define g 9.80 //constante de gravité


class MoteurPhysique
{
    public :

    MoteurPhysique();
    ~MoteurPhysique();
    void Anime(Person&, double, int*);

    protected :


};

#endif // MOTEURPHYSIQUE_H_INCLUDED
