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
#include "UIImage.h"

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
	/*auto panel = Instantiate(EObjectType::UI);
	{
		auto tr = panel->AddComponent<Transform>();
		{
			tr->SetScale(Vector3(Global::ClientOption.width, Global::ClientOption.height, 0.f));
		}
		auto im = panel->AddComponent<UIImage>();
		{
			im->color = Vector4(0.f, 0.f, 0.f, 0.5f);
		}
	}*/

	for (i32 i = 0; i < 3; ++i)
	{
		for (i32 j = 0; j < 3; ++j)
		{
			auto desc = Instantiate(EObjectType::UI);
			{
				auto descTr = desc->AddComponent<Transform>();
				{
					descTr->SetPosition(Vector3(200.f * j - 200.f, -200.f * i + 200.f, 0.f));
					descTr->SetScale(Vector3(100.f, 100.f, 1.f));
				}
				auto descText = desc->AddComponent<UIText>();
				{
					descText->Text(L"New Text");
					descText->Alignment((EHorizontalAlignment)i, (EVerticalAlignment)j);
					descText->Space(5);
					descText->Scale(24);
				}
			}
		}
	}
}
