#ifndef OBJ_H
#define OBJ_H

struct obj_mesh_vertices {
	float *position;
	float *normal;
	float *tex_coord;

	unsigned int num_positions;
	unsigned int num_normals;
	unsigned int num_tex_coords;
};

struct obj_mesh_face {
	unsigned int v, n, t;
};

struct obj_mesh {
	struct obj_mesh_vertices vertices;
	struct obj_mesh_face *faces;

	unsigned int num_faces;
};

struct obj_mesh *obj_mesh_create(const char *filename);
void obj_mesh_destroy(struct obj_mesh *m);

#endif //OBJ_H
