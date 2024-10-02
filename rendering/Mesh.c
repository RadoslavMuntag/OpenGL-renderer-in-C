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
    for (int i = 0; i < face->count; ++i) {
        add_vertex(vertices, &face->v[i], &face->vt[i], &face->vn[i], (float)material->mtlID);
    }

    int triangles = 0;
    while(triangles + 2 < face->count){
        indices->data[indices->size++] = old_size;
        indices->data[indices->size++] = 1 + triangles + old_size;
        indices->data[indices->size++] = 2 + triangles + old_size;
        triangles++;
    }

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
