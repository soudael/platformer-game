#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <vector>
#include "Platforms.h"

class Player
{
	public:
		Player(float x, float y);

		SDL_Texture* playerIdleSprite = nullptr;
		void loadPlayerTexture(SDL_Renderer* renderer);

		void update(float deltaTime, const std::vector<Platforms>& platforms);
		void render(SDL_Renderer* renderer, float cameraXOffset, float cameraYOffset);

		SDL_FRect getPlayerRectObj() const { return playerRect; }
	private:
		SDL_FRect playerRect;
		bool spriteNeedsFlip;
		float playerXSpeed;
		float playerYSpeed;
		
		bool onGround;
		float coyoteTimer;

		const float COYOTE_TIME_DURATION = 0.1f;
		const float MOVE_SPEED = 300.0f;
		const float GRAVITY = 1250.0f;
		const float JUMP_FORCE = -550.0f;
};