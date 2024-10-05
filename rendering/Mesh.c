//
// Created by muntr on 23. 9. 2024.
//

#include "Mesh.h"

void debug_print(Vertices *vertices, Indices *indices){
    for (int i = 0; i < vertices->size; ++i) {
        if(i%11 == 0){
            printf("\n");
        }
        printf("%f ", vertices->data[i]);
    }
    printf("\n");

    for (int i = 0; i < indices->size; ++i) {
        if(i%3 == 0){
            printf("\n");
        }
        printf("%ud ", indices->data[i]);
    }
    printf("\n");

}

void average_vec3(vec3* vectors, int n, vec3 result) {
    // Initialize result to zero vector
    glm_vec3_zero(result);

    // Sum all vectors
    for (int i = 0; i < n; i++) {
        glm_vec3_add(result, vectors[i], result);
    }

    // Divide by number of vectors to get the average
    glm_vec3_scale(result, 1.0f / (float)n, result);
}

bool is_point_in_triangle(vec3 v, vec3 v1, vec3 v2, vec3 v3) {
    vec3 e1, e2, e3;
    vec3 p1, p2, p3;
    vec3 c1, c2, c3;

    // Define triangle edges
    glm_vec3_sub(v2, v1, e1); // e1 = v2 - v1
    glm_vec3_sub(v3, v2, e2); // e2 = v3 - v2
    glm_vec3_sub(v1, v3, e3); // e3 = v1 - v3

    // Create vectors from triangle vertices to the point
    glm_vec3_sub(v, v1, p1); // p1 = v - v1
    glm_vec3_sub(v, v2, p2); // p2 = v - v2
    glm_vec3_sub(v, v3, p3); // p3 = v - v3

    // Compute cross products
    glm_vec3_cross(e1, p1, c1); // c1 = e1 x p1
    glm_vec3_cross(e2, p2, c2); // c2 = e2 x p2
    glm_vec3_cross(e3, p3, c3); // c3 = e3 x p3

    // Compute dot products
    float dot1 = glm_vec3_dot(c1, c2);
    float dot2 = glm_vec3_dot(c2, c3);
    float dot3 = glm_vec3_dot(c3, c1);

    // Check if all dot products have the same sign
    return dot1 >= 0 && dot2 >= 0 && dot3 >= 0;
}


float angle_at_vertex(vec3 v1, vec3 v2, vec3 v3, vec3 triangle_normal) {
    vec3 a, b;

    // Create vectors a and b
    glm_vec3_sub(v1, v2, a); // a = v1 - v2
    glm_vec3_sub(v3, v2, b); // b = v3 - v2

    vec3 cross_product;
    glm_vec3_cross(a, b, cross_product);

    glm_vec3_normalize(cross_product);
    glm_vec3_normalize(triangle_normal);

    float normals_dot = glm_vec3_dot(cross_product,triangle_normal);

    // Calculate the dot product
    float dot_product = glm_vec3_dot(a, b);

    // Calculate magnitudes
    float mag_a = glm_vec3_norm(a);
    float mag_b = glm_vec3_norm(b);

    // Calculate the angle in radians
    float angle = acosf(dot_product / (mag_a * mag_b));

    // Optionally convert angle to degrees
    float angle_degrees = angle * (180.0f / GLM_PIf);

    if (normals_dot > 0){
        return 360.0f - angle_degrees;
    }


    return angle_degrees; // returns the angle in radians
}

int find_lower_vertex(const bool *buffer, int buffer_size, int index){

    for (int i = index - 1; true ; --i) {
        if (i < 0){
            i = buffer_size -1;
        }

        if (i == index){
            return -1;
        }

        if(buffer[i]){
            return i;
        }

    }

}

int find_upper_vertex(const bool *buffer, int buffer_size, int index){
    for (int i = index + 1; true ; ++i) {
        if (i >= buffer_size){
            i = 0;
        }

        if (i == index){
            return -1;
        }

        if(buffer[i]){
            return i;
        }

    }
}

