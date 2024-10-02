//
// Created by muntr on 20. 9. 2024.
//

#include "renderer.h"

void renderer_create(struct Renderer *self){
    init_entity_list(&self->entityList);
    MeshComponent* mesh_c;
    Entity *entity;

    create_mesh_component(&self->meshList, "../assets/dome.obj");
    mesh_c = get_mesh_by_id(&self->meshList, 0);
    init_entity(&self->entityList);
    entity = get_entity(&self->entityList,0);
    add_mesh_component(entity, mesh_c);
    add_transform_component(entity);
    transform_set_scale(entity->transform, 100.0f,100.0f,100.0f);
    //printf("%p\n",self->sky_entity->transform );


    create_mesh_component(&self->meshList, "../assets/casa_try.obj");
    mesh_c = get_mesh_by_id(&self->meshList, 1);
    init_entity(&self->entityList);
    entity = get_entity(&self->entityList,1);

    add_mesh_component(entity, mesh_c);
    add_transform_component(entity);

    /*for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {

        init_entity(&self->entityList);

        Entity *entity = get_entity(&self->entityList,i*100 + j);

        add_mesh_component(entity, mesh_c);
        add_transform_component(entity);
        transform_set_position(entity->transform,(float)i,0,(float)j);
        transform_set_scale(entity->transform, 0.5f, 0.5f, 0.5f);

        }
    }*/


    glm_vec3_copy((vec3){2.27909f,0.58606f,0.69754f}, self->sun_pos);
    glm_vec3_copy((vec3){0.0f, 0.0f, 0.1f}, self->sky_color);

    //glm_vec3_copy((vec3){-100.0f,100.0f,-100.0f}, self->sun_pos);
    //glm_vec3_copy((vec3){0.65f, 0.75f, 0.9f}, self->sky_color);

    self->default_shader = shader_create(
            "../shaders/default.vert", "../shaders/default.frag",
            2, (struct VertexAttr[]){
                    {.index = 0, .name = "aPos"},
                    {.index = 1, .name = "aColor"}
            });

    self->sky_shader = shader_create(
            "../shaders/sky.vert", "../shaders/sky.frag",
            1, (struct VertexAttr[]){
                    {.index = 0, .name = "aPos"}
            });

}

