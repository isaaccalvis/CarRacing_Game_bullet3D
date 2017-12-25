#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
#include "PugiXml/src/pugixml.hpp"

#define MAX_SNAKE 2

enum primitiveTypes {
	NONE,
	CUBE,
	SPHERE,
	CIRCUIT_RECTA,
	CIRCUIT_ROTA_FRONT_RIGHT,
	CIRCUIT_ROTA_FRONT_LEFT,
	CIRCUIT_ROTA_BACK_RIGHT,
	CIRCUIT_ROTA_BACK_LEFT,
	CIRCUIT_RECTA_LATERAL
};

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	void createMap1();
	void addPrimitiveToMap(primitiveTypes type, int x , int y, int z, int radOrX, int Y, int Z);
	void addSensor(int x, int y);
public:

	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

	pugi::xml_document* mapXML;
};