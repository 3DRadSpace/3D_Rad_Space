#pragma once
#include "..\IObject3D.hpp"
#include "..\Reflection\Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	class Empty : public IObject3D
	{
	public:
		Empty(const std::string& name = "", const std::string& tag = "", const Math::Vector3& pos = {0,0,0}, const Math::Vector3& pivot = {0,0,0},
			  const Math::Quaternion& rot = Math::Quaternion(), const Math::Vector3& scale = {1,1,1});

		// Inherited via IObject3D
		void Initialize() override;

		void Update(Input::Keyboard& keyboard, Input::Mouse& mouse, double dt) override;

		void Load(Content::ContentManager* content) override;

		void Load(Content::ContentManager* content, const std::filesystem::path& path) override;

		void EditorInitialize() override;

		void EditorLoad(Content::ContentManager* content) override;

		Reflection::UUID GetUUID() override;

		void Draw(Math::Matrix4x4& view, Math::Matrix4x4& projection, double dt) override;

		void EditorDraw(const Math::Matrix4x4& view, const Math::Matrix4x4& projection, double dt, bool selected) override;

		std::optional<float> Intersects(const Math::Ray& r) override;
	};
}

REFL_FWD(Empty)