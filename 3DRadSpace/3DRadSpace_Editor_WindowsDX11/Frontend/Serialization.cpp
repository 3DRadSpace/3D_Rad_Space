#include "Serialization.hpp"
#include <Engine3DRadSpace/Content/AssetID.hpp>
#include <fstream>
#include <ranges>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Math;

void Engine3DRadSpace::Reflection::to_json(json& j, const UUID& uuid)
{
	j = json{
		{"Data1", uuid.Data1},
		{"Data2", uuid.Data2},
		{"Data3", uuid.Data3},
		{"Data4",
			{
				{"0", uuid.Data4[0]},
				{"1", uuid.Data4[1]},
				{"2", uuid.Data4[2]},
				{"3", uuid.Data4[3]},
				{"4", uuid.Data4[4]},
				{"5", uuid.Data4[5]},
				{"6", uuid.Data4[6]},
				{"7", uuid.Data4[7]},
			}
		}
	};
}

void Engine3DRadSpace::Reflection::from_json(const json& j, UUID& uuid)
{
	uuid.Data1 = j["Data1"].get<unsigned long>();
	uuid.Data2 = j["Data2"].get<unsigned short>();
	uuid.Data3 = j["Data3"].get<unsigned short>();

	uuid.Data4[0] = j["Data4"]["0"].get<unsigned char>();
	uuid.Data4[1] = j["Data4"]["1"].get<unsigned char>();
	uuid.Data4[2] = j["Data4"]["2"].get<unsigned char>();
	uuid.Data4[3] = j["Data4"]["3"].get<unsigned char>();
	uuid.Data4[4] = j["Data4"]["4"].get<unsigned char>();
	uuid.Data4[5] = j["Data4"]["5"].get<unsigned char>();
	uuid.Data4[6] = j["Data4"]["6"].get<unsigned char>();
	uuid.Data4[7] = j["Data4"]["7"].get<unsigned char>();
}

