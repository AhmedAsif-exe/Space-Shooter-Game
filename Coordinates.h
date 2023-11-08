#ifndef COORDINATES_H
#define COORDINATES_H
struct Coordinates
{
    float x;
    float y;
    Coordinates() : x(0), y(0) {}
    Coordinates(float X, float Y) : x(X), y(Y) {}
    Coordinates(int X, int Y) : x(X), y(Y) {}
    Coordinates& setCo(float X, float Y)
    {
        x = X;
        y = Y;
        return *this;
    }
    Coordinates operator+(const Coordinates& obj)
    {
        Coordinates temp(x, y);
        temp.x = x + obj.x;
        temp.y = y + obj.y;
        
        return temp;
    }
};
#endif
