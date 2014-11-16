#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

#include "gVector.h"

class Person
{
    public :

    Person();
    ~Person();

    gVector GetPos() const;
    gVector GetVit() const;
    gVector GetAcc() const;
    gVector GetOri() const;


    void SetPos(gVector pos);
    void SetPos(double x, double y, double z);

    void SetVit(double x, double y, double z);
    void SetVit(gVector vit);

    void SetAcc(double x, double y, double z);
    void SetAcc(gVector vit);

    void SetOri(double x, double y, double z);
    void SetOri(gVector ori);

    void LookAt(const Person&);
    void Follow(const Person&, double);

    protected :

    gVector m_pos;
    gVector m_vit;
    gVector m_acc;
    gVector m_ori;
    uint8_t m_vie;

};

#endif // PERSON_H_INCLUDED