void _render_sky(struct Shader* sky_shader, EntityList* entityList, mat4* view, mat4* projection){
    GLint viewLoc;
    GLint projLoc;
    GLint modelLoc;
    mat4 model_tmp;
    Entity* entity;

    float timeOfDay = 0.0f;
    float starVisibility = 1.0f;
    float sunAngle = timeOfDay * 2.0f * GLM_PIf;
    vec3 sunDirection;
    glm_vec3_normalize_to((vec3){sinf(sunAngle), cosf(sunAngle), 0.0f}, sunDirection);

    glUseProgram(sky_shader->handle);

    GLint timeOfDayLocation = glGetUniformLocation(sky_shader->handle, "timeOfDay");
    GLint sunDirectionLocation = glGetUniformLocation(sky_shader->handle, "sunDirection");
    GLint starVisibilityLocation = glGetUniformLocation(sky_shader->handle, "starVisibility");
    glUniform1f(timeOfDayLocation, timeOfDay);                        // Pass time of day
    glUniform3fv(sunDirectionLocation, 1, sunDirection); // Pass sun direction
    glUniform1f(starVisibilityLocation, starVisibility);

    viewLoc = glGetUniformLocation(sky_shader->handle, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, ( GLfloat*)view);
    projLoc = glGetUniformLocation(sky_shader->handle, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, ( GLfloat*)projection);
    entity = get_entity(entityList,0);
    transform_get_model_matrix(entity->transform, model_tmp);
    modelLoc = glGetUniformLocation(sky_shader->handle, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (GLfloat*)model_tmp);


    vao_bind(entity->mesh->vao);
    vbo_bind(entity->mesh->ebo);
    glDrawElements(GL_TRIANGLES, entity->mesh->model_size, GL_UNSIGNED_INT,(void *) 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void set_uniform_materials(MtlArr *mtl_arr, struct Shader *shaderProgram){
    for (int i = 0; i < mtl_arr->size ;i++) {
        char buffer[64];

        // Set Ns
        snprintf(buffer, sizeof(buffer), "materials[%d].Ns", i);
        glUniform1f(glGetUniformLocation(shaderProgram->handle, buffer), mtl_arr->data[i].Ns);

        // Set Ka
        snprintf(buffer, sizeof(buffer), "materials[%d].Ka", i);
        glUniform3fv(glGetUniformLocation(shaderProgram->handle, buffer), 1, mtl_arr->data[i].Ka);

        // Set Kd
        snprintf(buffer, sizeof(buffer), "materials[%d].Kd", i);
        glUniform3fv(glGetUniformLocation(shaderProgram->handle, buffer), 1, mtl_arr->data[i].Kd);
        //printf( "Kd %d: %f %f %f\n", i, mtl_arr->data[i].Kd[0], mtl_arr->data[i].Kd[1], mtl_arr->data[i].Kd[2]);

        // Set Ks
        snprintf(buffer, sizeof(buffer), "materials[%d].Ks", i);
        glUniform3fv(glGetUniformLocation(shaderProgram->handle, buffer), 1, mtl_arr->data[i].Ks);
    }
};


void renderer_update(struct Renderer *self, struct Camera* camera){
    GLint viewLoc;
    GLint projLoc;
    GLint modelLoc;
    mat4 model_tmp;
    Entity *entity;

    glClearColor(self->sky_color[0], self->sky_color[1], self->sky_color[2], 1.0f);

    //_render_sky(&self->sky_shader, &self->entityList, camera->view, camera->projection);
//  ------------------------------------------------------------------------------------
    glUseProgram(self->default_shader.handle);

    glUniform3f(glGetUniformLocation(self->default_shader.handle, "lightPos"), self->sun_pos[0], self->sun_pos[1], self->sun_pos[2]);
    glUniform3f(glGetUniformLocation(self->default_shader.handle, "viewPos"), camera->cameraPos[0], camera->cameraPos[1], camera->cameraPos[2]);
    glUniform3f(glGetUniformLocation(self->default_shader.handle, "lightColor"), 1.0f, 0.33f, 0.01f);
    glUniform3f(glGetUniformLocation(self->default_shader.handle, "skyColor"), self->sky_color[0], self->sky_color[1], self->sky_color[2]);
    glUniform2f(glGetUniformLocation(self->default_shader.handle, "winSize"), (float)camera->width, (float)camera->height);
    //1.0f, 0.6f, 0.3f
    //1.0f, 0.23f, 0.01f
    viewLoc = glGetUniformLocation(self->default_shader.handle, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, ( GLfloat*)camera->view);
    projLoc = glGetUniformLocation(self->default_shader.handle, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, ( GLfloat*)camera->projection);

    for (int i = 1; i < self->entityList.size; ++i) {

        entity = get_entity(&self->entityList,i);
        MeshComponent* mesh_c = entity->mesh;
        transform_get_model_matrix(entity->transform, model_tmp);

        set_uniform_materials(&mesh_c->materials,&self->default_shader);

        modelLoc = glGetUniformLocation(self->default_shader.handle, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (GLfloat*)model_tmp);

        vao_bind(mesh_c->vao);
        vbo_bind(mesh_c->ebo);


        glDrawElements(GL_LINES, mesh_c->model_size, GL_UNSIGNED_INT,(void *) 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
}

void renderer_destroy(struct Renderer *self){
    shader_destroy(self->default_shader);
    shader_destroy(self->sky_shader);
    destroy_mesh_list(&self->meshList);
    destroy_entity_list(&self->entityList);

}

