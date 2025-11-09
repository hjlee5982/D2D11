#pragma once

#include "Scene.h"

struct IngredientInfo : public IJson
{
	i32 calories;
	f32 carbohydrate;
	f32 protein;
	f32 fat;

	virtual void MakeJson() override
	{
		_json["calories"]     = calories;
		_json["carbohydrate"] = carbohydrate;
		_json["protein"]      = protein;
		_json["fat"]          = fat;
	}
	virtual void LoadJson() override
	{
		if (_json.contains("calories"))     calories	 = _json["calories"];
		if (_json.contains("carbohydrate")) carbohydrate = _json["carbohydrate"];
		if (_json.contains("protein"))      protein      = _json["protein"];
		if (_json.contains("fat"))          fat		     = _json["fat"];
	}
};



struct Product : public IJson
{
	int code;
	string tag;
	SortedDictionary<string, string> productData;
	IngredientInfo ingredient;

	Vector3 v;

	virtual void MakeJson() override
	{
		_json["code"]       = code;
		_json["tag"]        = tag;
		ingredient.MakeJson();
		_json["ingredient"] = ingredient._json;

		nlohmann::json productDataJson;
		for (auto& kv : productData)
		{
			productDataJson[kv.first] = kv.second;
		}
		_json["productData"] = productDataJson;
	}
	virtual void LoadJson()
	{
		if (_json.contains("code")) code = _json["code"];
		if (_json.contains("tag"))  tag  = _json["tag"];
		if (_json.contains("productData"))
		{
			productData.clear();
			for (auto& kvp : _json["productData"].items())
			{
				productData[kvp.key()] = kvp.value();
			}
		}
		if (_json.contains("ingredient"))
		{
			ingredient._json = _json["ingredient"];
			ingredient.LoadJson();
		}
	}
};

class MainScene : public Scene
{
public:
	MainScene(const string& sceneName) : Scene(sceneName) {}
public:
	void InitializeScene() override;
public:
	void LoadResources();
	void SetInputSystem();
public:
	void JsonTest();
};