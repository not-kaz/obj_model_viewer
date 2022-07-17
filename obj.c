#include "obj.h"

#include <stdio.h>
#include <stdlib.h>

static void ftostr(FILE *f, const char **ptr)
{
	char *buf;
	size_t len;
	*ptr = NULL; // move

	fseek(f, 0, SEEK_END);
	len = ftell(f);
	fseek(f, 0, SEEK_SET);

	buf = malloc(len + 1);
	if (!buf)
		return;

	fread(buf, 1, len, f); // replace w/ own implementation
	buf[len] = '\0'; // null-terminate string
	*ptr = buf;
}

static const char *lnskip(const char *ptr)
{
	const char *p;

	p = ptr;
	while (*p != '\n')
		*(p++);

	*(p++); // start of next line
	return p;
}

static void strparse(const char *str, struct obj_mesh *m)
{
	const char *p;
	unsigned int v, n, t, f;

	{    // first pass - count for pre-alloc
		p = str;
		v = n = t = f = 0;
		while (p[0] != '\0') {
			switch (p[0]) {
			case 'v':
				switch (p[1]) {
				case 'n':
					n++;
					break;
				case 't':
					t++;
					break;
				default:
					v++;
					break;
				}
				break;
			case 'f':
				f++;
				break;
			default:
				break;
			}
			p = lnskip(p);
		}
	}

	{ // mem alloc
		m->vertices.num_positions = 3 * v;
		m->vertices.num_normals = 3 * n;
		m->vertices.num_tex_coords = 2 * t;
		m->num_faces = 3 * f;

		m->vertices.position = malloc(m->vertices.num_positions * sizeof(float));
		m->vertices.normal = malloc(m->vertices.num_normals * sizeof(float));
		m->vertices.tex_coord = malloc(m->vertices.num_tex_coords * sizeof(float));
		m->faces = malloc(m->num_faces * 3 * sizeof(struct obj_mesh_face));
	}

	{ // second pass - store data
		p = str;
		v = n = t = f = 0;
		while (*p != '\0') {
			switch (*p++) {
			case 'v':
				switch (*p++) {
				case 'n':
					sscanf(p, " %f %f %f ", // replace sscanf
						   &m->vertices.normal[n],
						   &m->vertices.normal[n + 1],
						   &m->vertices.normal[n + 2]);
					n += 3;
					break;
				case 't':
					sscanf(p, " %f %f ",
						   &m->vertices.normal[t],
						   &m->vertices.normal[t + 1],
						   &m->vertices.normal[t + 2]);
					t += 2;
					break;
				default:
					sscanf(p, " %f %f %f ",
						   &m->vertices.position[v],
						   &m->vertices.position[v + 1],
						   &m->vertices.position[v + 2]);
					v += 3;
					break;
				}
				break;
			case 'f':
				sscanf(p, " %d//%d %d//%d %d//%d ",
					   &m->faces[f].v, &m->faces[f].n,
					   &m->faces[f + 1].v, &m->faces[f + 1].n,
					   &m->faces[f + 2].v, &m->faces[f + 2].n);
				f += 3;
				break;
			default:
				break;
			}
			p = lnskip(p);
		}
	}
}

struct obj_mesh *obj_mesh_create(const char *filename)
{
	FILE *fp;
	const char *str;
	struct obj_mesh *m;

	fp = fopen(filename, "rb+");
	if (!fp)
		return NULL;

	ftostr(fp, &str);
	fclose(fp);
	if (!str)
		return NULL;

	m = malloc(sizeof(struct obj_mesh));
	if (!m)
		return NULL;

	strparse(str, m);
	free((char *) str); // cast to avoid const warn
	return m;
}

void obj_mesh_destroy(struct obj_mesh *m)
{
	// free members!
	free(m->vertices.position);
	free(m->vertices.normal);
	free(m->vertices.tex_coord);
	free(m->faces);
	free(m);
}
