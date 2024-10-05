//
// Created by muntr on 22. 9. 2024.
//

#ifndef MYGLFWPROJECT_ENTITY_H
#define MYGLFWPROJECT_ENTITY_H
#include "../utils/utils.h"
#include "components.h"


typedef struct{
    uint64_t id;
    MeshComponent *mesh;
    TransformComponent *transform;
    PhysicsComponent *physics;
} Entity;

typedef struct{
    Entity* data;
    uint64_t size;
} EntityList;

void init_entity_list(EntityList* list);
Entity* get_entity(EntityList* list, uint64_t id);
void add_mesh_component(Entity* entity, MeshComponent* component);
void add_transform_component(Entity* entity);
void add_physics_component(Entity* entity);
void init_entity(EntityList* list);
void destroy_entity_list(EntityList* list);

#endif //MYGLFWPROJECT_ENTITY_H
