#include "mineLayer.h"
#include "common.h"

void initLayer(MineLayer* layer)
{
	layer->scale = 640.0f;
	layer->position = { (float)SCREEN_WIDTH / 2.0f,
		(float)SCREEN_HEIGHT / 2.0f};
	layer->active = true;
	//layer->active = false;
	layer->rotation = 0.0f;
	layer->layerEnd = false;
}

int updateLayer(MineLayer* layer, float deltaTime)
{
	if (layer->active && layer->scale >= 32.0f)
		layer->scale -= layer->scale*1000.0f / 1024.0f*deltaTime;

	if(layer->scale <= 32.0f)
	{
		layer->scale = 0.0f;
		layer->active = false;
		layer->layerEnd = true;
		return (1);
	}
	return (0);
}
void drawLayer(MineLayer* layer, const Texture2D* texture)
{
	if (layer->active && layer->scale >= 32.0f)
	{
		Rectangle rect = { texture->width / 2.0f,0.0f,texture->width / 4.0f,texture->height / 2.0f };
		Rectangle position = { layer->position.x,layer->position.y,layer->scale,layer->scale};
		Vector2 center = { layer->scale / 2.0f,layer->scale / 2.0f };

		DrawTexturePro(*texture, rect, position, center, layer->rotation, WHITE);
	}
}