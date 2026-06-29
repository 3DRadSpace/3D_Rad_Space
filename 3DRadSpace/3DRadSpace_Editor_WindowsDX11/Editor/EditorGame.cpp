#include "EditorGame.hpp"
#include <Engine3DRadSpace/Graphics/Font.hpp>
#include "../Frontend/Settings.hpp"
#include <Engine3DRadSpace/Objects/ObjectList.hpp>
#include <Engine3DRadSpace/Objects/IGizmo.hpp>
#include <Engine3DRadSpace\Objects\Gizmos.hpp>

EditorGame::EditorGame(HWND parent, HINSTANCE hInstance) :
	Game(Engine3DRadSpace::Native::Window(hInstance, parent)),
	editorWindow(parent)
{
}

void EditorGame::Initialize()
{
	std::vector<VertexPositionColor> axisLines =
	{
		//+X
		VertexPositionColor{Vector3(0,0,0),Colors::Red},
		VertexPositionColor{Vector3(500,0,0),Colors::Red},
		//-X
		VertexPositionColor{Vector3(0,0,0),Colors::White},
		VertexPositionColor{Vector3(-500,0,0),Colors::White},
		//+Y
		VertexPositionColor{Vector3(0,0,0),Colors::Green},
		VertexPositionColor{Vector3(0,500,0),Colors::Green},
		//-Y
		VertexPositionColor{Vector3(0,0,0),Colors::White},
		VertexPositionColor{Vector3(0,-500,0),Colors::White},
		//+Z
		VertexPositionColor{Vector3(0,0,0),Colors::Blue},
		VertexPositionColor{Vector3(0,0,500),Colors::Blue},
		//-Z
		VertexPositionColor{Vector3(0,0,0),Colors::White},
		VertexPositionColor{Vector3(0,0,-500),Colors::White},
	};

	constexpr int halfNumLines = 25;

	std::vector<VertexPositionColor> dLines;
	for(int i = -halfNumLines; i <= halfNumLines; i++)
	{
		if(i == 0) continue;
		dLines.push_back(VertexPositionColor{Vector3(float(i),0,halfNumLines), Colors::Gray});
		dLines.push_back(VertexPositionColor{Vector3(float(i),0,-halfNumLines), Colors::Gray});

		dLines.push_back(VertexPositionColor{Vector3(halfNumLines, 0, float(i)), Colors::Gray});
		dLines.push_back(VertexPositionColor{Vector3(-halfNumLines, 0, float(i)), Colors::Gray});
	}

	auto centerLines = std::initializer_list<VertexPositionColor>{
		VertexPositionColor{ Vector3(0,0,halfNumLines), Colors::Gray },
		VertexPositionColor{ Vector3(0,0,-halfNumLines), Colors::Gray },
		VertexPositionColor{ Vector3(halfNumLines, 0, 0), Colors::Gray },
		VertexPositionColor{ Vector3(-halfNumLines, 0, 0), Colors::Gray }
	};

	axis = std::make_unique<Primitives::LineList>(Device.get(), axisLines);
	grid_center = std::make_unique<Primitives::LineList>(Device.get(), centerLines);
	grid = std::make_unique<Primitives::LineList>(Device.get(), dLines);

	Camera.InternalInitialize(this);
	Camera.FarPlaneDistance = 1000.0f;
}

