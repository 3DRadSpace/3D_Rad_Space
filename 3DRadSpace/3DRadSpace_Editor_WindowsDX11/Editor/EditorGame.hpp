#pragma once
#include "Engine3DRadSpace/Games/Game.hpp"
#include "Engine3DRadSpace/Graphics/IVertexBuffer.hpp"
#include <Engine3DRadSpace/Objects/Impl/Button.hpp>
#include <Engine3DRadSpace/Objects/Impl/Camera.hpp>
#include <Engine3DRadSpace/Graphics/Model3D.hpp>
#include <Engine3DRadSpace/Graphics/SpriteBatch.hpp>
#include <Engine3DRadSpace/Graphics/Primitives/LineList.hpp>
#include <Engine3DRadSpace/Graphics/Primitives/Arrow.hpp>
#include <Engine3DRadSpace/Graphics/Font.hpp>

//Despite using namespaces are ill-advised to be used in headers, this header is not meant to be included in other files.
using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Content::Assets;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

class EditorGame : public Engine3DRadSpace::Game
{
	Vector2 cameraPos = Vector2(
		cosf(std::numbers::pi_v<float> / 6), //30 degrees = pi/6 radians
		sinf(-std::numbers::pi_v<float> / 6)
	);

	Vector3 cursor3D = Vector3::Zero();

	HWND editorWindow;
	Camera Camera;
	std::unique_ptr<LineList> axis;
	std::unique_ptr<LineList> grid;
	std::unique_ptr<LineList> grid_center;

	float zoom = 5.0f;
	float timer = 0;

	std::unique_ptr<Font> _font;

	IObject* _selectedObject = nullptr;

	std::unique_ptr<ITexture2D> _btnSpritesheet;
	//std::unique_ptr<CilindricalBillboard> billboard;

	Button btnMvX;
	Button btnMvY;
	Button btnMvZ;

	Button btnRtX;
	Button btnRtY;
	Button btnRtZ;

	Button btnScX;
	Button btnScY;
	Button btnScZ;

	Button* _selectedTransformButton = nullptr;

	/// <summary>
	/// Helper function. Calls specified function fn on the specified buttons depending on whenever g allows 2D or 3D rendering.
	/// </summary>
	/// <param name="g">Object gizmo.</param>
	/// <param name="btns">Array of buttons, usually btn[]X, btn[]Y, btn[]Z</param>
	/// <param name="fn">Function, usually Draw2D(), or Update().</param>
	/// <param name="allow2D">Flag value that limits what what buttons are affected when Allow2DRendering is true.</param>
	void _gizmoFn(Gizmos::IGizmo* g, std::array<Button*, 3> btns, void (Button::* fn)(), uint8_t allow2D = 0b11);
	void _controlCamera();
	void _picking();
	void _gizmoButtons();
public:
	EditorGame(HWND parent, HINSTANCE hInstance);

	void Initialize() override;
	void Load() override;
	void Update() override;
	void Draw2D() override;

	void Draw3D() override;

	bool IsEditor() const noexcept override;

	bool IsFocused() const;
	void Reset3DCursor();
	void SelectObject(IObject* obj);

	~EditorGame();
};