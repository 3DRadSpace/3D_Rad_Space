#pragma once
#include "../Reflection/Reflection.hpp"
#include "../Games/Game.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace Engine3DRadSpace::Reflection
{
	void to_json(json& j, const UUID& uuid);
	void from_json(const json& j, UUID& uuid);
}

namespace Engine3DRadSpace::Projects
{
	/// <summary>
	/// Handles object and project loading/unloading.
	/// </summary>
	class E3DRSP_PROJECTS_EXPORT Serializer
	{
	public:
		Serializer() = delete;
		/// <summary>
		/// Serializes a object into JSON.
		/// </summary>
		/// <param name="obj">Reference to an object.</param>
		/// <returns>JSON data.</returns>
		static json SerializeObject(Objects::IObject* obj);
		/// <summary>
		/// Creates an object from JSON data.
		/// </summary>
		/// <param name="j">JSON data, usually from a project file.</param>
		/// <returns>Newly allocated object. Must be freed.</returns>
		static [[nodiscard]] Objects::IObject* DeserializeObject(const json& j);

		static bool LoadProject(
			Objects::ObjectList* lst,
			Content::ContentManager* content,
			const std::filesystem::path& projectPath
		);

		/// <summary>
		/// Loads a single object from a project file. Used when resetting objects.
		/// </summary>
		/// <param name="path">Path to project.</param>
		/// <param name="id">Object ID.</param>
		/// <returns>Newly allocated object. Must be freed.</returns>
		static [[nodiscard]] Objects::IObject* LoadObjectFromProject(const std::filesystem::path& path, unsigned id);

		/// <summary>
		/// Saves all the objects and asset data into a 3DRSP file.
		/// </summary>
		/// <param name="lst">Object list.</param>
		/// <param name="content">Content manager.</param>
		/// <param name="projectPath">File to save to.</param>
		/// <returns>True if succeded.</returns>
		static bool SaveProject(Objects::ObjectList* lst, Content::ContentManager* content, const std::filesystem::path& projectPath);
	};
}