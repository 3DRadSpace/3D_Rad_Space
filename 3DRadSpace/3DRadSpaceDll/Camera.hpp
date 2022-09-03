#pragma once

#include "Maths.hpp"
#include "IObjectReflection.hpp"

__REFLECTOBJECT_FORWARDDECL(Camera)

namespace Engine3DRadSpace
{
	/// <summary>
	/// Represents a Camera used to render 3D scenes.
	/// </summary>
	class DLLEXPORT Camera : public IObject
	{
		Vector3 lookat;
	public:
		/// <summary>
		/// Camera "up" vector. Defines the vector perpendicular to the surface the character is standing on.
		/// </summary>
		Vector3 Normal;
		/// <summary>
		/// The field of view expressed in radians in the y direction.
		/// </summary>
		float FOV;
		/// <summary>
		/// Width divided by height of the viewing volume or screen.
		/// </summary>
		float AspectRatio;
		/// <summary>
		/// The minimum drawing distance.
		/// </summary>
		float NearPlaneDistance;
		/// <summary>
		/// The maximum drawing distance.
		/// </summary>
		float FarPlaneDistance;

		/// <summary>
		/// Main constructor of the Camera class. 
		/// </summary>
		/// <param name="g">A pointer to the Game instance containing rendering information and data like the graphics device handles.</param>
		/// <param name="name">The name of the camera. Can be used as an tag.</param>
		/// <param name="enabled">Toggles the rendering of the camera.</param>
		/// <param name="pos">The camera's position in world-space.</param>
		/// <param name="rot">The camera's rotation expressed in a quaterinon.</param>
		/// <param name="normal">The camera's "up" direction.</param>
		/// <param name="fov">The field of view in Y axis.</param>
		/// <param name="aspect_ratio">The width and height of the screen divided.</param>
		/// <param name="npd">Viewing frustum near plane distance closest to the camera position.</param>
		/// <param name="fpd">Viewing frustum far plane distance furthest from the camera position.</param>
		Camera(
				const std::string& name = "Camera",
				bool enabled = true,
				const Vector3& pos = Vector3::Zero(),
				const Quaternion& rot = Quaternion(),
				const Vector3& normal = Vector3::UnitY(),
				float fov = Engine3DRadSpace::Math::ToRadians(65.0f),
				float aspect_ratio = 4.f / 3.f,
				float npd = 0.01f,
				float fpd = 500):
			IObject(name,enabled,pos,rot),
			Normal(normal),
			FOV(fov),
			AspectRatio(aspect_ratio),
			NearPlaneDistance(npd),
			FarPlaneDistance(fpd),
			lookat(Vector3::UnitZ() * rot)
		{
		
		}
		/// <summary>
		/// Default constructor used to maintain the vtables.
		/// </summary>
		//Camera();

		/// <summary>
		/// Gets the 3D world position expressed as a 4x4 matrix.
		/// </summary>
		/// <returns></returns>
		Matrix GetTranslation() override;
		/// <summary>
		/// This function has no effect.
		/// </summary>
		/// <param name="dt"></param>
		void Update(float dt) override;
		/// <summary>
		/// This function has no effect.
		/// </summary>
		/// <param name="dt"></param>
		/// <param name="g"></param>
		void Draw(float dt, Game* g) override;

		/// <summary>
		/// Toggles the rendering on.
		/// </summary>
		void Enable() override;

		/// <summary>
		/// Doesn't load anything.
		/// </summary>
		void Load() override;

		/// <summary>
		/// Validates the look-at vector.
		/// </summary>
		/// <returns></returns>
		bool Validate() override;

		/// <summary>
		/// Sets the look direction using a quaternion.
		/// </summary>
		/// <param name="q">Quaternion used for the looking direction.</param>
		void SetLookDirection(const Quaternion& q);
		/// <summary>
		/// Sets the looking direction using a unit vector.
		/// </summary>
		/// <param name="v">Unit vector</param>
		void SetLookDirection(const Vector3& v);
		/// <summary>
		/// Gets the view matrix.
		/// </summary>
		/// <returns></returns>
		Matrix GetViewMatrix() const;
		/// <summary>
		/// Gets the projection matrix.
		/// </summary>
		/// <returns></returns>
		Matrix GetProjectionMatrix() const;

		Matrix GetCameraMatrix() const;

		~Camera();
	};
}