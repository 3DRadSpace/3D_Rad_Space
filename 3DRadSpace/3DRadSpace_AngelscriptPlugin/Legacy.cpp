#include "Legacy.hpp"
#include <Engine3DRadSpace/Objects/Impl/Objects.hpp>
#include <Engine3DRadSpace/Objects/Impl/TextPrint.hpp>
#include <Engine3DRadSpace/Objects/ObjectList.hpp>
#include <Engine3DRadSpace/Physics/Objects/RigidDynamic.hpp>
#include <Engine3DRadSpace/Physics/Objects/RigidStatic.hpp>
#include <Engine3DRadSpace/Projects/Serialization.hpp>
#include <Engine3DRadSpace/Native/LibraryLoader.hpp>

#include <thread>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Physics;
using namespace Engine3DRadSpace::Physics::Objects;
using namespace Engine3DRadSpace::Projects;

static ObjectList *objList;
static std::filesystem::path projectPath;

void Engine3DRadSpace::Legacy::SetObjectList(ObjectList *list)
{
	objList = list;
}

void Engine3DRadSpace::Legacy::SetProjectPath(const std::filesystem::path &path)
{
	projectPath = std::filesystem::path(path);
}

void iObjectStart(unsigned obj_x)
{
	(*objList)[obj_x]->Enable();
}

void iObjectStop(unsigned obj_x)
{
	(*objList)[obj_x]->Disable();
}

void iObjectSwitch(unsigned obj_x)
{
	(*objList)[obj_x]->Switch();

}

void iObjectShow(unsigned obj_x)
{
	(*objList)[obj_x]->Show();
}

void iObjectHide(unsigned obj_x)
{
	(*objList)[obj_x]->Hide();
}

void iObjectShowHideSwitch(unsigned obj_x)
{
	(*objList)[obj_x]->SwitchVisibility();
}

void iObjectReset(unsigned obj_x)
{
	auto obj = Serializer::LoadObjectFromProject(projectPath, obj_x);
	objList->Replace(obj, obj_x);
	delete obj;
}

void iObjectOrientation(unsigned obj_x, Quaternion& q)
{
	auto refobj = (*objList)[obj_x];
	if(auto obj = dynamic_cast<IObject3D*>(refobj); obj != nullptr)
	{
		q = obj->Rotation;
		return;
	}
	if(auto obj = dynamic_cast<IObject2D*>(refobj); obj != nullptr)
	{
		auto r = obj->Rotation;
		q = Quaternion(r, r, r, r);
		return;
	}
	q = Quaternion();
}

void iObjectOrientationSet(unsigned obj_x, const Quaternion& q)
{
	auto refobj = (*objList)[obj_x];
	if(auto obj = dynamic_cast<IObject3D*>(refobj); obj != nullptr) obj->Rotation = q;
	if(auto obj = dynamic_cast<IObject2D*>(refobj); obj != nullptr) obj->Rotation = q.X;
}

void iObjectOrientationReset(unsigned obj_x, const Quaternion& q)
{
	std::unique_ptr<IObject> temp;
	temp.reset(Serializer::LoadObjectFromProject(projectPath, obj_x));

	if(auto refobj_lst = dynamic_cast<IObject3D*>((*objList)[obj_x]), temp_obj = dynamic_cast<IObject3D*>(temp.get()); refobj_lst != nullptr && temp_obj != nullptr)
	{
		temp_obj->Rotation = q;
	}

	if(auto refobj_lst = dynamic_cast<IObject2D*>((*objList)[obj_x]), temp_obj = dynamic_cast<IObject2D*>(temp.get()); refobj_lst != nullptr && temp_obj != nullptr)
	{
		temp_obj->Rotation = q.X;
	}

	objList->Replace(temp.release(), obj_x);
}

void iObjectLocation(unsigned obj_x, Vector3& v)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[obj_x]);
	if (obj != nullptr) v = obj->Position;
	else v = Vector3();
}

