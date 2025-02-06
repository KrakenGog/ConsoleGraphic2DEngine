#include "EntityContainers/EntityContainer.h"
#include "EntityComponentBase/EntityCreator.h"
#include "EntityComponentBase/ComponentCreator.h"
#include "Transform.h"


class Scene
{
public:
	Scene();
	virtual void Update(double delta);
	EntityContainer& GetContainer() { return *_container; }
protected:
	EntityContainer* _container;
	EntityCreator* _entityCreator;
	ComponentCreator* _componentCreator;
};