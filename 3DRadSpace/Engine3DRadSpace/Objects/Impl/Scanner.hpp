#pragma once
#include "../IObject3D.hpp"
#include "../../Reflection/Reflection.hpp"
#include "../../Reflection/Event.hpp"

namespace Engine3DRadSpace::Objects
{
	class E3DRSP_OBJECTS_IMPL_EXPORT Scanner : public IObject3D
	{
	public:
		Scanner(
			const std::string& name = "Scanner",
			const Math::Vector3& position = Math::Vector3::Zero(),
			const Math::Quaternion& rotation = Math::Quaternion(),
			float maxDistance = 100.0f,
			std::initializer_list<ObjectID> scanList = {}
		);

		float MaxDistance;
		std::vector<ObjectID> ScanList;
	
		Reflection::Event OnScanHit;

		Math::Ray GetScanRay() const noexcept;
		
		struct ScanResult
		{
			ObjectID HitObjectID;
			float Distance;
			bool Hit;
		} LastScanResult;

		ScanResult Scan() const;
		float Scan(ObjectID obj) const;

		// Inherited via IObject3D
		void Initialize() override;
		void Update() override;
		void Load() override;
		void Load(const std::filesystem::path& path) override;
		Reflection::UUID GetUUID() const noexcept override;
		Objects::Gizmos::IGizmo* GetGizmo() const noexcept override;
		void Draw3D() override;
		float Intersects(const Math::Ray& r) const override;

		ObjectID GetLastHitObjectID() const noexcept;
		float GetLastHitDistance() const noexcept;
		bool GetLastHit() const noexcept;
	};
}

REFL_FWD(Scanner)