void iObjectLocationSet(unsigned obj_x, const Vector3& v)
{
	auto refobj = (*objList)[obj_x];
	if(auto obj = dynamic_cast<IObject3D*>(refobj); obj != nullptr) obj->Position = v;
	if(auto obj = dynamic_cast<IObject2D*>(refobj); obj != nullptr) obj->Position = Vector2(v.X, v.Y);
}

void iObjectLocationReset(unsigned obj_x, const Engine3DRadSpace::Math::Vector3& v)
{
	std::unique_ptr<IObject> temp;
	temp.reset(Serializer::LoadObjectFromProject(projectPath, obj_x));

	if(auto refobj_lst = dynamic_cast<IObject3D*>((*objList)[obj_x]), temp_obj = dynamic_cast<IObject3D*>(temp.get()); refobj_lst != nullptr && temp_obj != nullptr)
	{
		temp_obj->Position = v;
		objList->Replace(temp.release(), obj_x);
	}
}

void iObjectPositionReset(unsigned obj_x,const Engine3DRadSpace::Math::Quaternion& rotation,const Engine3DRadSpace::Math::Vector3& location)
{
	std::unique_ptr<IObject> temp;
	temp.reset(Serializer::LoadObjectFromProject(projectPath, obj_x));
	if(auto refobj_lst = dynamic_cast<IObject3D*>((*objList)[obj_x]), temp_obj = dynamic_cast<IObject3D*>(temp.get()); refobj_lst != nullptr && temp_obj != nullptr)
	{
		temp_obj->Position = location;
		temp_obj->Rotation = rotation;
	}

	objList->Replace(temp.release(), obj_x);
}

void iObjectScaleSet(unsigned obj_x, const Vector3& v)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[obj_x]);
	if (obj != nullptr) obj->Scale = v;
}

void iObjectScale(unsigned obj_x, Vector3& v)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[obj_x]);
	if (obj != nullptr) v = obj->Scale;
	else v = Math::Vector3();
}

float iObjectKmh(unsigned obj_x)
{
	auto obj = dynamic_cast<RigidDynamic*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		auto vel = obj->GetLinearVelocity();
		return vel.Length() * 3.6f;
	}
	else return 0.0f;
}

void iObjectVelocity(unsigned obj_x, Math::Vector3& v)
{
	auto obj = dynamic_cast<RigidDynamic*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		 v = obj->GetLinearVelocity();
	}
	else v = Vector3::Zero();
}

void iObjectVelocitySet(unsigned obj_x, Math::Vector3& v)
{
	auto obj = dynamic_cast<RigidDynamic*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		obj->SetLinearVelocity(v);
	}
}

void iObjectSpin(unsigned obj_x, Math::Vector3& v)
{
	auto obj = dynamic_cast<RigidDynamic*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		 v = obj->GetAngularVelocity();
	}
	else v = Vector3::Zero();
}

void iObjectSpinSet(unsigned obj_x, Math::Vector3& v)
{
	auto obj = dynamic_cast<RigidDynamic*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		obj->SetAngularVelocity(v);
	}
}

void iObjectTorqueApply(unsigned obj_x, Math::Vector3& v)
{
	auto obj = dynamic_cast<RigidDynamic*>((*objList)[obj_x]);
	if (obj != nullptr) obj->GetCollider()->ApplyTorque(v);
}

void iObjectAngularAccelerationApply(unsigned obj_x, Math::Vector3& v)
{
	auto obj = dynamic_cast<RigidDynamic*>((*objList)[obj_x]);
	if (obj != nullptr) obj->GetCollider()->ApplyAngularAcceleration(v);
}

void iObjectForceApply(unsigned ojb_x, Math::Vector3 f, Math::Vector3* p)
{
	auto obj = dynamic_cast<RigidDynamic*>((*objList)[ojb_x]);
	if(obj != nullptr)
	{
		if(p == nullptr)
			obj->GetCollider()->ApplyForce(f);
		else
			obj->GetCollider()->ApplyForce(f, *p);
	}
}

