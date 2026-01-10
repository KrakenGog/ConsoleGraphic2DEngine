#include "gtest/gtest.h"
#include "EntityComponentBase/ComponentAllocator.h"


class TestComponent : public Component {
	COMPONENT(10)



public:
	int a;
	int b;
};

TEST(allocator, oneComponent) {
	ComponentAllocator* allocator = new ComponentAllocator();
	allocator->LinearAllocate<TestComponent>();
	LinearAllocatedData* data = allocator->GetAllocatedData<TestComponent>();
	
	ASSERT_EQ(data->CellCount, 10);
	ASSERT_EQ(data->CellSize, sizeof(TestComponent));
	ASSERT_EQ(data->CellStates[0], true);

	delete allocator;
}

