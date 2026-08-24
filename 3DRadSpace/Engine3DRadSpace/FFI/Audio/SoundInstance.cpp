#include "SoundInstance.h"
#include "../../Audio/SoundInstance.hpp"

using namespace Engine3DRadSpace::Audio;
using namespace Engine3DRadSpace::Math;

#define SI_SETSOURCE \
src.Pitch = source.Pitch; \
src.ConeInnerAngle = source.ConeInnerAngle; \
src.ConeOuterAngle = source.ConeOuterAngle; \
src.ConeOuterGain = source.ConeOuterGain; \
src.Direction.X = source.Direction.X; \
src.Direction.Y = source.Direction.Y; \
src.Direction.Z = source.Direction.Z; \
src.Gain = source.Gain; \
src.Looping = source.Looping; \
src.MaxDistance = source.MaxDistance; \
src.MaxGain = source.MaxGain; \
src.MinGain = source.MinGain;

E3DRSP_SoundInstance E3DRSP_SoundInstance_Create(E3DRSP_Sound sound,const E3DRSP_AudioSource *pSource)
{
	if (sound == nullptr) return nullptr;
	if (pSource == nullptr) return nullptr;

	//Assumed that E3DRSP_AudioSource may or may not have the same alignment. Avoided reinterpret_casts.
	AudioSource src{};
	E3DRSP_AudioSource source = *pSource;
	SI_SETSOURCE;
	return new SoundInstance(static_cast<Sound*>(sound), src);
}

E3DRSP_SoundInstance E3DRSP_SoundInstance_Create1(E3DRSP_Sound sound)
{
	if (sound == nullptr) return nullptr;
	return new SoundInstance(static_cast<Sound*>(sound));
}

E3DRSP_AUDIO_EXPORT E3DRSP_AudioSource E3DRSP_SoundInstance_GetSource(E3DRSP_SoundInstance sndInstance)
{
	assert(sndInstance != nullptr);

	E3DRSP_AudioSource src{};
	auto source = static_cast<SoundInstance*>(sndInstance)->GetSource();
	SI_SETSOURCE;
	return src;
}

void E3DRSP_SoundInstance_SetSource(E3DRSP_SoundInstance sndInstance, const E3DRSP_AudioSource * pSource)
{
	if (sndInstance == nullptr) return;

	auto source = *pSource;
	AudioSource src{};
	SI_SETSOURCE;
	static_cast<SoundInstance*>(sndInstance)->SetSource(src);
}

E3DRSP_SoundState E3DRSP_SoundInstance_GetState(E3DRSP_SoundInstance sndInstance)
{
	if (sndInstance == nullptr) return E3DRSP_SoundState_Undefined;
	return static_cast<E3DRSP_SoundState>(static_cast<SoundInstance*>(sndInstance)->GetState());
}

void E3DRSP_SoundInstance_SetPitch(E3DRSP_SoundInstance sndInstance, float pitch)
{
	if (sndInstance == nullptr) return;
	static_cast<SoundInstance*>(sndInstance)->SetPitch(pitch);
}

void E3DRSP_SoundInstance_SetGain(E3DRSP_SoundInstance sndInstance, float gain)
{
	if (sndInstance == nullptr) return;
	static_cast<SoundInstance*>(sndInstance)->SetGain(gain);
}

void E3DRSP_SoundInstance_SetMaxGain(E3DRSP_SoundInstance sndInstance, float maxGain)
{
	if (sndInstance == nullptr) return;
	static_cast<SoundInstance*>(sndInstance)->SetMaxGain(maxGain);
}

void E3DRSP_SoundInstance_SetMinGain(E3DRSP_SoundInstance sndInstance, float minGain)
{
	if (sndInstance == nullptr) return;
	static_cast<SoundInstance*>(sndInstance)->SetMinGain(minGain);
}

