#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif
#include <GL/GLU.h>
#include <GL/GL.h>
#include "MoteurGraphique.h"
#include "MoteurPhysique.h"

int main ( int argc, char** argv )
{
    MoteurGraphique mg;
    MoteurPhysique mp;
    Map map;
    Person pers, jean, paul;

    pers.SetPos(2,6,1);
    jean.SetPos(2,30,1);
    paul.SetPos(30,30,1);
    map.LoadMap("map.map");
    //map.CreateVolume('a',28,28,0,4,4,30);

    mg.Initialisation();

    // program main loop
    bool done = false;
    double t1=0, t2=0, ya=0, za=-45;
    gVector ori;
    int *collPos;
    bool coll = true;
    int fps;
    std::ofstream file("fps.txt");

    while (!done)
    {
        Uint8 *touches = SDL_GetKeyState(NULL);
        // message processing loop
        SDL_Event event;


        ori.SetCoordByAngle(ya,0,1);

        if (touches[SDLK_w])
        {
            pers.SetPos(pers.GetPos()+gVector(ori.GetX()/50, ori.GetY()/50,0));
        }

        if (touches[SDLK_s])
        {
            pers.SetPos(pers.GetPos()+gVector(-ori.GetX()/50, -ori.GetY()/50,0));
        }

        ori.SetCoordByAngle(ya-90,0,1);

        if (touches[SDLK_d])
        {
            pers.SetPos(pers.GetPos()+gVector(ori.GetX()/50, ori.GetY()/50,0));
        }

        if (touches[SDLK_a])
        {
            pers.SetPos(pers.GetPos()+gVector(-ori.GetX()/50, -ori.GetY()/50,0));
        }

        if (touches[SDLK_SPACE])
        {
            pers.SetVit(pers.GetVit().GetX(), pers.GetVit().GetY(), 3);
        }

            coll = touches[SDLK_TAB];

        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE){
                    std::cout << map.GetTargetCube(pers.GetPos(), pers.GetOri()+1.5) << std::endl;
                        done = true;}
                    break;
                }

            case SDL_MOUSEMOTION :
                ya -= (double)(event.motion.x-width/2)/2;
                za -= (double)(event.motion.y-height/2)/2;
                if(za>89){za=89;}
                if(za<-89){za=-89;}
                if(ya>360){ya-=360;}
                if(ya<0){ya+=360;}
                SDL_WarpMouse(width/2,height/2);
                break;

             case SDL_MOUSEBUTTONDOWN :
                    if(event.button.button == SDL_BUTTON_LEFT){map.Destroy(map.GetTargetCube(pers.GetPos(), pers.GetOri()));}
            } // end switch
        } // end of message processing

        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

        jean.Follow(pers, 2);
        paul.Follow(jean, 8);
        t2=(double)SDL_GetTicks()/1000;
        fps = 1/(t2-t1);
        file << fps << std::endl;
        collPos = map.GetCollPos(pers.GetPos());
        mp.Anime(pers, t2-t1, collPos);
        collPos = map.GetCollPos(jean.GetPos());
        mp.Anime(jean, t2-t1, collPos);
        collPos = map.GetCollPos(paul.GetPos());
        mp.Anime(paul, t2-t1, collPos);
        t1=(double)SDL_GetTicks()/1000;
        ori.SetCoordByAngle(ya,za,1);
        pers.SetOri(ori);

        mg.AfficherViseur();

        if(coll)
        {
            mg.OrienterCam(pers.GetPos(),ori, OBJECTIVE);
            mg.Afficher(pers);

        }
        else
        {
            mg.OrienterCam(pers.GetPos(),ori, SUBJECTIVE);
        }

        mg.Afficher(map, pers.GetPos(), pers.GetOri());
        mg.Afficher(jean);
        mg.Afficher(paul);

        glFlush();
        SDL_GL_SwapBuffers();
    }

    delete collPos;

    SDL_Quit();
    return 0;
}
