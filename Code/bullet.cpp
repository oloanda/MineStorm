#include "bullet.h"
#include <math.h>
#include "common.h"

void initBullet(Bullet* bullet,Vector2 position,float angle)
{
	bullet->position = position;
	bullet->speed    = 700.0f;
	bullet->angle    = angle;
}
void updateBullet(Bullet* bullet,float deltaTime)
{
	Vector2 *position = &bullet->position;
	Vector2 *addPosition = &bullet->addPosition;

	float xDeplacement = bullet->speed * cosf(bullet->angle*DEG2RAD) * deltaTime;
	float yDeplacement = bullet->speed * sinf(bullet->angle*DEG2RAD) * deltaTime;
	position->x += xDeplacement;
	position->y += yDeplacement;
	addPosition->x += xDeplacement;
	addPosition->y += yDeplacement;

	if (position->x < 64.0f) { position->x = (float)SCREEN_WIDTH - 64.0f; }
	else if (position->x > (float)SCREEN_WIDTH - 64.0f) { position->x = 64.0f; }

	if (position->y < 80.0f) { position->y = (float)SCREEN_HEIGHT - 80.0f; }
	else if (position->y > (float)SCREEN_HEIGHT - 80.0f) { position->y = 80.0f; }
}

void drawBullet(Bullet* bullet, const Texture2D texture, Color color)
{
	Rectangle rect     = {885, 116, 25, 25};
	Rectangle position = {bullet->position.x,bullet->position.y , rect.width / 4, rect.height / 4};
	Vector2 origin     = {position.width / 2, position.height / 2};

	DrawTexturePro(texture,rect,position,origin, 0, color);
}