json Serializer::SerializeObject(IObject* obj)
{
	json r;
	void* objPtr = static_cast<void*>(obj);

	using namespace Engine3DRadSpace::Reflection;
	using namespace Engine3DRadSpace::Content;

	r["UUID"] = obj->GetUUID();

	AddObjectDialog::InitializeReflData();
	auto refl = AddObjectDialog::GetReflDataFromUUID(obj->GetUUID());
	for (auto& field : *refl)
	{
		json jsonField;
		intptr_t offset = 0;
		auto repr = field->Representation();
		for (int i = 0; auto &[reprType, sFieldName] : repr)
		{
			std::string subFieldName = !sFieldName.empty() ? sFieldName : "f";

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
					unsigned texture = field->GetAtOffset<unsigned>(objPtr, offset);
					jsonField[subFieldName][str_i] = texture;

					offset += sizeof(unsigned);
					break;
				}
				case FieldRepresentationType::Model:
				{
					unsigned model = field->GetAtOffset<unsigned>(objPtr, offset);
					jsonField[subFieldName][str_i] = model;

					offset += sizeof(unsigned);
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

		r[field->FieldName()] = jsonField;
	}

	return r;
}

[[nodiscard]] IObject* Serializer::DeserializeObject(const json& j)
{
	using namespace Engine3DRadSpace::Reflection;

	Reflection::UUID uuid = j["UUID"];

	AddObjectDialog::InitializeReflData();
	auto refl = AddObjectDialog::GetReflDataFromUUID(uuid);

	auto r = refl->CreateBlankObject();

	for (auto& field : *refl)
	{
		auto repr = field->Representation();

		int structSize = static_cast<int>(field->TypeSize());
		auto newStruct = std::make_unique<uint8_t[]>(structSize);
		int offset = 0;

		for (int i = 0; auto & [reprType, sFieldName] : repr)
		{
			std::string subFieldName = !sFieldName.empty() ? sFieldName : "f";

			auto& jsonField = j[field->FieldName()][subFieldName][std::to_string(i)];

			switch (reprType)
			{
				case FieldRepresentationType::Boolean:
				{
					bool value = jsonField.get<bool>();

					memcpy_s(newStruct.get() + offset, sizeof(bool), &value, sizeof(bool));
					offset += sizeof(bool);
					break;
				}
				case FieldRepresentationType::Integer:
				{
					switch (structSize / field->Representation().size())
					{
						case sizeof(int8_t) :
						{
							int8_t value = jsonField.get<uint8_t>();

							memcpy_s(newStruct.get() + offset, sizeof(int8_t), &value, sizeof(int8_t));
							offset += sizeof(int8_t);
							break;
						}
						case sizeof(int16_t) :
						{
							int16_t value = jsonField.get<uint16_t>();

							memcpy_s(newStruct.get() + offset, sizeof(int16_t), &value, sizeof(int16_t));
							offset += sizeof(int16_t);
							break;
						}
						case sizeof(int32_t) :
						{
							int32_t value = jsonField.get<uint32_t>();

							memcpy_s(newStruct.get() + offset, sizeof(int32_t), &value, sizeof(int32_t));
							offset += sizeof(int32_t);
							break;
						}
						case sizeof(int64_t) :
						{
							int64_t value = jsonField.get<uint64_t>();

							memcpy_s(newStruct.get() + offset, sizeof(int64_t), &value, sizeof(int64_t));
							offset += sizeof(int64_t);
							break;
						}
						default:
							throw std::logic_error("Unknown signed type");
					}
					break;
				}
				case FieldRepresentationType::Unsigned:
				{
					switch (structSize / field->Representation().size())
					{
						case sizeof(uint8_t) :
						{
							uint8_t value = jsonField.get<uint8_t>();
							memcpy_s(newStruct.get() + offset, sizeof(uint8_t), &value, sizeof(uint8_t));
							offset += sizeof(uint8_t);
							break;
						}
						case sizeof(uint16_t) :
						{
							uint16_t value = jsonField.get<uint16_t>();
							memcpy_s(newStruct.get() + offset, sizeof(uint16_t), &value, sizeof(uint16_t));
							offset += sizeof(uint16_t);
							break;
						}
						case sizeof(uint32_t) :
						{
							uint32_t value = jsonField.get<uint32_t>();
							memcpy_s(newStruct.get() + offset, sizeof(uint32_t), &value, sizeof(uint32_t));
							offset += sizeof(uint32_t);
							break;
						}
						case sizeof(uint64_t) :
						{
							uint64_t value = jsonField.get<uint64_t>();
							memcpy_s(newStruct.get() + offset, sizeof(uint64_t), &value, sizeof(uint64_t));
							offset += sizeof(uint64_t);
							break;
						}
						default:
							throw std::logic_error("Unknown unsigned type");
					}
					break;
				}
				case FieldRepresentationType::Float:
				{
					switch (structSize / field->Representation().size())
					{
						case sizeof(float) :
						{
							float value = jsonField.get<float>();
							memcpy_s(newStruct.get() + offset, sizeof(float), &value, sizeof(float));
							offset += sizeof(float);
							break;
						}
						case sizeof(double) :
						{
							double value = jsonField.get<double>();
							memcpy_s(newStruct.get() + offset, sizeof(float), &value, sizeof(double));
							offset += sizeof(double);
							break;
						}
						default:
							throw std::logic_error("Unknown floating point type");
					}
					break;
				}
				case FieldRepresentationType::Quaternion:
				{
					float x = jsonField["X"].get<float>();
					float y = jsonField["Y"].get<float>();;
					float z = jsonField["Z"].get<float>();;
					float w = jsonField["W"].get<float>();;

					Quaternion q(x, y, z, w);

					memcpy_s(newStruct.get() + offset, sizeof(Math::Quaternion), &q, sizeof(Math::Quaternion));
					offset += sizeof(Math::Quaternion);
					break;
				}
				case FieldRepresentationType::String:
				{
					std::string string = jsonField.get<std::string>();

					std::string* dest = reinterpret_cast<std::string*>(newStruct.get() + offset);

					new (dest) std::string(string);
					offset += sizeof(std::string);

					break;
				}
				case FieldRepresentationType::Image:
				case FieldRepresentationType::Model:
				{
					unsigned value = jsonField.get<unsigned>();

					memcpy_s(newStruct.get() + offset, sizeof(unsigned), &value, sizeof(unsigned));
					offset += sizeof(unsigned);
					break;
				}
				case FieldRepresentationType::Key:
				{
					Input::Key k = static_cast<Input::Key>(jsonField.get<uint8_t>());

					memcpy_s(newStruct.get() + offset, sizeof(Input::Key), &k, sizeof(Input::Key));
					offset += sizeof(Input::Key);
					break;
				}
				case FieldRepresentationType::Enum:
				{
					break;
				}
				case FieldRepresentationType::Color:
				{
					uint8_t r = jsonField["R"].get<uint8_t>();
					uint8_t g = jsonField["G"].get<uint8_t>();
					uint8_t b = jsonField["B"].get<uint8_t>();
					uint8_t a = jsonField["A"].get<uint8_t>();

					Color color(r, g, b, a);

					memcpy_s(newStruct.get() + offset, sizeof(Color), &color, sizeof(Color));
					offset += sizeof(Color);
					break;
				}
				case FieldRepresentationType::Custom:
				{
					break;
				}
				default:
					break;
			}
			i++;
		}
		field->Set(r, newStruct.get());
	}

	return r;
}

bool Serializer::LoadProject(ObjectList* lst, ContentManager *content, const std::filesystem::path& projectPath, Internal::InitializationFlag f )
{
	std::ifstream file(projectPath);

	if (file.bad() || file.bad()) return false;

	json j;
	file >> j;

	size_t numObjects = j["numObjects"].get<size_t>();
	size_t numAssets = j["numAssets"].get<size_t>();

	for (size_t i = 1; i < numAssets; ++i)
	{
		auto& jAsset = j["assets"][std::to_string(i)];

		auto type = jAsset["type"].get<Reflection::UUID>();
		auto path = jAsset["path"].get<std::string>();

		content->Load(type, path, nullptr);
	}

	for (size_t i = 0; i < numObjects; ++i)
	{
		auto obj = DeserializeObject(j["objects"][std::to_string(i)]);
		lst->Add(obj, f);

		obj->EditorInitialize();
		obj->EditorLoad(content);
	}

	return true;
}

bool Serializer::SaveProject(ObjectList* lst, ContentManager* content,const std::filesystem::path& projectPath)
{
	std::ofstream file(projectPath);

	if (file.bad() || file.fail()) return false;

	json j;
	j["numObjects"] = lst->Count();
	j["numAssets"] = content->Count();

	for (auto& asset : *content)
	{
		auto id = std::to_string(asset.ID);

		auto& json_asset = j["assets"][id];
		json_asset["type"] = asset.Entry->GetUUID();
		json_asset["path"] = asset.Path;
		json_asset["name"] = asset.Name;
	}

	for (size_t i = 0; i < lst->Count(); i++)
	{
		auto obj = SerializeObject((*lst)[i]);
		j["objects"][std::to_string(i)] = obj;
	}

	file << std::setw(4) << j;
	return true;
} 

