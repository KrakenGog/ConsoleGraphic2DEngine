#include "Scene/Scene.h"
#include "Components/SpriteRenderData.h"
#include "SpriteSystem/SpriteLoader.h"
#include <random>
#include "Input/Input.h"
#include "Components/UnitMover.h"
#include "Components/PlayerContoroller.h"
#include "Camera.h"

class MainScene : public Scene
{
public:
	MainScene() : Scene() {
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 6);

		SpriteLoader spriteLoader;
		Entity* player = _entityCreator->Create()->AddComponents(
			_componentCreator->Create<SpriteRenderData>(SpriteRenderData(spriteLoader.Load("D:\\Projects\\KrakenEngine\\KrakenEngine\\Resources\\Models\\Player.txt"), 1)),
			_componentCreator->Create<UnitMover>()->Init(1),
			_componentCreator->Create<PlayerContoroller>()
		);


		_entityCreator->Create()->AddComponents(
			_componentCreator->Create<SpriteRenderData>(SpriteRenderData(spriteLoader.Load("D:\\Projects\\KrakenEngine\\KrakenEngine\\Resources\\Models\\Test.txt"), 1))
		)->GetTransform().Position = Vector2(1,1);


		
		Entity* camera = _entityCreator->Create()->AddComponents(
			_componentCreator->Create<Camera>()->Init()->SetSize(Vector2(128,100))
		);
	

	}

	void Update(double delta) override;
};