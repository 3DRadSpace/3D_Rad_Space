#include "Scanner.hpp"
#include "../ObjectList.hpp"
#include "../Gizmos.hpp"
#include "../Gizmos/ScannerGizmo.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

Scanner::Scanner(
	const std::string& name,
	const Vector3& position,
	const Quaternion& rotation,
	float maxDistance,
	std::initializer_list<ObjectID> scanList
) : IObject3D(name, false, false, position, Vector3::Zero(), rotation),
	MaxDistance(maxDistance), 
	ScanList(scanList)
{
}

Math::Ray Engine3DRadSpace::Objects::Scanner::GetScanRay() const noexcept
{
	return Math::Ray{
		Position,
		Math::Vector3::Transform(Math::Vector3::UnitZ(), Rotation)
	};
}

float Scanner::Scan(ObjectID obj) const
{
	auto r = this->GetScanRay();
	auto objList = this->GetGame()->RequireService<ObjectList>({});
	auto ptrObj = obj.Get(objList);

	if (auto obj3d = dynamic_cast<IObject3D*>(ptrObj); obj3d != nullptr)
	{
		return obj3d->Intersects(r);
	}
	else
	{
		return std::numeric_limits<float>::signaling_NaN();
	}
}

Scanner::ScanResult Scanner::Scan() const
{
	for (auto& id : ScanList)
	{
		float distance = Scan(id);
		if (distance >= 0.0f && distance <= MaxDistance)
		{
			ScanResult result;

			result.Distance = distance;
			result.HitObjectID = id;
			result.Hit = true;
			return result;
		}
	}

	ScanResult nullResult;
	nullResult.Distance = std::numeric_limits<float>::signaling_NaN();
	nullResult.Hit = false;
	nullResult.HitObjectID = ObjectID();
	return nullResult;
}

void Scanner::Initialize()
{
}

void Scanner::Update()
{
	if (Enabled)
	{
		for (auto& id : ScanList)
		{
			float distance = Scan(id);
			if (distance >= 0.0f && distance <= MaxDistance)
			{
				OnScanHit.InvokeAll({});
				LastScanResult.Distance = distance;
				LastScanResult.HitObjectID = id;
				LastScanResult.Hit = true;
			}
		}
		Enabled = false;
	}
}

void Scanner::Load()
{
}

void Scanner::Load(const std::filesystem::path& path)
{
}

Reflection::UUID Scanner::GetUUID() const noexcept
{
	// {7A1F8908-76D5-4B46-8169-CE03CA3A50B2}
	return { 0x7a1f8908, 0x76d5, 0x4b46, { 0x81, 0x69, 0xce, 0x3, 0xca, 0x3a, 0x50, 0xb2 } };
}

Objects::Gizmos::IGizmo* Scanner::GetGizmo() const noexcept
{
	return Internal::GizmoOf<Scanner>(this);
}

void Scanner::Draw3D()
{
}

float Scanner::Intersects(const Math::Ray& r) const
{
	return 0.0f;
}

ObjectID Scanner::GetLastHitObjectID() const noexcept
{
	return LastScanResult.HitObjectID;
}

float Scanner::GetLastHitDistance() const noexcept
{
	return LastScanResult.Distance;
}

bool Scanner::GetLastHit() const noexcept
{
	return LastScanResult.Hit;
}

REFL_BEGIN(Scanner, "Scanner", "Others", "A scanner object that can detect other objects within a specified distance.")
REFL_FIELD(Scanner, std::string, Name, "Name", "Scanner", "Object name")
REFL_FIELD(Scanner, bool, Visible, "Gizmo visible", true, "Is the arrow visible in the editor?")
REFL_FIELD(Scanner, Vector3, Position, "Position", Vector3::Zero(), "Position in world space")
REFL_FIELD(Scanner, Quaternion, Rotation, "Rotation", Quaternion(), "Rotation in world space")
REFL_FIELD(Scanner, float, MaxDistance, "MaxDistance", 500.0f, "Maximum distance for scanning")
//TODO!: Support reflection for std::vector<T> types
//REFL_FIELD(Scanner, std::vector<ObjectID>, ScanList, "ScanList", "Scanner", "List of object IDs to scan for")
REFL_METHOD(Scanner, float, &Scanner::Scan, "Scan for object", ObjectID)
REFL_METHOD(Scanner, void, &Scanner::Enable, "Begin Scan")
REFL_METHOD(Scanner, ObjectID, &Scanner::GetLastHitObjectID, "Get Last Hit Object ID")
REFL_METHOD(Scanner, float, &Scanner::GetLastHitDistance, "Get Last Hit Distance")
REFL_METHOD(Scanner, bool, &Scanner::GetLastHit, "Get Last Hit")
REFL_ATTR("Icon", "Data\\Editor\\OBJ_Scanner.png")
REFL_ATTR("HelpURL", "https://3dradspace.github.io/Docs/Scanner.html")
REFL_END