#ifndef MOTEURGRAPHIQUE_H_INCLUDED
#define MOTEURGRAPHIQUE_H_INCLUDED

#include <SDL.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include "gVector.h"
#include "Map.h"
#include "Person.h"
#include <stdio.h>
#include <stdlib.h>

#define width 800
#define height 600

enum camType{SUBJECTIVE, OBJECTIVE};

class MoteurGraphique
{
    public :

    MoteurGraphique();
    void Initialisation();
    void Afficher(const Map&, gVector pos, gVector ori);
    void Afficher(const Person&);
    void AfficherViseur();
    void OrienterCam(gVector, gVector, camType);
    void AfficherParaRect(double, double, double, double, double, double);
    void AfficherCube(double, double, double, double);

    protected :




};

#endif // MOTEURGRAPHIQUE_H_INCLUDED
