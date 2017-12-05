#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	//mapXML = new pugi::xml_document;
	//mapXML.load_file("mapa.tmx");
	LOG("Loading Intro assets");
	bool ret = true;
	createMap1();
	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

void ModuleSceneIntro::createMap1() {
	addPrimitiveToMap(CUBE, 4, 1, 1, 3, 3, 3);
	addPrimitiveToMap(CUBE, 4, 1, 2, 3, 3, 3);
	addPrimitiveToMap(CUBE, 4, 1, 3, 3, 3, 3);
	addPrimitiveToMap(CUBE, 4, 1, 4, 3, 3, 3);


	//pugi::xml_node layer_data = mapXML.child("layer").child("data");
	//
	////for (pugi::xml_node iterator = mapXML.child("layer").child("data").child("tile"); iterator != nullptr; iterator = iterator.next_sibling())
	////{
	////	layer->size_data++;

	////}

	////layer->data = new uint[layer->size_data];
	////memset(layer->data, 0, layer->width*layer->height);

	////int i = 0;

	//for (pugi::xml_node tile = layer_data.child("tile"); tile; tile = tile.next_sibling("tile"))
	//{
	//	printf_s("%i\n",tile.attribute("gid").as_int(0));
	//}


}

void ModuleSceneIntro::addPrimitiveToMap(primitiveTypes type, int x, int y, int z, int radOrX, int Y = 1, int Z = 1) {
	switch (type) {
	case CUBE: {
		Cube cube(radOrX, Y, Z);
		cube.SetPos(x, y, z);
		App->physics->AddBody(cube, 999);
		break;
	}
	case SPHERE: {
		Sphere sphere(radOrX);
		sphere.SetPos(x, y, z);
		App->physics->AddBody(sphere, 999);
		break;
	}
	}
}