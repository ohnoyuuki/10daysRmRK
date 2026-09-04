#pragma once
#include <KamataEngine.h>

#include "Fade.h"
class TitleScene {
public:

	enum class Phase {
		kFadeIn,
		kMain,
		kFadeOut,
	};

	void Initialize();
	void Update();
	void Draw();
	~TitleScene();

	KamataEngine::Model* model_;

	KamataEngine::Camera camera_;

	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::WorldTransform worldTransformPlayer_;

	bool isFinished() const { return finished_; }

private:
	bool finished_ = false;

	Fade* fade_ = nullptr;

	Phase phase_ = Phase::kFadeIn;

	//追加↓
	// スプライト
	KamataEngine::Sprite* startbarSprite_ = nullptr;
	KamataEngine::Sprite* titleSprite_ = nullptr;
	//画像
	uint32_t startbarHandle_ = 0;
	uint32_t titleHandle_ = 0;

	// 点滅用
	float startbarAlpha_ = 1.0f;
	float startbarTimer_ = 0.0f;
};