void iObjectAccelerationApply(unsigned obj_x, const Math::Vector3& acc)
{
	auto obj = dynamic_cast<RigidDynamic*>((*objList)[obj_x]);
	if(obj != nullptr) obj->GetCollider()->ApplyAcceleration(acc);
}

void iObjectDampingApply(unsigned obj_x, Math::Vector3& v, bool is_rotation, bool local_axis)
{
	auto obj = dynamic_cast<RigidStatic*>((*objList)[obj_x]);
	obj->SetLinearDamping(v.X);
}

float iObjectPicked(unsigned obj_x, Math::Vector3& outHitResult)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		auto game = static_cast<Game*>(obj->GetGame());

		auto mousePos = game->Mouse.Position();

		auto viewport = game->Device->ImmediateContext()->GetViewport();
		auto windowSize = game->Window->Size();

		// Scale mouse coordinates from window space to viewport space
		float scaleX = viewport.ScreenRectangle.Width / static_cast<float>(windowSize.X);
		float scaleY = viewport.ScreenRectangle.Height / static_cast<float>(windowSize.Y);
		Point scaledMousePos = Point(
			static_cast<int>(mousePos.X * scaleX),
			static_cast<int>(mousePos.Y * scaleY)
		);

		auto activeCamera = game->Cameras->GetActiveCamera();

		auto ray = game->GetMouseRay(scaledMousePos, activeCamera->GetViewMatrix(), activeCamera->GetProjectionMatrix());
		Math::Vector3 normal;
		iObjectScan(obj_x, ray.Origin, ray.Direction, 1000.0f, outHitResult, normal);
		return (ray.Origin - outHitResult).Length();
	}
	else return -std::numeric_limits<float>::infinity();
}

int iObjectScan(
	unsigned obj_x, 
	const Math::Vector3& origin,
	const Math::Vector3& direction,
	float radius,
	Math::Vector3& contactPoint, 
	Math::Vector3& contactNormal)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		auto intersection = obj->Intersects(
			Ray{
				.Origin = origin,
				.Direction = direction
			}
		);
		if (!std::isnan(intersection))
		{
			float d = intersection;
			if (d > radius) return false;
			else
			{
				contactPoint = origin + (d * direction);
				contactNormal = -direction;
				return true;
			}
		}
		else return false;
	}
	else return false;
}

void iObjectTextSet(unsigned obj_x, const std::string &str)
{
	auto txtPrint = dynamic_cast<TextPrint*>((*objList)[obj_x]);
	if(txtPrint != nullptr) txtPrint->Text = str;
}

void iObjectParamSet(unsigned obj_x, int index, float t)
{
	auto obj = (*objList)[obj_x];
	if (obj == nullptr) return;

	auto uuid = obj->GetUUID();
	if (uuid == Reflection::UUID{}) return;

	auto refl = Internal::GetReflDataFromUUID(uuid);
	if (refl->NumFields() > index) return;
	if (refl == nullptr) return;

	auto field = refl->operator[](index);

	if(field->TypeHash() == typeid(float).hash_code())
	{
		field->Set(obj, &t);
	}
}

void iObjectRefresh(unsigned obj_x, const std::string& path)
{
	auto obj = (*objList)[obj_x];
	obj->Load(path);
}

void iObjectChildTransform(
	unsigned obj_x,
	unsigned obj_y,
	const Engine3DRadSpace::Math::Vector3& eulerAnglesAngularOffset,
	const Engine3DRadSpace::Math::Vector3& linearOffset
)
{
	auto parentObj = (*objList)[obj_x];
	auto childObj = (*objList)[obj_y];
	if (parentObj == nullptr || childObj == nullptr) return;

	if (auto parent3D = dynamic_cast<IObject3D*>(parentObj); parent3D != nullptr)
	{
		if (auto child3D = dynamic_cast<IObject3D*>(childObj); child3D != nullptr)
		{
			child3D->Position = parent3D->Position + linearOffset;
			child3D->Rotation = parent3D->Rotation * Quaternion::FromYawPitchRoll(
				eulerAnglesAngularOffset.Y,
				eulerAnglesAngularOffset.X,
				eulerAnglesAngularOffset.Z
			);
		}
	}
}

