#include "TitleScene.h"

using namespace KamataEngine;

TitleScene::~TitleScene() {

	delete fade_;
	delete startbarSprite_; // 追加
	delete titleSprite_;    // 追加
 }

void TitleScene::Initialize() {
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
	startbarHandle_ = TextureManager::Load("Sprite/start.png");//追加
	titleHandle_ = TextureManager::Load("Sprite/title.png"); // 追加

	//スプライトのインスタンスの生成
	startbarSprite_ = Sprite::Create(startbarHandle_, {400, 560});//追加
	titleSprite_ = Sprite::Create(titleHandle_, {0,0});//追加

}

void TitleScene::Update() {

	// スタートバーを点滅させる
	startbarTimer_ += 1.0f / 60.0f; // 追加

	// 透明度を0～1の間で変化させる
	startbarAlpha_ = (sinf(startbarTimer_ * 3.0f) + 1.0f) / 2.0f;//追加

	startbarSprite_->SetColor({1.0f, 1.0f, 1.0f, startbarAlpha_}); //追加


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

void TitleScene::Draw() {

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	//スプライト描画
	Sprite::PreDraw(dxCommon->GetCommandList());

	titleSprite_->Draw(); // 追加
	startbarSprite_->Draw(); // 追加
	

	// スプライト描画終了
	Sprite::PostDraw();

	Model::PreDraw(dxCommon->GetCommandList());

Model::PostDraw();

fade_->Draw();
}
