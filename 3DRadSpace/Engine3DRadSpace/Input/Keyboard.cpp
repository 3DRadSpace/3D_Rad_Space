#include "Keyboard.hpp"

void Engine3DRadSpace::Input::Keyboard::_addKey(uint8_t k)
{
    for (int i = 0; i < 10; i++)
    {
        if (_keys[i] == k) return; //Do not duplicate keys.
        if (_keys[i] == 0)
        {
            _keys[i] = k;
            break;
        }
    }
}

void Engine3DRadSpace::Input::Keyboard::_removeKey(uint8_t k)
{
    for (int i = 0; i < 10; i++)
    {
        if (k == _keys[i]) _keys[i] = 0;
    }
}

void Engine3DRadSpace::Input::Keyboard::_erase()
{
    for (int i = 0; i < 10; i++)
    {
        _keys[i] = 0;
    }
}

Engine3DRadSpace::Input::Keyboard::Keyboard() :
    _keys{0}
{
}

bool Engine3DRadSpace::Input::Keyboard::IsKeyDown(Key k)
{
    for (int i = 0; i < 10; i++)
    {
        if (static_cast<uint8_t>(k) == _keys[i])
        {
            return true;
        }
    }
    return false;
}

bool Engine3DRadSpace::Input::Keyboard::IsKeyUp(Key k)
{
    for (int i = 0; i < 10; i++)
    {
        if (static_cast<uint8_t>(k) == _keys[i])
        {
            return false;
        }
    }
    return true;
}
