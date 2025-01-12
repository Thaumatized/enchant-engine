#include "eeMath.h"

typedef struct PhysicsComponent {
    int entityID;
    Vector2 position;
    Vector2 velocity;
    float rotation;
    float angularVelocity;
} PhysicsComponent;

PhysicsComponent* createPhysicsComponent(int entityID);

PhysicsComponent* getPhysicsComponent(int entityID);