#include "game.h"
#include "draw.h"
#include "Math.h"

//cross->textureCoord[0] = (Rectangle){345, 90, 75, 75};
//ship->textureCoord[0] = (Rectangle){513, 89, 256, 79};

#include <stdlib.h>

static int framesCounter;

int addEnemy(Game *game, EnemySize size)
{
	for (int i = 0; i < game->enemyCount;i++)
	{
		Enemy *enemy = &game->enemies[i];
		if (!enemy->active)
		{
			initEnemy(enemy, enemy->position, enemy->type, size);
			enemy->active = true;
			return (1);
		}
	}
	return (0);
}

void initLevel1(Game *game)
{
	Vector2 Random;

	game->layer = {};
	initLayer(&game->layer);

	game->enemyCount = ENEMY_COUNT;
	game->level = 1;
	for(int i = 0; i < game->enemyCount; i++)
	{
		Random.x = GetRandomValue(64.0f, (float)SCREEN_WIDTH - 64.0f);
		Random.y = GetRandomValue(80.0f, SCREEN_HEIGHT - 80.0f);
		initEnemy(&game->enemies[i], Random, ET_FLOATING, ES_NONE);
		game->enemies[i].active = false;
	}
}

bool initGame(Game* game)
{
	game->state = GS_MENU;
	InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"VICTOR-MATHIEU-OSVALDO");
	SetExitKey(KEY_NULL);
	SetTargetFPS(60);

	initPlayer(&game->player[0], {SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT / 2.0f});
	initPlayer(&game->player[1], {SCREEN_WIDTH / 1.5f, SCREEN_HEIGHT / 2.0f});

	initLevel1(game);

	loadData(game);
	game->ticksCount = 0;
	return true;
}

void runGameLoop(Game* game)
{
	while (!WindowShouldClose() && game->state != GS_CLOSE)
	{
		game->ticksCount = GetFrameTime();
		processInput(game);
		updateGame(game);
		drawGame(game, framesCounter);
	}

}


int setInputFlagPressed(KeyboardKey key, PlayerAction *flag, PlayerAction action)
{
	if(IsKeyPressed(key))
	{
		//*flag |= action;
		*flag =  (PlayerAction)(*flag | action);
		return (1);
	}
	else
		*flag = (PlayerAction)(*flag & ~action);
	return (0);
}

void setInputFlag(KeyboardKey key, PlayerAction *flag, PlayerAction action)
{
	if(IsKeyDown(key))
		//*flag |= action;
		*flag =  (PlayerAction)(*flag | action);

	else
		//*flag &= ~action;
		*flag = (PlayerAction)(*flag & ~action);
}

void processInput(Game* game)
{
	Player *player1 = &game->player[0];
	Player *player2 = &game->player[1];
	if(IsKeyPressed(KEY_SPACE))
	{
		static GameState temp = {};

		if (game->state == GS_PLAY || game->state == GS_PLAY2)
		{
			temp = game->state;
			game->state = GS_PAUSE;
		}
		else if (game->state == GS_PAUSE)
			game->state = temp;
	}

	setInputFlagPressed(KEY_F, &player1->action, PA_SHOOT);
	if (!setInputFlagPressed(KEY_T, &player1->action, PA_TELEPORT))
		setInputFlagPressed(KEY_E, &player1->action, PA_TELEPORT);
	setInputFlag(KEY_D, &player1->action, PA_TURN_LEFT);
	setInputFlag(KEY_G, &player1->action, PA_TURN_RIGHT);
	setInputFlag(KEY_R, &player1->action, PA_ACCELERATION);

	if(IsKeyPressed('K') && (game->state == GS_MENU))
		game->state = GS_PLAY2;
	if (game->state == GS_PLAY2)
	{
		setInputFlagPressed(KEY_K, &player2->action, PA_SHOOT);
		if (!setInputFlagPressed(KEY_U, &player2->action, PA_TELEPORT))
			setInputFlagPressed(KEY_O, &player2->action, PA_TELEPORT);
		setInputFlag(KEY_J, &player2->action, PA_TURN_LEFT);
		setInputFlag(KEY_L, &player2->action, PA_TURN_RIGHT);
		setInputFlag(KEY_I, &player2->action, PA_ACCELERATION);
	}
	if(IsKeyPressed(KEY_ESCAPE))
	{
		if (game->state == GS_MENU)
			game->state = GS_CLOSE;
		if (game->state == GS_PAUSE || game->state == GS_GAMEOVER)
		{
			game->state = GS_MENU;
			*player1 = {0};
			*player2 = {0};
			initPlayer(player1, {SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT / 2.0f});
			initPlayer(player2, {SCREEN_WIDTH / 1.5f, SCREEN_HEIGHT / 2.0f});
			initLevel1(game);
			game->levelStart = false;
		}
	}
}