int iStringLen(const std::string &str)
{
	return str.length();
}

void iStringUCase(std::string &out, const std::string &in)
{
	out = in;

	std::transform(in.begin(), in.end(), out.begin(),
	[](char c) -> char
	{
		return std::toupper(c);
	});
}

void iStringLCase(std::string& out, const std::string& in)
{
	out = in;

	std::transform(in.begin(), in.end(), out.begin(),
	[](char c) -> char
	{
		return std::tolower(c);
	});
}

void iStringLeft(std::string& out, const std::string& in, int n)
{
	auto subStr = in.substr(0, n);
	out += subStr;
}

void iStringRight(std::string& out, const std::string& in, int n)
{
	auto subStr = in.substr(in.length() - n, n);
	out += subStr;
}

void iStringMid(std::string& out, const std::string& in, int start, int length)
{
	auto subStr = in.substr(start, length);
	out += subStr;
}

void iStringStr(std::string& result, float value, const std::string& format)
{
	int size = snprintf(NULL, 0, format.c_str(), value);
	result.resize(size);
	snprintf(result.data(), size + 1, format.c_str(), value);
}

float iStringVal(const std::string& str)
{
	try
	{
		return std::stof(str);
	}
	catch (...)
	{
		return 0.0f;
	}
}

int iStringFind(const std::string& str, const std::string& substr, int start, bool case_sensitive)
{
	std::string str_cpy = str;
	std::string substr_cpy = substr;

	if (case_sensitive)
	{
		iStringLCase(str_cpy, str);
		iStringLCase(substr_cpy, substr);
	}

	return static_cast<int>(str_cpy.find(substr_cpy, start));
}

void iStringReplace(std::string& result, const std::string& str, const std::string& old_substr, const std::string& new_substr, bool case_sensitive)
{
	result = str;

	while (true)
	{
		int pos = iStringFind(result, old_substr, 0, case_sensitive);
		if (std::string::npos == -1) break;
		result.replace(pos, old_substr.length(), new_substr);
	}
}

void iPrint(const std::string& str, float x, float y, unsigned obj_x)
{
	auto obj = dynamic_cast<TextPrint*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		obj->Text = str;
		obj->Position = Vector2(x, y);
	}
}

std::array<std::string, 1024> globalStrings;

void iGlobalStringSet(const std::string& str, int id)
{
	if (id >= 0 && id < static_cast<int>(globalStrings.size()))
	{
		globalStrings[id] = str;
	}
}

void iGlobalStringGet(std::string& outStr, int id)
{
	if (id >= 0 && id < static_cast<int>(globalStrings.size()))
	{
		outStr = globalStrings[id];
	}
}

std::mt19937 rng(std::random_device{}());

float iFloatRand(float a, float b)
{
	std::uniform_real_distribution<float> dist(a, b);
	return dist(rng);
}

float iFloatAbs(float x)
{
	return std::fabs(x);
}

float iFloatSin(float x)
{
	return std::sin(x);
}

float iFloatCos(float x)
{
	return std::cos(x);
}

float iFloatSqrt(float x)
{
	return std::sqrt(x);
}

float iFloatInterpolate(float x, float srcmin, float srcmax, float dstmin, float dstmax, bool clamp)
{
	float t = (x - srcmin) / (srcmax - srcmin);
	if (clamp)
	{
		t = std::clamp(t, 0.0f, 1.0f);
	}
	return dstmin + (dstmax - dstmin) * t;
}

//float iFloatTendTo(float adjust, float ref, float target, float speed, int mode)
//{
//	switch (mode)
//	{
//	case 0: // Linear
//	{
//		float delta = target - ref;
//		float step = speed * adjust;
//		if (std::fabs(delta) <= step)
//		{
//			return target;
//		}
//		else
//		{
//			return ref + (delta > 0 ? step : -step);
//		}
//	}
//	default:
//		return ref;
//	}
//	
//}

