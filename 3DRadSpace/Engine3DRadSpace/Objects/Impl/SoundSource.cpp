#include "SoundSource.hpp"
#include "Gizmos.hpp"
#include "Gizmos/SoundSourceGizmo.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Audio;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Objects::Gizmos;

#define SS_INITIALIZE \
_volume(1.0f), \
_pitch(1.0f), \
_looping(false), \
_maxDistance(std::numeric_limits<float>::max()), \
_referenceDistance(1.0f), \
_rolloffFactor(1.0f), \
_coneOuterGain(0.0f), \
_coneInnerAngle(360.0f), \
_coneOuterAngle(360.0f)

#define SS_SETPARAM \
SetVolume(_volume); \
SetPitch(_pitch); \
SetLooping(_looping); \
SetVelocity(_velocity); \
SetDirection(_direction); \
SetMaxDistance(_maxDistance); \
SetReferenceDistance(_referenceDistance); \
SetRolloffFactor(_rolloffFactor); \
SetConeOuterGain(_coneOuterGain); \
SetConeInnerAngle(_coneInnerAngle); \
SetConeOuterAngle(_coneOuterAngle); 

SoundSource::SoundSource() : SS_INITIALIZE
{
}

SoundSource::SoundSource(
	const std::string& name,
	bool enabled,
	RefSound sound,
	const Vector3& position
) : IObject3D(name, enabled, false, Position),
	SS_INITIALIZE
{
	_underlying.Sound = sound;
}

SoundSource::SoundSource(
	const std::string & name,
	bool enabled, 
	const std::filesystem::path & soundFile,
	const Math::Vector3 &position
) : IObject3D(name, enabled, false, Position),
	SS_INITIALIZE
{
}

RefSound SoundSource::GetSoundAsset() const noexcept
{
	return _underlying.Sound;
}

void SoundSource::SetSoundAsset(RefSound sound) noexcept
{
	_underlying.Sound = sound;
}

float SoundSource::GetVolume() const noexcept
{
	return _underlying.GetVolume();
}

void SoundSource::SetVolume(float volume) noexcept
{
	_underlying.SetVolume(volume);
}

float SoundSource::GetPitch() const noexcept
{
	return _underlying.GetPitch();
}

void SoundSource::SetPitch(float pitch) noexcept
{
	_underlying.SetPitch(pitch);
}

bool SoundSource::IsLooping() const noexcept
{
	return _underlying.IsLooping();
}

void SoundSource::SetLooping(bool looping) noexcept
{
	_underlying.SetLooping(looping);
}


Vector3 SoundSource::GetVelocity() const noexcept
{
	auto instance = GetInstance();
	return instance ? instance->GetVelocity() : _velocity;
}

void SoundSource::SetVelocity(const Vector3 &velocity) noexcept
{
	auto instance = GetInstance();
	if(instance)
		instance->SetVelocity(velocity);
	else
		_velocity = velocity;
}

Vector3 SoundSource::GetDirection() const noexcept
{
	auto instance = GetInstance();
	return instance ? instance->GetDirection() : _direction;
}

void SoundSource::SetDirection(const Vector3& direction) noexcept
{
	auto instance = GetInstance();
	if(instance)
		instance->SetDirection(direction);
	else
		_direction = direction;
}

float SoundSource::GetMaxDistance() const noexcept
{
	auto instance = GetInstance();
	return instance ? instance->GetMaxDistance() : _maxDistance;
}

void SoundSource::SetMaxDistance(float distance) noexcept
{
	auto instance = GetInstance();
	if(instance)
		instance->SetMaxDistance(distance);
	else _maxDistance = distance;
}

float SoundSource::GetReferenceDistance() const noexcept
{
	auto instance = GetInstance();
	return instance ? instance->GetReferenceDistance() : _referenceDistance;
}

void SoundSource::SetReferenceDistance(float refDst) noexcept
{
	auto instance = GetInstance();
	if(instance)
		instance->SetReferenceDistance(refDst);
	else
		_referenceDistance = refDst;
}

float SoundSource::GetRolloffFactor() const noexcept
{
	auto instance = GetInstance();
	return instance ? instance->GetRolloffFactor() : _rolloffFactor;
}

void SoundSource::SetRolloffFactor(float rollOff) noexcept
{
	auto instance = GetInstance();
	if(instance)
		instance->SetRolloffFactor(rollOff);
	else
		_rolloffFactor = rollOff;
}

float SoundSource::GetConeInnerAngle() const noexcept
{
	auto instance = GetInstance();
	return instance ? instance->GetConeInnerAngle() : _coneInnerAngle;
}

