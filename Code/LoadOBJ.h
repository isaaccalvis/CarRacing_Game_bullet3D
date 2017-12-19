#ifndef __LoadOBJ_H__
#define __LoadOBJ_H__

#include "Module.h"
#include "Globals.h"
#include <vector>
#include "glut\glut.h"

class ModuleLoadOBJ : public Module {
public:
	ModuleLoadOBJ(Application* app);
	~ModuleLoadOBJ();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	bool loadOBJ(
		const char * path,
		std::vector < vec3 > & out_vertices,
		std::vector < vec2 > & out_uvs,
		std::vector < vec3 > & out_normals
	);

private:
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< vec3 > temp_vertices;
	std::vector< vec2 > temp_uvs;
	std::vector< vec3 > temp_normals;
	
	FILE* file;
};

#endif __LoadOBJ_H__