float iVectorLength(const Math::Vector3& v)
{
	return v.Length();
}

float iVectorLengthSq(const Math::Vector3& v)
{
	return v.LengthSquared();
}

void iVectorLengthSet(Math::Vector3& v, float length)
{
	v.Normalize();
	v *= length;
}

float iVectorDot(const Math::Vector3& a, const Math::Vector3& b)
{
	return a.Dot(b);
}

void iVectorCross(Math::Vector3& out, const Math::Vector3& a, const Math::Vector3& b)
{
	out = Math::Vector3::Cross(a, b);
}

void iVectorRotate(Math::Vector3& out, const Math::Vector3& vec, const Math::Quaternion& q)
{
	out = Math::Vector3::Transform(vec, q);
}

void iVectorEulerRotate(Math::Vector3& out, const Math::Vector3& vec, float pitch, float yaw, float roll, const std::string& order)
{
	Math::Quaternion q;
	iQuaternionFromEulerAngles(q, pitch, yaw, roll, order);

	out = Math::Vector3::Transform(vec, q);
}

bool iVectorCompare(const Math::Vector3& a, const Math::Vector3& b, float tolerance)
{
	return std::fabs(a.X - b.X) <= tolerance &&
		   std::fabs(a.Y - b.Y) <= tolerance &&
		   std::fabs(a.Z - b.Z) <= tolerance;
}

bool iQuaternionCompare(const Math::Quaternion& a, const Math::Quaternion& b)
{
	return  Math::WithinEpsilon(a.X, b.X) &&
			Math::WithinEpsilon(a.Y, b.Y) &&
			Math::WithinEpsilon(a.Z, b.Z) &&
			Math::WithinEpsilon(a.W, b.W);
}

void iQuaternionFromAxisAngle(Math::Quaternion& out, const Math::Vector3& axis, float angle)
{
	out = Math::Quaternion::FromAxisAngle(axis, angle);
}

void iQuaternionFromEulerAngles(Math::Quaternion& out, float pitch, float yaw, float roll, const std::string& order)
{
	Math::Quaternion q;
	for (auto chr : order)
	{
		switch (chr)
		{
		case 'x':
		case 'X':
			q *= Math::Quaternion::FromYawPitchRoll(0.0f, pitch, 0.0f) * q;
			break;
		case 'y':
		case 'Y':
			q *= Math::Quaternion::FromYawPitchRoll(yaw, 0.0f, 0.0f) * q;
			break;
		case 'z':
		case 'Z':
			q *= Math::Quaternion::FromYawPitchRoll(0.0f, 0.0f, roll) * q;
			break;
		default:
			break;
		}
	}
	out = q;
}

void iQuaternionToEulerAngles(const Math::Quaternion& quat, float& pitch, float& yaw, float& roll)
{
	Math::Vector3 euler = quat.ToYawPitchRoll();
	pitch = euler.Y;
	yaw = euler.X;
	roll = euler.Z;
}

