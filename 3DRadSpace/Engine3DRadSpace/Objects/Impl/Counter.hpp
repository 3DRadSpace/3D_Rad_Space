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
		/// <summary>
		/// Value stored in this counter.
		/// </summary>
		double Value;
		/// <summary>
		/// How much the counter will increment when Enabled is set to true.
		/// </summary>
		double Increment;
		/// <summary>
		/// Does the value load from a file?
		/// </summary>
		bool LoadFromFile = false;
		/// <summary>
		/// File path if LoadFromFile is true. The file will be created if it does not exist.
		/// </summary>
		std::string FilePath;
		/// <summary>
		/// Does nothing.
		/// </summary>
		void Initialize() override;
		/// <summary>
		/// Loads the value from FilePath.
		/// </summary>
		void Load() override;
		/// <summary>
		/// Loads the value from an alternate path.
		/// </summary>
		/// <param name="path">Path to load the value from.</param>
		void Load(const std::filesystem::path& path) override;
		/// <summary>
		/// Reads the Enabled state, and if true, increments the Value by Increment, then sets Enabled to false.
		/// </summary>
		void Update() override;
		/// <summary>
		/// Saves the value into the file.
		/// </summary>
		void Save();
		/// <summary>
		///	Returns null.
		/// </summary>
		/// <returns>Returns a null gizmo.</returns>
		Gizmos::IGizmo* GetGizmo() const noexcept override;
		/// <summary>
		/// Returns the UUID of this object.
		/// </summary>
		Reflection::UUID GetUUID() const noexcept override;

		~Counter() override;
	};
}

REFL_FWD(Counter)