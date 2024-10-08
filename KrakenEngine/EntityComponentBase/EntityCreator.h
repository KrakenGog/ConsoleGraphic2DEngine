#include "Entity.h"
#include "EntityContainers/EntityContainer.h"


class ComponentCreator;

class EntityCreator {
public:
	EntityCreator(EntityContainer* container, ComponentCreator* creator);

	Entity* Create();
	void Delete(Entity* entity);
private:
	EntityContainer* _container;
	ComponentCreator* _creator;
};