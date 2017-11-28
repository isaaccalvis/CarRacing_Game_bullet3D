#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo car = createVehicle(MOTOR_BIKE);
	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(0, 0, - 10);
	
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	turn = acceleration = brake = 0.0f;

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		acceleration = MAX_ACCELERATION;
	}

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		if(turn < TURN_DEGREES)
			turn +=  TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if(turn > -TURN_DEGREES)
			turn -= TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		brake = BRAKE_POWER;
	}

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_I) == KEY_REPEAT)
	{
		vehicle->info.deleteThisObject = true;
		App->physics->deleteVehiclesFromWorld();
		VehicleInfo car = createVehicle(CAR);
		vehicle = App->physics->AddVehicle(car);
		vehicle->SetPos(App->camera->Position.x , App->camera->Position.y + 10, App->camera->Position.z);
	}
	else if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_I) == KEY_REPEAT) {
		vehicle->info.deleteThisObject = true;
		App->physics->deleteVehiclesFromWorld();
		VehicleInfo car = createVehicle(MOTOR_BIKE);
		vehicle = App->physics->AddVehicle(car);
		vehicle->SetPos(App->camera->Position.x, App->camera->Position.y + 10, App->camera->Position.z);
	}

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();

	char title[80];
	sprintf_s(title, "%.1f Km/h", vehicle->GetKmh());
	App->window->SetTitle(title);
	
	App->camera->Position.x = App->player->vehicle->vehicle->getRigidBody()->getCenterOfMassPosition().getX();
	App->camera->Position.y = App->player->vehicle->vehicle->getRigidBody()->getCenterOfMassPosition().getY() + 5;
	App->camera->Position.z = App->player->vehicle->vehicle->getRigidBody()->getCenterOfMassPosition().getZ() + 10;

	App->camera->LookAt(vec3(App->player->vehicle->vehicle->getRigidBody()->getCenterOfMassPosition().getX(), vehicle->vehicle->getRigidBody()->getCenterOfMassPosition().getY(), App->player->vehicle->vehicle->getRigidBody()->getCenterOfMassPosition().getZ()));// = App->player->vehicle->vehicle->getRigidBody()->getCenterOfMassPosition().getX();
	App->camera->Reference.y = App->player->vehicle->vehicle->getRigidBody()->getCenterOfMassPosition().angle();
	//App->camera->Reference.z = App->player->vehicle->vehicle->getRigidBody()->getCenterOfMassPosition().getX();

	return UPDATE_CONTINUE;
}

VehicleInfo ModulePlayer::createVehicle(type_vehicle type = CAR) {
	VehicleInfo car;
	switch (type) {
	case type_vehicle::CAR:
	{
		// Car properties ----------------------------------------
		car.chassis_size.Set(2, 2, 4);
		car.chassis_offset.Set(0, 1.5, 0);
		car.mass = 500.0f;
		car.suspensionStiffness = 15.88f;
		car.suspensionCompression = 0.83f;
		car.suspensionDamping = 0.88f;
		car.maxSuspensionTravelCm = 1000.0f;
		car.frictionSlip = 50.5;
		car.maxSuspensionForce = 6000.0f;

		// Wheel properties ---------------------------------------
		float connection_height = 1.2f;
		float wheel_radius = 0.6f;
		float wheel_width = 0.5f;
		float suspensionRestLength = 1.2f;

		// Don't change anything below this line ------------------

		float half_width = car.chassis_size.x*0.5f;
		float half_length = car.chassis_size.z*0.5f;

		vec3 direction(0, -1, 0);
		vec3 axis(-1, 0, 0);

		car.num_wheels = 4;
		car.wheels = new Wheel[4];

		// FRONT-LEFT ------------------------
		car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);
		car.wheels[0].direction = direction;
		car.wheels[0].axis = axis;
		car.wheels[0].suspensionRestLength = suspensionRestLength;
		car.wheels[0].radius = wheel_radius;
		car.wheels[0].width = wheel_width;
		car.wheels[0].front = true;
		car.wheels[0].drive = true;
		car.wheels[0].brake = false;
		car.wheels[0].steering = true;

		// FRONT-RIGHT ------------------------
		car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
		car.wheels[1].direction = direction;
		car.wheels[1].axis = axis;
		car.wheels[1].suspensionRestLength = suspensionRestLength;
		car.wheels[1].radius = wheel_radius;
		car.wheels[1].width = wheel_width;
		car.wheels[1].front = true;
		car.wheels[1].drive = true;
		car.wheels[1].brake = false;
		car.wheels[1].steering = true;

		// REAR-LEFT ------------------------
		car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
		car.wheels[2].direction = direction;
		car.wheels[2].axis = axis;
		car.wheels[2].suspensionRestLength = suspensionRestLength;
		car.wheels[2].radius = wheel_radius;
		car.wheels[2].width = wheel_width;
		car.wheels[2].front = false;
		car.wheels[2].drive = false;
		car.wheels[2].brake = true;
		car.wheels[2].steering = false;

		// REAR-RIGHT ------------------------
		car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
		car.wheels[3].direction = direction;
		car.wheels[3].axis = axis;
		car.wheels[3].suspensionRestLength = suspensionRestLength;
		car.wheels[3].radius = wheel_radius;
		car.wheels[3].width = wheel_width;
		car.wheels[3].front = false;
		car.wheels[3].drive = false;
		car.wheels[3].brake = true;
		car.wheels[3].steering = false;
	}
		break;

	case type_vehicle::MOTOR_BIKE: {
		// Car properties ----------------------------------------
		car.chassis_size.Set(1, 2, 4);
		car.chassis_offset.Set(0, 1.5, 0);
		car.mass = 300.0f;
		car.suspensionStiffness = 15.88f;
		car.suspensionCompression = 0.83f;
		car.suspensionDamping = 10.88f;
		car.maxSuspensionTravelCm = 100.0f;
		car.frictionSlip = 50.5;
		car.maxSuspensionForce = 2000.0f;

		// Wheel properties ---------------------------------------
		float connection_height = 1.2f;
		float wheel_radius = 0.6f;
		float wheel_width = 0.7f;
		float suspensionRestLength = 0.9f;

		// Don't change anything below this line ------------------

		float half_width = car.chassis_size.x*0.5f;
		float half_length = car.chassis_size.z*0.5f;

		vec3 direction(0, -1, 0);
		vec3 axis(-1, 0, 0);

		car.num_wheels = 2;
		car.wheels = new Wheel[2];

		// FRONT-LEFT ------------------------
		car.wheels[0].connection.Set( 0, connection_height, - wheel_radius - half_width);
		car.wheels[0].direction = direction;
		car.wheels[0].axis = axis;
		car.wheels[0].suspensionRestLength = suspensionRestLength;
		car.wheels[0].radius = wheel_radius;
		car.wheels[0].width = wheel_width;
		car.wheels[0].front = true;
		car.wheels[0].drive = true;
		car.wheels[0].brake = false;
		car.wheels[0].steering = false;

		// FRONT-RIGHT ------------------------
		car.wheels[1].connection.Set( 0 , connection_height, half_length - wheel_radius);
		car.wheels[1].direction = direction;
		car.wheels[1].axis = axis;
		car.wheels[1].suspensionRestLength = suspensionRestLength;
		car.wheels[1].radius = wheel_radius;
		car.wheels[1].width = wheel_width;
		car.wheels[1].front = true;
		car.wheels[1].drive = true;
		car.wheels[1].brake = false;
		car.wheels[1].steering = true;
	}
		break;
	}
	return car;

}