void updateGame(Game* game)
{
	switch(game->state)
	{
		case GS_MENU:
		{
			if (game->player[1].action & PA_SHOOT)
			{
				game->state = GS_PLAY2;
				//game->player[1].action &= ~(PA_SHOOT);
				game->player[1].action = (PlayerAction)(game->player[1].action & ~(PA_SHOOT));
			}
			else if (game->player[0].action & PA_SHOOT)
				game->state = GS_PLAY;
			//game->player[0].action &= ~(PA_SHOOT);
			game->player[0].action = (PlayerAction)(game->player[0].action & ~(PA_SHOOT));

			framesCounter++;
		}break;
		case GS_PLAY:
		case GS_PLAY2:
		{
			if (game->levelStart == false)
			{
				if (updateLayer(&game->layer, game->ticksCount))
				{
					game->levelStart = true;
					addEnemy(game, ES_BIG);
					addEnemy(game, ES_BIG);
				}
			}
			if (game->levelStart)
			{
				updatePlayer(&game->player[0], game->ticksCount);
				if (game->player[0].action & PA_SHOOT)
				{
					gameAddBullet(&game->player[0]);
					//game->player[0].action &= ~PA_SHOOT;
					game->player[0].action = (PlayerAction)(game->player[0].action & ~(PA_SHOOT));

				}
				if (game->state == GS_PLAY2)
				{
					if (game->player[1].action & PA_SHOOT)
						gameAddBullet(&game->player[1]);
					updatePlayer(&game->player[1], game->ticksCount);
				}
				for(int i = 0; i < game->enemyCount; i++)
					updateEnemy(&game->enemies[i], game->ticksCount);

				for(int i = 0; i < game->player[0].bulletCount; i++)
				{
					Bullet* bullet = &game->player[0].bullets[i];
					updateBullet(bullet,game->ticksCount);
				}

				if (game->state == GS_PLAY2)
				{
					for(int i = 0; i < game->player[1].bulletCount; i++)
					{
						Bullet* bullet = &game->player[1].bullets[i];
						updateBullet(bullet,game->ticksCount);
					}
				}

				gameCollisions(game, &game->player[0]);
				if (game->state == GS_PLAY2)
					gameCollisions(game, &game->player[1]);
				gameRemoveBullet(&game->player[0]);
				gameRemoveBullet(&game->player[1]);
				gameIsOver(game);
			}
		} break;
		default:
		{
			framesCounter++;
		}
	}
}


void gameAddBullet(Player *player)
{
	Vector2 *position = &player->position;
	float   rotation = player->rotation;
	if(player->bulletCount == BULLET_CAPACITY)
		return;

	Bullet bullet = {0};

	initBullet(&bullet, *position, rotation);

	player->bullets[player->bulletCount] = bullet;
	player->bulletCount += 1;
}

