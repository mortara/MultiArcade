#include "gameobject.h"


double determinant(Vector2DF vec1, Vector2DF vec2){
     return vec1.X * vec2.Y - vec1.Y * vec2.X;
 }
 
 //one edge is a-b, the other is c-d
 bool edgeIntersection(Vector2DF a, Vector2DF b, Vector2DF c, Vector2DF d){
     double det = determinant(b - a, c - d);
     double t   = determinant(c - a, c - d) / det;
     double u   = determinant(b - a, c - a) / det;
     if ((t < 0) || (u < 0) || (t > 1) || (u > 1)) {
        return false;
         //return Vector2DF();
     } else {
        return true;
         //return a * (1.0 - t) + b * t;
     }
 }

void GameObject::Setup(int16_t num, Vector2DF *points)
{
    _numPoints = num;
    _points = points;
    _rotatedpoints = new Vector2DF[_numPoints] {};
    Rold = 1;
}

void GameObject::Move(float d)
{

    Velocity.X += Acceleration.X * d;
    Velocity.Y += Acceleration.Y * d;

    Position.X = Position.X + Velocity.X * d;
    Position.Y = Position.Y + Velocity.Y * d;

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

void GameObject::Render(TFT_eSPI tft, bool force)
{
    //tft.fillRect(   X,    Y, 5, 5, WHITE);
    if(!force && (int)Position.X == (int)OldPosition.X && (int)Position.Y == (int)OldPosition.Y && (int)Rold == (int)Rotation)
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
    Vector2DF rotatedstartpoint = _points[0].GetRotated(rads);

    int32_t xs = (int32_t)(cx + rotatedstartpoint.X);
    int32_t ys = (int32_t)(cy + rotatedstartpoint.Y);

    int32_t xc = xs;
    int32_t yc = ys;

    for(int i = 1; i < _numPoints; i++)
    {
        Vector2DF rotatedpoint = _points[i].GetRotated(rads);

        int32_t xt = (int32_t)(cx + rotatedpoint.X);
        int32_t yt = (int32_t)(cy + rotatedpoint.Y);

        tft.drawLine(xc,yc,xt,yt, color);

        xc = xt;
        yc = yt;
    }

    tft.drawLine(xc,yc,xs, ys, color);
}

bool GameObject::Intersects(GameObject * go2)
{
    if(!( (go2->Position.X) > (Position.X+Size.X) || (go2->Position.X+go2->Size.X) < Position.X || (go2->Position.Y) > (Position.Y + Size.Y) || (go2->Position.Y+go2->Size.Y) < Position.Y))
    {
        if(go2->_numPoints > 0 && _numPoints > 0)
        {
            float rads1 = Rotation / 360.0f * 2.0f * PI;
            float rads2 = go2->Rotation / 360.0f * 2.0f * PI;

            for(int p1 = 0; p1 < _numPoints; p1++)
            {
                Vector2DF v1s = _points[p1].GetRotated(rads1);

                int next = p1+1;
                if(next == _numPoints)
                    next = 0;

                Vector2DF v1e = _points[next].GetRotated(rads1);

                for(int p2 = 0; p2 < go2->_numPoints; p2++)
                {
                    Vector2DF v2s = go2->_points[p2].GetRotated(rads2);

                    next = p2+1;
                    if(next == go2->_numPoints)
                        next = 0;

                    Vector2DF v2e = go2->_points[next].GetRotated(rads2);
                    if(edgeIntersection(v1s, v1e, v2s, v2e))
                        return true;
                }
            }
            return false;
        }
        return true;
    }
    return false;
}


