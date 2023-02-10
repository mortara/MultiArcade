#include "ground.hpp"

Ground::Ground(int mountains, int screen_width, int screen_height)
{
    _peaks = mountains;

    float w = screen_width / (_peaks+1);
    int _nodenum = _peaks + 2;
    Vector2DF *_nodes = new Vector2DF[_nodenum]();

    _nodes[0] = Vector2DF(screen_width + 50, screen_height - 10);
    _nodes[1] = Vector2DF(-50, screen_height + 100);
    int _platformindex = random(mountains - 4) + 2;
    Vector2DF _last;

    for(int i = 0; i < _peaks; i++)
    {
        if(i == _platformindex)
        {
            _platformLocation = _last;
            _nodes[2 + i] = Vector2DF(_last.X + _platformSize, _last.Y);
        }
        else
        {
            _last = Vector2DF(i*w, screen_height - 10 - random(50));
            _nodes[2 + i] = _last;
        }
    }

    GameObject::Setup(_nodenum, _nodes);
}