#include <Arduino.h>
#include "../general/gameobject.h"

class Bullet: public GameObject
{
    public:
        void CollisionCheck();
};