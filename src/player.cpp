#include "Player.h"

Player::Player(float x, float y)
{
    playerRect.x = x;
    playerRect.y = y;
    playerRect.w = 50.0f;
    playerRect.h = 50.0f;
    playerYSpeed = 0.0f;
    onGround = false;
}

// Jump Physics Handler
void Player::handleJump(const SDL_Event& event)
{
    if (event.type == SDL_EVENT_KEY_DOWN) {
        if (event.key.key == SDLK_UP && onGround) {
            playerYSpeed = JUMP_FORCE;
            onGround = false;
        }
    }
}

// Gravity and Collision Physics
void Player::update(float deltaTime, const std::vector<Platforms>& platforms)
{
    playerYSpeed += GRAVITY * deltaTime;

	// Horizontal Movement
    const bool *keyboardKey = SDL_GetKeyboardState(NULL);
	float playerXSpeed = 0.0f;
	if (keyboardKey[SDL_SCANCODE_LEFT]) playerXSpeed -= 1.0f;
	if (keyboardKey[SDL_SCANCODE_RIGHT]) playerXSpeed += 1.0f;
	
	if (playerXSpeed != 0) {
		playerRect.x += MOVE_SPEED * playerXSpeed * deltaTime;
    }

	// Horizontal Collision Fix
    for (const auto& platformObj : platforms) {
		SDL_FRect platform = platformObj.getPlatformRectObj();

		if (SDL_HasRectIntersectionFloat(&playerRect, &platform)) {
			if (playerRect.y + playerRect.h -5.0f > platform.y && playerRect.y +5.0f < platform.y + platform.h) {
				if (playerXSpeed < 0) {
					playerRect.x = platform.x + platform.w;
				}
				if (playerXSpeed > 0) {
					playerRect.x = platform.x - playerRect.w;
				}
			}
		}
	}
    playerRect.y += playerYSpeed * deltaTime;
    onGround = false;

    // Vertical Collision Fix
	for (const auto& platformObj : platforms) {
		SDL_FRect platform = platformObj.getPlatformRectObj();

		if (SDL_HasRectIntersectionFloat(&playerRect, &platform)) {
			if (playerYSpeed < 0 && playerRect.y > platform.y + platform.h -5.0f) {
				playerRect.y = platform.y + platform.h;
				playerYSpeed = 0.0f;
			}
			if (playerYSpeed > 0 && playerRect.y + playerRect.h < platform.y +5.0f) {
				playerRect.y = platform.y - playerRect.h;
				playerYSpeed = 0.0f;
				onGround = true;
			}
		}
	}
}

void Player::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 225, 225, 225, 255);
    SDL_RenderFillRect(renderer, &playerRect);
}