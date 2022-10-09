#pragma once

#include <string>
#include <map>
#include <d2d1.h>
#include <dwrite.h>
#include <time.h>

#pragma comment(lib,"winmm.lib")

using namespace std;

extern HWND hWnd;

extern float cameraX;
extern float cameraY;


//다이렉트 2d의 각종 객체를 생성하기 위한 Factory
extern ID2D1Factory* pD2dFactory;
//다이렉트 2D의 글자를 출력하는 Factory
extern IDWriteFactory* pDWriteFactory;

//그림 그릴 곳
extern ID2D1HwndRenderTarget* pRenderTarget;
extern map<wstring, ID2D1Bitmap*>* bitmapMap;

int CreateBmpFromPng(ID2D1RenderTarget* target, const wchar_t* directory, ID2D1Bitmap** result);

class ID2D1Bitmap* BitMapFind(wstring name);
class Animation* AnimationFind(wstring name);
class NineSlice* NineSliceFind(wstring name);
class Sprite* SpriteFind(wstring name);

void SetInfo();
void Initialize();
void Release();
void Draw();

enum class SourceType {
	Sprite,
	Animator,
	NineSlice,
};

class FontSource {
public:
	class D2D1::ColorF* color;
	int size;
	const wchar_t* font;
	DWRITE_TEXT_ALIGNMENT horizontalAlign;
	DWRITE_PARAGRAPH_ALIGNMENT verticalAlign;
	DWRITE_FONT_WEIGHT thickness;
	DWRITE_FONT_STYLE style;

	FontSource(D2D1::ColorF wantColor, int wantSize = 14, const wchar_t* wantFont = L"나눔고딕", DWRITE_TEXT_ALIGNMENT wantHorizontalAlign = DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT wantVerticalAlign = DWRITE_PARAGRAPH_ALIGNMENT_NEAR, DWRITE_FONT_WEIGHT wantThickness = DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE wantStyle = DWRITE_FONT_STYLE_NORMAL) {
		color = &wantColor;
		size = wantSize;
		font = wantFont;
		font = wantFont;
		horizontalAlign = wantHorizontalAlign;
		verticalAlign = wantVerticalAlign;
		thickness = wantThickness;
		style = wantStyle;
	}
};
extern class FontSource baseFont;
inline void Write2Screen(const wchar_t* text, float posX, float posY, float width, float height, float angle = 0, class FontSource wantFont = baseFont);
inline void Write2Field(const wchar_t* text, float posX, float posY, float width, float height, float angle = 0, class FontSource wantFont = baseFont);

class DrawSource {
public:
	virtual float GetWidth() { return 0; };
	virtual float GetHeight() { return 0; };
	virtual bool IsEnd(DWORD animTime) { return false; };
	virtual SourceType GetType() = 0;
	virtual void Draw(float pos_X, float pos_Y, float scale_X = 1.0f, float scale_Y = 1.0f, float alpha = 1.0f, float angle = 0.0f, bool ignoreCamera = false) = 0;
};

class Sprite : public DrawSource {
private:
	ID2D1Bitmap* srcBitmap;
	D2D1_RECT_F srcLocation;

public:
	Sprite(wstring bitmapName, float src_X, float src_Y, float src_Width, float src_Height) {
		srcBitmap = BitMapFind(bitmapName);
		srcLocation.left = src_X;
		srcLocation.right = src_X + src_Width;
		srcLocation.top = src_Y;
		srcLocation.bottom = src_Y + src_Height;
	}
	Sprite(wstring bitmapName) {
		srcBitmap = BitMapFind(bitmapName);
		D2D1_SIZE_F size = srcBitmap->GetSize();
		srcLocation.left = 0;
		srcLocation.right = size.width;
		srcLocation.top = 0;
		srcLocation.bottom = size.height;
	}
	D2D1_RECT_F GetLocation() { 
		D2D1_RECT_F result; 
		result.bottom = srcLocation.bottom;
		result.top = srcLocation.top;
		result.left = srcLocation.left;
		result.right = srcLocation.right;
		return result;
	}
	ID2D1Bitmap* GetSource() { return srcBitmap; };
	float GetWidth() { return srcLocation.right - srcLocation.left; };
	float GetHeight() { return srcLocation.top - srcLocation.bottom; };
	SourceType GetType() { return SourceType::Sprite; };
	void Draw(float pos_X, float pos_Y, float scale_X = 1.0f, float scale_Y = 1.0f, float alpha = 1.0f, float angle = 0.0f, bool ignoreCamera = false);
};
extern map<wstring, Sprite>* spriteMap;