bool validate_triangle(const bool *buffer, int buffer_size,
                    vec3 v1, vec3 v2, vec3 v3,
                    int v1_index, int v2_index, int v3_index,
                    Face *face){
    for (int i = 0; i < buffer_size; ++i) {
        if( i == v1_index || i == v2_index || i == v3_index || !buffer[i]){
            continue;
        }
        Vertex *v_temp = &face->v[i];
        vec3 v;
        glm_vec3_copy((vec3){v_temp->x, v_temp->y, v_temp->z}, v);

        if(is_point_in_triangle(v, v1, v2, v3)){
            return false;
        }
    }
    return true;
}

void ear_clipping_algorithm(bool *v_buffer, int buffer_size, Face* face, Indices *indices, int old_size){
    while(buffer_size > 0){
        int control_val = 0;

        for (int i = 0; i < buffer_size; ++i) {
            if(v_buffer[i] == false){
                continue;
            }

            int v1_index = find_lower_vertex(v_buffer, buffer_size, i);
            int v3_index = find_upper_vertex(v_buffer, buffer_size, i);

            if(v1_index == v3_index || v1_index == -1 || v3_index == -1){
                return;
            }

            Vertex *v1_temp = &face->v[v1_index];
            Vertex *v2_temp = &face->v[i];
            Vertex *v3_temp = &face->v[v3_index];


            vec3 v1;
            vec3 v2;
            vec3 v3;

            vec3 normals[3];

            glm_vec3_copy((vec3){v1_temp->x, v1_temp->y, v1_temp->z}, v1);
            glm_vec3_copy((vec3){v2_temp->x, v2_temp->y, v2_temp->z}, v2);
            glm_vec3_copy((vec3){v3_temp->x, v3_temp->y, v3_temp->z}, v3);


            if(glm_vec3_eqv(v2, v3) || glm_vec3_eqv(v1,v2)){
                control_val++;
                v_buffer[i] = false;
                continue;
            }

            Vertex *vn1_temp = &face->vn[v1_index];
            Vertex *vn2_temp = &face->vn[i];
            Vertex *vn3_temp = &face->vn[v3_index];

            glm_vec3_copy((vec3){vn1_temp->x, vn1_temp->y, vn1_temp->z}, normals[0]);
            glm_vec3_copy((vec3){vn2_temp->x, vn2_temp->y, vn2_temp->z}, normals[1]);
            glm_vec3_copy((vec3){vn3_temp->x, vn3_temp->y, vn3_temp->z}, normals[2]);

            vec3 triangle_normal;
            average_vec3(normals, 3, triangle_normal);

            float angle = angle_at_vertex(v1,v2,v3, triangle_normal);

            if(angle == 180.0f){
                control_val++;
                v_buffer[i] = false;
                continue;
            }

            if (angle > 180.0f ||
                !validate_triangle(v_buffer, buffer_size,
                                   v1, v2, v3,
                                   v1_index, i, v3_index,
                                   face))
            {
                continue;
            }

            indices->data[indices->size++] = old_size + v1_index;
            indices->data[indices->size++] = old_size + i;
            indices->data[indices->size++] = old_size + v3_index;

            v_buffer[i] = false;
            control_val++;
            /*if (i == buffer_size - 1){
                buffer_size--;
            }*/
        }
        /*if(control_val == 0){
            return;
        }*/
    }
}


void add_vertex(Vertices *vertices, Vertex *v, TexCoord *vt, Vertex *vn, float id){
    vertices->data[vertices->size++] = v->x;
    vertices->data[vertices->size++] = v->y;
    vertices->data[vertices->size++] = v->z;
    vertices->data[vertices->size++] = vt->u;
    vertices->data[vertices->size++] = vt->v;
    vertices->data[vertices->size++] = vn->x;
    vertices->data[vertices->size++] = vn->y;
    vertices->data[vertices->size++] = vn->z;
    vertices->data[vertices->size++] = id;
}

