#include "EntityComponentBase/Component.h"
#include "EntityComponentBase/ComponentAllocator.h"
#include "ENtityComponentBase/ComponentContainer.h"

class ComponentCreator {
public:
	ComponentCreator(ComponentContainer* container);

	template<class T, class ... Args>
	ComPtr<T> Create(Args... args);

	template<class T>
	void Delete(T* component);
private:
	ComponentContainer* _container;
};

template<class T, class ... Args>
inline ComPtr<T> ComponentCreator::Create(Args... args)
{
	ComPtr<T> component = _container->AddNewComponent<T>(args...);
	component->SetSelfPointer(component);
	
	
	return component;
}

template<class T>
inline void ComponentCreator::Delete(T* component)
{
	_container->RemoveComponent(component);
}
