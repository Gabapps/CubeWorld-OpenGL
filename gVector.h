#ifndef GVECTOR_H_INCLUDED
#define GVECTOR_H_INCLUDED

#include <iostream>
#include <math.h>

class gVector
{
    public :

    gVector();
    gVector(double x);
    gVector(double x, double y);
    gVector(double x, double y, double z);

    //Methods

    void SetCoord(double x, double y, double z);
    void SetCoordByAngle(double xom, double zom, double norme);
    void AddCoord(double x, double y, double z);

    double GetX() const;
    double GetY() const;
    double GetZ() const;

    double GetZom() const;
    double GetXom() const;

    double GetNorme() const;

    double GetScalarProductWith(const gVector& vector) const;
    bool IsColinearWith(const gVector& vector) const;
    bool IsOrthonormalWith(const gVector& vector) const;

    void Afficher(std::ostream &flux) const;

    //Operators

    gVector& operator+=(const gVector &v);
    gVector& operator-=(const gVector &v);
    gVector& operator*=(const double k);
    gVector& operator/=(const double k);

    protected :

    double m_x;
    double m_y;
    double m_z;

};


    //Operators

    std::ostream &operator<<(std::ostream &flux, gVector const& vector);
    gVector operator+(const gVector&, const gVector&);
    gVector operator-(const gVector&, const gVector&);
    gVector operator*(const gVector&, const double k);
    gVector operator/(const gVector&, const double k);
    double operator*(const gVector&, const gVector&);
    bool operator==(const gVector&, const gVector&);
    bool operator!=(const gVector&, const gVector&);


#endif // GVECTOR_H_INCLUDED
