#pragma once
#include <Engine3DRadSpace/Reflection/Reflection.hpp>
#include <nlohmann/json.hpp>

#include <Engine3DRadSpace/Objects/Camera.hpp>

using json = nlohmann::json;

namespace Engine3DRadSpace::Reflection
{
	void to_json(json& j, const UUID& uuid);
	void from_json(const json& j, UUID& uuid);
}

using namespace Engine3DRadSpace::Math;

/*
class Serializator
{
public:
	template<Engine3DRadSpace::Reflection::ReflectableObject O>
	static json SerializeObject(int id, O* obj)
	{
		json r;
		
		using namespace Engine3DRadSpace::Reflection;

		const std::string strID = std::to_string(id);
		r[strID]["UUID"] = obj->GetUUID();
		
		auto refl = ReflectedObject::AllObjectTypes[typeid(O)];
		for (auto& field : *refl)
		{
			json jsonField;
			auto repr = field->Representation();
			for (int i = 0; auto& [reprType, subFieldName] : repr)
			{
				size_t numSubFields = field->TypeSize() / field->Representation().size();
				switch (reprType)
				{
					case FieldRepresentationType::Boolean:
					{
						jsonField[subFieldName] = IReflectedField::GetSubfield<bool>(field, obj, i);
						break;
					}
					case FieldRepresentationType::Integer:
					{
						switch (numSubFields)
						{
							case sizeof(int8_t) :
							{
								jsonField[subFieldName] = IReflectedField::GetSubfield<int8_t>(field, obj, i);
								break;
							}
							case sizeof(int16_t) :
							{
								jsonField[subFieldName] = IReflectedField::GetSubfield<int16_t>(field, obj, i);
								break;
							}
							case sizeof(int32_t) :
							{
								jsonField[subFieldName] = IReflectedField::GetSubfield<int32_t>(field, obj, i);
								break;
							}
							case sizeof(int64_t) :
							{
								jsonField[subFieldName] = IReflectedField::GetSubfield<int64_t>(field, obj, i);
								break;
							}
							default:
								throw std::logic_error("Unknown integer type!");
						}
					}
					case FieldRepresentationType::Unsigned:
					{
						switch (numSubFields)
						{
							case sizeof(uint8_t) :
							{
								jsonField[subFieldName] = IReflectedField::GetSubfield<uint8_t>(field, obj, i);
								break;
							}
							case sizeof(uint16_t) :
							{
								jsonField[subFieldName] = IReflectedField::GetSubfield<uint16_t>(field, obj, i);
								break;
							}
							case sizeof(uint32_t) :
							{
								jsonField[subFieldName] = IReflectedField::GetSubfield<uint32_t>(field, obj, i);
								break;
							}
							case sizeof(uint64_t) :
							{
								jsonField[subFieldName] = IReflectedField::GetSubfield<uint64_t>(field, obj, i);
								break;
							}
							default:
								throw std::logic_error("Unknown integer type!");
						}
					}
					case FieldRepresentationType::Float:
					{
						switch (numSubFields)
						{
							case sizeof(float) :
							{
								jsonField[subFieldName] = IReflectedField::GetSubfield<float>(field, obj, i);
								break;
							}
							case sizeof(double) :
							{
								jsonField[subFieldName] = IReflectedField::GetSubfield<float>(field, obj, i);
								break;
							}
							default:
								throw std::logic_error("Unknown floating point type!");
						}
					}
					case FieldRepresentationType::Quaternion:
					{
						Quaternion q = IReflectedField::GetSubfield<Quaternion>(field, obj, i);
						jsonField[subFieldName]["X"] = q.X;
						jsonField[subFieldName]["Y"] = q.Y;
						jsonField[subFieldName]["Z"] = q.Z;
						jsonField[subFieldName]["W"] = q.W;
						break;
					}
					default:
						break;
				}
				++i;
			}
		}
	}
};*/