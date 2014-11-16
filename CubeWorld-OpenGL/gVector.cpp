#include "gVector.h"

using namespace std;
//Constructors

gVector::gVector() : m_x(0), m_y(0), m_z(0)
{

}

gVector::gVector(double x) : m_x(x), m_y(0), m_z(0)
{

}

gVector::gVector(double x, double y) : m_x(x), m_y(y), m_z(0)
{

}

gVector::gVector(double x, double y, double z) : m_x(x), m_y(y), m_z(z)
{

}

//Methods

void gVector::SetCoord(double x, double y, double z)
{
    m_x = x, m_y = y, m_z = z;
}

void gVector::SetCoordByAngle(double xom, double zom, double norme)
{
    m_x = norme*cos(zom*M_PI/180)*cos(xom*M_PI/180);
    m_y = norme*cos(zom*M_PI/180)*sin(xom*M_PI/180);
    m_z = norme*sin(zom*M_PI/180);
    /*if((m_x-(double)(int)m_x)<.0000000001){m_x = (double)(int)m_x;}
    if((m_y-(double)(int)m_y)<.0000000001){m_y = (double)(int)m_y;}
    if((m_z-(double)(int)m_z)<.0000000001){m_z = (double)(int)m_z;}*/
}

void gVector::AddCoord(double x, double y, double z)
{
    m_x += x, m_y += y, m_z += z;
}

double gVector::GetScalarProductWith(const gVector& vector) const
{
    return m_x*vector.GetX() + m_y*vector.GetY() + m_z*vector.GetZ();
}

bool gVector::IsOrthonormalWith(const gVector& v) const
{
    if(GetScalarProductWith(v) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool gVector::IsColinearWith(const gVector& v) const {return true;}

double gVector::GetX() const{return m_x;}

double gVector::GetY() const{return m_y;}

double gVector::GetZ() const{return m_z;}

double gVector::GetNorme() const{return pow(pow(m_x, 2)+pow(m_y, 2)+pow(m_z, 2), 0.5);}

double gVector::GetZom() const{return (180/M_PI)*asin(m_z/GetNorme());}

double gVector::GetXom() const
{
    if(m_x>=0 && m_y>=0){return (180/M_PI)*asin(m_y/(GetNorme()*cos(GetZom()*M_PI/180)));}
    else if(m_x<0 && m_y>=0){return (180/M_PI)*acos(m_x/(GetNorme()*cos(GetZom()*M_PI/180)));}
    else if(m_x<0 && m_y<0){return 360-(180/M_PI)*acos(m_x/(GetNorme()*cos(GetZom()*M_PI/180)));}
    else {return 360+(180/M_PI)*asin(m_y/(GetNorme()*cos(GetZom()*M_PI/180)));}
}

void gVector::Afficher(ostream &flux) const
{
    flux << "x : " << m_x << endl;
    flux << "y : " << m_y << endl;
    flux << "z : " << m_z << endl;
}



//Operators

ostream &operator<<(ostream &flux, gVector const& vector)
{
    vector.Afficher(flux);
    return flux;
}

gVector& gVector::operator+=(const gVector &v)
{
    m_x += v.GetX();
    m_y += v.GetY();
    m_z += v.GetZ();

    return *this;

}

gVector operator+(const gVector& v1, const gVector& v2)
{
    gVector v(v1);
    v += v2;

    return v;
}

gVector& gVector::operator-=(const gVector &v)
{
    m_x -= v.GetX();
    m_y -= v.GetY();
    m_z -= v.GetZ();

    return *this;

}

gVector operator-(const gVector& v1, const gVector& v2)
{
    gVector v(v1);
    v -= v2;
    return v;
}

gVector& gVector::operator*=(const double k)
{
    m_x *= k;
    m_y *= k;
    m_z *= k;

    return *this;

}

gVector operator*(const gVector &v, const double k)
{
    gVector v1(v);
    v1 *= k;
    return v1;
}

double operator*(const gVector &v1, const gVector &v2)
{

    return v1.GetScalarProductWith(v2);

}

gVector& gVector::operator/=(const double k)
{
    *this *= 1/k;
    return *this;
}

gVector operator/(const gVector v, const double k)
{
    gVector v1(v);
    v1 *= 1/k;
    return v1;
}

bool operator==(const gVector& v1, const gVector& v2)
{
    if((v1.GetX()==v2.GetX()) & (v1.GetY()==v2.GetY()) & (v1.GetZ()==v2.GetZ()))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator!=(const gVector& v1, const gVector& v2)
{
    if(v1 == v2)
    {
        return false;
    }
    else
    {
        return true;
    }
}