void iQuaternionLookAt(Math::Quaternion& out, const Math::Vector3& eye, const Math::Vector3& target)
{
	Math::Vector3 forward = (target - eye).Normalize();
	Math::Vector3 up = Math::Vector3::Up();
	Math::Vector3 right = Math::Vector3::Cross(up, forward).Normalize();
	up = Math::Vector3::Cross(forward, right);

	Math::Matrix4x4 rotationMatrix(
		right.X, right.Y, right.Z, 0.0f,
		up.X, up.Y, up.Z, 0.0f,
		forward.X, forward.Y, forward.Z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
	out = Math::Quaternion::FromMatrix(rotationMatrix);
}

void  iQuaternionMultiply(Math::Quaternion& out, const Math::Quaternion& a, const Math::Quaternion& b)
{
	out = a * b;
}

void iQuaternionInterpolate(Math::Quaternion& out, const Math::Quaternion& a, const Math::Quaternion& b, float t)
{
	out = Math::Quaternion::Slerp(a, b, t);
}

std::vector<std::unique_ptr<std::fstream>> files;

int iFileReadOpen(const std::string& filename)
{
	int idx = 0;
	for (auto& pFile : files)
	{
		if (!pFile)
		{
			pFile = std::make_unique<std::fstream>(filename, std::ios::in | std::ios::binary);
			return ++idx;
		}
		++idx;
	}
	
	files.push_back(std::make_unique<std::fstream>(filename, std::ios::in | std::ios::binary));
	return files.size() - 1;	
}

int iFileWriteOpen(const std::string& filename)
{
	int idx = 0;
	for (auto& pFile : files)
	{
		if (!pFile)
		{
			pFile = std::make_unique<std::fstream>(filename, std::ios::out | std::ios::binary);
			return ++idx;
		}
		++idx;
	}
	files.push_back(std::make_unique<std::fstream>(filename, std::ios::out | std::ios::binary));
	return files.size() - 1;
}

void iFileClose(int fileHandle)
{
	if (fileHandle >= 0 && fileHandle < static_cast<int>(files.size()))
	{
		files[fileHandle].reset();
	}
}

float iFileValueRead(int fileHandle)
{
	if (fileHandle >= 0 && fileHandle < static_cast<int>(files.size()) && files[fileHandle])
	{
		float value;
		files[fileHandle]->read(reinterpret_cast<char*>(&value), sizeof(float));
		return value;
	}
	return 0.0f;
}

void iFileValueWrite(int fileHandle, float value, bool useNewline)
{
	if (fileHandle >= 0 && fileHandle < static_cast<int>(files.size()) && files[fileHandle])
	{
		files[fileHandle]->write(reinterpret_cast<const char*>(&value), sizeof(float));
		if (useNewline)
		{
			files[fileHandle]->put('\n');
		}
	}
}

int iFileByteRead(int fileHandle)
{
	if (fileHandle >= 0 && fileHandle < static_cast<int>(files.size()) && files[fileHandle])
	{
		char byte;
		files[fileHandle]->read(&byte, sizeof(char));
		return static_cast<unsigned char>(byte);
	}
	return -1;
}

void iFileByteWrite(int fileHandle, int byte)
{
	if (fileHandle >= 0 && fileHandle < static_cast<int>(files.size()) && files[fileHandle])
	{
		char b = static_cast<char>(byte);
		files[fileHandle]->write(&b, sizeof(char));
	}
}

void iFileStringRead(int fileHandle, std::string& outStr)
{
	if (fileHandle >= 0 && fileHandle < static_cast<int>(files.size()) && files[fileHandle])
	{
		std::string result;
		(*files[fileHandle]) >> result;
		outStr = result;
	}
}

void iFileStringWrite(int fileHandle, const std::string& value, bool useNewline)
{
	if (fileHandle >= 0 && fileHandle < static_cast<int>(files.size()) && files[fileHandle])
	{
		files[fileHandle]->write(value.c_str(), value.size());
		if (useNewline)
		{
			files[fileHandle]->put('\n');
		}
	}
}

bool iFileEOF(int fileHandle)
{
	if (fileHandle >= 0 && fileHandle < static_cast<int>(files.size()) && files[fileHandle])
	{
		return files[fileHandle]->eof();
	}
	return true;
}

bool iFileExists(const std::string& filename)
{
	return std::filesystem::exists(filename);
}

void iFileCopy(const std::string& source, const std::string& destination)
{
	std::filesystem::copy(source, destination);
}

void iFileDelete(const std::string& filename)
{
	std::filesystem::remove(filename);
}

void iFolderCreate(const std::string& folderName)
{
	std::filesystem::create_directory(folderName);
}

void iFolderDelete(const std::string& folderName)
{
	std::filesystem::remove_all(folderName);
}

//void iFileDownload(const std::string& url, const std::string& destination)
//{
//	// Implement file download logic here
//}
//
//void iFileDownloadPB(const std::string& url, const std::string& destination)
//{
//	// Implement file download with progress bar logic here
//}

int iFileSize(const std::string& filename)
{
	if (std::filesystem::exists(filename))
	{
		return static_cast<int>(std::filesystem::file_size(filename));
	}
	return -1;
}

void iLocalFolder(std::string& folderName)
{
	folderName = std::filesystem::current_path().string();
}

bool isKeyDown(int keyCode)
{
	auto game = static_cast<Game*>(objList->GetOwner());
	return game->Keyboard.IsKeyDown(static_cast<Input::Key>(keyCode));
}

int iKeyCode(const std::string& keyName)
{
	return static_cast<int>(Input::KeyIntFromVirtualKeyCode(keyName));
}

int iTypedChar()
{
	auto game = static_cast<Game*>(objList->GetOwner());
	return static_cast<int>(*game->Keyboard.Buffer());
}

float iMouseX()
{
	auto game = static_cast<Game*>(objList->GetOwner());
	return static_cast<float>(game->Mouse.Position().X) / game->Device->Resolution().X;
}

float iMouseY()
{
	auto game = static_cast<Game*>(objList->GetOwner());
	return static_cast<float>(game->Mouse.Position().Y) / game->Device->Resolution().Y;
}

float iMouseZ()
{
	auto game = static_cast<Game*>(objList->GetOwner());
	return static_cast<float>(game->Mouse.ScrollWheel());
}

bool iMouseButtonDown(int button)
{
	auto game = static_cast<Game*>(objList->GetOwner());
	switch (button)
	{
		case 0: return game->Mouse.LeftButton() != Input::ButtonState::Released;
		case 1: return game->Mouse.RightButton() != Input::ButtonState::Released;
		case 2: return game->Mouse.MiddleButton() != Input::ButtonState::Released;
	}
	return false;
}

//bool iMouseButtonPressed(int button)
//{
//
//}

//void iShaderSet(unsigned obj_x, const std::string& path)
//{
//	auto obj = dynamic_cast<Skinmesh*>((*objList)[obj_x]);
//	for (auto& mesh : *obj->GetModel())
//	{
//		for (auto& meshPart : *mesh)
//		{
//			
//		}
//	}
//}

int iObjectHandle(int h)
{
	return h;
}

int iSystemTime(int identifier)
{
	auto now = std::chrono::system_clock::now();
	auto time = std::chrono::system_clock::to_time_t(now);
	std::tm localTime;
	localtime_s(&localTime, &time);

	switch (identifier)
	{
		case 0: return localTime.tm_year + 1900;
		case 1: return localTime.tm_mon + 1;
		case 2: return localTime.tm_wday;
		case 3: return localTime.tm_mday;
		case 4: return localTime.tm_hour;
		case 5: return localTime.tm_min;
		case 6: return localTime.tm_sec;
		case 7: return static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() % 1000);
		default: return -1;
	}
}

