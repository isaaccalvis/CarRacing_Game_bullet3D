#ifndef __PhysBody3D_H__
#define __PhysBody3D_H__

#include "p2List.h"

enum COLLISION_STATE {
	COLLISION_ENTER,
	COLLISION_EXIT
};

class btRigidBody;
class Module;

// =================================================
struct PhysBody3D
{
	friend class ModulePhysics3D;
public:
	PhysBody3D(btRigidBody* body);
	~PhysBody3D();

	void Push(float x, float y, float z);
	void GetTransform(float* matrix) const;
	void SetTransform(const float* matrix) const;
	void SetPos(float x, float y, float z);
	void SetAsSensor(bool is_sensor);

private:
	btRigidBody* body = nullptr;
protected:
	bool is_sensor = false;
	COLLISION_STATE col_state = COLLISION_EXIT;
public:
	p2List<Module*> collision_listeners;
};

#endif // __PhysBody3D_H__