#include "Keyboard.hpp"

void Engine3DRadSpace::Input::Keyboard::_addKey(uint8_t k)
{
    for (int i = 0; i < 10; i++)
    {
        if (keys[i] == 0)
        {
            keys[i] = k;
            break;
        }
    }
}

void Engine3DRadSpace::Input::Keyboard::_removeKey(uint8_t k)
{
    for (int i = 0; i < 10; i++)
    {
        if (k == keys[i]) keys[i] = 0;
    }
}

void Engine3DRadSpace::Input::Keyboard::_erase()
{
    for (int i = 0; i < 10; i++)
    {
        keys[i] = 0;
    }
}

bool Engine3DRadSpace::Input::Keyboard::IsKeyDown(Key k)
{
    for (int i = 0; i < 10; i++)
    {
        if (static_cast<uint8_t>(k) == keys[i])
        {
            keys[i] = 0; //remove key fron the list
            return true;
        }
    }
    return false;
}

bool Engine3DRadSpace::Input::Keyboard::IsKeyUp(Key k)
{
    for (int i = 0; i < 10; i++)
    {
        if (static_cast<uint8_t>(k) == keys[i])
        {
            return false;
        }
    }
    return true;
}
