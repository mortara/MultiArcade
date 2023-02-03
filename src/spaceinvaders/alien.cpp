#include "alien.hpp"

Alien::Alien(int c, int r, int num_cols, TFT_eSPI* screen )
{
    ObjectType = 2;
    
    X = 27 + (screen->width() - 40) / num_cols * c;

    Position = Vector2DF(X, 10 * r);
    Velocity.Y = 2;
    float scale = 2;

    Row = r;
    Column = c;

    GameObject::Setup(4, new Vector2DF[4] 
        {
            Vector2DF(-2.0f,2.0f) * scale, 
            Vector2DF(2.0f,2.0f)* scale,
            Vector2DF(2.0f,-2.0f)* scale, 
            Vector2DF(-2.0f,-2.0f)* scale
        });
}   

void Alien::Move(float elapsed)
{
    GameObject::Move(elapsed);
    c += elapsed;
    Position.X = X + (int)((int)(cos(c) * 50) / 5) * 2.5;
}
