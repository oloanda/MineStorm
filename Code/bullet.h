#pragma once
#include <raylib.h>

typedef struct Bullet
{
	Vector2 position;
	Vector2 addPosition;
	float speed;
	float angle;
} Bullet;

void initBullet(Bullet* bullet,Vector2 position,float angle);
void updateBullet(Bullet* bullet,float deltaTime);
void drawBullet(Bullet* bullet, const Texture2D texture, Color color);
void unloadBulletData(Bullet* bullet);
