#pragma once
#include "Globals.hpp"
#include "IObject.hpp"
#include "Vector4.hpp"
#include "Vector2.hpp"

#define __BEGIN_REFLECTOBJECT(ObjName) \
Engine3DRadSpace::Reflection::Reflect<ObjName> ObjName##ReflInst = \
{ \

#define __REFLECTFIELD(ObjName,FType,FName,FInternalName,FDefaultValue) []() -> Engine3DRadSpace::Reflection::ReflectedFieldBase* \
{ \
	ObjName *o = static_cast<ObjName*>( ::operator new(sizeof(ObjName))); \
	Engine3DRadSpace::Reflection::ReflectedField<ObjName,FType> *field = new Engine3DRadSpace::Reflection::ReflectedField<ObjName,FType>( FName ,FDefaultValue); \
	field->MemIndex = (char*)&o->FInternalName - (char*)o; \
	::operator delete(o); \
	return field; \
} \

#define __END_REFLECTOBJECT(ObjName) \
}; \
Engine3DRadSpace::Reflection::Reflect<ObjName> DLLEXPORT &ObjName##GetRefl() \
{ \
	return ObjName##ReflInst; \
} \

namespace Engine3DRadSpace
{
	namespace Reflection
	{
		template<typename T>
		concept SupportedEditorVariables =
			std::is_same<T,bool>::value ||
			std::is_arithmetic<T>::value || //integers
			std::is_floating_point<T>::value || //real numbers
			std::is_same<T, Vector2>::value || //2d vectors
			std::is_same<T, Vector3>::value || //3d vectors
			std::is_same<T, Vector4>::value || //4d vectors
			std::is_same<T, Quaternion>::value || //quaternions
			std::is_same<T, ColorShader>::value || //Normalized RGBA colors
			std::is_same<T, std::string>::value || std::is_same<T, std::wstring>::value; //strings

		template<typename Object>
		concept IObjectDerived = std::is_base_of<IObject, Object>::value;

		class ReflectedFieldBase
		{
		public:
			virtual const std::type_info& GetFieldType() const = 0;
			virtual const void* GetDefaultValue() const = 0;
			virtual const char* const GetVisibleName() const = 0;
			virtual std::ptrdiff_t GetFieldPtr() const = 0;

			template<class F,IObjectDerived obj>
			F* TryGetF(obj* o) const
			{
				if(typeid(F) == GetFieldType())
					return (F*)((char*)o + GetFieldPtr());
				else return nullptr;
			}

			template<class F,IObjectDerived obj>
			bool TrySetF(obj* o, F v) const
			{
				if(typeid(F) == GetFieldType())
				{
					*((F*)((char*)o + GetFieldPtr())) = v;
					return true;
				}
				return false;
			}

			virtual DLLEXPORT ~ReflectedFieldBase();
		};

		template<IObjectDerived obj, SupportedEditorVariables T>
		class ReflectedField : public ReflectedFieldBase
		{
			const std::type_info& FieldType;
			const T DefaultValue;
			const char* const VisibleName;
		public:
			std::ptrdiff_t MemIndex; 

			ReflectedField(const char* name, T&& _val) : FieldType(typeid(T)), DefaultValue(_val), VisibleName(name),MemIndex(0) {};

			const std::type_info& GetFieldType() const override
			{
				return this->FieldType;
			}

			const void* GetDefaultValue() const override
			{
				return &DefaultValue;
			}

			const char* const GetVisibleName() const
			{
				return this->VisibleName;
			}
			std::ptrdiff_t GetFieldPtr() const
			{
				return this->MemIndex;
			}
		};

		template<IObjectDerived obj>
		class Reflect
		{
			const size_t _numFields;
			std::vector<ReflectedFieldBase*> _fields;
		public:
			Reflect(const std::initializer_list<std::function<ReflectedFieldBase*()>> fields) :
				_numFields(fields.size()),
				_fields(fields.size()),
				Name(typeid(obj).name())
			{
				for(size_t i = 0; i < this->_numFields; i++)
				{
					_fields[i] = (*(fields.begin() + i))();
				}
			};
			Reflect(Reflect&& r) = delete;
			const char* const Name;

			const size_t Size()
			{
				return this->_numFields;
			}
			const ReflectedFieldBase* operator[](size_t index)
			{
				return this->_fields[index];
			}
		};
	}
}