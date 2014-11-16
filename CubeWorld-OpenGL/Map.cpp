#include "Map.h"
using namespace std;

double NonIntPart(double v)
{
    return v-(double)(int)v;
}

Map::Map()
{
    for(int i = 0; i<SIZE; i++)
    {
        for(int j = 0; j<SIZE; j++)
        {
            for(int k = 0; k<SIZE; k++)
            {
                m_map[i][j][k]=0;
            }
        }
    }

}

void Map::SaveMap(const std::string filename)
{
    std::ofstream file(filename.c_str());
    if(file)
    {
        cout << "Ouverture reussie" << endl;
        for(int i = 0; i<SIZE; i++)
        {
            if(i%(int)SIZE/10 == 0){cout << ".";}
            for(int j = 0; j<SIZE; j++)
            {
                for(int k = 0; k<SIZE; k++)
                {
                    file << m_map[i][j][k];
                }
            }
        }
        cout << " 100%\nSauvegarde effectuée" << endl;
        cout << file.tellp() << " octets" << endl << endl;
    }
    else
    {
        cout << "Ouverture impossible" << endl;
    }
}

void Map::LoadMap(const std::string filename)
{
    std::ifstream file(filename.c_str());
    if(file)
    {
        cout << "Ouverture reussie" << endl;
        for(int i = 0; i<SIZE; i++)
        {
            if(i%(int)SIZE/10 == 0){cout << ".";}
            for(int j = 0; j<SIZE; j++)
            {
                for(int k = 0; k<SIZE; k++)
                {
                    char a;
                    file.get(a);
                    m_map[i][j][k] = a;
                }
            }
        }
        cout << " 100%\nChargement effectue" << endl;
        cout << file.tellg() << " octets" << endl << endl;
    }
    else
    {
        cout << "Ouverture impossible" << endl;
    }
}

void Map::CreateVolume(const char type, const int x, const int y, const int z, const int sizex, const int sizey, const int sizez)
{
    for(int i(x); i < x+sizex ; i++)
    {
        for(int j(y); j < y+sizey ; j++)
        {
            for(int k(z); k < z+sizez ; k++)
            {
                m_map[i][j][k] = type;
            }
        }
    }
}

void Map::Destroy(const int x, const int y, const int z)
{
    m_map[x][y][z] = 0;
}

void Map::Destroy(const gVector pos)
{
    Destroy(int(pos.GetX()), int(pos.GetY()), int(pos.GetZ()));
}

int *Map::GetCollPos(gVector Pos) const
{
    int *collPos = new int[6];
    int i;

    //Axe X

    i = (int)Pos.GetX()-1;
    while(m_map[i][(int)Pos.GetY()][(int)Pos.GetZ()] == 0 && i >= (int)Pos.GetX()-2 && i >= 0)
    {
        i--;
    }
    collPos[XL]=i+1;



    i = (int)Pos.GetX()+1;
    while(m_map[i][(int)Pos.GetY()][(int)Pos.GetZ()] == 0 && i <= (int)Pos.GetX()+2 && i < SIZE)
    {
        i++;
    }
    collPos[XM]=i;


    //Axe Y


    i = (int)Pos.GetY()-1;
    while(m_map[(int)Pos.GetX()][i][(int)Pos.GetZ()] == 0 /*&& i >= (int)Pos.GetY()-2*/ && i >= 0)
    {
        i--;
    }
    collPos[YL]=i+1;


    i = (int)Pos.GetY()+1;
    while(m_map[(int)Pos.GetX()][i][(int)Pos.GetZ()] == 0 /*&& i <= (int)Pos.GetY()+2*/ && i < SIZE)
    {
        i++;
    }
    collPos[YM]=i;


    //Axe Z


    i = (int)Pos.GetZ()-1;
    while(m_map[(int)Pos.GetX()][(int)Pos.GetY()][i] == 0 && i >= (int)Pos.GetZ()-2 && i>=0)
    {
        i--;
    }
    collPos[ZL]=i+1;



    i = (int)Pos.GetZ()+1;
    while(m_map[(int)Pos.GetX()][(int)Pos.GetY()][i] == 0 && i <= (int)Pos.GetZ()+2 && i < SIZE)
    {
        i++;
    }
    collPos[ZM]=i;



    return collPos;
}

char Map::GetMap(int  x, int y, int z) const
{
    return m_map[x][y][z];
}

gVector Map::GetTargetCube(gVector pos, gVector ori) const
{
    gVector posCube;
    /*for(double t(0); t < 3; t+=0.1)
    {
        int x = pos.GetX()+ori.GetX()*t;
        int y = pos.GetY()+ori.GetY()*t;
        int z = pos.GetZ()+1.5+ori.GetZ()*t;
        if(x>=0 && x<SIZE && y>=0 && y<SIZE && z>=0 && z<SIZE)
        {
            if (m_map[x][y][z] != 0){return gVector(x,y,z); break;}
        }
        else{return 0; break;}
    }*/

    double x,y,z, t=0;
    while(1)
    {
        x=pos.GetX()+ori.GetX()*t;
        y=pos.GetY()+ori.GetX()*t;
        z=pos.GetZ()+ori.GetX()*t;

        if(x>=0 && x<SIZE && y>=0 && y<SIZE && z>=0 && z<SIZE)
        {
            if((NonIntPart(x)+ori.GetX()) > y+(unsigned)ori.GetY() and x+(unsigned)ori.GetX() > z+(unsigned)ori.GetZ())//face x
            {
                if(ori.GetX()>0) t+=(-(pos.GetX()+(int)(x+1)))/ori.GetX();
                else t+=(-(pos.GetX()+(int)(x-1)))/ori.GetX();
            }

            else if(y+(unsigned)ori.GetY() > x+(unsigned)ori.GetX() and y+(unsigned)ori.GetY() > z+(unsigned)ori.GetZ())//face y
            {
                if(ori.GetY()>0) t+=(-(pos.GetY()+(int)(y+1)))/ori.GetY();
                else t+=(-(pos.GetY()+(int)(y-1)))/ori.GetY();
            }

            else if(z+(unsigned)ori.GetZ() > x+(unsigned)ori.GetX() and z+(unsigned)ori.GetZ() > y+(unsigned)ori.GetY())//face z
            {
                if(ori.GetZ()>0) t+=(-(pos.GetZ()+(int)(z+1)))/ori.GetZ();
                else t+=(-(pos.GetZ()+(int)(z-1)))/ori.GetZ();
            }
            else break;
        }
        else
        {
            posCube = 0;
            break;
        }
        if (m_map[(int)x,(int)y,(int)z]!=0)
        {
            posCube.SetCoord((int)x,(int)y,(int)z);
            break;
        }

    }
    //
    return posCube;

}
