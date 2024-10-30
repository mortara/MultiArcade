#include "CannonGround.hpp"

CannonGround::CannonGround(int mountains, int mountain_height, int screen_width, int screen_height)
{
    _peaks = mountains;

    float w = screen_width / (_peaks+1);
    int _nodenum = _peaks + 2;
    Vector2DF *_nodes = new Vector2DF[_nodenum]();

    _nodes[0] = Vector2DF(screen_width + 50, screen_height - 10);
    _nodes[1] = Vector2DF(-50, screen_height + 100);
    
    int _platformindex = mountains - 1;
    int last = 1;

    TargetPlatformLocation = Vector2DF(_nodes[1].X + _platformSize / 2, _nodes[1].Y);
    _nodes[2] = Vector2DF(_nodes[1].X + _platformSize, _nodes[1].Y);

    for(int i = 1; i < _peaks; i++)
    {
       if(i == _platformindex)
        {
            TargetPlatformLocation = Vector2DF(_nodes[last].X + _platformSize, _nodes[last].Y);
            _nodes[2 + i] = Vector2DF(_nodes[last].X + _platformSize, _nodes[last].Y);
        }
        else
        {
            last = 2 + i;
            _nodes[last] = Vector2DF(i*w, screen_height - 10 - random(50));
        }
    }

    GameObject::Setup(_nodenum, _nodes);
}
