#include "gameobject.h"


void GameObject::Setup(int16_t num, VectorF *points)
{
    _numPoints = num;
    _points = points;
}

void GameObject::Move(float d)
{
    Xold = X;
    Yold = Y;

    vX += aX * d;
    vY += aY * d;

    X = X + vX * d;
    Y = Y + vY * d;
}

void GameObject::Render(TFT_eSPI tft)
{
    if(Enabled == 0 || _numPoints == 0)
        return;

    RenderLines(tft, BLACK, Xold, Yold);
    RenderLines(tft, WHITE, X, Y);
}

void GameObject::RenderLines(TFT_eSPI tft, int16_t color, float cx, float cy)
{
    
    int xs = (int)(cx + _points[0].X);
    int ys = (int)(cy + _points[0].Y);

    for(int i = 0; i < _numPoints; i++)
    {
        int xt = (int)(cx + _points[i].X);
        int yt = (int)(cy + _points[i].Y);

        tft.drawLine(xs,ys,xt,yt, WHITE);

        xs = xt;
        ys = yt;
    }
}