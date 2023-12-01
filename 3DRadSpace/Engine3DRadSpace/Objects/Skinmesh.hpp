#pragma once
#include "../IObject3D.hpp"
#include "../Graphics/Model3D.hpp"
#include "../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	class DLLEXPORT Skinmesh : public IObject3D
	{
		Graphics::Model3D *_model;
		std::unique_ptr<std::string> _path;
	public:
		Skinmesh();

		Skinmesh(const std::string &name, bool visible, const std::string &tag, Reflection::RefModel3D model, const Math::Vector3 &pos,
			const Math::Quaternion &rot, const Math::Vector3 &pivot, const Math::Vector3 &scale);

		Skinmesh(const std::string &name, bool visible, const std::string &tag, const std::filesystem::path &path,const Math::Vector3 &pos = Math::Vector3::Zero(),
			const Math::Quaternion &rot = Math::Quaternion(), const Math::Vector3 &pivot = Math::Vector3::Zero(), const Math::Vector3 &scale = Math::Vector3::One());

		Reflection::RefModel3D Model;

		Graphics::Model3D *GetModel();

		void Initialize() override;
		void Update(Input::Keyboard &keyboard, Input::Mouse &mouse, double dt) override;
		void Load(Content::ContentManager *content) override;
		void Load(Content::ContentManager* content, const std::filesystem::path& path) override;
		void EditorInitialize() override;
		void EditorLoad(Content::ContentManager *content) override;
		Reflection::UUID GetUUID() override;
		void Draw(Math::Matrix4x4 &view, Math::Matrix4x4 &projection, double dt) override;
		void EditorDraw(const Math::Matrix4x4 &view, const Math::Matrix4x4 &projection, double dt, bool selected) override;
		std::optional<float> Intersects(const Math::Ray &r) override;

		~Skinmesh() override = default;
	};
}

REFL_FWD(Skinmesh)