#include "gameobject.hpp"


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
    PolygonPoints = num;
    _points = points;
    _rotatedpoints = new Vector2DF[PolygonPoints] {};
    Rold = 1;
}

void GameObject::SetOrientation(float d)
{
    if(PolygonPoints == 0 || d == Orientation)
        return;

    float r = degreesToRadians(d);

    for(int i = 0; i < PolygonPoints; i++)
    {
        _rotatedpoints[i] = _points[i].GetRotated(r);
    }

    Orientation = d;
}

void GameObject::Move(float d)
{
    Velocity = Velocity + Acceleration * d;
    Position = Position + Velocity * d;
    Orientation = Orientation + vR * d;
}

void GameObject::RemoveFromScreen(TFT_eSPI tft)
{
    if(PolygonPoints > 0)
        RenderLines(tft, BLACK, OldPosition, Rold);
        //tft.fillCircle((int16_t)Xold, (int16_t)Yold, Size * 5, BLACK);
    else
        tft.drawPixel((int32_t)OldPosition.X, (int32_t)OldPosition.Y, BLACK);
}

void GameObject::Render(TFT_eSPI tft, bool force)
{
    //tft.fillRect(   X,    Y, 5, 5, WHITE);
    if(!force && (int)Position.X == (int)OldPosition.X && (int)Position.Y == (int)OldPosition.Y && (int)Rold == (int)Orientation)
        return;

    RemoveFromScreen(tft);

    Rold = Orientation;
    OldPosition = Position;

    if(PolygonPoints == 0)
    {
        tft.drawPixel((int32_t)Position.X, (int32_t)Position.Y, Color);
    }
    else
    {
        RenderLines(tft, Color, Position, Orientation);
    }
}

void GameObject::RenderLines(TFT_eSPI tft, int16_t color, Vector2DF position, float rotation)
{
    float rads = degreesToRadians(rotation);

    Vector2DF drawstart = position + _points[0].GetRotated(rads);
    Vector2DF drawcurrent = drawstart;

    for(int i = 1; i < PolygonPoints; i++)
    {
        Vector2DF target = position + _points[i].GetRotated(rads);
   
        tft.drawLine(drawcurrent.X,drawcurrent.Y,target.X,target.Y, color);

        drawcurrent = target;
    }

    tft.drawLine(drawcurrent.X, drawcurrent.Y, drawstart.X, drawstart.Y, color);
}

bool GameObject::Intersects(GameObject * go2)
{
    //if(!( (go2->Position.X) > (Position.X+Size.X) || (go2->Position.X+go2->Size.X) < Position.X || (go2->Position.Y) > (Position.Y + Size.Y) || (go2->Position.Y+go2->Size.Y) < Position.Y))
    {
        if(go2->PolygonPoints > 0 && PolygonPoints > 0)
        {
            float rads1 = degreesToRadians(Orientation);
            float rads2 = degreesToRadians(go2->Orientation);

            for(int p1 = 0; p1 < PolygonPoints; p1++)
            {
                Vector2DF v1s = Position + _points[p1].GetRotated(rads1);

                int next = p1+1;
                if(next == PolygonPoints)
                    next = 0;

                Vector2DF v1e = Position + _points[next].GetRotated(rads1);

                for(int p2 = 0; p2 < go2->PolygonPoints; p2++)
                {
                    Vector2DF v2s = go2->Position + go2->_points[p2].GetRotated(rads2);

                    next = p2+1;
                    if(next == go2->PolygonPoints)
                        next = 0;

                    Vector2DF v2e = go2->Position + go2->_points[next].GetRotated(rads2);
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

bool GameObject::PointInPolygon(Vector2DF test) {
    float rads1 = degreesToRadians(Orientation);
    test = test - Position;
    int i, j, nvert = PolygonPoints;
    bool c = false;
    for (i = 0, j = nvert-1; i < nvert; j = i++) {
        if ( ((_points[i].GetRotated(rads1).Y>test.Y) != (_points[j].GetRotated(rads1).Y>test.Y)) &&
        (test.X < (_points[j].GetRotated(rads1).X-_points[i].GetRotated(rads1).X) * (test.Y-_points[i].GetRotated(rads1).Y) / (_points[j].GetRotated(rads1).Y-_points[i].GetRotated(rads1).Y) + _points[i].GetRotated(rads1).X) )
        c = !c;
    }
    return c;

}


