#include "MoteurPhysique.h"

using namespace std;

MoteurPhysique::MoteurPhysique()
{

}

MoteurPhysique::~MoteurPhysique()
{

}

void MoteurPhysique::Anime(Person& pers, double  t, int* collPos)
{
    gVector acc;
    gVector vit(pers.GetAcc()*t+pers.GetVit());
    gVector pos(1/2*pers.GetAcc().GetX()*pow(t,2)+pers.GetVit().GetX()*t+pers.GetPos().GetX(),
                1/2*pers.GetAcc().GetY()*pow(t,2)+pers.GetVit().GetY()*t+pers.GetPos().GetY(),
                1/2*pers.GetAcc().GetZ()*pow(t,2)+pers.GetVit().GetZ()*t+pers.GetPos().GetZ());

    if (pos.GetX() < (double)collPos[XL]+0.5)
    {
        pos.SetCoord((double)collPos[XL]+0.5,pos.GetY(),pos.GetZ());
        vit.SetCoord(0,vit.GetY(),vit.GetZ());
        acc.SetCoord(0, pers.GetAcc().GetY(), pers.GetAcc().GetZ());
    }

    if (pos.GetX() > (double)collPos[XM]-0.5)
    {
        pos.SetCoord((double)collPos[XM]-0.5,pos.GetY(),pos.GetZ());
        vit.SetCoord(0,vit.GetY(),vit.GetZ());
        acc.SetCoord(0, pers.GetAcc().GetY(), pers.GetAcc().GetZ());
    }

    if (pos.GetY() < (double)collPos[YL]+0.5)
    {
        pos.SetCoord(pos.GetX(),(double)collPos[YL]+0.5,pos.GetZ());
        vit.SetCoord(vit.GetX(),0,vit.GetZ());
        acc.SetCoord(pers.GetAcc().GetX(), 0, pers.GetAcc().GetZ());
    }

    if (pos.GetY() > (double)collPos[YM]-0.5)
    {
        pos.SetCoord(pos.GetX(),(double)collPos[YM]-0.5,pos.GetZ());
        vit.SetCoord(vit.GetX(),0,vit.GetZ());
        acc.SetCoord(pers.GetAcc().GetX(), 0, pers.GetAcc().GetZ());
    }

    if (pos.GetZ() < (double)collPos[ZL])
    {
        pos.SetCoord(pos.GetX(),pos.GetY(),(double)collPos[ZL]);
        vit.SetCoord(vit.GetX(),vit.GetY(),0);
        acc.SetCoord(pers.GetAcc().GetX(), pers.GetAcc().GetY(), 0);
    }
    else
    {
        acc.SetCoord(pers.GetAcc().GetX(), pers.GetAcc().GetY(), -g);
    }

    if (pos.GetZ() > (double)collPos[ZM]-2)
    {
        pos.SetCoord(pos.GetX(),pos.GetY(),(double)collPos[ZM]-2);
        vit.SetCoord(vit.GetX(),vit.GetY(),0);

    }

    pers.SetVit(vit);
    pers.SetPos(pos);
    pers.SetAcc(acc);
}
