#pragma once

struct Glyph
{
	i32 id;
	i32 x, y;
	i32 witdh, height;
	i32 xOffset, yOffset;
	i32 xAdvance;

	f32 u0, v0, u1, v1;
};

class FontManager : public Singleton<FontManager>
{
public:
	virtual void Awake() override;
private:
	bool Load(const string& fileName);
private:
	void ParseCommon(const string& line);
	void ParsePage(const string& line);
	void ParseChar(const string& line);
private:
	Dictionary<string, string> Tokenize(const string& line);
public:
	i32 _textureWidth;
	i32 _textureHeight;
	string _textureFile;
	Dictionary<i32, Glyph> glyphs;
};