void EditorGame::Load()
{
	_font = std::make_unique<Font>(Device.get(), "Data//Fonts//Arial.ttf");

	_btnSpritesheet = Device->CreateTexture2D("Data//Editor//transformButtons.png");

	auto setButtonImage = [this](Button* btn, ITexture2D* texture, RectangleF screenNormCoords, RectangleF UVcoords)
	{
		btn->InternalInitialize(this);
		btn->SetSpriteImage(texture);

		btn->Position = Vector2(screenNormCoords.X, screenNormCoords.Y);
		btn->Scale = Vector2(screenNormCoords.Width, screenNormCoords.Height);

		btn->UVCoordinates = UVcoords;
		btn->IdleTextureRect = UVcoords;
		btn->HoverTextureRect = UVcoords;
		btn->ClickTextureRect = UVcoords;
	};

	constexpr float btnSize = 1.0f / 9.0f;

	//translation buttons
	setButtonImage(
		&btnMvX,
		_btnSpritesheet.get(),
		RectangleF(0.0f, 0.0f, btnSize, btnSize),
		RectangleF(0.0f, 0.0f, 0.25f, 0.25f)
	);

	setButtonImage(
		&btnMvY,
		_btnSpritesheet.get(),
		RectangleF(btnSize, 0.0f, btnSize, btnSize),
		RectangleF(0.25f, 0.0, 0.25f, 0.25f)
	);

	setButtonImage(
		&btnMvZ,
		_btnSpritesheet.get(),
		RectangleF(btnSize * 2, 0.0f, btnSize, btnSize),
		RectangleF(0.5f, 0.0f, 0.25f, 0.25f)
	);

	//rotation buttons
	setButtonImage(
		&btnRtX,
		_btnSpritesheet.get(),
		RectangleF(btnSize * 3, 0.0f, btnSize, btnSize),
		RectangleF(0.75f, 0.0f, 0.25f, 0.25f)
	);

	//2nd column
	setButtonImage(
		&btnRtY,
		_btnSpritesheet.get(),
		RectangleF(btnSize * 4, 0.0f, btnSize, btnSize),
		RectangleF(0.0f, 0.25f, 0.25f, 0.25f)
	);

	setButtonImage(
		&btnRtZ,
		_btnSpritesheet.get(),
		RectangleF(btnSize * 5, 0.0f, btnSize, btnSize),
		RectangleF(0.25f, 0.25f, 0.25f, 0.25f)
	);
	
	//scale buttons
	setButtonImage(
		&btnScX,
		_btnSpritesheet.get(),
		RectangleF(btnSize * 6, 0.0f, btnSize, btnSize),
		RectangleF(0.5f, 0.25f, 0.25f, 0.25f)
	);

	setButtonImage(
		&btnScY,
		_btnSpritesheet.get(),
		RectangleF(btnSize * 7, 0.0f, btnSize, btnSize),
		RectangleF(0.75f, 0.25f, 0.25f, 0.25f)
	);

	//3rd column
	setButtonImage(
		&btnScZ,
		_btnSpritesheet.get(),
		RectangleF(btnSize * 8, 0.0f, btnSize, btnSize),
		RectangleF(0.0f, 0.5f, 0.25f, 0.25f)
	);
}

void EditorGame::_controlCamera()
{
	zoom = Mouse.ScrollWheel();
	if(zoom < -4.0f) zoom = -4.0f;

	static bool released = true;

	if(Mouse.LeftButton() == ButtonState::Pressed && IsFocused())
	{
		Point screenCenter = Window->Size() / 2;
		Point mousePos = Mouse.Position();
		Window->SetMousePosition(screenCenter);

		auto mouseDelta = (Vector2)(screenCenter - mousePos) * float(Update_dt) / 100.0f;
		cameraPos -= mouseDelta * Settings::CameraSensitivity.Value;

		constexpr float poleLimit = 0.01f;
		cameraPos.Y = std::clamp<float>(
			cameraPos.Y,
			-std::numbers::pi_v<float> / 2.f + poleLimit,
			std::numbers::pi_v<float> / 2.f - poleLimit
		);

		Window->SetMouseVisibility(false);
		released = false;
	}
	else
	{
		if(!released)
		{
			released = true;
			Window->SetMouseVisibility(true);
		}
	}
}

