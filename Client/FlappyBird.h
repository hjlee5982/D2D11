#pragma once

#include "IScene.h"

struct IngredientInfo : public IJson
{
	i32 calories;
	f32 carbohydrate;
	f32 protein;
	f32 fat;

	virtual void MakeJson() override
	{
		_json["calories"] = calories;
		_json["carbohydrate"] = carbohydrate;
		_json["protein"] = protein;
		_json["fat"] = fat;
	}
};

struct Product : public IJson
{
	int code;
	string tag;
	IngredientInfo ingredient;
	SortedDictionary<string, string> productData;

	virtual void MakeJson() override
	{
		_json["code"] = code;
		_json["tag"] = tag;
		ingredient.MakeJson();
		_json["ingredient"] = ingredient._json;

		nlohmann::json productDataJson;
		for (auto& kv : productData)
		{
			productDataJson[kv.first] = kv.second;
		}
		_json["productData"] = productData;
	}
};

class FlappyBird : public IScene
{
public:
	void InitializeScene() override;
};

