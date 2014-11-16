#include "MoteurGraphique.h"

MoteurGraphique::MoteurGraphique()
{

}

void MoteurGraphique::Initialisation()
{
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
    }

    SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_OPENGL);
    SDL_ShowCursor(0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70,(double)width/height,0.4,1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(3,3,1,0,0,1,0,0,1);
}

void MoteurGraphique::Afficher(const Map& map, gVector pos, gVector ori)
{
    for(int i(0); i < SIZE; i++)
    {
        for(int j(0); j < SIZE; j++)
        {
            for(int k(0); k < SIZE; k++)
            {
                if(map.GetMap(i,j,k)!=0)
                {
                    if(map.GetTargetCube(pos, ori)== gVector(i,j,k))
                    {
                        glColor3f(0,0,1);
                    }
                    else{glColor3d(1,1,1);}
                    AfficherCube((double)i, (double)j,(double)k,1);
                }
            }
        }
    }
}

void MoteurGraphique::Afficher(const Person& pers)
{
    glPushMatrix();
    glTranslated(pers.GetPos().GetX(), pers.GetPos().GetY(), pers.GetPos().GetZ());
    glRotated(pers.GetOri().GetXom(),0,0,1);
    glColor3d(0.5,0,1);
    AfficherParaRect(-0.5, -0.5, 0, 1.0, 1.0, 2.0);
    glPopMatrix();

}

void MoteurGraphique::AfficherViseur()
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-(height/width),(height/width),-(width/height),(width/height));
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor3f(0,1,1);
    glBegin(GL_LINES);
    glVertex2d(-0.05,0);
    glVertex2d(0.05,0);
    glVertex2d(0,-0.05);
    glVertex2d(0,0.05);
    glEnd();
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

void MoteurGraphique::AfficherParaRect(double x, double y, double z, double lx, double ly, double h)
{
    glBegin(GL_QUADS);
    glVertex3d(x,y,z);
    glVertex3d(x+lx,y,z);
    glVertex3d(x+lx,y+ly,z);
    glVertex3d(x,y+ly,z);

    glVertex3d(x,y,z);
    glVertex3d(x,y+ly,z);
    glVertex3d(x,y+ly,z+h);
    glVertex3d(x,y,z+h);

    glVertex3d(x,y+ly,z);
    glVertex3d(x,y+ly,z+h);
    glVertex3d(x+lx,y+ly,z+h);
    glVertex3d(x+lx,y+ly,z);

    glVertex3d(x,y,z);
    glVertex3d(x+lx,y,z);
    glVertex3d(x+lx,y,z+h);
    glVertex3d(x,y,z+h);

    glVertex3d(x+lx,y,z);
    glVertex3d(x+lx,y,z+h);
    glVertex3d(x+lx,y+ly,z+h);
    glVertex3d(x+lx,y+ly,z);

    glVertex3d(x,y,z+h);
    glVertex3d(x+lx,y,z+h);
    glVertex3d(x+lx,y+ly,z+h);
    glVertex3d(x,y+ly,z+h);

    glEnd();
    glBegin(GL_LINES);
    glColor3d(1,0,0);
    glVertex3d(x,y,z);
    glVertex3d(x+lx,y,z);

    glVertex3d(x,y,z);
    glVertex3d(x,y+ly,z);

    glVertex3d(x,y,z);
    glVertex3d(x,y,z+h);

    glVertex3d(x,y+ly,z);
    glVertex3d(x,y+ly,z+h);

    glVertex3d(x+lx,y+ly,z);
    glVertex3d(x+lx,y+ly,z+h);

    glVertex3d(x,y,z+h);
    glVertex3d(x+lx,y,z+h);

    glVertex3d(x+lx,y,z+h);
    glVertex3d(x+lx,y+ly,z+h);

    glVertex3d(x,y+ly,z+h);
    glVertex3d(x+lx,y+ly,z+h);

    glVertex3d(x+lx,y,z);
    glVertex3d(x+lx,y+ly,z);

    glVertex3d(x,y,z+h);
    glVertex3d(x,y+ly,z+h);

    glVertex3d(x,y+ly,z);
    glVertex3d(x+lx,y+ly,z);

    glVertex3d(x+lx,y,z);
    glVertex3d(x+lx,y,z+h);

    glEnd();
}

void MoteurGraphique::AfficherCube(double x, double y, double z, double h)
{
    AfficherParaRect(x,y,z,h,h,h);

}

void  MoteurGraphique::OrienterCam(gVector pos, gVector ori, camType type)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if(type == SUBJECTIVE){gluLookAt(pos.GetX(), pos.GetY(), pos.GetZ()+1.5, pos.GetX()+ori.GetX(), pos.GetY()+ori.GetY(), pos.GetZ()+1.5+ori.GetZ(),0,0,1);}
    else{gluLookAt(pos.GetX()-5*ori.GetX(), pos.GetY()-5*ori.GetY(), pos.GetZ()+1.5-5*ori.GetZ(), pos.GetX()+ori.GetX(), pos.GetY()+ori.GetY(), pos.GetZ()+1.5+ori.GetZ(),0,0,1);}
}
