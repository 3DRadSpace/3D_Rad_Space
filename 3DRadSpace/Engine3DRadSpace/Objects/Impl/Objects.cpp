#include "Objects.hpp"
#include "../Reflection/Reflection.hpp"
#include "../../Logging/Exception.hpp"

//Forward declarations of object reflection data
REFL_FWD(Camera)
REFL_FWD(Sprite)
REFL_FWD(Skinmesh)
REFL_FWD(GForce)
REFL_FWD(Empty)
REFL_FWD(SkyColor)
REFL_FWD(TextPrint)
REFL_FWD(Fog)
REFL_FWD(Counter)
REFL_FWD(ExitFade)
REFL_FWD(Skybox)
REFL_FWD(SoundEffect)
REFL_FWD(SoundSource)
REFL_FWD(Box)
REFL_FWD(Sphere)
REFL_FWD(Cone)
REFL_FWD(Cylinder)
REFL_FWD(FreeCam)
REFL_FWD(RigidStatic)
REFL_FWD(RigidDynamic)
REFL_FWD(Joint)
REFL_FWD(FPCharacter)
REFL_FWD(SettingsManager)
REFL_FWD(Force)
REFL_FWD(EventOnKey)
REFL_FWD(EventOnLocation)
REFL_FWD(Timer)
REFL_FWD(DirectionalLight)

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Reflection;

std::vector<ReflectedObject*> e3drsp_internal_objects_list;
bool e3drsp_internal_objects_list_initialized = false;

void Engine3DRadSpace::Internal::LoadDefaultObjects()
{
	if (e3drsp_internal_objects_list_initialized) return;

	e3drsp_internal_objects_list_initialized = true;

	auto ppDefaultObjects =
	{
		&CameraReflInstance, //Camera
		&CounterReflInstance, //Counter
		&EmptyReflInstance, //Empty
		&EventOnKeyReflInstance, //Event On Key
		&EventOnLocationReflInstance, //Event On Location
		&ExitFadeReflInstance, //ExitFade
		&FogReflInstance, //Fog
		&ForceReflInstance, //Force
		&FPCharacterReflInstance,
		&SettingsManagerReflInstance, //SettingsManager
		&GForceReflInstance, //G-Force 
		&JointReflInstance,
		&RigidStaticReflInstance, //RigidStatic
		&RigidDynamicReflInstance, //RigidDynamic
		&SkinmeshReflInstance, //Skinmesh
		&SkyboxReflInstance, //Skybox
		&SkyColorReflInstance,
		&SoundEffectReflInstance,
		&SoundSourceReflInstance,
		/*
		CameraReflInstance, //C++ source
		*/
		&SpriteReflInstance, //Sprite
		&TextPrintReflInstance, //Textprint
		&BoxReflInstance,
		&SphereReflInstance,
		&ConeReflInstance,
		&CylinderReflInstance,
		&FreeCamReflInstance,
		&TimerReflInstance,
	};

	e3drsp_internal_objects_list.insert_range(e3drsp_internal_objects_list.begin(), ppDefaultObjects);
}

ReflectedObject* Engine3DRadSpace::Internal::GetReflDataFromUUID(const Reflection::UUID& uuid)
{
	if(e3drsp_internal_objects_list.empty()) throw Logging::Exception("LoadDefaultObjects() must be called first!");

	for(auto &refl : e3drsp_internal_objects_list)
	{
		if(uuid == refl->ObjectUUID)
			return refl;
	}
	return nullptr;
}
