#pragma once
#include <raylib.h>


typedef enum EnemySize
{
	ES_NONE,
	ES_SMALL,
	ES_MEDIUM,
	ES_BIG
} EnemySize;

typedef enum EnemyType
{
	ET_NONE,
	ET_FLOATING,
	ET_FIREBALL,
	ET_MAGNETIC,
	ET_MAGNETIC_FIREBALL,
} EnemyType;

typedef struct Enemy
{
	Vector2   position;
	Vector2   speed;
	float     rotation;
	int       life;
	bool      active;
	EnemyType type;
	EnemySize size;
} Enemy;

void initEnemy(Enemy* enemy, Vector2 position, EnemyType type, EnemySize size);
void makeEnemyType(Enemy* enemy, EnemyType type);
void updateEnemy(Enemy* enemy,float deltaTime);
void drawEnemy(Enemy* enemy, const Texture2D texture);
void loadEnemyData(Enemy* enemy);
void unLoadEnemyData(Enemy* enemy);
