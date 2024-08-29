#include "EntityComponentBase/Component.h"
#include "EntityComponentBase/ComponentAllocator.h"
#include "ENtityComponentBase/ComponentContainer.h"

class ComponentCreator {
public:
	ComponentCreator(ComponentContainer* container);

	template<class T>
	ComPtr<T> Create();

	template<class T>
	void Delete(T* component);
private:
	ComponentContainer* _container;
};

template<class T>
inline ComPtr<T> ComponentCreator::Create()
{
	ComPtr<T> component = _container->AddNewComponent<T>();

	return component;
}

template<class T>
inline void ComponentCreator::Delete(T* component)
{
	_container->RemoveComponent(component);
}
