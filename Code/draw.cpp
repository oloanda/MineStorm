#include "game.h"

static void drawScoreBoard(Game *game, Vector2 offset)
{
	float scale = 0.1f;
	Player player = game->player[0];

	player.position = {60 + offset.x, 30 + offset.y};
	player.rotation = -90.0f;

	DrawText("Player ONE", 45 + offset.x, 0 + offset.y, 20, BLUE);

	if (player.lives > 0)
		drawPlayer(&player, scale, BLUE, &game->atlas);
	player.position = {80 + offset.x, 30 + offset.y};
	if (player.lives > 1)
		drawPlayer(&player, scale, BLUE, &game->atlas);
	player.position = {100 + offset.x, 30 + offset.y};
	if (player.lives > 2)
		drawPlayer(&player, scale, BLUE, &game->atlas);

	DrawText(TextFormat("%d", game->player[0].score), 240 + offset.x, 0 + offset.y, 20, BLUE);

	if (game->state == GS_PLAY2)
	{
		DrawText("Player TWO", 470 - offset.x, 0 + offset.y, 20, LIME);

		player = game->player[1];
		player.rotation = -90.0f;
		player.position = {530 - offset.x, 30 + offset.y};
		if (player.lives > 0)
			drawPlayer(&player, scale, LIME, &game->atlas);
		player.position = {550 - offset.x, 30 + offset.y};
		if (player.lives > 1)
			drawPlayer(&player, scale, LIME, &game->atlas);
		player.position = {570 - offset.x, 30 + offset.y};
		if (player.lives > 2)
			drawPlayer(&player, scale, LIME, &game->atlas);
		DrawText(TextFormat("%d", game->player[1].score), 370 - offset.x, 0 + offset.y, 20, LIME);
	}
}

static void drawPauseMenu(Game *game, int frameCounter)
{
	DrawText("Resume" , SCREEN_WIDTH / 3 - MeasureText("Resume",25),
			 SCREEN_HEIGHT / 4,25, BLUE);
	DrawText("Main Menu" , SCREEN_WIDTH / 3 - MeasureText("Resume",25),
			 SCREEN_HEIGHT / 3,25, RED);
	if((frameCounter / 30) % 2)
	{
		DrawText("PAUSE" , SCREEN_WIDTH / 2 - MeasureText("PAUSE",25) + 67,
				 SCREEN_HEIGHT / 8,25, WHITE);
	}
	else
	{
		DrawText("SPACE",SCREEN_WIDTH/2 - MeasureText("SPACE",25) + 125,
				 SCREEN_HEIGHT / 4,25, BLUE);
		DrawText("Esc",SCREEN_WIDTH/2 - MeasureText("Esc",25) + 125,
				 SCREEN_HEIGHT / 3,25, RED);
	}
}

static void drawGameOver(Game *game, int frameCounter)
{
	DrawText("Game Over" , SCREEN_WIDTH / 2 - MeasureText("Game Over",25) + 67,
			 SCREEN_HEIGHT / 8,25, WHITE);
	DrawText("Main Menu" , SCREEN_WIDTH / 3 - MeasureText("Resume",25),
			 SCREEN_HEIGHT / 3,25, RED);
	if((frameCounter / 30) % 2)
	{
		DrawText("Esc",SCREEN_WIDTH/2 - MeasureText("Esc",25) + 125,
				 SCREEN_HEIGHT / 3,25, RED);
	}
}

static void drawMenu(Game *game, int frameCounter)
{
	DrawText("MENU" , SCREEN_WIDTH / 2 - MeasureText("MENU",25) + 67,
			 SCREEN_HEIGHT / 8,25, WHITE);
	DrawText("Single Player" , SCREEN_WIDTH / 2 - MeasureText("Single Player",25),
			 SCREEN_HEIGHT / 4,25, BLUE);
	DrawText("2 Players" , SCREEN_WIDTH / 2 - MeasureText("Single Player",25),
			 SCREEN_HEIGHT / 3,25, GREEN);
	DrawText("QUIT" , SCREEN_WIDTH / 2 - MeasureText("Single Player",25),
			 SCREEN_HEIGHT / 2,25, RED);
	if((frameCounter / 30) % 2)
	{
		DrawText("\'F\'", SCREEN_WIDTH /2 - MeasureText("'F'",25) + 125,
				 SCREEN_HEIGHT / 4,25, BLUE);
		DrawText("\'K\'", SCREEN_WIDTH /2 - MeasureText("'F'",25) + 125,
				 SCREEN_HEIGHT / 3,25, GREEN);
		DrawText("Escape", SCREEN_WIDTH /2 - MeasureText("Escape",25) + 125,
				 SCREEN_HEIGHT / 2,25, RED);
	}
}

void drawGame(Game* game, int frameCounter)
{
	BeginDrawing();

	DrawTextureEx(game->background, {0, 0}, 0, 1.0f, WHITE);
	switch(game->state)
	{
		case GS_MENU:
		{
			drawMenu(game, frameCounter);
		}break;
		case GS_PAUSE:
		{
			drawPauseMenu(game, frameCounter);
		}break;
		case GS_PLAY:
		case GS_PLAY2:
		{
			for(int i = 0; i < game->enemyCount; i++)
				drawEnemy(&game->enemies[i], game->atlas);
			for(int i = 0; i < game->player[0].bulletCount; i++)
			{
				Bullet* bullet = &game->player[0].bullets[i];
				drawBullet(bullet, game->atlas, SKYBLUE);
			}

			drawLayer(&game->layer, &game->atlas);
			drawPlayer(&game->player[0], 0.25f, SKYBLUE, &game->atlas);
			if (game->state == GS_PLAY2)
			{
				for(int i = 0; i < game->player[1].bulletCount; i++)
				{
					Bullet* bullet = &game->player[1].bullets[i];
					drawBullet(bullet, game->atlas, SKYBLUE);
				}
				drawPlayer(&game->player[1], 0.25f, GREEN, &game->atlas);
			}
		}break;
		case GS_GAMEOVER:
		{
			drawGameOver(game, frameCounter);
		}break;
		default:
		{

		}
	}
	DrawTextureEx(game->foreground, {0, 0}, 0, 1.0f, WHITE);
	drawScoreBoard(game, {0, 0});
#if 0
	if (game->state == GS_PAUSE)
	{
		DrawRectangle(70, 400, 245, 40, SKYBLUE);
		DrawRectangle(315, 400, 255, 40, GREEN);
		drawScoreBoard(game, (Vector2){30, 400});
	}
#endif


#if 0

	// TODO(v.caraulan): What I started doing here.
	// I want to take the segments of the collision polygons
	// from the image automatically.
	// We could also do it manualy with an image processor, or something like that;

	typedef struct Image {
		void *data;             // Image raw data
		int  width;              // Image base width
		int  height;             // Image base height
		int  mipmaps;            // Mipmap levels, 1 by default
		int  format;             // Data format (PixelFormat type)
	} Image;

	Image image = LoadImage("./assets/mines.png");
	printf("image format = %d\n", image.format);
	unsigned char *m = image.data;

	for (int i = 0; i < image.width;i++)
	{
		for (int j = 0; j < image.height; j++)
		{

			if (m[i * image.width + j] != 0)
				ImageDrawPixel(&image, j, i, RED);
		}
	}
	UnloadImage(image);
#endif
	EndDrawing();
}
