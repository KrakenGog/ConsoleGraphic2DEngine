#include "EntityComponentBase/ComponentContainer.h"
#include "gtest/gtest.h"

class TestComponent : public Component {
	COMPONENT(10);

	TestComponent(int a, int b) {
		this->a = a;
		this->b = b;
	}

public:
	int a;
	int b;
};

TEST(componentContainer, linearIteratorTest) {
	ComponentAllocator allocator;
	ComponentContainer container(&allocator);

	container.AddNewComponent<TestComponent>(2,2);
	container.AddNewComponent<TestComponent>(1,1);
	container.AddNewComponent<TestComponent>(3,3);

	auto it = container.GetIterator<TestComponent>();

	ComPtr<TestComponent> ptr = *it;

	ASSERT_EQ(ptr->a, 2);

	++++it;
	ptr = *it;
	ASSERT_EQ(ptr->a, 3);
	++it;

	ASSERT_EQ(it.IsEnd(), true);
}