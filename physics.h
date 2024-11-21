#include "eeMath.h"

typedef struct physics_component {
    int entityID;
    Vector2 position;
    Vector2 velocity;
    float rotation;
    float angularVelocity;
} physics_component;

physics_component* createPhysicsComponent(int entityID);

physics_component* getPhysicsComponent(int entityID);