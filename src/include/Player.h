#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "Platforms.h"

class Player
{
	public:
		Player(float x, float y);

		void update(float deltaTime, const std::vector<Platforms>& platforms);
		void render(SDL_Renderer* renderer, float cameraXOffset, float cameraYOffset);

		SDL_FRect getPlayerRectObj() const { return playerRect; }
	private:
		SDL_FRect playerRect;
		float playerXSpeed;
		float playerYSpeed;
		bool onGround;
		float coyoteTimer;

		const float COYOTE_TIME_DURATION = 0.1f;
		const float MOVE_SPEED = 300.0f;
		const float GRAVITY = 2000.0f;
		const float JUMP_FORCE = -1000.0f;
};