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
    _rendered_points = new Vector2DF[PolygonPoints] {};
    for(int i = 0; i < PolygonPoints; i++)
    {
       if(_points[i].Length() > Radius)
            Radius = _points[i].Length();

       _rotatedpoints[i] = _points[i];
       _rendered_points[i] = _points[i];
    }
    Rold = 1;
    SetOrientation(0);   
}

void GameObject::SetOrientation(float d)
{
    if(PolygonPoints == 0 || (int)d == (int)_orientation)
        return;
    _orientation = d;

    float r = degreesToRadians(d);

    for(int i = 0; i < PolygonPoints; i++)
    {
        _rotatedpoints[i] = _points[i].GetRotated(r);
    }
}

float GameObject::GetOrientation()
{
    return _orientation;
}

void GameObject::Move(float d)
{
    Velocity = Velocity + Acceleration * d;
    Position = Position + Velocity * d;
    SetOrientation(_orientation + vR * d);
}

void GameObject::RemoveFromScreen(TFT_eSPI tft)
{
    if(PolygonPoints > 0)
        RenderLines(tft, BLACK, OldPosition, _rendered_points);
    else
        tft.drawPixel((int32_t)OldPosition.X, (int32_t)OldPosition.Y, BLACK);
}

void GameObject::Render(TFT_eSPI tft, bool force)
{
    if(!force && ((int)Position.X == (int)OldPosition.X && (int)Position.Y == (int)OldPosition.Y && (int)Rold == (int)_orientation))
        return;

    RemoveFromScreen(tft);

    Rold = _orientation;
    OldPosition = Position;

    if(PolygonPoints == 0)
    {
        tft.drawPixel((int32_t)Position.X, (int32_t)Position.Y, Color);
    }
    else
    {
        RenderLines(tft, Color, Position, _rotatedpoints);
    }
}

void GameObject::RenderLines(TFT_eSPI tft, int16_t color, Vector2DF position, Vector2DF *points)
{
    _rendered_points[0] = points[0];
    Vector2DF drawcurrent = _rendered_points[0];
    for(int i = 1; i < PolygonPoints; i++)
    {
        _rendered_points[i] = points[i];
        tft.drawLine(position.X + drawcurrent.X, position.Y + drawcurrent.Y, position.X + _rendered_points[i].X, position.Y + _rendered_points[i].Y, color);
        drawcurrent = _rendered_points[i];
    }

    tft.drawLine(position.X + drawcurrent.X, position.Y + drawcurrent.Y, position.X +  _rendered_points[0].X, position.Y + _rendered_points[0].Y, color);
}

bool GameObject::CollidesWith(GameObject * go2)
{
    if(go2->PolygonPoints > 0 && PolygonPoints > 0)
    {
        float dist = Position.DistanceSquared(go2->Position);
        if(dist > (Radius + go2->Radius) * (Radius + go2->Radius))
            return false;

        for(int p1 = 0; p1 < PolygonPoints; p1++)
        {
            Vector2DF v1s = Position + _rotatedpoints[p1];

            int next = p1+1;
            if(next == PolygonPoints)
                next = 0;

            Vector2DF v1e = Position + _rotatedpoints[next];

            for(int p2 = 0; p2 < go2->PolygonPoints; p2++)
            {
                Vector2DF v2s = go2->Position + go2->_rotatedpoints[p2];

                next = p2+1;
                if(next == go2->PolygonPoints)
                    next = 0;

                Vector2DF v2e = go2->Position + go2->_rotatedpoints[next];
                if(edgeIntersection(v1s, v1e, v2s, v2e))
                    return true;
            }
        }
        return false;
    } else if(go2->PolygonPoints > 0)
    {
        return go2->PointInPolygon(Position);
    } else if(PolygonPoints > 0)
    {
        return PointInPolygon(go2->Position);
    }
    else if(!( (go2->Position.X) > (Position.X+Size.X) || (go2->Position.X+go2->Size.X) < Position.X || (go2->Position.Y) > (Position.Y + Size.Y) || (go2->Position.Y+go2->Size.Y) < Position.Y))
        return true;

    return false;
}

bool GameObject::PointInPolygon(Vector2DF test) {
    test = test - Position;
    int i, j, nvert = PolygonPoints;
    bool c = false;
    for (i = 0, j = nvert-1; i < nvert; j = i++) {
        if ( ((_rotatedpoints[i].Y>test.Y) != (_rotatedpoints[j].Y>test.Y)) &&
        (test.X < (_rotatedpoints[j].X-_rotatedpoints[i].X) * (test.Y-_rotatedpoints[i].Y) / (_rotatedpoints[j].Y-_rotatedpoints[i].Y) + _rotatedpoints[i].X) )
        c = !c;
    }
    return c;

}


