#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <fstream>
#include "gVector.h"

#define SIZE 32

enum Position {XL,XM,YL,YM,ZL,ZM};

class Map
{
    public :

    Map();
    void LoadMap(const std::string);
    void SaveMap(const std::string);
    void CreateVolume(const char, const int, const int, const int, const int, const int, const int);
    void Destroy(const int, const int, const int);
    void Destroy(const gVector);
    int *GetCollPos(gVector Pos) const;
    char GetMap(int, int, int) const;
    gVector GetTargetCube(gVector pos, gVector ori) const;

    protected :

    char m_map[SIZE][SIZE][SIZE];

};

#endif // MAP_H_INCLUDED
