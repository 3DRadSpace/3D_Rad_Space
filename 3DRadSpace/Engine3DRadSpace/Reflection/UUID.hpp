#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Reflection
{
	/// <summary>
	/// Represents a universally unique identifier, used to identify object types during serialization/deserialization and runtime.
	/// </summary>
	struct E3DRSP_REFLECTION_EXPORT UUID
	{
		unsigned long  Data1;
		unsigned short Data2;
		unsigned short Data3;
		unsigned char  Data4[8];

		/// <summary>
		/// Checks if this UUID is equal to another UUID.
		/// </summary>
		/// <param name="other">other uuid</param>
		/// <returns>True if equal.</returns>
		bool operator ==(const UUID &other) const = default;
		/// <summary>
		/// Checks if this UUID is not equal to another UUID.
		/// </summary>
		/// <param name="other">other uuid</param>
		/// <returns>True if different.</returns>
		bool operator !=(const UUID &other) const = default;
		/// <summary>
		/// Creates a new UUID, version 4 variant 10.
		/// </summary>
		/// <returns></returns>
		static UUID New();
	};
}

namespace std
{
	template<>
	struct hash<Engine3DRadSpace::Reflection::UUID>
	{
		size_t operator()(const Engine3DRadSpace::Reflection::UUID &uuid) const noexcept
		{
			size_t h = 0;
			h ^= uuid.Data1;
			h ^= uuid.Data2;
			h ^= uuid.Data3;
			for (int i = 0; i < 8; i++)
			{
				h ^= uuid.Data4[i];
			}
			return h;
		}
	};

	template<>
	struct formatter<Engine3DRadSpace::Reflection::UUID>
	{
		constexpr auto parse(std::format_parse_context& ctx) {
			return ctx.begin();
		}

		auto format(const Engine3DRadSpace::Reflection::UUID& uuid, std::format_context& ctx) const {
			return std::format_to(ctx.out(), "{{{:x}-{:x}-{:x}-{:x}{:x}-{:x}{:x}{:x}{:x}{:x}{:x}}}", 
				uuid.Data1,
				uuid.Data2,
				uuid.Data3,
				uuid.Data4[0],
				uuid.Data4[1],
				uuid.Data4[2],
				uuid.Data4[3],
				uuid.Data4[4],
				uuid.Data4[5],
				uuid.Data4[6],
				uuid.Data4[7]
			);
		}
	};
}