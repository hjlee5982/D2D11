#include "pch.h"
#include "TextTest.h"
#include "SpriteRenderer.h"
#include "AssetManager.h"
#include "Texture.h"
#include "UIText.h"
#include "Transform.h"
#include "Camera.h"
#include "UIBoundary.h"
#include "Renderer.h"

void TextTest::Awake()
{
	RENDERER.colliderRendering = true;
	RENDERER.uiBoundaryRendering = true;

	{
		auto camera = Instantiate();
		{
			{
				camera->name = "MainCamera";
			}
			{
				auto tf = camera->AddComponent<Transform>();
				auto cm = camera->AddComponent<Camera>();
				{
					CameraDesc desc;
					{
						desc.Type = ProjectionType::Orthogonal;
						desc.Near = 0.3f;
						desc.Far = 1000.f;
						desc.OrthoSize = 5.f;
					}
					cm->Initialize(desc);
				}
			}
		}
	}
	/*{
		auto go = Instantiate();
		{
			auto tr = go->AddComponent<Transform>();
			{
				tr->SetScale(Vector3(2.f, 2.f, 2.f));
			}
			auto sr = go->AddComponent<SpriteRenderer>();
			{
				sr->SetTexture(ASSET.Get<Texture>(L"Texture_Default"));
			}
		}
	}*/
	// 스코어 UI
	auto score = Instantiate(EObjectType::UI);
	{
		auto tr = score->AddComponent<Transform>();
		{
			tr->SetPosition(Vector3(0.f, 460.f, 0.f));
			tr->SetScale(Vector3(200.f, 80.f, 0.f));
		}
		score->AddComponent<UIBoundary>();

		auto test = Instantiate(EObjectType::UI);
		{
			auto testT = test->AddComponent<Transform>();
			{
				testT->SetParent(tr);
				testT->SetLocalScale(Vector3(1.f, 0.8f, 0.f));
				testT->SetLocalPosition(Vector3(-0.25f, 0.f, 0.f));
			}
			test->AddComponent<UIBoundary>();
			auto ut = test->AddComponent<UIText>();
			{
				ut->Text(L"가나다라");
			}
		}
	}
}