void EditorGame::_picking()
{
	static bool rightButtonPrevPressed = false;
	static bool middleButtonPrevPressed = false;

	bool middleBtn = Mouse.MiddleButton() == ButtonState::Pressed && !middleButtonPrevPressed;

	if((Mouse.RightButton() == ButtonState::Pressed && !rightButtonPrevPressed) || middleBtn)
	{
		auto mousePos = Mouse.Position();

		auto viewport = Device->ImmediateContext()->GetViewport();
		auto windowSize = Window->Size();

		// Scale mouse coordinates from window space to viewport space
		float scaleX = viewport.ScreenRectangle.Width / static_cast<float>(windowSize.X);
		float scaleY = viewport.ScreenRectangle.Height / static_cast<float>(windowSize.Y);
		Point scaledMousePos = Point(
			static_cast<int>(mousePos.X * scaleX),
			static_cast<int>(mousePos.Y * scaleY)
		);

		auto ray = GetMouseRay(scaledMousePos, View, Projection);

		float closestDistance = std::numeric_limits<float>::infinity();
		Vector3 closestIntersection = cursor3D;
		IObject* closestObject = _selectedObject;

		for(auto& obj : *Objects)
		{
			if(obj.InternalType == ObjectType::IObject3D)
			{
				auto dst = static_cast<IObject3D*>(obj.Object.get())->Intersects(ray);

				if(!std::isnan(dst) && dst > 0.0f && dst < closestDistance)
				{
					closestDistance = dst;
					closestIntersection = ray.Origin + (ray.Direction * dst);
					closestObject = obj.Object.get();
				}
			}
		}

		if(closestDistance < std::numeric_limits<float>::infinity())
		{
			if(!middleBtn) cursor3D = closestIntersection;
			else cursor3D = static_cast<IObject3D*>(closestObject)->Position;
			_selectedObject = closestObject;
		}
	}

	rightButtonPrevPressed = (Mouse.RightButton() == ButtonState::Pressed);
	middleButtonPrevPressed = (Mouse.MiddleButton() == ButtonState::Pressed);
}