void E3DRSP_SoundInstance_SetPosition(E3DRSP_SoundInstance sndInstance, const E3DRSP_Vector3 *pos)
{
	if (sndInstance == nullptr) return;
	Vector3 p(pos->X, pos->Y, pos->Z);
	static_cast<SoundInstance*>(sndInstance)->SetPosition(p);
}

E3DRSP_AUDIO_EXPORT void E3DRSP_SoundInstance_SetVelocity(E3DRSP_SoundInstance sndInstance, const E3DRSP_Vector3 *vel)
{
	if (sndInstance == nullptr) return;
	Vector3 v(vel->X, vel->Y, vel->Z);
	static_cast<SoundInstance*>(sndInstance)->SetVelocity(v);
}

void E3DRSP_SoundInstance_SetDirection(E3DRSP_SoundInstance sndInstance, const E3DRSP_Vector3 *dir)
{
	if (sndInstance == nullptr) return;
	Vector3 d(dir->X, dir->Y, dir->Z);
	static_cast<SoundInstance*>(sndInstance)->SetDirection(d);
}

void E3DRSP_SoundInstance_SetMaxDistance(E3DRSP_SoundInstance sndInstance, float distance)
{
	if (sndInstance == nullptr) return;
	static_cast<SoundInstance*>(sndInstance)->SetMaxDistance(distance);
}

void E3DRSP_SoundInstance_SetReferenceDistance(E3DRSP_SoundInstance sndInstance, float refDistance)
{
	if (sndInstance == nullptr) return;
	static_cast<SoundInstance*>(sndInstance)->SetReferenceDistance(refDistance);
}

void E3DRSP_SoundInstance_SetRolloffFactor(E3DRSP_SoundInstance sndInstance, float rolloff)
{
	if (sndInstance == nullptr) return;
	static_cast<SoundInstance*>(sndInstance)->SetRolloffFactor(rolloff);
}

void E3DRSP_SoundInstance_SetConeOuterGain(E3DRSP_SoundInstance sndInstance, float outerGain)
{
	if (sndInstance == nullptr) return;
	static_cast<SoundInstance*>(sndInstance)->SetConeOuterGain(outerGain);
}

void E3DRSP_SoundInstance_SetConeInnerAngle(E3DRSP_SoundInstance sndInstance, float angle)
{
	if (sndInstance == nullptr) return;
	static_cast<SoundInstance*>(sndInstance)->SetConeInnerAngle(angle);
}
void E3DRSP_SoundInstance_SetConeOuterAngle(E3DRSP_SoundInstance sndInstance, float angle)
{
	if (sndInstance == nullptr) return;
	static_cast<SoundInstance*>(sndInstance)->SetConeOuterAngle(angle);
}

float E3DRSP_SoundInstance_GetPitch(E3DRSP_SoundInstance sndInstance)
{
	if (sndInstance == nullptr) return 0.0f;
	return static_cast<SoundInstance*>(sndInstance)->GetPitch();
}

float E3DRSP_SoundInstance_GetGain(E3DRSP_SoundInstance sndInstance)
{
	if (sndInstance == nullptr) return 0.0f;
	return static_cast<SoundInstance*>(sndInstance)->GetGain();
}

float E3DRSP_SoundInstance_GetMaxGain(E3DRSP_SoundInstance sndInstance)
{
	if (sndInstance == nullptr) return 0.0f;
	return static_cast<SoundInstance*>(sndInstance)->GetMaxGain();
}

float E3DRSP_SoundInstance_GetMinGain(E3DRSP_SoundInstance sndInstance)
{
	if (sndInstance == nullptr) return 0.0f;
	return static_cast<SoundInstance*>(sndInstance)->GetMinGain();
}

E3DRSP_Vector3 E3DRSP_SoundInstance_GetPosition(E3DRSP_SoundInstance sndInstance)
{
	if (sndInstance == nullptr) return { 0.0f, 0.0f, 0.0f };
	auto p = static_cast<SoundInstance*>(sndInstance)->GetPosition();
	return {p.X, p.Y, p.Z};
}

