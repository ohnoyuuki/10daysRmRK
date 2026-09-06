#include "ScoreScene.h"

using namespace KamataEngine;

ScoreScene::~ScoreScene() {

	delete fade_;
	delete scoreSprite_; // 追加
	delete endbarSprite_; // 追加

}

void ScoreScene::Initialize() {
	// 3Dモデル
	//	model_ = Model::CreateFromOBJ("titleFont");

	// カメラ初期化
	camera_.Initialize();

	worldTransform_.Initialize();
	worldTransformPlayer_.Initialize();

	fade_ = new Fade();
	fade_->Initialize();

	fade_->Start(Fade::Status::FadeIn, 1.0f);

	// 画像読み込み
	scoreHandle_ = TextureManager::Load("Sprite/score.png"); // 追加
	endbarHandle_ = TextureManager::Load("Sprite/end.png"); // 追加


	// スプライトのインスタンスの生成
	scoreSprite_ = Sprite::Create(scoreHandle_, {0, 0}); // 追加
	endbarSprite_ = Sprite::Create(endbarHandle_, {400, 560}); // 追加
}

void ScoreScene::Update() {

	// スタートバーを点滅させる
	endbarTimer_ += 1.0f / 60.0f; // 追加

	// 透明度を0～1の間で変化させる
	endbarAlpha_ = (sinf(endbarTimer_ * 3.0f) + 1.0f) / 2.0f; // 追加

	endbarSprite_->SetColor({1.0f, 1.0f, 1.0f, endbarAlpha_}); // 追加

	switch (phase_) {
	case Phase::kMain:
		if (Input::GetInstance()->PushKey(DIK_SPACE)) {
			phase_ = Phase::kFadeOut;
			fade_->Start(Fade::Status::FadeOut, 1.0f);
		}
		break;
	case Phase::kFadeIn:
		fade_->Update();
		if (fade_->isFinished()) {
			phase_ = Phase::kMain;
		}
		break;
	case Phase::kFadeOut:
		fade_->Update();
		if (fade_->isFinished()) {
			finished_ = true;
		}
	}
}

void ScoreScene::Draw() {

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// スプライト描画
	Sprite::PreDraw(dxCommon->GetCommandList());

	scoreSprite_->Draw(); // 追加
	endbarSprite_->Draw(); // 追加

	// スプライト描画終了
	Sprite::PostDraw();

	Model::PreDraw(dxCommon->GetCommandList());

	Model::PostDraw();

	fade_->Draw();
}
