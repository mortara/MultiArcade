#include "CannonGround.hpp"

CannonGround::CannonGround(int _peaks, int mountain_height, int screen_width, int screen_height)
{
   
    
    int _nodenum = _peaks + 4;

    float w = (screen_width - 2 * _platformSize) / (_peaks+1);

    Vector2DF *_nodes = new Vector2DF[_nodenum]();

    _nodes[0] = Vector2DF(screen_width + 50, screen_height - 10);
    _nodes[1] = Vector2DF(-50, screen_height + 100);
    _nodes[2] = Vector2DF(0, screen_height - random(mountain_height));
    int _platformindex = _nodenum - 1;
   
    CannonPlatformLocation = Vector2DF(0 + _platformSize / 2, _nodes[2].Y);
    _nodes[3] = Vector2DF(0 + _platformSize, _nodes[2].Y);
    float cx = _platformSize;

    for(int i = 0; i < _peaks; i++)
    {
        if(i < (_peaks - 1))
            cx += w;
        else
            cx = screen_width - _platformSize;

       _nodes[4 + i] = Vector2DF(cx, (float)(screen_height - 10 - (int)random(1, mountain_height)));
       //Serial.print("Y:" + String(_nodes[4 + i].Y));
    }

    TargetPlatformLocation = Vector2DF(cx + (float)random(_platformSize), _nodes[_nodenum-2].Y);
    _nodes[_nodenum-1] = Vector2DF(cx + _platformSize * 2, _nodes[_nodenum-2].Y);
  
    GameObject::Setup(_nodenum, _nodes);
}
