#include "Serialization.hpp"

void Engine3DRadSpace::Reflection::to_json(json& j, const UUID& uuid)
{
	j = json{
		{"Data1", uuid.Data1},
		{"Data2", uuid.Data2},
		{"Data3", uuid.Data3},
		{"Data4",
			{
				"0", uuid.Data4[0],
				"1", uuid.Data4[1],
				"2", uuid.Data4[2],
				"3", uuid.Data4[3],
				"4", uuid.Data4[4],
				"5", uuid.Data4[5],
				"6", uuid.Data4[6],
				"7", uuid.Data4[7],
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
