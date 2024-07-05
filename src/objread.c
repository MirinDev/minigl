#include <objread.h>

#define chunk_size 100

poly_t* read_obj(char* path)
{
    FILE* file = fopen(path, "r");
    if (!file) return NULL;

    unsigned int data_i = 0;
    unsigned int data_size = chunk_size;
    vec3_t* data = (vec3_t*)malloc(data_size * sizeof(vec3_t));

    unsigned int inds_i = 0;
    unsigned int inds_size = chunk_size;    
    unsigned int* inds = (unsigned int*)malloc(inds_size * sizeof(unsigned int));

    char type[128];
    while (fscanf(file, "%s", type) != EOF)
    {
        if (strcmp(type, "v") == 0)
        {
            vec3_t vec;
            fscanf(file, "%f %f %f\n", &vec.x, &vec.y, &vec.z);

            if (data_i + 1 > data_size)
            {
                data_size += chunk_size;
                data = (vec3_t*)realloc(data, data_size * sizeof(vec3_t));
            }

            data_i++;
            data[data_i - 1] = vec;
        }

        if (strcmp(type, "f") == 0)
        {
            int v1, t1, n1, v2, t2, n2, v3, t3, n3;
            //fscanf(file, "%d/%d %d/%d %d/%d\n", &v1, &t1, &v2, &t2, &v3, &t3);
            fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &v1, &t1, &n1, &v2, &t2, &n2, &v3, &t3, &n3);

            if (inds_i + 3 > inds_size)
            {
                inds_size += chunk_size;
                inds = (unsigned int*)realloc(inds, inds_size * sizeof(unsigned int));
            }

            inds_i += 3;
            inds[inds_i - 3] = v1 - 1;
            inds[inds_i - 2] = v2 - 1;
            inds[inds_i - 1] = v3 - 1;
        }
    }
    
    fclose(file);

    poly_t* poly = (poly_t*)malloc(sizeof(poly_t));
    poly->n = inds_i;
    poly->data = (vec3_t*)malloc(data_i * sizeof(vec3_t));
    memcpy(poly->data, data, data_i * sizeof(vec3_t));
    poly->inds = (unsigned int*)malloc(inds_i * sizeof(unsigned int));
    memcpy(poly->inds, inds, inds_i * sizeof(unsigned int));

    free(data);
    free(inds);

    return poly;
}