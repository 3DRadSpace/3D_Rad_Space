#pragma once
#include <Engine3DRadSpace/Reflection/Reflection.hpp>
#include <Engine3DRadSpace/Game.hpp>
#include "Windows/AddObjectDialog.hpp"
#include <nlohmann/json.hpp>

#include <Engine3DRadSpace/Objects/Camera.hpp>

using json = nlohmann::json;

namespace Engine3DRadSpace::Reflection
{
	void to_json(json& j, const UUID& uuid);
	void from_json(const json& j, UUID& uuid);
}

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;


class Serializator
{
public:
	static json SerializeObject(int id, IObject* obj)
	{
		json r;
		void* objPtr = static_cast<void*>(obj);

		using namespace Engine3DRadSpace::Reflection;

		const std::string strID = std::to_string(id);
		r[strID]["UUID"] = obj->GetUUID();

		json assets;

		AddObjectDialog::InitializeReflData();
		auto refl = AddObjectDialog::GetReflDataFromUUID(obj->GetUUID());
		for (auto& field : *refl)
		{
			json jsonField;
			intptr_t offset = 0;
			auto repr = field->Representation();
			for (int i = 0; auto & [reprType, subFieldName] : repr)
			{
				auto str_i = std::to_string(i);
				size_t numSubFields = field->TypeSize() / field->Representation().size();
				switch (reprType)
				{
					case FieldRepresentationType::Boolean:
					{
						jsonField[subFieldName][str_i] = field->GetAtOffset<bool>(objPtr, offset);
						offset += sizeof(bool);
						break;
					}
					case FieldRepresentationType::Integer:
					{
						switch (numSubFields)
						{
							case sizeof(int8_t) :
							{
								jsonField[subFieldName][str_i] = field->GetAtOffset<int8_t>(objPtr, offset);
								offset += sizeof(int8_t);
								break;
							}
							case sizeof(int16_t) :
							{
								jsonField[subFieldName][str_i] = field->GetAtOffset<int16_t>(objPtr, offset);
								offset += sizeof(int16_t);
								break;
							}
							case sizeof(int32_t) :
							{
								jsonField[subFieldName][str_i] = field->GetAtOffset<int32_t>(objPtr, offset);
								offset += sizeof(int32_t);
								break;
							}
							case sizeof(int64_t) :
							{
								jsonField[subFieldName][str_i] = field->GetAtOffset<int64_t>(objPtr, offset);
								offset += sizeof(int64_t);
								break;
							}
							default:
								throw std::logic_error("Unknown integer type!");
						}
						break;
					}
					case FieldRepresentationType::Unsigned:
					{
						switch (numSubFields)
						{
							case sizeof(uint8_t) :
							{
								jsonField[subFieldName][str_i] = field->GetAtOffset<uint8_t>(objPtr, offset);
								offset += sizeof(uint8_t);
								break;
							}
							case sizeof(uint16_t) :
							{
								jsonField[subFieldName][str_i] = field->GetAtOffset<uint16_t>(objPtr, offset);
								offset += sizeof(uint16_t);
								break;
							}
							case sizeof(uint32_t) :
							{
								jsonField[subFieldName][str_i] = field->GetAtOffset<uint32_t>(objPtr, offset);
								offset += sizeof(uint32_t);
								break;
							}
							case sizeof(uint64_t) :
							{
								jsonField[subFieldName][str_i] = field->GetAtOffset<uint64_t>(objPtr, offset);
								offset += sizeof(uint64_t);
								break;
							}
							default:
								throw std::logic_error("Unknown integer type!");
						}
						break;
					}
					case FieldRepresentationType::Float:
					{
						switch (numSubFields)
						{
							case sizeof(float) :
							{
								jsonField[subFieldName][str_i] = field->GetAtOffset<float>(objPtr, offset);
								offset += sizeof(float);
								break;
							}
							case sizeof(double) :
							{
								jsonField[subFieldName][str_i] = field->GetAtOffset<double>(objPtr, offset);
								offset += sizeof(double);
								break;
							}
							default:
								throw std::logic_error("Unknown floating point type!");
						}
						break;
					}
					case FieldRepresentationType::Quaternion:
					{
						Quaternion q = field->GetAtOffset<Quaternion>(objPtr, offset);
						jsonField[subFieldName][str_i]["X"] = q.X;
						jsonField[subFieldName][str_i]["Y"] = q.Y;
						jsonField[subFieldName][str_i]["Z"] = q.Z;
						jsonField[subFieldName][str_i]["W"] = q.W;

						offset += sizeof(Quaternion);
						break;
					}
					case FieldRepresentationType::String:
					{
						std::string str = field->GetAtOffset<std::string>(objPtr, offset);
						jsonField[subFieldName][str_i] = str;

						offset += sizeof(std::string);
						break;
					}
					case FieldRepresentationType::Image:
					{
						RefTexture2D texture = field->GetAtOffset<RefTexture2D>(objPtr, offset);
						assets[std::to_string(texture.ID)]["Path"] = obj->GetGame()->Content->operator[](texture)->Path;
						assets[std::to_string(texture.ID)]["Type"] = texture.AssetType.name();
						jsonField[subFieldName][str_i] = texture.ID;

						offset += sizeof(RefTexture2D);
						break;
					}
					case FieldRepresentationType::Model:
					{
						RefModel3D model = field->GetAtOffset<RefModel3D>(objPtr, offset);
						assets[std::to_string(model.ID)]["Path"] = obj->GetGame()->Content->operator[](model)->Path;
						assets[std::to_string(model.ID)]["Type"] = model.AssetType.name();
						jsonField[subFieldName][str_i] = model.ID;

						offset += sizeof(RefModel3D);
						break;
					}
					case FieldRepresentationType::Key:
					{
						Input::Key k = field->GetAtOffset<Input::Key>(objPtr, offset);
						jsonField[subFieldName][str_i] = static_cast<uint8_t>(k);

						offset += sizeof(Input::Key);
						break;
					}
					case FieldRepresentationType::Enum:
					{
						int e = field->GetAtOffset<int>(objPtr, offset);
						jsonField[subFieldName][str_i] = e;

						offset += sizeof(int);
						break;
					}
					case FieldRepresentationType::Color:
					{
						Color c = field->GetAtOffset<Color>(objPtr, offset);
						jsonField[subFieldName][str_i]["R"] = c.R;
						jsonField[subFieldName][str_i]["G"] = c.G;
						jsonField[subFieldName][str_i]["B"] = c.B;
						jsonField[subFieldName][str_i]["A"] = c.A;

						offset += sizeof(Color);
						break;
					}
					default:
						break;
				}
				++i;
			}

			r[strID][field->FieldName()] = jsonField;
		}
		r[strID]["Assets"] = assets;

		return r;
	}

	static IObject* DeserializeObject(const json& j, int id)
	{
		using namespace Engine3DRadSpace::Reflection;

		const auto strID = std::to_string(id);
		Reflection::UUID uuid = j[strID]["UUID"];

		AddObjectDialog::InitializeReflData();
		auto refl = AddObjectDialog::GetReflDataFromUUID(uuid);

		for (auto& asset : j[strID]["Assets"])
		{
			auto id = asset.get<std::string>();
		
			//std::string path = asset[id]["Path"].get<std::string>()
		}

		for (auto& field : *refl)
		{
			auto repr = field->Representation();
		}
	}
};