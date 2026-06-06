#pragma once
#include "../IObject.hpp"
#include "../../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	/// <summary>
	/// Counter object to be used together with other event objects (EoL, EoV, et cetera...)
	/// To be maninly used (eventually) as compatibility with 3DRad v722.
	/// </summary>
	/// 
	/// <remarks>
	/// Notes:
	///  -When toggling Enabled to true, the counter will increment by the Increment value, then Enabled will become false. 
	/// This behiavor is defined in ::Update().\
	/// </remarks>
	class E3DRSP_OBJECTS_IMPL_EXPORT Counter: public IObject
	{
	public:
		Counter();
		Counter(const std::string& name, double vaulue, double increment);

		Counter(Counter&&) noexcept = default;
		Counter& operator=(Counter&&) noexcept = default;

		double Value;
		double Increment;

		bool LoadFromFile = false;
		std::string FilePath;

		void Initialize() override;

		void Load() override;
		void Load(const std::filesystem::path& path) override;

		void Update() override;

		void Save();

		Gizmos::IGizmo* GetGizmo() const noexcept override;

		Reflection::UUID GetUUID() const noexcept override;

		~Counter() override;
	};
}

REFL_FWD(Counter)