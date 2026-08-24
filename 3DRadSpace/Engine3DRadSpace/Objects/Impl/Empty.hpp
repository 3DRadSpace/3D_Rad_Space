#pragma once
#include "..\IObject3D.hpp"
#include "..\..\Reflection\Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	/// <summary>
	/// Represents a blank object, with no behiavour. Can be used as a dummy, or plain 3D transform.
	/// </summary>
	class E3DRSP_OBJECTS_IMPL_EXPORT Empty : public IObject3D
	{
	public:
		/// <summary>
		/// Complete constructor for the Empty object.
		/// </summary>
		/// <param name="name">Name of the object</param>
		/// <param name="pos">Position of the object</param>
		/// <param name="pivot">Pivot point of the object</param>
		/// <param name="rot">Rotation of the object</param>
		/// <param name="scale">Scale of the object</param>
		explicit Empty(
			const std::string& name = "",
			const Math::Vector3& pos = Math::Vector3{0,0,0},
			const Math::Vector3& pivot = Math::Vector3{0,0,0},
			const Math::Quaternion& rot = Math::Quaternion(),
			const Math::Vector3& scale = Math::Vector3{1,1,1}
		);
		/// <summary>
		/// Move constructor for the Empty object.
		/// </summary>
		/// <param name="other">Other Empty object to move from</param>
		Empty(Empty&& other) noexcept = default;
		/// <summary>
		/// Move assignment operator for the Empty object.
		/// </summary>
		/// <param name="other">Other Empty object to move from</param>
		Empty& operator=(Empty&& other) noexcept = default;

		/// <summary>
		///	Does nothing.
		/// </summary>
		void Initialize() override;
		/// <summary>
		///	Does nothing.
		/// </summary>
		void Update() override;
		/// <summary>
		///	Does nothing.
		/// </summary>
		void Load() override;
		/// <summary>
		///	Does nothing.
		/// </summary>
		/// <param name="path">unused</param>
		void Load(const std::filesystem::path& path) override;
		/// <summary>
		///	Returns the UUID of the Empty object type, that has all the bytes zero.
		/// </summary>
		/// <returns>{00000000-0000-0000-0000-000000000000}</returns>
		Reflection::UUID GetUUID() const noexcept override;
		/// <summary>
		///	Does nothing.
		/// </summary>
		void Draw3D() override;
		/// <summary>
		/// Returns NaN.
		/// </summary>
		/// <param name="r">unused</param>
		/// <returns>NaN</returns>
		float Intersects(const Math::Ray& r) const override;
		/// <summary>
		///	Returns null.
		/// </summary>
		/// <returns>Null gizmo.</returns>
		Gizmos::IGizmo* GetGizmo() const noexcept override;
	};
}

REFL_FWD(Empty)