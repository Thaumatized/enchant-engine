#pragma once

#include "eeMath.h"

typedef struct PhysicsComponent {
    int entityId;
    Vector3 position;
    Vector3 velocity;
    float rotation;
    float angularVelocity;
} PhysicsComponent;

PhysicsComponent* createPhysicsComponent(int entityId);

PhysicsComponent* getPhysicsComponent(int entityId);