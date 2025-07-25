#include "render.h"
#include "CONSTANTS.h"
#include "enchant-engine.h"
#include "physics.h"

/*
    Currently entity id and the index of the component are the same. This isn't great. Eventully a better solution is needed.
*/

RenderComponent RenderComponents[OBJECT_LIMIT];
int component_count = OBJECT_LIMIT;

void render()
{
    for(int i = 0; i < component_count; i++)
    {
        PhysicsComponent phys = *getPhysicsComponent(RenderComponents[i].entityId);
    }
}

RenderComponent *createRenderComponent(int entityId, int spriteId)
{
    RenderComponent *renderComponent = createRenderComponent(entityId, spriteId);
    renderComponent->spriteId=spriteId;
    return renderComponent;
}

RenderComponent *getRenderComponent(int entityId)
{
    return &RenderComponents[entityId];
}

int loadTexture(char* texturePath);

int getTexture(char* texturePath);

void render();