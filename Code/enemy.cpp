#include "enemy.h"
#include "common.h"

void initEnemy(Enemy* enemy, Vector2 position, EnemyType type, EnemySize size)
{
	enemy->life = MAX_ENEMY_LIFE;
	enemy->position = position;

	switch(size)
	{
		case ES_SMALL:
		{
			enemy->speed.x = 60;
			enemy->speed.y = 60;
		}break;
		case ES_MEDIUM:
		{
			enemy->speed.x = 40;
			enemy->speed.y = 40;
		}break;
		case ES_BIG:
		{
			enemy->speed.x = 20;
			enemy->speed.y = 20;
		}break;
		default:
		{
			enemy->speed.x = 0;
			enemy->speed.y = 0;
		}
	}
	enemy->rotation = 0;
	enemy->type = type;
	enemy->size = size;
}

void updateEnemy(Enemy* enemy,float deltaTime)
{
	if(enemy->life <= 0.0f) //if enemy is dead, we do not update his position
		return;

	Vector2 *position = &enemy->position;

	if (enemy->active)
	{
		position->x += enemy->speed.x * deltaTime;
		position->y += enemy->speed.y * deltaTime;
	}

	if (position->x < 64.0f) { position->x = (float)SCREEN_WIDTH - 64.0f; }
	else if (position->x > (float)SCREEN_WIDTH - 64.0f) { position->x = 64.0f; }

	if (position->y < 80.0f) { position->y = (float)SCREEN_HEIGHT - 80.0f; }
	else if (position->y > (float)SCREEN_HEIGHT - 80.0f) { position->y = 80.0f; }

}

void drawEnemy(Enemy* enemy, const Texture2D texture)
{
	Color color = RED;
	Vector2 size;
	Rectangle textureCoord = {0};

	if (enemy->type == ET_NONE)
		return;
	if (!enemy->active)
		textureCoord = {345, 90, 75, 75};
	else
	{
		switch (enemy->type)
		{
			case ET_NONE: break;
			case ET_FLOATING: textureCoord = {70, 332, 117, 109}; break;
			case ET_FIREBALL: textureCoord = {846, 332, 104, 106}; break;
			case ET_MAGNETIC: textureCoord = {335, 332, 99, 105}; break;
			case ET_MAGNETIC_FIREBALL: textureCoord = {567, 308, 149, 153}; break;
		}
	}

	switch(enemy->size)
	{
		case ES_NONE:
		{
			size.x = textureCoord.width / 8;
			size.y = textureCoord.height / 8;
			color = WHITE;
		}break;
		case ES_SMALL:
		{
			size.x = textureCoord.width / 8;
			size.y = textureCoord.height / 8;
		}break;
		case ES_MEDIUM:
		{
			size.x = textureCoord.width / 4;
			size.y = textureCoord.height / 4;
		}break;
		case ES_BIG:
		{
			size.x = textureCoord.width / 2;
			size.y = textureCoord.height / 2;
		}break;
	}

	Rectangle position = {
		enemy->position.x,
		enemy->position.y,
		size.x,
		size.y};

	Vector2 center = {position.width / 2.0f, position.height / 2.0f};
	DrawTexturePro(texture, textureCoord ,position,center,enemy->rotation, color);
}
