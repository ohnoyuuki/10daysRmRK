#include "GameScene.h"
#include "KamataEngine.h"
#include "ScoreScene.h"
#include "TitleScene.h"
#include <Windows.h>

enum class Scene {

	kUnknow = 0,

	kTitle,
	kGame,
	kClear,
	kScore,
};

Scene scene = Scene::kUnknow;

using namespace KamataEngine;

void ChangeScene();

void UpdateScene();

void DrawScene();

GameScene* gameScene = nullptr;

TitleScene* titleScene = nullptr;

ScoreScene* scoreScene = nullptr;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// エンジンの初期化
	KamataEngine::Initialize(L"3064_ルームリンカー");

	// DirectXCommon*インスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	scene = Scene::kTitle;

	// タイトルシーン生成
	titleScene = new TitleScene;
	titleScene->Initialize();

	// メインループ
	while (true) {

		// エンジンの更新
		if (KamataEngine::Update()) {
			break;
		}

		// シーン切り替え
		ChangeScene();

		// 更新
		UpdateScene();

		// 描画開始
		dxCommon->PreDraw();

		// 描画
		DrawScene();

		// 描画終了
		dxCommon->PostDraw();
	}

	// シーンの解放
	delete gameScene;
	gameScene = nullptr;

	delete titleScene;
	titleScene = nullptr;

	delete scoreScene;
	scoreScene = nullptr;

	// エンジンの終了処理
	KamataEngine::Finalize();

	return 0;
}

void ChangeScene() {

	switch (scene) {

	// =========================
	// タイトル
	// =========================
	case Scene::kTitle:

		if (titleScene && titleScene->isFinished()) {

			scene = Scene::kGame;

			// タイトルシーン解放
			delete titleScene;
			titleScene = nullptr;

			// ゲームシーン生成
			gameScene = new GameScene;
			gameScene->Initialize();
		}

		break;

	// =========================
	// ゲーム
	// =========================
	case Scene::kGame:

		if (gameScene && gameScene->isFinished()) {

			scene = Scene::kScore;

			// ゲームシーン解放
			delete gameScene;
			gameScene = nullptr;

			// スコアシーン生成
			scoreScene = new ScoreScene;
			scoreScene->Initialize();
		}

		break;

	// =========================
	// スコア
	// =========================
	case Scene::kScore:

		if (scoreScene && scoreScene->isFinished()) {

			scene = Scene::kTitle;

			// スコアシーン解放
			delete scoreScene;
			scoreScene = nullptr;

			// タイトルシーン生成
			titleScene = new TitleScene;
			titleScene->Initialize();
		}

		break;
	}
}

void UpdateScene() {

	switch (scene) {

	case Scene::kTitle:

		if (titleScene) {
			titleScene->Update();
		}

		break;

	case Scene::kGame:

		if (gameScene) {
			gameScene->Update();
		}

		break;

	case Scene::kScore:

		if (scoreScene) {
			scoreScene->Update();
		}

		break;
	}
}

void DrawScene() {

	switch (scene) {

	case Scene::kTitle:

		if (titleScene) {
			titleScene->Draw();
		}

		break;

	case Scene::kGame:

		if (gameScene) {
			gameScene->Draw();
		}

		break;

	case Scene::kScore:

		if (scoreScene) {
			scoreScene->Draw();
		}

		break;
	}
}