int iDisplayWidth()
{
	auto game = static_cast<Game*>(objList->GetOwner());
	return static_cast<int>(game->Window->Size().X);
}

int iDisplayHeight()
{
	auto game = static_cast<Game*>(objList->GetOwner());
	return static_cast<int>(game->Window->Size().Y);
}

int iShaderVersion(bool minor)
{
	//Assume DirectX11::GraphicsDevice was succesfully initialized. 
	//Then the minimally supported shader version is 4.0.
	return minor ? 0 : 4;
}

void iRenderingEnable(bool enable)
{
	auto game = static_cast<Game*>(objList->GetOwner());
	
	for (auto& object : *game->Objects)
	{
		object->Visible = enable;
	}
}

void iShadowsEnable(bool enable)
{
	auto game = static_cast<Game*>(objList->GetOwner());
}

void iEscKeyEnable()
{
}

void iEscKeyDisable()
{
}

bool iCommand(const std::string& command)
{
	return std::system(command.c_str()) == 0;
}

bool iCommandContinue(const std::string& command)
{
	std::thread cmdThread([command]()
		{
			std::system(command.c_str());
		});
	
	cmdThread.detach();
	return true;
}

bool i3DPointVisible(unsigned camera, const Engine3DRadSpace::Math::Vector3& point)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[camera]);

	if (auto cam = dynamic_cast<ICamera*>(obj); cam != nullptr)
	{
		auto viewFrustum = cam->GetViewingFrustum();
		return viewFrustum.Contains(point);
	}
	return false;
}

