#include "pch.h"
#include "TextTest.h"
#include "SpriteRenderer.h"
#include "AssetManager.h"
#include "Texture.h"
#include "UIText.h"
#include "Transform.h"
#include "Camera.h"

void TextTest::Awake()
{
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
	{
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
	}
	{
		auto go = Instantiate(EObjectType::UI);
		{
			auto tr = go->AddComponent<Transform>();
			{
				tr->SetPosition(Vector3(250.f, 450.f, 0.f));
				tr->SetScale(Vector3(30.f, 30.f, 0.f));
			}
			auto ut = go->AddComponent<UIText>();
			{
				ut->Text(L"A");
			}
		}
	}
}
