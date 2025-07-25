#include "physics.h"
#include "CONSTANTS.h"
#include "enchant-engine.h"

/*
    Currently entity id and the index of the component are the same. This isn't great. Eventully a better solution is needed.
*/

PhysicsComponent PhysicsComponents[OBJECT_LIMIT];
int component_count = OBJECT_LIMIT;

void physicsUpdate()
{
    for(int i = 0; i < component_count; i++)
    {
        PhysicsComponents[i].position.x += PhysicsComponents[i].velocity.x;
        PhysicsComponents[i].position.y += PhysicsComponents[i].velocity.y;
    }
}

PhysicsComponent *createPhysicsComponent(int entityId)
{
    PhysicsComponents[entityId].entityId = entityId;
    PhysicsComponents[entityId].velocity.x = 0;
    PhysicsComponents[entityId].velocity.y = 0;
    PhysicsComponents[entityId].angularVelocity = 0;
    return  &PhysicsComponents[entityId];
}

PhysicsComponent *getPhysicsComponent(int entityId)
{
    return &PhysicsComponents[entityId];
}