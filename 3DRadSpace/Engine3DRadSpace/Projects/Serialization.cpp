#include "Serialization.hpp"
#include "../Content/AssetID.hpp"
#include "../Objects/Impl/Objects.hpp"
#include "../Objects/ObjectList.hpp"
#include "../Reflection/Event.hpp"
#include <fstream>
#include "EventInvocationRepresentation.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Internal;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Projects;
using namespace Engine3DRadSpace::Reflection;

static void deserializeObjectHierarchy(ObjectList* lst, IObject* obj, const json& j)
{
	auto numChildren = j["Children"].size();
	
	for(size_t i = 0; i < numChildren; i++)
	{
		auto child = j["Children"][i];
		obj->Children.Add(lst->operator[](child.get<int>()));
	}

	auto parent = j["Parent"].get<int>();

	if(parent != -1)
	{
		obj->SetParent(lst->operator[](parent));
	}
}

static void validateEvents(IObject* obj, ObjectList* lst)
{
	auto refl = GetReflDataFromUUID(obj->GetUUID());

	for (auto& field : *refl)
	{
		auto repr = field->Representation();

		for (auto& [reprType, sFieldName] : repr)
		{
			if (reprType == FieldRepresentationType::Event)
			{
				auto event = std::launder<Event>(reinterpret_cast<Event*>(reinterpret_cast<std::byte*>(obj) + field->FieldOffset()));

				std::vector<std::pair<EventInvocationRepresentation, IReflectedFunction*>> invocations;

				for (auto& binding : *event)
				{
					EventInvocationRepresentation invocRepr;
					invocRepr.FunctionID = binding.FunctionID;
					invocRepr.OwnerObject = binding.ObjectID;

					auto reflObj = GetReflDataFromUUID(lst->operator[](binding.ObjectID)->GetUUID());
					invocations.emplace_back(invocRepr, invocRepr.FindFunction(reflObj, binding.FunctionID));
				}

				event->Reset();

				for (auto& [invocRepr, fn] : invocations)
				{
					if (fn == nullptr) continue;
					auto objPtr = lst->operator[](invocRepr.OwnerObject);

					auto fn2 = dynamic_cast<IReflectedFunction*>(fn->Clone().release());
					event->Bind(std::move(std::unique_ptr<IReflectedFunction>(fn2)), invocRepr.OwnerObject, invocRepr.FunctionID);
					(event->end() - 1)->Object = objPtr;
				}
			}
		}
	}
}

static void serializeObjectHierarchy(std::unordered_map<IObject*, int> dictPtrID, ObjectList* lst, IObject* obj, json& j)
{
	json children = json::array();
	for(size_t i = 0; i < obj->Children.Count(); i++)
	{
		children.push_back(dictPtrID[obj->Children[i]]);
	}
	j["Children"] = children;
	j["Parent"] = obj->HasParent() ? dictPtrID[obj->GetParent()] : -1;
}

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

