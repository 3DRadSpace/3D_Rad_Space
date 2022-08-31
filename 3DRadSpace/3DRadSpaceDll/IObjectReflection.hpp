#pragma once
#include "Globals.hpp"
#include "IObject.hpp"
#include "Vector4.hpp"
#include "Vector2.hpp"


#define __BEGIN_REFLECTOBJECT(ObjName) \
Engine3DRadSpace::Reflection::Reflect ObjName##ReflInst = \
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
Engine3DRadSpace::Reflection::Reflect DLLEXPORT &ObjName##GetRefl() \
{ \
	return ObjName##ReflInst; \
} \

#define __REFLECTOBJECT_FORWARDDECL(ObjName) Engine3DRadSpace::Reflection::Reflect DLLEXPORT &ObjName##GetRefl();

//The things here are used in the Editor's internals for interactive controls - there are not meant for end users!

namespace Engine3DRadSpace
{
	namespace Reflection
	{
		template<typename T>
		concept SupportedEditorVariable =
			std::is_arithmetic<T>::value || //integers
			std::is_same<T, Vector2>::value || //2d vectors
			std::is_same<T, Vector3>::value || //3d vectors
			std::is_same<T, Vector4>::value || //4d vectors
			std::is_same<T, Quaternion>::value || //quaternions
			std::is_same<T, ColorShader>::value || //Normalized RGBA colors
			std::is_same<T, std::string>::value; //strings

		template<typename Object>
		concept IObjectDerived = std::is_base_of<IObject, Object>::value;

		class DLLEXPORT ReflectedFieldBase
		{
		public:
			virtual const std::type_info& GetFieldType() const = 0;
			virtual const void* GetDefaultValue() const = 0;
			virtual const char* const GetVisibleName() const = 0;
			virtual std::ptrdiff_t GetFieldPtr() const = 0;
			virtual const size_t GetFieldSize() const = 0;

			template<class F,IObjectDerived obj>
			F* TryGetF(obj* o) const
			{
				return typeid(F) == GetFieldType() ? (F*)((char*)o + GetFieldPtr()) : nullptr;
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

			template<IObjectDerived obj>
			bool TrySetF(obj* o, const std::type_info& t, void* v, size_t s) const
			{
				if(t == GetFieldType())
				{
					*((char*)o + GetFieldPtr()) = v;
					return true;
				}
				return false;
			}
			
			void ForceSetF(char* o, void* v, size_t size) const
			{
				memcpy_s(o + GetFieldPtr(), size, v, size);
			}

			void ForceGetF(char* o, void* v, size_t size) const
			{
				memcpy_s(v, size, o + GetFieldPtr(), size);
			}

			void ForceSetF(char* o, void* v) const
			{
				memcpy_s(o + GetFieldPtr(), GetFieldSize(), v, GetFieldSize());
			}

			void ForceGetF(char* o, void* v) const
			{
				memcpy_s(v, GetFieldSize(), o + GetFieldPtr(),GetFieldSize());
			}
			virtual ~ReflectedFieldBase();
		};

		template<IObjectDerived obj, SupportedEditorVariable T>
		class ReflectedField : public ReflectedFieldBase
		{
			const std::type_info& FieldType;
			const T DefaultValue;
			const char* const VisibleName;
			const size_t _size;
		public:
			std::ptrdiff_t MemIndex; 

			ReflectedField(const char* name, T&& _val) : 
				FieldType(typeid(T)),
				DefaultValue(_val), 
				VisibleName(name),
				MemIndex(0),
				_size(sizeof(T)) 
			{
			};

			const std::type_info& GetFieldType() const override
			{
				return this->FieldType;
			}

			const void* GetDefaultValue() const override
			{
				return &DefaultValue;
			}

			const char* const GetVisibleName() const override
			{
				return this->VisibleName;
			}
			std::ptrdiff_t GetFieldPtr() const override
			{
				return this->MemIndex;
			}
			const size_t GetFieldSize() const override
			{
				return this->_size;
			}
		};

	#pragma warning(push)
	#pragma warning(disable : 4251)
		class DLLEXPORT Reflect
		{
			const size_t _numFields;
			std::vector<ReflectedFieldBase*> _fields;
		public:
			Reflect(const std::initializer_list<std::function<ReflectedFieldBase* ()>> fields);
			Reflect(Reflect&& r) = delete;

			inline static std::unordered_map<std::type_index, int> TypeDict =
			{
				//bool
				{typeid(bool),1},
				//signed and unsigned integers
				{typeid(uint8_t),2},
				{typeid(uint16_t),2},
				{typeid(uint32_t),2},
				{typeid(uint64_t),2},

				{typeid(int8_t),3},
				{typeid(int16_t),3},
				{typeid(int32_t),3},
				{typeid(int64_t),3},
				//floats
				{typeid(float),3},
				{typeid(double),3},
				{typeid(long double),3},

				{typeid(Vector2),4},
				{typeid(Vector3),5},
				{typeid(Vector4),6},

				{typeid(Quaternion),7},
				{typeid(ColorShader),8},
				{typeid(std::string),9}
			};

			inline static std::unordered_map<std::type_index, int> FullTypeDict =
			{
				//bool
				{typeid(bool),1},
				//signed and unsigned integers
				{typeid(uint8_t),2},
				{typeid(uint16_t),3},
				{typeid(uint32_t),4},
				{typeid(uint64_t),5},

				{typeid(int8_t),6},
				{typeid(int16_t),7},
				{typeid(int32_t),8},
				{typeid(int64_t),9},
				//floats
				{typeid(float),10},
				{typeid(double),11},
				{typeid(long double),12},

				{typeid(Vector2),13},
				{typeid(Vector3),14},
				{typeid(Vector4),15},

				{typeid(Quaternion),16},
				{typeid(ColorShader),17},
				{typeid(std::string),18}
			};


			const size_t Size() const;
			const ReflectedFieldBase* operator[](size_t index) const;
		};
	}
#pragma warning(pop)
}