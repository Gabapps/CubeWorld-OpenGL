#include "Person.h"

Person::Person() : m_pos(0,0,0), m_vit(0,0,0), m_ori(1,0,0), m_acc(0,0,0), m_vie(100)
{

}

Person::~Person()
{

}

gVector Person::GetPos() const
{
    return m_pos;
}

gVector Person::GetVit() const
{
    return m_vit;
}

gVector Person::GetOri() const
{
    return m_ori;
}

gVector Person::GetAcc() const
{
    return m_acc;
}

void Person::SetPos(double x, double y, double z)
{
    m_pos.SetCoord(x,y,z);
}

void Person::SetPos(gVector pos)
{
    m_pos = pos;
}

void Person::SetVit(double x, double y, double z)
{
    m_vit.SetCoord(x,y,z);
}

void Person::SetVit(gVector vit)
{
    m_vit = vit;
}

void Person::SetAcc(double x, double y, double z)
{
    m_acc.SetCoord(x,y,z);
}

void Person::SetAcc(gVector acc)
{
    m_acc = acc;
}

void Person::SetOri(double x, double y, double z)
{
    m_ori.SetCoord(x,y,z);
}

void Person::SetOri(gVector ori)
{
    m_ori = ori;
}

void Person::LookAt(const Person& pers)
{
    m_ori = pers.m_pos-m_pos;
}

void Person::Follow(const Person& pers, double d)
{
    double vitZ = m_vit.GetZ();
    if((m_pos-pers.m_pos).GetNorme()>d)
    {
        LookAt(pers);
        m_vit.SetCoordByAngle(m_ori.GetXom(),0,2);
        m_vit += gVector(0,0,vitZ);
    }

    else
    {
        m_vit = gVector(0,0,vitZ);
    }


}
