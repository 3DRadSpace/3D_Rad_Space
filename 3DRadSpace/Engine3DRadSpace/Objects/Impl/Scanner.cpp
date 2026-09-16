#include "Scanner.hpp"

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
	return Reflection::UUID();
}

Objects::Gizmos::IGizmo* Scanner::GetGizmo() const noexcept
{
	return nullptr;
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

REFL_BEGIN(Scanner, "Scanner", "Other", "A scanner object that can detect other objects within a specified distance.")
REFL_FIELD(Scanner, std::string, Name, "Name", "Scanner", "Object name")
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
REFL_ATTR("Icon", "Data\\Editor\\Scanner.png")
REFL_ATTR("HelpURL", "https://3dradspace.github.io/Docs/Scanner.html")
REFL_END