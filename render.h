#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct RenderComponent {
    int entityId;
    int spriteId;
} RenderComponent;

RenderComponent* createRenderComponent(int entityID, int spriteId);

RenderComponent* getRenderComponent(int entityID);

typedef struct SpriteInfo
{
    SDL_Surface *surface;
    SDL_Texture *sprite;
    char *spritePath;
};


/*
 * Load sprite into spriteInfo, returns index 
 */
int loadSprite(char* spritePath);


/*
 * Find or load sprite into spriteInfo, returns index 
 */
int getSprite(char* spritePath);

void render();