void EditorGame::_gizmoButtons()
{
	if(_selectedObject != nullptr)
	{
		auto gizmo = _selectedObject->GetGizmo();

		[[unlikely]]
		if(gizmo == nullptr) return;

		static bool lastClickFrame = false;
		static bool firstClickFrame = false;

		if(Mouse.LeftButton() != ButtonState::Pressed)
		{
			_selectedTransformButton = nullptr;
			lastClickFrame = true;
		}

		if(gizmo->AllowTranslating) _gizmoFn(gizmo, {&btnMvX, &btnMvY, &btnMvZ}, &Button::Update, 0b11);
		else _gizmoFn(gizmo, {&btnMvX, &btnMvY, &btnMvZ}, &Button::ResetInputState, 0b111);

		if(gizmo->AllowRotating) _gizmoFn(gizmo, {&btnRtX, &btnRtY, &btnRtZ}, &Button::Update, 0b100);
		else _gizmoFn(gizmo, {&btnRtX, &btnRtY, &btnRtZ}, &Button::ResetInputState, 0b111);

		if(gizmo->AllowScaling) _gizmoFn(gizmo, {&btnScX, &btnScY, &btnScZ}, &Button::Update, 0b11);
		else _gizmoFn(gizmo, {&btnScX, &btnScY, &btnScZ}, &Button::ResetInputState, 0b111);

		//handles each gizmo button when selected
		auto handleGizmoBtn = [this](Button* btn, float num, float sgn) -> float
		{
			if(btn->IsClicked() && _selectedTransformButton == nullptr)
			{
				_selectedTransformButton = btn;
				firstClickFrame = true;
				lastClickFrame = false;
			}

			if(_selectedTransformButton == btn)
			{
				_selectedTransformButton = btn;

				auto btnCenter = btn->Position + (btn->Scale / 2.0f);
				auto mousePos = static_cast<Vector2>(Mouse.Position());
				btnCenter.Hadamard(static_cast<Vector2>(Window->Size()));

				//remove floating point remainder (fix mismatch between SetMousePosition and deltaM)
				btnCenter.X = std::trunc(btnCenter.X);
				btnCenter.Y = std::trunc(btnCenter.Y);

				this->Window->SetMousePosition(Point(
					static_cast<int>(btnCenter.X),
					static_cast<int>(btnCenter.Y)
				));

				auto deltaM = (btnCenter - mousePos) * float(Update_dt);
				return num + ((deltaM.X - deltaM.Y) * Settings::GizmoSensitivity.Value * sgn);
			}
			return num;
		};

		auto handleGizmoBtn2 = [this, handleGizmoBtn](Button* btn, float (*fn)(float), float num, float sgn) -> float
		{
			return fn(handleGizmoBtn(btn, num, sgn));
		};

		auto clampScale = [](float num) -> float
		{
			return std::max(0.00001f, num);
		};

		if(auto obj3d = dynamic_cast<IObject3D*>(_selectedObject); obj3d != nullptr)
		{
			float dx = handleGizmoBtn(&btnMvX, 0, -1);
			float dy = handleGizmoBtn(&btnMvY, 0, -1);
			float dz = handleGizmoBtn(&btnMvZ, 0, -1);
			auto dp = Vector3(dx, dy, dz);

			obj3d->Position += dp;
			cursor3D += dp;

			float rx = handleGizmoBtn(&btnRtX, 0, 1);
			float ry = handleGizmoBtn(&btnRtY, 0, 1);
			float rz = handleGizmoBtn(&btnRtZ, 0, 1);
			obj3d->Rotation *= Quaternion::FromYawPitchRoll(ry, rx, rz);
			obj3d->Rotation.Normalize();

			obj3d->Scale.X = handleGizmoBtn2(&btnScX, clampScale, obj3d->Scale.X, -1);
			obj3d->Scale.Y = handleGizmoBtn2(&btnScY, clampScale, obj3d->Scale.Y, -1);
			obj3d->Scale.Z = handleGizmoBtn2(&btnScZ, clampScale, obj3d->Scale.Z, -1);
		}
		else if(auto obj2D = dynamic_cast<IObject2D*>(_selectedObject); obj2D != nullptr)
		{
			obj2D->Position.X = handleGizmoBtn(&btnMvX, obj2D->Position.X, -1);
			obj2D->Position.Y = handleGizmoBtn(&btnMvY, obj2D->Position.Y, -1);

			obj2D->Rotation = handleGizmoBtn(&btnRtZ, obj2D->Rotation, 1);

			obj2D->Scale.X = handleGizmoBtn2(&btnScX, clampScale, obj2D->Scale.X, -1);
			obj2D->Scale.Y = handleGizmoBtn2(&btnScY, clampScale, obj2D->Scale.Y, -1);
		}

		if(firstClickFrame)
		{
			Window->SetMouseVisibility(false);
			firstClickFrame = false;
		}

		if(lastClickFrame)
		{
			lastClickFrame = false;
			Window->SetMouseVisibility(true);
		}
	}
}

void EditorGame::Update()
{
	//update gizmos
	for(auto &obj : *Objects)
	{
		auto gizmo = obj.Object->GetGizmo();
		if(gizmo != nullptr)
		{
			gizmo->Object = obj.Object.get();
			gizmo->Update();
		}
	}

	bool areTopButtonsVisible = _selectedObject != nullptr && _selectedObject->GetGizmo();

	if(areTopButtonsVisible && Mouse.Position().Y >= ((1.0f / 9.0f) * Window->Size()))
	{
		_controlCamera();
		_picking();
	}
	else if(!areTopButtonsVisible)
	{
		_controlCamera();
		_picking();
	}

	_gizmoButtons();

	Camera.Rotation = Quaternion::FromYawPitchRoll(cameraPos.X, cameraPos.Y, 0);
	Camera.Position = cursor3D + Vector3::UnitZ().Transform(Camera.Rotation) * (zoom + 5);
}

