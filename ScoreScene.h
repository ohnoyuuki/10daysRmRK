#pragma once
#include <KamataEngine.h>

#include "Fade.h"
class ScoreScene {
public:
	enum class Phase {
		kFadeIn,
		kMain,
		kFadeOut,
	};

	void Initialize();
	void Update();
	void Draw();
	~ScoreScene();

	KamataEngine::Model* model_;

	KamataEngine::Camera camera_;

	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::WorldTransform worldTransformPlayer_;

	bool isFinished() const { return finished_; }

private:
	bool finished_ = false;

	Fade* fade_ = nullptr;

	Phase phase_ = Phase::kFadeIn;

	// 追加↓
	//  スプライト
	KamataEngine::Sprite* scoreSprite_ = nullptr;
	KamataEngine::Sprite* endbarSprite_ = nullptr;

	// 画像
	uint32_t scoreHandle_ = 0;
	uint32_t endbarHandle_ = 0;

	// 点滅用
	float endbarAlpha_ = 1.0f;
	float endbarTimer_ = 0.0f;
	
};
