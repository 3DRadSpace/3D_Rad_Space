#pragma once

#include "IObject.h"

/*
Provides View and Projection transformation matrices calculated from the viewer's translation 
*/

class Camera : public IObject
{
	Vector3 lookat;
public:

	Vector3 Normal;
	float FOV;
	float AspectRatio;
	float NearPlaneDistance;
	float FarPlaneDistance;


	Camera() = default;
	Camera(Game *g,std::string name, bool enabled,const Vector3 &pos, const Quaternion &rot,const Vector3 &normal, float fov,float aspect_ratio, float npd, float fpd) :
		IObject(g,name, enabled, pos, rot), Normal(normal),FOV(fov),AspectRatio(aspect_ratio), NearPlaneDistance(npd), FarPlaneDistance(fpd), lookat(Vector3::UnitZ() * rot) {};
	
	Matrix GetTranslation() override;

	void Update(float dt) override;
	void Draw(float dt, Game* g) override;

	void Enable() override;

	char* WriteToFileBuffer(size_t& s);
	
	void SetLookDirection(const Quaternion &q);
	void SetLookDirection(const Vector3& v);
	Matrix GetViewMatrix() const;
	Matrix GetProjectionMatrix() const;

	~Camera();
};

