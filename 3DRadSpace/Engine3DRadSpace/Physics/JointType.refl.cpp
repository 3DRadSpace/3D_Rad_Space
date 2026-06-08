#include "JointType.hpp"
#include "../Reflection/Reflection.hpp"

using namespace Engine3DRadSpace::Physics;

REFL_ENUM_BEGIN(JointType, "JointType")
REFL_ENUM_ENTRY("Fixed", static_cast<int>(JointType::Fixed))
REFL_ENUM_ENTRY("Distance", static_cast<int>(JointType::Distance))
REFL_ENUM_ENTRY("Spherical", static_cast<int>(JointType::Spherical))
REFL_ENUM_ENTRY("Revolute", static_cast<int>(JointType::Revolute))
REFL_ENUM_ENTRY("Prismatic", static_cast<int>(JointType::Prismatic))
REFL_ENUM_ENTRY("D6", static_cast<int>(JointType::D6))
REFL_ENUM_END
