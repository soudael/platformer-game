#include "Player.h"

Player::Player(float x, float y)
{
    playerRect.x = x;
    playerRect.y = y;
    playerRect.w = 50.0f;
    playerRect.h = 50.0f;
	playerXSpeed = 0.0f;
    playerYSpeed = 0.0f;
    onGround = false;
	coyoteTimer = 0.0f;
}

// Gravity and Collision Physics
void Player::update(float deltaTime, const std::vector<Platforms>& platforms)
{
    playerYSpeed += GRAVITY * deltaTime;

	if (onGround) {
        coyoteTimer = COYOTE_TIME_DURATION;
    } else {
        coyoteTimer -= deltaTime;
    }

	// Horizontal Movement & Jump
    const bool *keyboardKey = SDL_GetKeyboardState(NULL);
	playerXSpeed = 0.0f;
	if (keyboardKey[SDL_SCANCODE_LEFT]) playerXSpeed -= 1.0f;
	if (keyboardKey[SDL_SCANCODE_RIGHT]) playerXSpeed += 1.0f;
	if (keyboardKey[SDL_SCANCODE_UP])
	{
		if (onGround || coyoteTimer > 0.0f) { 
			playerYSpeed = JUMP_FORCE;
			onGround = false;
			coyoteTimer = 0.0f;
        }
    }
	
	if (playerXSpeed != 0) {
		playerRect.x += MOVE_SPEED * playerXSpeed * deltaTime;
    }

	// Horizontal Collision Fix
    for (const auto& platformObj : platforms) {
		SDL_FRect platform = platformObj.getPlatformRectObj();

		if (SDL_HasRectIntersectionFloat(&playerRect, &platform)) {
			if (playerRect.y + playerRect.h -5.0f > platform.y && playerRect.y +5.0f < platform.y + platform.h)
			{
				// Left
				if (playerXSpeed < 0) {
					playerRect.x = platform.x + platform.w;
				}
				// Right
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
			if (playerRect.x + playerRect.w -5.0f > platform.x && playerRect.x +5.0f < platform.x + platform.w)
			{
				// Jump
				if (playerYSpeed < 0 && playerRect.y > platform.y + platform.h/2) {
					playerRect.y = platform.y + platform.h;
					playerYSpeed = 0.0f;
				}
				// Fall
				if (playerYSpeed > 0 && playerRect.y + playerRect.h < platform.y + platform.h/2) {
					playerRect.y = platform.y - playerRect.h;
					playerYSpeed = 0.0f;
					onGround = true;
				}
			}
		}
	}
}

void Player::render(SDL_Renderer* renderer, float cameraXOffset, float cameraYOffset)
{
	SDL_FRect ghostPlayer = playerRect;
	ghostPlayer.x -= cameraXOffset;
	ghostPlayer.y -= cameraYOffset;

    SDL_SetRenderDrawColor(renderer, 210, 210, 210, 255);
    SDL_RenderFillRect(renderer, &ghostPlayer);
}