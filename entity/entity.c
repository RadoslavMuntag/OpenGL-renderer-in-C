//
// Created by muntr on 22. 9. 2024.
//

#include "entity.h"

void init_entity_list(EntityList* list){
    list->data = NULL;
    list->size = 0;
}

void add_mesh_component(Entity* entity, MeshComponent* component){
    if(entity->mesh != NULL){
        printf("Mesh component already added or cannot by added.");
        exit(-1);
    }
    entity->mesh = component;
}

void add_transform_component(Entity* entity){
    if(entity->transform != NULL){
        printf("Transform component already added or cannot by added.");
        exit(-1);
    }
    entity->transform = (TransformComponent*)calloc(1, sizeof(TransformComponent));
    init_transform(entity->transform );

}

void add_physics_component(Entity* entity){
    if(entity->physics != NULL){
        printf("Physics component already added or cannot by added.");
        exit(-1);
    }
    entity->physics = (PhysicsComponent*)calloc(1, sizeof(PhysicsComponent));

}


bool has_entity(EntityList* list, uint64_t id){
    return id >= list->size;
}

Entity* get_entity(EntityList* list, uint64_t id){
    assert(!has_entity(list,id));
    return &list->data[id];
}

Entity* get_last(EntityList* list){
    return &list->data[list->size - 1];
}


void reset_entity(Entity* entity, uint64_t size){
    entity->id = size - 1;
    entity->mesh = NULL;
    entity->transform = NULL;
    entity->physics = NULL;
}

void init_entity(EntityList* list){
    list->size++;
    if(list->data == NULL){
        list->data = (Entity*) calloc(list->size, sizeof(Entity));
    }
    else{
        list->data = (Entity*)realloc(list->data,list->size*sizeof(Entity));
    }

    Entity *current = get_last(list);
    reset_entity(current, list->size);


    /*for (int i = 0; i < COMPONENT_LAST + 1; ++i) {
        switch (cenum[i]) {
            case C_MESH:
                add_mesh_component(current);
                break;
            case C_TRANSFORM:
                add_transform_component(current);
                break;
            case C_PHYSICS:
                add_physics_component(current);
                break;
            default:
                break;
        }
    }*/
}

void destroy_entity(EntityList* list, uint64_t id){
    if (has_entity(list, id)){
        printf("Invalid id");
        return;
    }

    Entity* entity = get_entity(list, id);
    if(entity->transform != NULL){
        free(entity->transform);
    }
    if(entity->physics != NULL){
        free(entity->physics);
    }
}

void destroy_entity_list(EntityList* list){
    for (uint64_t i = 0; i < list->size; ++i) {
        destroy_entity(list, i);
    }
    free(list->data);
}
