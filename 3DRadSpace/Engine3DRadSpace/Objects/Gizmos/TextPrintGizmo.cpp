#include "TextPrintGizmo.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Objects::Gizmos;

Gizmo<TextPrint>::Gizmo()
{
	Allow3DRendering = false;
}

void Gizmo<TextPrint>::Load()
{
	if (Object != nullptr)
	{
		Object->Initialize();
		Object->Load();
	}
}

void Gizmo<TextPrint>::Load(const std::filesystem::path& path)
{
}

void Gizmo<TextPrint>::Draw2D()
{
	if (Object == nullptr) return;

	auto textPrint = static_cast<TextPrint*>(Object);
	if (textPrint != nullptr)
	{
		if (Selected)
		{
			auto oldColor = textPrint->Colour;
			textPrint->Colour = Color(1.0f, 0.5f, 0.0f, 1.0f);
			textPrint->Draw2D();
			textPrint->Colour = oldColor;
		}
		else textPrint->Draw2D();
	}
}

void Gizmo<TextPrint>::Draw3D()
{
}

void Gizmo<TextPrint>::Update()
{
}
