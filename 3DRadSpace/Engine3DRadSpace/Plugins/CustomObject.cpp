#include "CustomObject.hpp"
#include "../Logging/Logging.hpp"
#include "../Native/LibraryLoader.hpp"
#include "../Reflection/ReflectedObject.hpp"
#include "../Objects/Impl/Objects.hpp"

using namespace Engine3DRadSpace::Plugins;

size_t Engine3DRadSpace::Plugins::LoadCustomObjectsFromLibHandle(void* libraryHandle)
{
	LoadCustomObjects loadCustomObjects = Native::GetFunctionFromLibrary<LoadCustomObjects>(libraryHandle, "LoadCustomObjects");
	if(loadCustomObjects)
	{
		auto rawObjects = loadCustomObjects();

		std::vector<Reflection::ReflectedObject*> objects(rawObjects.Size);
		for (auto i = 0u; i < rawObjects.Size; i++)
		{
			objects[i] = static_cast<Reflection::ReflectedObject*>(rawObjects.Ptr) + i;
		}

		for(auto& object : objects)
		{
			bool ok = true;

			auto &allObjects = Internal::GetInternalObjectsList();

			//avoid repeating UUIDs. O(n^2) but hopefully the number of custom objects is small.
			for(auto& internalObject : allObjects)
			{
				//if UUIDs are in conflicting throw an exception. We can't guarantee serialization when saving or loading... Skip this object...
				if(internalObject->ObjectUUID == object->ObjectUUID)
				{					
					Logging::PrintWarning(std::format("Conflicting UUIDs for {} and {}. ", object->Name, internalObject->Name));
					ok = false;
					break;
				}
			}

			if(!ok) continue;

			allObjects.push_back(object);
			Logging::PrintMessage(Logging::Message(1000, "Loaded custom object " + object->Name, nullptr));
		}
		return rawObjects.Size;
	}
	return 0;
}