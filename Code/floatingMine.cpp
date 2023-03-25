#include "floatingMine.h"
#include "common.h"

void initFloatingMine(FloatingMine* mine)
{
    mine->life = 1;
    mine->position.x = GetRandomValue(0,SCREEN_WIDTH);
    mine->position.y = GetRandomValue(0,SCREEN_HEIGHT);
    mine->speed.x = GetRandomValue(-20,80);
    mine->speed.y = GetRandomValue(-20,80);
    mine->rotation = GetRandomValue(0,360);
    mine->scale = 128.0f;

    //mine->rectComponent.min.x = mine->position.x;
    //mine->rectComponent.min.y = mine->position.y;
    //mine->rectComponent.max.x = mine->position.x + mine->scale / 2.0f;
    //mine->rectComponent.max.y = mine->position.y + mine->scale /2.0f;
    /*mine->rectComponent.position.x = mine->position.x;
    mine->rectComponent.position.y = mine->position.y;
    mine->rectComponent.size.x = mine->scale;
    mine->rectComponent.size.y = mine->scale;*/

}

void updateFloatingMine(FloatingMine* mine,float deltaTime)
{
    if(mine->life <= 0.0f) //if enemy is dead, we do not update his position
    {
        mine->scale = 0.0f;
        return;
    } 
    
    Vector2 position = mine->position;

    position.x += mine->speed.x * deltaTime;
    position.y += mine->speed.y * deltaTime;

    if (position.x < 64.0f) { position.x = (float)SCREEN_WIDTH - 64.0f; }
    else if (position.x > (float)SCREEN_WIDTH - 64.0f) { position.x = 64.0f; }

    if (position.y < 80.0f) { position.y = (float)SCREEN_HEIGHT - 80.0f; }
    else if (position.y > (float)SCREEN_HEIGHT - 80.0f) { position.y = 80.0f; }


    mine->position = position;

    //update rectangle component
    //mine->rectComponent.min.x = (mine->position.x <  mine->rectComponent.min.x) ? mine->position.x : mine->rectComponent.min.x ;
    //mine->rectComponent.min.y = (mine->position.y <  mine->rectComponent.min.y) ? mine->position.y : mine->rectComponent.min.y ;
    //mine->rectComponent.max.x = (mine->position.x >  mine->rectComponent.max.x) ? mine->position.x : mine->rectComponent.max.x ;
    //mine->rectComponent.max.y = (mine->position.y >  mine->rectComponent.max.y) ? mine->position.y : mine->rectComponent.max.y ;
}
void drawFloatingMine(FloatingMine* mine,const Texture2D* texture)
{
    if(mine->life > 0)
    {
        Rectangle rect = { texture->width,texture->width /4.0f,texture->width/4.0f,texture->height/2.0f};
        Rectangle position = {mine->position.x,mine->position.y,mine->scale,mine->scale};
        
        Vector2 center = {mine->scale / 2.0f,mine->scale / 2.0f};
        DrawTexturePro(*texture,rect,position,center,mine->rotation,WHITE);
    }
    //Rectangle rect = { texture->width,texture->width /4.0f,texture->width/4.0f,texture->height/2.0f};
    //Rectangle position = {mine->position.x,mine->position.y,mine->scale,mine->scale};
    
    //Vector2 center = {mine->scale / 2.0f,mine->scale / 2.0f};
    //DrawTexturePro(*texture,rect,position,center,mine->rotation,WHITE);
}