bool iSphereVisible(unsigned camera, const Engine3DRadSpace::Math::Vector3& center, float radius)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[camera]);
	if (auto cam = dynamic_cast<ICamera*>(obj); cam != nullptr)
	{
		auto viewFrustum = cam->GetViewingFrustum();
		return viewFrustum.Contains(BoundingSphere(center, radius));
	}
	return false;
}

void i3DLocationToScreen(Math::Vector3& outScreenPos, const Engine3DRadSpace::Math::Vector3& worldPos, unsigned camera)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[camera]);
	if (auto cam = dynamic_cast<ICamera*>(obj); cam != nullptr)
	{
		auto viewMatrix = cam->GetViewMatrix();
		auto projectionMatrix = cam->GetProjectionMatrix();
		outScreenPos = Vector3::Transform(worldPos, viewMatrix * projectionMatrix);
	}
	else
	{
		outScreenPos = Math::Vector3();
	}
}

void iScreenRay(
	Engine3DRadSpace::Math::Vector3& outRayOrigin,
	Engine3DRadSpace::Math::Vector3& outRayDirection,
	const Engine3DRadSpace::Math::Vector3& screenLocation,
	unsigned cameraID
)
{
	auto camera = ((*objList)[cameraID]);
	auto game = static_cast<Game*>(objList->GetOwner());

	auto mousePos = game->Mouse.Position();

	auto viewport = game->Device->ImmediateContext()->GetViewport();
	auto windowSize = game->Window->Size();

	// Scale mouse coordinates from window space to viewport space
	float scaleX = viewport.ScreenRectangle.Width / static_cast<float>(windowSize.X);
	float scaleY = viewport.ScreenRectangle.Height / static_cast<float>(windowSize.Y);
	Point scaledMousePos = Point(
		static_cast<int>(mousePos.X * scaleX),
		static_cast<int>(mousePos.Y * scaleY)
	);

	auto activeCamera = game->Cameras->GetActiveCamera();

	auto ray = game->GetMouseRay(scaledMousePos, activeCamera->GetViewMatrix(), activeCamera->GetProjectionMatrix());

	outRayDirection = ray.Direction;
	outRayOrigin = ray.Origin;
}

int iSphereSegmentIntersect(
	const Engine3DRadSpace::Math::Vector3& center,
	float radius,
	const Engine3DRadSpace::Math::Vector3& segStart,
	const Engine3DRadSpace::Math::Vector3& segEnd,
	Engine3DRadSpace::Math::Vector3& outIntersectionPoint1,
	Engine3DRadSpace::Math::Vector3& outIntersectionPoint2
)
{
	BoundingSphere sphere(center, radius);
	Ray ray{
		.Origin = segStart,
		.Direction = (segEnd - segStart).Normalize()
	};

	if (ray.Intersects(sphere))
	{
		float t = ray.Intersects(sphere);
		if (t >= 0.0f && t <= (segEnd - segStart).Length())
		{
			outIntersectionPoint1 = ray.Origin + ray.Direction * t;
			return 1; // Intersection occurs
		}
	}
	return 0; // No intersection
}

void iScreenshotSave(const std::string& filename)
{
	auto game = static_cast<Game*>(objList->GetOwner());
	auto texture = game->Device->GetBackBufferTexture();
	try 
	{
		texture->SaveToFile(filename);
	}
	catch (...)
	{
		//Silently fail
	}
}