json Engine3DRadSpace::Projects::Serializer::SerializeObject(IObject* obj)
{
	json r;
	void* objPtr = static_cast<void*>(obj);

	r["UUID"] = obj->GetUUID();

	LoadDefaultObjects();
	auto refl = GetReflDataFromUUID(obj->GetUUID());
	if(refl == nullptr) return r;
	
	for (auto& field : *refl)
	{
		json jsonField;
		intptr_t offset = 0;
		auto repr = field->Representation();
		bool useDirectGet = (field->FieldOffset() == 0 && repr.Size() == 1);
	
		if (field->TypeSize() == 0 || repr.Size() == 0)
			continue;

		for (int i = 0; auto &[reprType, sFieldName] : repr)
		{
			if ((reprType == FieldRepresentationType::None) ||
				(reprType == FieldRepresentationType::Function))
			{
				++i;
				continue;
			}

			auto subFieldName = !sFieldName.empty() ? sFieldName : "f";

			auto str_i = std::to_string(i);
			size_t numSubFields = field->TypeSize() / field->Representation().Size();
			switch (reprType)
			{
				case FieldRepresentationType::Boolean:
				{
					if (useDirectGet)
						jsonField[subFieldName][str_i] = *static_cast<const bool*>(field->Get(objPtr));
					else
						jsonField[subFieldName][str_i] = field->GetAtOffset<bool>(objPtr, offset);
					offset += sizeof(bool);
					break;
				}
				case FieldRepresentationType::Integer:
				{
					if (useDirectGet)
					{
						switch (numSubFields)
						{
							case sizeof(int8_t): jsonField[subFieldName][str_i] = *static_cast<const int8_t*>(field->Get(objPtr)); break;
							case sizeof(int16_t): jsonField[subFieldName][str_i] = *static_cast<const int16_t*>(field->Get(objPtr)); break;
							case sizeof(int32_t): jsonField[subFieldName][str_i] = *static_cast<const int32_t*>(field->Get(objPtr)); break;
							case sizeof(int64_t): jsonField[subFieldName][str_i] = *static_cast<const int64_t*>(field->Get(objPtr)); break;
							default: throw std::logic_error("Unknown integer type!");
						}
						offset += numSubFields;
					}
					else
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
					}
					break;
				}
				case FieldRepresentationType::Unsigned:
				{
					if (useDirectGet)
					{
						switch (numSubFields)
						{
							case sizeof(uint8_t): jsonField[subFieldName][str_i] = *static_cast<const uint8_t*>(field->Get(objPtr)); break;
							case sizeof(uint16_t): jsonField[subFieldName][str_i] = *static_cast<const uint16_t*>(field->Get(objPtr)); break;
							case sizeof(uint32_t): jsonField[subFieldName][str_i] = *static_cast<const uint32_t*>(field->Get(objPtr)); break;
							case sizeof(uint64_t): jsonField[subFieldName][str_i] = *static_cast<const uint64_t*>(field->Get(objPtr)); break;
							default: throw std::logic_error("Unknown unsigned type!");
						}
						offset += numSubFields;
					}
					else
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
					}
					break;
				}
				case FieldRepresentationType::Float:
				{
					if (useDirectGet)
					{
						switch (numSubFields)
						{
							case sizeof(float): jsonField[subFieldName][str_i] = *static_cast<const float*>(field->Get(objPtr)); break;
							case sizeof(double): jsonField[subFieldName][str_i] = *static_cast<const double*>(field->Get(objPtr)); break;
							default: throw std::logic_error("Unknown floating point type!");
						}
						offset += numSubFields;
					}
					else
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
				case FieldRepresentationType::Model:
				case FieldRepresentationType::Font:
				case FieldRepresentationType::Skybox:
				case FieldRepresentationType::Sound:
				{
					unsigned texture = field->GetAtOffset<unsigned>(objPtr, offset);
					jsonField[subFieldName][str_i] = texture;

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
				case FieldRepresentationType::Event:
				{
					auto event = std::launder<Event>(reinterpret_cast<Event*>(static_cast<std::byte*>(objPtr) + field->FieldOffset() + offset));

					jsonField[subFieldName][str_i]["NumInvocations"] = event->Count();
					
					for (auto k = 0; k < event->Count(); k++)
					{
						jsonField[subFieldName][str_i]["Invocations"][std::to_string(k)]["OwnerObject"] = event->At(k).ObjectID;
						jsonField[subFieldName][str_i]["Invocations"][std::to_string(k)]["FunctionID"] = event->At(k).FunctionID;	
					}

					offset += sizeof(Event);
					break;
				}
				case FieldRepresentationType::ObjectID:
				{
					size_t id = field->GetAtOffset<size_t>(objPtr, offset);
					jsonField[subFieldName][str_i] = id;
					offset += sizeof(size_t);
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

[[nodiscard]] IObject* Engine3DRadSpace::Projects::Serializer::DeserializeObject(const json& j)
{
	Reflection::UUID uuid = j["UUID"];

	LoadDefaultObjects();
	auto refl = GetReflDataFromUUID(uuid);
	if(refl == nullptr) return nullptr;

	auto r = refl->CreateBlankObject();

	for (auto& field : *refl)
	{
		auto repr = field->Representation();

		int structSize = static_cast<int>(field->TypeSize());
		auto newStruct = std::make_unique<uint8_t[]>(structSize);
		int offset = 0;

		if (field->TypeSize() == 0 || repr.Size() == 0)
			continue;

		bool useDirectSet = (field->FieldOffset() == 0 && repr.Size() == 1);
		std::vector<Event*> placedEvents;

		for (int i = 0; auto & [reprType, sFieldName] : repr)
		{
			if(reprType == FieldRepresentationType::None) continue;
			if(reprType == FieldRepresentationType::Function) continue;

			auto subFieldName = !sFieldName.empty() ? sFieldName : "f";

			auto jsonField = j[field->FieldName()][subFieldName][std::to_string(i)];

			switch (reprType)
			{
				case FieldRepresentationType::Boolean:
				{
					bool value = jsonField.get<bool>();

					if (useDirectSet)
						field->Set(r, &value);
					else
					{
						memcpy_s(newStruct.get() + offset, sizeof(bool), &value, sizeof(bool));
						offset += sizeof(bool);
					}
					break;
				}
				case FieldRepresentationType::Integer:
				{
					if (useDirectSet)
					{
						switch (structSize / field->Representation().Size())
						{
							case sizeof(int8_t):
							{
								int8_t value = jsonField.get<int8_t>();
								field->Set(r, &value);
								break;
							}
							case sizeof(int16_t):
							{
								int16_t value = jsonField.get<int16_t>();
								field->Set(r, &value);
								break;
							}
							case sizeof(int32_t):
							{
								int32_t value = jsonField.get<int32_t>();
								field->Set(r, &value);
								break;
							}
							case sizeof(int64_t):
							{
								int64_t value = jsonField.get<int64_t>();
								field->Set(r, &value);
								break;
							}
							default:
								throw std::logic_error("Unknown signed type");
						}
					}
					else
					{
						switch (structSize / field->Representation().Size())
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
					}
					break;
				}
				case FieldRepresentationType::Unsigned:
				{
					if (useDirectSet)
					{
						switch (structSize / field->Representation().Size())
						{
							case sizeof(uint8_t):
							{
								uint8_t value = jsonField.get<uint8_t>();
								field->Set(r, &value);
								break;
							}
							case sizeof(uint16_t):
							{
								uint16_t value = jsonField.get<uint16_t>();
								field->Set(r, &value);
								break;
							}
							case sizeof(uint32_t):
							{
								uint32_t value = jsonField.get<uint32_t>();
								field->Set(r, &value);
								break;
							}
							case sizeof(uint64_t):
							{
								uint64_t value = jsonField.get<uint64_t>();
								field->Set(r, &value);
								break;
							}
							default:
								throw std::logic_error("Unknown unsigned type");
						}
					}
					else
					{
						switch (structSize / field->Representation().Size())
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
					}
					break;
				}
				case FieldRepresentationType::Float:
				{
					if (useDirectSet)
					{
						switch (structSize / field->Representation().Size())
						{
							case sizeof(float):
							{
								float value = jsonField.get<float>();
								field->Set(r, &value);
								break;
							}
							case sizeof(double):
							{
								double value = jsonField.get<double>();
								field->Set(r, &value);
								break;
							}
							default:
								throw std::logic_error("Unknown floating point type");
						}
					}
					else
					{
						switch (structSize / field->Representation().Size())
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
								memcpy_s(newStruct.get() + offset, sizeof(double), &value, sizeof(double));
								offset += sizeof(double);
								break;
							}
							default:
								throw std::logic_error("Unknown floating point type");
						}
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
				case FieldRepresentationType::Font:
				case FieldRepresentationType::Skybox:
				case FieldRepresentationType::Sound:
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
					float r = jsonField["R"].get<float>();
					float g = jsonField["G"].get<float>();
					float b = jsonField["B"].get<float>();
					float a = jsonField["A"].get<float>();

					Color color(r, g, b, a);

					memcpy_s(newStruct.get() + offset, sizeof(Color), &color, sizeof(Color));
					offset += sizeof(Color);
					break;
				}
				case FieldRepresentationType::Event:
				{
					auto numInvocations = jsonField["NumInvocations"].get<size_t>();

					Event event;

					for (auto i = 0; i < numInvocations; i++)
					{
						auto invocation = jsonField["Invocations"][std::to_string(i)];

						EventInvocationRepresentation repr;

						repr.OwnerObject = invocation["OwnerObject"].get<size_t>();
						repr.FunctionID = invocation["FunctionID"].get<size_t>();
								
						//TODO: Support arguments.

						event.BindIncomplete(
							repr.OwnerObject,
							repr.FunctionID
						);
					}

					placedEvents.push_back(new (newStruct.get() + offset) Event(std::move(event)));
					offset += sizeof(Event);
					break;
				}
				case FieldRepresentationType::ObjectID:
				{
					size_t value = jsonField.get<size_t>();
					memcpy_s(newStruct.get() + offset, sizeof(size_t), &value, sizeof(size_t));
					offset += sizeof(size_t);
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
		if (!useDirectSet)
			field->Set(r, newStruct.get());

		for (Event* e : placedEvents)
			e->~Event();
	}

	return static_cast<IObject*>(r);
}

bool Engine3DRadSpace::Projects::Serializer::LoadProject(ObjectList* lst, ContentManager *content, const std::filesystem::path& projectPath)
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
		lst->Add(obj);
	}

	for (size_t i = 0; i < numObjects; ++i)
	{
		auto obj = lst->operator[](i);
		deserializeObjectHierarchy(lst, obj, j["objects"][std::to_string(i)]);
		validateEvents(obj, lst);
	}

	return true;
}

[[nodiscard]] IObject* Engine3DRadSpace::Projects::Serializer::LoadObjectFromProject(const std::filesystem::path &path ,unsigned id)
{
	std::ifstream file(path);

	if (file.bad() || file.bad()) return nullptr;

	json j;
	file >> j;

	return DeserializeObject(j["objects"][std::to_string(id)]);
}

bool Engine3DRadSpace::Projects::Serializer::SaveProject(ObjectList* lst, ContentManager* content,const std::filesystem::path& projectPath)
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

	std::unordered_map<IObject*, int> dictPtrID;
	for (size_t i = 0; i < lst->Count(); i++)
	{
		dictPtrID[(*lst)[i]] = static_cast<int>(i);
	}

	for (size_t i = 0; i < lst->Count(); i++)
	{
		auto obj = SerializeObject((*lst)[i]);
		serializeObjectHierarchy(dictPtrID, lst, (*lst)[i], obj);

		j["objects"][std::to_string(i)] = obj;
	}

	file << std::setw(4) << j;
	return true;
}