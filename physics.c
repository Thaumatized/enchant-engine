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

PhysicsComponent *createPhysicsComponent(int entityID)
{
    PhysicsComponents[entityID].entityID = entityID;
    PhysicsComponents[entityID].velocity.x = 0;
    PhysicsComponents[entityID].velocity.y = 0;
    PhysicsComponents[entityID].angularVelocity = 0;
    return  &PhysicsComponents[entityID];
}

PhysicsComponent *getPhysicsComponent(int entityID)
{
    return &PhysicsComponents[entityID];
}