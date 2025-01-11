#include "physics.h"
#include "CONSTANTS.h"

/*
    Currently entity id and the index of the component are the same. This isn't great. Eventully a better solution is needed.
*/

physics_component physics_components[OBJECT_LIMIT];
int component_count = OBJECT_LIMIT;

void physicsUpdate()
{
    for(int i = 0; i < component_count; i++)
    {
        physics_components[i].position.x += physics_components[i].velocity.x;
        physics_components[i].position.y += physics_components[i].velocity.y;
    }
}

physics_component *createPhysicsComponent(int entityID)
{
    physics_components[entityID].entityID = entityID;
    physics_components[entityID].position.x = 0;
    physics_components[entityID].position.y = 0;
    physics_components[entityID].velocity.x = 0;
    physics_components[entityID].velocity.y = 0;
    physics_components[entityID].rotation = 0;
    physics_components[entityID].angularVelocity = 0;
    return  &physics_components[entityID];
}

physics_component *getPhysicsComponent(int entityID)
{
    return &physics_components[entityID];
}