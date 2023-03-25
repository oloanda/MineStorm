#pragma once
#include <raylib.h>
#include "common.h"

#include "mineLayer.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"

typedef enum
{
	GS_MENU,
	GS_PAUSE,
	GS_PAUSE2,
	GS_PLAY,
	GS_PLAY2,
	GS_GAMEOVER,
	GS_GAMEOVER2,
	GS_CLOSE,
} GameState;

typedef struct Game
{
	GameState state;
	Texture2D atlas;
	Texture2D foreground;
	Texture2D background;

	Rectangle bulletCoord;
	float ticksCount;

	Player player[2];
	MineLayer layer;
	int enemyCount;
	Enemy enemies[ENEMY_COUNT];
	int    level;
	bool   levelStart;
} Game;

bool initGame(Game* game);
void runGameLoop(Game* game);
void processInput(Game* game);
void updateGame(Game* game);

int gameEnemyAliveCount(Game* game);

void gameAddBullet(Player *player);
void gameRemoveBullet(Player *player);
void gameCollisions(Game* game, Player *player);

void loadData(Game* game);
void unloadData(Game* game);

void gameIsOver(Game* game);
void Shutdown(Game* game);


bool initGame(Game* game);
void processInput(Game* game);
void updateGame(Game* game);
void runGameLoop(Game* game);
void shutdown(Game* game);


void pauseGame(Game* game);
void drawGameBackground(Game* game);
void loadGameData(Game* game);
void unloadGameData(Game* game);