E3DRSP_Vector3 E3DRSP_SoundInstance_GetVelocity(E3DRSP_SoundInstance sndInstance)
{
	if (sndInstance == nullptr) return { 0.0f, 0.0f, 0.0f };
	auto v = static_cast<SoundInstance*>(sndInstance)->GetVelocity();
	return {v.X, v.Y, v.Z};
}

E3DRSP_Vector3 E3DRSP_SoundInstance_GetDirection(E3DRSP_SoundInstance sndInstance)
{
	if (sndInstance == nullptr) return { 0.0f, 0.0f, 0.0f };
	auto d = static_cast<SoundInstance*>(sndInstance)->GetDirection();
	return {d.X, d.Y, d.Z};
}

float E3DRSP_SoundInstance_GetMaxDistance(E3DRSP_SoundInstance sndInstance)
{
	if (sndInstance == nullptr) return 0.0f;
	return static_cast<SoundInstance*>(sndInstance)->GetMaxDistance();
}

float E3DRSP_SoundInstance_GetReferenceDistance(E3DRSP_SoundInstance sndInstance)
{
	if (sndInstance == nullptr) return 0.0f;
	return static_cast<SoundInstance*>(sndInstance)->GetReferenceDistance();
}

float E3DRSP_SoundInstance_GetRolloffFactor(E3DRSP_SoundInstance sndInstance)
{
	if (sndInstance == nullptr) return 0.0f;
	return static_cast<SoundInstance*>(sndInstance)->GetRolloffFactor();
}

float E3DRSP_SoundInstance_GetConeOuterGain(E3DRSP_SoundInstance sndInstance)
{
	if (sndInstance == nullptr) return 0.0f;
	return static_cast<SoundInstance*>(sndInstance)->GetConeOuterGain();
}

float E3DRSP_SoundInstance_GetConeInnerAngle(E3DRSP_SoundInstance sndInstance)
{
	if (sndInstance == nullptr) return 0.0f;
	return static_cast<SoundInstance*>(sndInstance)->GetConeInnerAngle();
}

float E3DRSP_SoundInstance_GetConeOuterAngle(E3DRSP_SoundInstance sndInstance)
{
	if (sndInstance == nullptr) return 0.0f;
	return static_cast<SoundInstance*>(sndInstance)->GetConeOuterAngle();
}

bool E3DRSP_SoundInstance_IsLooping(E3DRSP_SoundInstance sndInstance)
{
	if (sndInstance == nullptr) return false;
	return static_cast<SoundInstance*>(sndInstance)->IsLooping();
}

void E3DRSP_SoundInstance_SetLooping(E3DRSP_SoundInstance sndInstance, bool looping)
{
	if (sndInstance == nullptr) return;
	static_cast<SoundInstance*>(sndInstance)->SetLooping(looping);
}

void E3DRSP_SoundInstance_Play(E3DRSP_SoundInstance sndInstance, bool dontOverlap)
{
	if (sndInstance == nullptr) return;
	static_cast<SoundInstance*>(sndInstance)->Play(dontOverlap);
}

void E3DRSP_SoundInstance_Stop(E3DRSP_SoundInstance sndInstance)
{
	if (sndInstance == nullptr) return;
	static_cast<SoundInstance*>(sndInstance)->Stop();
}

void E3DRSP_SoundInstance_Pause(E3DRSP_SoundInstance sndInstance)
{
	if (sndInstance == nullptr) return;
	static_cast<SoundInstance*>(sndInstance)->Pause();
}

void E3DRSP_SoundInstance_Destroy(E3DRSP_SoundInstance sndInstance)
{
	assert(sndInstance != nullptr);
	delete static_cast<SoundInstance*>(sndInstance);
}

#undef SI_SETSOURCE