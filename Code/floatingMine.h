#pragma once
#include <raylib.h>
#include "Math.h"

//This structre is only to taste collion
typedef struct FloatingMine
{
    Vector2 position;
    Vector2 speed;
    float rotation;
    float scale;
    int life;

    AABB rectComponent;

} FloatingMine;

void initFloatingMine(FloatingMine* enemy);
void updateFloatingMine(FloatingMine* enemy,float deltaTime);
void drawFloatingMine(FloatingMine* mine,const Texture2D* texture);
