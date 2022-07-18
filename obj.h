#ifndef OBJ_H
#define OBJ_H

struct obj_mesh {
	float *positions;
	float *normals;
	float *tex_coords;
	struct {
		unsigned int v, n, t;
	} *faces;

	unsigned int num_positions;
	unsigned int num_normals;
	unsigned int num_tex_coords;
	unsigned int num_faces;
};

struct obj_mesh *obj_mesh_create(const char *filename);
void obj_mesh_destroy(struct obj_mesh *m);

#endif //OBJ_H
