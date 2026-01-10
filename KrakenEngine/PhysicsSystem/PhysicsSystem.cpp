#include "PhysicsSystem.h"


void PhysicsSystem::Init(EntityContainer& container)
{
	_container = &container.GetComponents();
	b2WorldDef worldDef = b2DefaultWorldDef();
	worldDef.gravity = {0.0f, -10.0f};
	_worldId = b2CreateWorld(&worldDef);

	_container->ComponentAdded.connect(&PhysicsSystem::AddNewComponentHandle, this);
}

void PhysicsSystem::Step(EntityContainer& container)
{
	b2World_Step(_worldId, _timeStep, 4);

	for (std::pair<ComPtr<Component>, b2BodyId> pair : _componentTob2Id) {
		b2Vec2 pos = b2Body_GetPosition(pair.second);
		pair.first->GetOwner().GetTransform().Position = { pos.x, pos.y };
	}
	
}

void PhysicsSystem::SetTimeStep(float value) {
	if (value <= 0)
		throw std::invalid_argument("Time step cant be less or equal zero");

	_timeStep = value;
}

void PhysicsSystem::AddNewComponentHandle(ComPtr<Component> component)
{
	if (component.IsEqualType(typeid(PhysicalBodyData))) {
		ComPtr ptr = static_cast<ComPtr<PhysicalBodyData>>(component);

		AddPhysicalObjectForPhysicsComponent(ptr);
	}
}

void PhysicsSystem::AddPhysicalObjectForPhysicsComponent(ComPtr<PhysicalBodyData> component)
{
	b2BodyDef body = b2DefaultBodyDef();
	if (component->Type == BodyType::Static)
		body.type = b2_staticBody;
	else
		body.type = b2_dynamicBody;
	
	b2BodyId id = b2CreateBody(_worldId, &body);
	
	_componentTob2Id[component] = id;
}

void PhysicsSystem::AddCollider(ComPtr<Collider> collider)
{
	auto entity = collider->GetOwner();
	auto physicalComponent = entity.FindComponentInParent<PhysicalBodyData>();

	if (physicalComponent == nullptr)
		throw std::exception("Cant find physical component on collider's entity or in parents");
	
	b2ShapeDef def;

	if (typeid(*collider) == typeid(RectColliderData)) {
		auto polygon = _adapter.GetShapeFromRect(static_cast<ComPtr<RectColliderData>>(collider), def);

		b2CreatePolygonShape(_componentTob2Id[physicalComponent], &def, &polygon);
	}
	
}

PhysicsSystem::~PhysicsSystem()
{
	_container->ComponentAdded.disconnect(&PhysicsSystem::AddNewComponentHandle, this);
}
