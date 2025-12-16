#include "pch.h"
#include "TextTest.h"
#include "SpriteRenderer.h"
#include "AssetManager.h"
#include "Texture.h"
#include "UIText.h"
#include "Transform.h"
#include "Camera.h"
#include "UIBoundary.h"
#include "BoxCollider2D.h"
#include "RenderManager.h"
#include "UIImage.h"
#include "CircleCollider2D.h"

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
	//for (i32 i = 0; i < 3; ++i)
	//{
	//	for (i32 j = 0; j < 3; ++j)
	//	{
	//		auto desc = Instantiate(EObjectType::UI);
	//		{
	//			auto descTr = desc->AddComponent<Transform>();
	//			{
	//				descTr->SetPosition(Vector3(200.f * j - 200.f, -200.f * i + 200.f, 0.f));
	//				descTr->SetScale(Vector3(100.f, 100.f, 1.f));
	//			}
	//			auto descText = desc->AddComponent<UIText>();
	//			{
	//				descText->Text(L"New Text");
	//				descText->Alignment((EHorizontalAlignment)i, (EVerticalAlignment)j);
	//				//descText->Space(5);
	//				descText->Scale(24);
	//			}
	//		}
	//	}
	//}

	auto go = Instantiate();
	{
		auto t = go->AddComponent<Transform>();
		{
		}
		auto s = go->AddComponent<SpriteRenderer>();
		{
			s->OrderInLayer = 100;
		}
		auto c = go->AddComponent<CircleCollider2D>();
		{
			c->Offset(Vector3(0.f, 0.f, 0.f));
			c->Radius(1.f);
		}
	}

	auto ui = Instantiate();
	{
		auto t = ui->AddComponent<Transform>();
		{
			t->SetScale(Vector3(Global::ClientOption.width / 2, Global::ClientOption.height / 2, 0.f));
		}
		auto i = ui->AddComponent<UIImage>();
		{
			i->color = Vector4(0.f, 0.f, 0.f, 0.5f);
		}
	}

	auto text = Instantiate();
	{
		auto t = text->AddComponent<Transform>();
		{
			t->SetPosition(Vector3(0.f, 300.f, 0.f));
			t->SetScale(Vector3(100.f, 100.f, 1.f));
		}
		auto tx = text->AddComponent<UIText>();
		{
			tx->Text(L"Test");
			tx->Alignment(EHorizontalAlignment::Center);
			tx->Color(Vector4(1.f, 0.f, 1.f, 0.5f));
		}
	}
}