void EditorGame::Draw3D()
{
	Camera.Draw3D();

	axis->Transform = Matrix4x4::CreateTranslation(cursor3D);
	axis->View = View;
	axis->Projection = Projection;
	axis->Draw3D();

	if (Settings::ShowGrid.Value)
	{
		grid->View = View;
		grid->Projection = Projection;
		grid->Draw3D();

		if (!Math::WithinEpsilon(cursor3D.X, 0) || !Math::WithinEpsilon(cursor3D.Y, 0) || !Math::WithinEpsilon(cursor3D.Z, 0))
		{
			grid_center->View = View;
			grid_center->Projection = Projection;
			grid_center->Draw3D();
		}
	}

	auto drawAllObjects = [this]()
	{
		for(auto& obj : *Objects)
		{
			if(obj.InternalType == ObjectType::IObject3D)
			{
				auto obj_3d = static_cast<IObject3D*>(obj.Object.get());

				auto gizmo = obj_3d->GetGizmo();
				if(gizmo != nullptr)
				{
					gizmo->Selected = obj.Object.get() == this->_selectedObject;
					gizmo->Object = obj.Object.get();
					gizmo->Draw3D();
				}
			}
		}
	};

	//Main rendering pass
	drawAllObjects();	
}

void EditorGame::SelectObject(IObject* obj)
{
	_selectedObject = obj;
	
	if (dynamic_cast<IObject3D*>(obj) != nullptr)
	{
		cursor3D = static_cast<IObject3D*>(obj)->Position;
	}
}

void EditorGame::_gizmoFn(Gizmos::IGizmo* g, std::array<Button*, 3> btns, void (Button::* fn)(), uint8_t allow2D)
{
	if(g->Allow2DRendering)
	{
		if((allow2D & 0b1) == 0b1) (*btns[0].*fn)();
		if((allow2D & 0b10) == 0b10)(*btns[1].*fn)();
		if((allow2D & 0b100) == 0b100)(*btns[2].*fn)();
	}
	else if(g->Allow3DRendering)
	{
		(*btns[0].*fn)();
		(*btns[1].*fn)();
		(*btns[2].*fn)();
	}
}

void EditorGame::Draw2D()
{
	this->ClearColor = Color(0, 0, 0, 1);

	SpriteBatch->Begin();
	//SpriteBatch->DrawString(
	//	_font.get(),
	//	std::format("Mouse {} {} FPS {}", cameraPos.X, cameraPos.Y, static_cast<int>(1.0f / Draw_dt)),
	//	Point(20, 20),
	//	1
	//);

	for(auto& obj : *Objects)
	{
		auto obj2d = static_cast<IObject2D*>(obj.Object.get());

		auto gizmo = obj2d->GetGizmo();
		if(gizmo != nullptr)
		{ 
			gizmo->Selected = obj.Object.get() == this->_selectedObject;
			gizmo->Object = obj.Object.get();
			gizmo->Draw2D();
		}
	}

	if(_selectedObject != nullptr)
	{
		auto gizmo = _selectedObject->GetGizmo();

		[[likely]]
		if(gizmo != nullptr)
		{
			if(gizmo->AllowTranslating) _gizmoFn(gizmo, {&btnMvX, &btnMvY, &btnMvZ}, &Button::Draw2D, 0b11);
			if(gizmo->AllowRotating) _gizmoFn(gizmo, {&btnRtX, &btnRtY, &btnRtZ}, &Button::Draw2D, 0b100);
			if(gizmo->AllowScaling) _gizmoFn(gizmo, {&btnScX, &btnScY, &btnScZ}, &Button::Draw2D, 0b11);
		}
	}

	SpriteBatch->End();
}

bool EditorGame::IsFocused() const
{
	return editorWindow == GetForegroundWindow();
}

void EditorGame::Reset3DCursor()
{
	cursor3D = Vector3::Zero();
	_selectedObject = nullptr;
}

bool EditorGame::IsEditor() const noexcept
{
	return true;
}

EditorGame::~EditorGame()
{
}