class NineSlice : public DrawSource {
private:
	class Sprite* src;
	D2D1_RECT_F outerRect;
	D2D1_RECT_F innerRect;
	float sourceScale;

public:
	NineSlice(wstring spriteName, float marginTop, float marginBottom, float marginLeft, float marginRight, float src_scale = 1.0f) {
		src = SpriteFind(spriteName);
		innerRect = D2D1_RECT_F();
		outerRect = D2D1_RECT_F();
		if (src == nullptr) {
			sourceScale = 0;
			return;
		};
		D2D1_RECT_F sourceRect = src->GetLocation();
		outerRect.left = sourceRect.left;
		outerRect.right = sourceRect.right;
		outerRect.top = sourceRect.top;
		outerRect.bottom = sourceRect.bottom;

		innerRect.left = outerRect.left + marginLeft;
		innerRect.right = outerRect.right - marginRight;
		innerRect.top = outerRect.top + marginTop;
		innerRect.bottom = outerRect.bottom - marginBottom;
		sourceScale = src_scale;
	}
	SourceType GetType() { return SourceType::NineSlice; };
	float GetWidth() { return src->GetWidth(); };
	float GetHeight() { return src->GetHeight(); };
	void Draw(float pos_X, float pos_Y, float scale_X = 1.0f, float scale_Y = 1.0f, float alpha = 1.0f, float angle = 0.0f, bool ignoreCamera = false);
};
extern map<wstring, NineSlice>* nineSliceMap;


class Animation : public DrawSource {
private:
	Sprite** sprites;
	int spriteNumber = 0;
	float speed;
	bool loop;
public:
	Animation(int wantNumber, wstring targetSprites[], float wantSpeed, bool wantLoop = true) {
		spriteNumber = wantNumber;
		sprites = new Sprite * [wantNumber];
		for (int i = 0; i < wantNumber; i++) {
			sprites[i] = SpriteFind(targetSprites[i]);
		};

		speed = wantSpeed;
		loop = wantLoop;
	};
	bool IsEnd(DWORD animTime) { return animTime * speed >= spriteNumber; };
	float GetWidth() { return sprites[spriteNumber]->GetWidth(); };
	float GetHeight() { return sprites[spriteNumber]->GetHeight(); };
	SourceType GetType() { return SourceType::Animator; };
	Sprite* GetSprite(DWORD animTime);

	void Draw(float pos_X, float pos_Y, float scale_X = 1.0f, float scale_Y = 1.0f, float alpha = 1.0f, float angle = 0.0f, bool ignoreCamera = false);
};
extern map<wstring, Animation>* animationMap;





class Renderer {
private:
	DrawSource* src = nullptr;
	DWORD lastDrawTime = 0;
	DWORD totalTime = 0;
public:
	Renderer(wstring wantName, SourceType wantType = SourceType::Sprite) {
		switch (wantType) {
		case SourceType::NineSlice:
			src = NineSliceFind(wantName);
			break;
		case SourceType::Animator:
			src = AnimationFind(wantName);
			break;
		default:
			src = SpriteFind(wantName);
			break;
		};
	}

	Renderer(DrawSource* wantSource) {
		src = wantSource;
		lastDrawTime = timeGetTime();
	}
	void SetSource(DrawSource* wantSource, bool forceChange = false) {
		if (forceChange || src != wantSource) {
			src = wantSource;
			lastDrawTime = timeGetTime();
			totalTime = 0;
		};
	}
	DrawSource* GetSource() {
		return src;
	}

	void Draw(float pos_X, float pos_Y, float scale_X = 1.0f, float scale_Y = 1.0f, float alpha = 1.0f, float angle = 0.0f, bool ignoreCamera = false);
};