void fill_vertices(Vertices *vertices, Indices *indices, Face *face, Material *material){
    assert(face->count >= 3);
    int old_size = vertices->size/9;

    bool v_buffer[1028];
    int buffer_size = 0;

    for (int i = 0; i < face->count; ++i) {
        add_vertex(vertices, &face->v[i], &face->vt[i], &face->vn[i], (float)material->mtlID);
        v_buffer[buffer_size++] = true;
    }

    ear_clipping_algorithm(v_buffer, buffer_size, face, indices, old_size);

    /*int triangles = 0;
    while(triangles + 2 < face->count){
        indices->data[indices->size++] = old_size;
        indices->data[indices->size++] = 1 + triangles + old_size;
        indices->data[indices->size++] = 2 + triangles + old_size;
        triangles++;
    }*/

}

void parse_mtl_file(const char *filename, MtlArr *mtl_arr){
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(1);
    }

    char line[128];
    Material *current;

    while (fgets(line, sizeof(line), file)) {

        if(line[0] == 'N' && line[1] == 's'){
            assert(mtl_arr->size > 0);
            sscanf(line, "Ns %f", &current->Ns);
        }

        else if(line[0] == 'K' && line[1] == 'a'){
            assert(mtl_arr->size > 0);
            sscanf(line, "Ka %f %f %f", &current->Ka[0], &current->Ka[1], &current->Ka[2]);
        }

        else if(line[0] == 'K' && line[1] == 'd'){
            assert(mtl_arr->size > 0);
            sscanf(line, "Kd %f %f %f", &current->Kd[0], &current->Kd[1], &current->Kd[2]);
        }

        else if(line[0] == 'K' && line[1] == 's'){
            assert(mtl_arr->size > 0);
            sscanf(line, "Ks %f %f %f", &current->Ks[0], &current->Ks[1], &current->Ks[2]);
        }

        else if (line[0] == 'n' && line[1] == 'e' && line[2] == 'w' && line[3] == 'm' && line[4] == 't' && line[5] == 'l'){
            mtl_arr->size++;

            if(mtl_arr->data == NULL) mtl_arr->data = (Material *)malloc( mtl_arr->size* sizeof(Material));
            else mtl_arr->data = (Material *)realloc(mtl_arr->data,  mtl_arr->size* sizeof(Material));

            current = &mtl_arr->data[mtl_arr->size - 1];
            current->mtlID = mtl_arr->size -1;
            sscanf(line, "%*s %s", current->name);

        }
    }
    fclose(file);
}


