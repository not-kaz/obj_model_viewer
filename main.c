#include "obj.h"

#include <stdio.h>

int main(void)
{
	struct obj_mesh *m;

	m = obj_mesh_create("../cube.obj");

	{ // debug printing
		fprintf(stdout, "\n");
		for (int i = 0; i < m->vertices.num_positions; i++) {
			fprintf(stdout, "%f ", m->vertices.position[i]);
			if (i % 3 == 2)
				fprintf(stdout, "\n");
		}

		fprintf(stdout, "\n");
		for (int i = 0; i < m->vertices.num_normals; i++) {
			fprintf(stdout, "%f ", m->vertices.normal[i]);
			if (i % 3 == 2)
				fprintf(stdout, 	"\n");
		}

		fprintf(stdout, "\n");
		for (int i = 0; i < m->num_faces; i++) {
			fprintf(stdout, "%d//%d ", m->faces[i].v, m->faces[i].n);
			if (i % 3 == 2)
				fprintf(stdout, 	"\n");
		}
	}

	obj_mesh_destroy(m);
	return 0;
}
