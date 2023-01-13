#include "gameobject.h"


void GameObject::Setup(int16_t num, VectorF *points)
{
    _numPoints = num;
    _points = points;
    _rotatedpoints = new VectorF[_numPoints] {};
    Rold = 1;
}

void GameObject::Move(float d)
{
    vX += aX * d;
    vY += aY * d;

    Position.X = Position.X + vX * d;
    Position.Y = Position.Y + vY * d;

    Rotation = Rotation + vR * d;
}

void GameObject::RemoveFromScreen(TFT_eSPI tft)
{
    if(_numPoints > 0)
        RenderLines(tft, BLACK, OldPosition.X, OldPosition.Y, Rold);
        //tft.fillCircle((int16_t)Xold, (int16_t)Yold, Size * 5, BLACK);
    else
        tft.drawPixel((int16_t)OldPosition.X, (int16_t)OldPosition.Y, BLACK);
}

void GameObject::Render(TFT_eSPI tft)
{
    //tft.fillRect(   X,    Y, 5, 5, WHITE);
    if((int)Position.X == (int)OldPosition.X && (int)Position.Y == (int)OldPosition.Y && (int)Rold == (int)Rotation)
        return;

    RemoveFromScreen(tft);

    Rold = Rotation;
    OldPosition.X = Position.X;
    OldPosition.Y = Position.Y;

    if(_numPoints == 0)
    {
        tft.drawPixel((int16_t)OldPosition.X, (int16_t)OldPosition.Y, WHITE);
    }
    else
    {
        RenderLines(tft, WHITE, Position.X, Position.Y, Rotation);
    }
}

void GameObject::RenderLines(TFT_eSPI tft, int16_t color, float cx, float cy, float rotation)
{
    float rads = rotation / 360.0f * 2.0f * PI; 
    VectorF rotatedstartpoint = _points[0].GetRotated(rads);

    int32_t xs = (int32_t)(cx + rotatedstartpoint.X * Size);
    int32_t ys = (int32_t)(cy + rotatedstartpoint.Y * Size);

    int32_t xc = xs;
    int32_t yc = ys;

    for(int i = 1; i < _numPoints; i++)
    {
        VectorF rotatedpoint = _points[i].GetRotated(rads);

        int32_t xt = (int32_t)(cx + rotatedpoint.X * Size);
        int32_t yt = (int32_t)(cy + rotatedpoint.Y * Size);

        tft.drawLine(xc,yc,xt,yt, color);

        xc = xt;
        yc = yt;
    }

    tft.drawLine(xc,yc,xs, ys, color);
}