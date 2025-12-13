#include "Player.h"

Player::Player(float x, float y)
{
    playerRect.x = x;
    playerRect.y = y;
    playerRect.w = 44.0f;
    playerRect.h = 97.0f;
	playerXSpeed = 0.0f;
    playerYSpeed = 0.0f;
    onGround = false;
	coyoteTimer = 0.0f;
}

// Player Sprite Texture
void Player::loadPlayerTexture(SDL_Renderer* renderer)
{
    playerIdleSprite = IMG_LoadTexture(renderer, "assets/playerIdle.png");
    
    if (!playerIdleSprite)
	{
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, 
			"Error","Failed to load player texture.", nullptr);
    }
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

	// Movement & Jump
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
	if (playerXSpeed > 0) { spriteNeedsFlip = true; }
	if (playerXSpeed < 0) { spriteNeedsFlip = false; }

	// Horizontal Collision
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

    // Vertical Collision
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
	// Camera follows player
    SDL_FRect activePlayerRect = playerRect;
    activePlayerRect.x -= cameraXOffset;
    activePlayerRect.y -= cameraYOffset;

	SDL_FRect playerSourceRect{
		0.0f, 0.0f, 44.0f, 97.0f
	};

	SDL_RenderTextureRotated(renderer, playerIdleSprite, &playerSourceRect, &activePlayerRect, 0, nullptr,
		(spriteNeedsFlip) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    
	// Hitbox
    // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 10);
    // SDL_RenderRect(renderer, &activePlayerRect);
}