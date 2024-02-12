#pragma once
#include <Engine3DRadSpace/Reflection/Reflection.hpp>
#include <Engine3DRadSpace/Game.hpp>
#include "Windows/AddObjectDialog.hpp"
#include <nlohmann/json.hpp>

#include <Engine3DRadSpace/Objects/Camera.hpp>
#include <Engine3DRadSpace/ObjectList.hpp>

using json = nlohmann::json;

namespace Engine3DRadSpace::Reflection
{
	void to_json(json& j, const UUID& uuid);
	void from_json(const json& j, UUID& uuid);
}

class Serializer
{
public:
	static json SerializeObject(Engine3DRadSpace::IObject* obj);
	static [[nodiscard]] Engine3DRadSpace::IObject* DeserializeObject(const json& j);

	static bool LoadProject(
		Engine3DRadSpace::ObjectList* lst, 
		Engine3DRadSpace::Content::ContentManager *content,
		const std::filesystem::path& projectPath,
		Engine3DRadSpace::Internal::InitializationFlag f = Engine3DRadSpace::Internal::InitializationFlag::InitializeAndLoad
	);

	static bool SaveProject(Engine3DRadSpace::ObjectList* lst, Engine3DRadSpace::Content::ContentManager* content, const std::filesystem::path& projectPath);
};