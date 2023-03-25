#pragma once
#include <raylib.h>

typedef struct MineLayer
{
	Vector2 position;
	float scale;
	bool active;
	float rotation;
	bool layerEnd;

} MineLayer;

void initLayer(MineLayer* layer);
int updateLayer(MineLayer* layer,float deltaTime);
void drawLayer(MineLayer* layer, const Texture2D* texture);
