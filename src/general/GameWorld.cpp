#include "GameWorld.hpp"


GameWorld::GameWorld(TFT_eSPI* tft)
{
    _tft = tft;

    Width = _tft->width();
    Height = _tft->height();
    _lastCleanup = millis();
    _objects = new std::list<GameObject *>();
}

void GameWorld::SetGravity(Vector2DF grav)
{
    _gravity = grav;
    _gravityenabled = (_gravity.Length() != 0);
}

bool GameWorld::AddObject(GameObject *go)
{
    _objects->push_back(go);
    return true;
}

bool GameWorld::RemoveObject(GameObject *go)
{
    _objects->remove(go);
    return true;
}

void GameWorld::Loop(float elapsed)
{
    MoveObjects(elapsed);

    unsigned long now = millis();
    if(now - _lastCleanup > 100)
    {
        _lastCleanup = now;
        Cleanup();
    }
    RenderObjects();
}

void GameWorld::MoveObjects(float elapsed)
{
    for (GameObject *obj : *_objects)
    {
        if(obj->Delete == true)
            continue;

        obj->Move(elapsed);

        if(_gravityenabled && obj->Gravity)
        {
            obj->Velocity = obj->Velocity + _gravity * elapsed;
        }
             
        if(obj->OutOfBoundsCheck(_tft))
        {
            obj->Delete = true;
            continue;
        }
    }
}

void GameWorld::RenderObjects()
{
    for (GameObject *obj : *_objects)
    {
        if(obj->Delete == true)
            continue;

        obj->Render(_tft); 
    }
}

void GameWorld::Clear()
{
    for (GameObject *obj : *_objects)
    {
        obj->RemoveFromScreen(_tft);
        delete obj;
    }
    _objects->clear();
}

void GameWorld::Cleanup()
{
    std::list<GameObject *> _removedobjects;
    for (GameObject *obj : *_objects)
    {
        if(obj->Delete == true)
            _removedobjects.push_back(obj);
    }

    for (GameObject *obj : _removedobjects)
    {
        obj->RemoveFromScreen(_tft);
        _objects->remove(obj);
        delete obj;
    }
}

std::list<GameObject *>* GameWorld::GetObjects()
{
    return _objects;
}

int GameWorld::CountObjects(int type)
{
    return std::count_if(_objects->begin(), _objects->end(), [&](GameObject *go) { return go->ObjectType == type; });
}

GameObject* GameWorld::CollisionCheck(GameObject *go, int objecttype)
{
    for (GameObject *obj : *_objects)
    {
        if(obj->Delete || obj->ObjectType != objecttype)
            continue;

        if(go->CollidesWith(obj))
            return obj;
    }

    return NULL;
}

void GameWorld::Explode(GameObject *go)
{
    int num = go->PolygonPoints / 2;
    if(num < 1)
        num = 1;

    for(int i = 0; i < num; i++)
    {
        Debris *debr = new Debris(go);
        AddObject(debr);
    }

    go->RemoveFromScreen(_tft);
}