void SoundSource::SetConeInnerAngle(float innerAngle) noexcept
{
	auto instance = GetInstance();
	if(instance)
		instance->SetConeInnerAngle(innerAngle);
	else
		_coneInnerAngle = innerAngle;
}

float SoundSource::GetConeOuterAngle() const noexcept
{
	auto instance = GetInstance();
	return instance ? instance->GetConeOuterAngle() : _coneOuterAngle;
}

void SoundSource::SetConeOuterAngle(float outerAngle) noexcept
{
	auto instance = GetInstance();
	if(instance)
		instance->SetConeOuterAngle(outerAngle);
	else
		_coneOuterAngle = outerAngle;
}

float SoundSource::GetConeOuterGain() const noexcept
{
	auto instance = GetInstance();
	return instance ? instance->GetConeOuterGain() : _coneOuterGain;
}

void SoundSource::SetConeOuterGain(float outerGain) noexcept
{
	auto instance = GetInstance();
	if(instance)
		instance->SetConeOuterGain(outerGain);
	else
		_coneOuterGain = outerGain;
}

void SoundSource::Draw3D()
{
}

float SoundSource::Intersects(const Math::Ray & r)
{
	return r.Intersects(Math::BoundingSphere(Position, 1.0f));
}

Reflection::UUID SoundSource::GetUUID() const noexcept
{
	// {4F91C443-67C3-40C3-9676-A13A84715D2B}
	return {0x4f91c443, 0x67c3, 0x40c3, { 0x96, 0x76, 0xa1, 0x3a, 0x84, 0x71, 0x5d, 0x2b }};
}

void SoundSource::Initialize()
{
	_underlying.Initialize();
}

void SoundSource::Update()
{
	_underlying.Update();

	auto instance = _underlying.GetInstance();
	if(instance != nullptr)
		instance->SetPosition(Position);
}

void SoundSource::Load()
{
	_underlying.Load();
	SS_SETPARAM
}

void SoundSource::Load(const std::filesystem::path &path)
{
	_underlying.Load(path);
	//SS_SETPARAM
}

Objects::Gizmos::IGizmo *SoundSource::GetGizmo() const noexcept
{
	return Internal::GizmoOf<SoundSource>(this);
}

void SoundSource::Enable()
{
	_underlying.Enable();
}

void SoundSource::Disable()
{
	_underlying.Disable();
}

bool SoundSource::Switch()
{
	return _underlying.Switch();
}

Sound* SoundSource::GetSound() const noexcept
{
	return _underlying.GetSound();
}

SoundInstance* SoundSource::GetInstance() const noexcept
{
	return _underlying.GetInstance();
}

#undef SS_INITIALIZE
#undef SS_SETPARAM

static RefSound ss_getsoundasset(SoundSource& ss) { return ss.GetSoundAsset(); }
static void ss_setsoundasset(SoundSource& ss, const RefSound& sound) { ss.SetSoundAsset(sound); }

static float ss_getvolume(SoundSource& ss) { return ss.GetVolume(); }
static void ss_setvolume(SoundSource& ss, const float& volume) { ss.SetVolume(volume); }

static float ss_getpitch(SoundSource& ss) { return ss.GetPitch(); }
static void ss_setpitch(SoundSource& ss, const float& pitch) { ss.SetPitch(pitch); }

static bool ss_getlooping(SoundSource& ss) { return ss.IsLooping(); }
static void ss_setlooping(SoundSource& ss, const bool& looping) { ss.SetLooping(looping); }

REFL_BEGIN(SoundSource, "SoundSource", "Sound", "3D Localized sound source")
REFL_FIELD(SoundSource, std::string, Name, "Name", "SoundSource", "Name of the object")
REFL_FIELD(SoundSource, bool, Enabled, "Playing at start",true, "Playing at startup")
REFL_FIELD_GS(SoundSource, RefSound, ss_getsoundasset, ss_setsoundasset, "Sound asset", 0, "Sound asset")
REFL_FIELD(SoundSource, Vector3, Position, "Position", Vector3::Zero(), "Sound position")
REFL_FIELD_GS(SoundSource, float, ss_getvolume, ss_setvolume, "Volume", 1.0f, "Sound gain")
REFL_FIELD_GS(SoundSource, float, ss_getpitch, ss_setpitch, "Pitch", 1.0f, "Sound pitch")
REFL_FIELD_GS(SoundSource, bool, ss_getlooping, ss_setlooping, "Is looping", true, "Is the sound looping?")
REFL_METHOD(SoundSource, void, &SoundSource::Enable, "Play")
REFL_METHOD(SoundSource, void, &SoundSource::Disable, "Pause")
REFL_ATTR("HelpURL", "https://3dradspace.github.io/Docs/SoundSource.html")
REFL_END