void parse_obj_file(const char *filename, Vertices *vertices, Indices *indices, MtlArr *mtl_arr) {

    /*Vertex v_temp[25000];
    TexCoord vt_temp[25000];
    Vertex vn_temp[25000];*/

    VertexArr v_temp;
    v_temp.data = NULL;
    v_temp.size = 0;
    TexCoordArr vt_temp;
    vt_temp.data = NULL;
    vt_temp.size = 0;
    VertexArr vn_temp;
    vn_temp.data = NULL;
    vn_temp.size = 0;

    vertices->size = 0;
    indices->size = 0;

    /*int vertex_count = 0;
    int texcoord_count = 0;
    int normal_count = 0;*/

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(1);
    }


    Material default_mtl;
    strcpy(default_mtl.name,"Default");

    default_mtl.Kd[0] = 1.0f;
    default_mtl.Kd[1] = 0.0f;
    default_mtl.Kd[2] = 1.0f;

    Material *current_mtl = &default_mtl;

    mtl_arr->data = (Material *)malloc(sizeof(Material));
    mtl_arr->size = 0;


    char line[1024];
    while (fgets(line, sizeof(line), file)) {

        if (line[0] == 'v' && line[1] == ' ') {  // Parse vertex position
            Vertex vertex;
            v_temp.size++;

            sscanf(line, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);

            if(v_temp.data == NULL) v_temp.data = (Vertex *)malloc( v_temp.size* sizeof(Vertex));
            else v_temp.data = (Vertex *)realloc(v_temp.data,  v_temp.size* sizeof(Vertex));
            v_temp.data[v_temp.size - 1] = vertex;
        }
        else if (line[0] == 'v' && line[1] == 't') {  // Parse texture coordinate
            TexCoord texcoord;
            vt_temp.size++;

            sscanf(line, "vt %f %f", &texcoord.u, &texcoord.v);

            if(vt_temp.data == NULL) vt_temp.data = (TexCoord *)malloc( vt_temp.size* sizeof(TexCoord));
            else vt_temp.data = (TexCoord *)realloc(vt_temp.data,  vt_temp.size* sizeof(TexCoord));

            vt_temp.data[vt_temp.size - 1] = texcoord;
        }
        else if (line[0] == 'v' && line[1] == 'n') {  // Parse normal vector
            Vertex normal;
            vn_temp.size++;

            sscanf(line, "vn %f %f %f", &normal.x, &normal.y, &normal.z);

            if(vn_temp.data == NULL) vn_temp.data = (Vertex *)malloc( vn_temp.size* sizeof(Vertex));
            else vn_temp.data = (Vertex *)realloc(vn_temp.data,  vn_temp.size* sizeof(Vertex));

            vn_temp.data[vn_temp.size - 1] = normal;
        }
        else if (line[0] == 'f' && line[1] == ' ') {  // Parse face
            Face face;
            face.count = 0;

            int i = 2;
            int dash_counter = 0;
            int v_index = 0;
            while(line[i] != '\0' && line[i] != '\n' && line[i] != '\r'){
                if(dash_counter > 2){
                    i++;
                    continue;
                }

                if(line[i] == ' '){
                    dash_counter = 0;
                    face.count++;
                    i++;
                    continue;
                }

                if(line[i] == '/'){
                    dash_counter++;
                }
                else{
                    char temp_str[10] = "";
                    int temp_i = 0;

                    while(line[i] >= 48 && line[i] <= 57){
                        temp_str[temp_i++] = line[i++];
                    }
                    i--;
                    sscanf(temp_str, "%d", &v_index);
                    switch(dash_counter) {
                        case 0:
                            face.v[face.count] = v_temp.data[v_index - 1];
                            break;
                        case 1:
                            face.vt[face.count] = vt_temp.data[v_index - 1];
                            break;
                        case 2:
                            face.vn[face.count] = vn_temp.data[v_index - 1];
                            break;
                        default:
                            break;
                    }
                }
                i++;
            }
            face.count++;
            fill_vertices(vertices, indices, &face, current_mtl);
        }
        else if (line[0] == 'm' && line[1] == 't' && line[2] == 'l' && line[3] == 'l' && line[4] == 'i' && line[5] == 'b'){
            char destination[256];
            char temp[128];

            sscanf(line, "%*s %s", temp);
            sprintf(destination, "../assets/%s", temp);

            parse_mtl_file(destination, mtl_arr);

        }
        else if (line[0] == 'u' && line[1] == 's' && line[2] == 'e' && line[3] == 'm' && line[4] == 't' && line[5] == 'l'){
            char temp[128];
            current_mtl = &default_mtl;

            if(mtl_arr->size < 1){
                continue;
            }

            sscanf(line, "%*s %s", temp);
            for (int i = 0; i < mtl_arr->size; ++i) {
                if(strcmp(mtl_arr->data[i].name, temp) == 0){
                    current_mtl = &mtl_arr->data[i];
                    break;
                }
            }
        }
    }
    //debug_print(vertices, indices);

    free(v_temp.data);
    free(vt_temp.data);
    free(vn_temp.data);
    fclose(file);
}
