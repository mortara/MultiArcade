

#ifndef VECTOR2DF_H
#define VECTOR2DF_H

class Vector2DF
{
    public:
        float X;
        float Y;

        Vector2DF();
        Vector2DF(float x, float y);

        void Rotate(float rads);
        Vector2DF GetRotated(float rads);

        float Distance(Vector2DF v2);

        Vector2DF operator + (Vector2DF const &obj)
        {
            Vector2DF r = Vector2DF();
            r.X = X + obj.X;
            r.Y = Y + obj.Y;
            return r;
        }

        Vector2DF operator - (Vector2DF const &obj)
        {
            Vector2DF r = Vector2DF();
            r.X = X - obj.X;
            r.Y = Y - obj.Y;
            return r;
        }

        Vector2DF operator * (Vector2DF const &obj)
        {
            Vector2DF r = Vector2DF();
            r.X = X * obj.X;
            r.Y = Y * obj.Y;
            return r;
        }

        Vector2DF operator * (double f)
        {
            Vector2DF r = Vector2DF();
            r.X = X * f;
            r.Y = Y * f;
            return r;
        }
};



#endif