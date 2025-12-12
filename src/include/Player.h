#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "Platforms.h"

class Player
{
	public:
		Player(float x, float y);

		void handleJump(const SDL_Event& event);
		void update(float deltaTime, const std::vector<Platforms>& platforms);
		void render(SDL_Renderer* renderer);

	private:
		SDL_FRect playerRect;
		float playerYSpeed;
		bool onGround;

		const float MOVE_SPEED = 300.0f;
		const float GRAVITY = 2000.0f;
		const float JUMP_FORCE = -1000.0f;
};