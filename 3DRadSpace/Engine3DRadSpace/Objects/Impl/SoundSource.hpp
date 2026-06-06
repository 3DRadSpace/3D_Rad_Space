#pragma once
#include "SoundEffect.hpp"
#include "../IObject3D.hpp"

namespace Engine3DRadSpace::Objects
{
	class E3DRSP_OBJECTS_IMPL_EXPORT SoundSource : public IObject3D
	{
		SoundEffect _underlying;

		float _volume;
		float _pitch;
		bool _looping;

		Math::Vector3 _velocity;
		Math::Vector3 _direction;

		float _maxDistance;
		float _referenceDistance;
		float _rolloffFactor;
		float _coneInnerAngle;
		float _coneOuterAngle;
		float _coneOuterGain;
	public:
		SoundSource();

		SoundSource(
			const std::string &name,
			bool enabled,
			RefSound sound,
			const Math::Vector3 &position
		);

		SoundSource(
			const std::string &name,
			bool enabled,
			const std::filesystem::path& soundFile,
			const Math::Vector3 &position
		);

		SoundSource(SoundSource&&) noexcept = default;
		SoundSource& operator=(SoundSource&&) noexcept = default;

		void Draw3D() override;
		float Intersects(const Math::Ray &r) override;

		Reflection::UUID GetUUID() const noexcept override;

		void Initialize() override;
		void Load() override;
		void Load(const std::filesystem::path & path) override;
		void Update() override;
		Objects::Gizmos::IGizmo *GetGizmo() const noexcept override;

		void Enable() override;
		void Disable() override;
		bool Switch() override;

		RefSound GetSoundAsset() const noexcept;
		void SetSoundAsset(RefSound sound) noexcept;

		float GetVolume() const noexcept;
		void SetVolume(float volume) noexcept;

		float GetPitch() const noexcept;
		void SetPitch(float pitch) noexcept;

		bool IsLooping() const noexcept;
		void SetLooping(bool looping) noexcept;

		Math::Vector3 GetVelocity() const noexcept;
		void SetVelocity(const Math::Vector3& velocity) noexcept;

		Math::Vector3 GetDirection() const noexcept;
		void SetDirection(const Math::Vector3& direction) noexcept;

		float GetMaxDistance() const noexcept;
		void SetMaxDistance(float dst) noexcept;

		float GetReferenceDistance() const noexcept;
		void SetReferenceDistance(float refDst) noexcept;

		float GetRolloffFactor() const noexcept;
		void SetRolloffFactor(float rollOff) noexcept;

		float GetConeInnerAngle() const noexcept;
		void SetConeInnerAngle(float innerAngle) noexcept;

		float GetConeOuterAngle() const noexcept;
		void SetConeOuterAngle(float outerAngle) noexcept;

		float GetConeOuterGain() const noexcept;
		void SetConeOuterGain(float outerGain) noexcept;
		
		Audio::Sound* GetSound() const noexcept;
		Audio::SoundInstance* GetInstance() const noexcept;

		~SoundSource() = default;
	};
}

REFL_FWD(SoundSource)