void gameRemoveBullet(Player *player)
{

	for(int i = 0; i < player->bulletCount; i++)
	{
		Bullet* bullet = &player->bullets[i];

		if (lengthVector2d({bullet->addPosition.x, bullet->addPosition.y}) > SCREEN_HEIGHT / 2)
		{
			player->bullets[i] = player->bullets[player->bulletCount - 1];
			player->bulletCount -= 1;
		}
	}
}

int gameEnemyAliveCount(Game* game)
{
	int count = 0;
	for(int i = 0; i < game->enemyCount; i++)
	{
		//if(game->enemies[i].life > 0)
		//count++;
	}
	return count;
}
void loadData(Game* game)
{
	game->atlas = LoadTexture("../Assets/mines.png");
	game->background = LoadTexture("../Assets/background.png");
	game->foreground = LoadTexture("../Assets/foreground.png");
}

void unloadData(Game* game)
{
	UnloadTexture(game->atlas);
	UnloadTexture(game->background);
	UnloadTexture(game->foreground);
}

//TODO : Collisions

int collisionEnemyBullet(Game *game, Player *player, Enemy *enemy, Bullet *bullet)
{
	Rectangle enemyRec = {enemy->position.x, enemy->position.y, 25, 25};
	Rectangle bulletRec = {bullet->position.x, bullet->position.y, 25 / 4, 25 / 4};
	if (enemy->active && enemy->type != ET_NONE)
	{
		if (CheckCollisionRecs(bulletRec, enemyRec))
		{
			switch(enemy->size)
			{
				case ES_SMALL:
				{
					player->score += 200;
				}break;
				case ES_MEDIUM:
				{
					addEnemy(game, ES_SMALL);
					addEnemy(game, ES_SMALL);
					player->score += 135;
				}break;
				case ES_BIG:
				{
					addEnemy(game, ES_MEDIUM);
					addEnemy(game, ES_MEDIUM);
					player->score += 100;
				}break;
				default:
				break;
			}
			enemy->type = ET_NONE;
			bullet->position.x = -1;
			bullet->position.y = -1;
			return (1);
		}
	}
	return (0);
}

void gameCollisions(Game* game, Player *player)
{
	for(int j = 0; j < game->enemyCount; j++)
	{
		Enemy* enemy = &game->enemies[j];
		Rectangle enemyRec = {enemy->position.x, enemy->position.y, 25, 25};
		for(int i = 0; i < player->bulletCount; i++)
		{
			Bullet* bullet = &player->bullets[i];
			if (collisionEnemyBullet(game, player, enemy, bullet))
				break;
		}
		Rectangle playerRec =
		{
			player->position.x,
			player->position.y,
			84 * 0.25f,
			140 * 0.25f
		};

		if (enemy->active && enemy->type != ET_NONE &&
			CheckCollisionRecs(playerRec, enemyRec))
		{
			int lives = player->lives - 1;
			game->levelStart = false;
			*player = {0};
			player->position.x = SCREEN_WIDTH / 3.0f;
			player->position.y = SCREEN_HEIGHT / 2.0f;
			player->rotation = -90.0f;
			player->lives = lives;
			initLevel1(game);
		}
	}
}

void gameIsOver(Game* game)
{
	if (game->state == GS_PLAY)
	{
		if (game->player[0].lives <= 0)
			game->state = GS_GAMEOVER;
	}
	else if (game->state == GS_PLAY2)
	{
		if (game->player[0].lives <= 0 &&
			game->player[1].lives <= 0 )
			game->state = GS_GAMEOVER;
	}



	for(int i = 0; i < game->enemyCount; i++)
	{
		if (game->enemies[i].type != ET_NONE)
			return;
	}
	game->level++;
	game->levelStart = false;
	switch(game->level)
	{
		case 2: initLevel1(game);break;
		case 3: initLevel1(game);break;
		case 4: initLevel1(game);break;
		case 5: initLevel1(game);break;
	}
}

void shutdown(Game* game)
{
	game->state = GS_CLOSE;
	unloadData(game);
	CloseWindow();
}
