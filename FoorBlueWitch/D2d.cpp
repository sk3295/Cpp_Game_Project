#include "D2d.h"
#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "Dwrite.lib")
using namespace D2D1;

#include <wincodec.h>
#include "framework.h"
#include "GameObject.h"

float cameraX = 0.0f;
float cameraY = 0.0f;

ID2D1Factory* pD2dFactory;
IDWriteFactory* pDWriteFactory;
ID2D1HwndRenderTarget* pRenderTarget;

void Draw() {
	if (pRenderTarget == nullptr) { return; }

	pRenderTarget->BeginDraw();
	//					           R    G    B
	pRenderTarget->Clear(ColorF(1.0f, 1.0f, 1.0f));

	//   대상자료형   각각을 부를 이름 : 리스트
	for (GameObject* currentObject   : gameObjectList) {
		currentObject->Draw();
	};
	
	/*
	for (int i = 0; i < gameObjectList.size(); i++)
	{
		gameObjectList[i]->Draw();
	}
	*/

	pRenderTarget->EndDraw();
}


int CreateBmpFromPng(ID2D1RenderTarget* target, const wchar_t* directory, ID2D1Bitmap** result) {
	IWICImagingFactory* pWicFactory;
	if (S_OK != CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pWicFactory))) {
		return 0;
	};

	IWICBitmapDecoder* pDecoder; 
	IWICBitmapFrameDecode* pFrame; 
	IWICFormatConverter* pConverter; 
	int succeed = 0; 

	if (S_OK == pWicFactory->CreateDecoderFromFilename(directory, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pDecoder)) {
		if (S_OK == pDecoder->GetFrame(0, &pFrame)) {
			if (S_OK == pWicFactory->CreateFormatConverter(&pConverter)) {
				if (S_OK == pConverter->Initialize(pFrame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom)) {
					if (S_OK == target->CreateBitmapFromWicBitmap(pConverter, NULL, result)) succeed = true;
				};
				pConverter->Release();
			};
			pFrame->Release(); 
		};
		pDecoder->Release();
	};
	pWicFactory->Release();

	return succeed;
}

void Initialize() {
	if (CoInitializeEx(NULL, COINIT_MULTITHREADED) != S_OK) return;

	RECT windowSize;
	GetClientRect(hWnd, &windowSize);

	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2dFactory);

	pD2dFactory->CreateHwndRenderTarget (
		//렌더 타겟 기본 설정
		RenderTargetProperties(),
		//어디에다가 그릴 건가요?
		HwndRenderTargetProperties(hWnd, SizeU(windowSize.right, windowSize.bottom)),
		//받을 사람
		&pRenderTarget
	);

	timeGetTime();

	SetInfo();

	pDWriteFactory = NULL;
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&pDWriteFactory));
}

void Release() {
	pD2dFactory->Release();
	nineSliceMap->clear();
	animationMap->clear();
	spriteMap->clear();

	for (auto iter = bitmapMap->begin(); iter != bitmapMap->end(); iter++) { iter->second->Release(); };
	bitmapMap->clear();

	CoUninitialize();
}


void Write(const wchar_t* text, float posX, float posY, float width, float height, float angle, FontSource wantFont) {
	width += posX;
	height += posY;

	IDWriteTextFormat* pTextFormat = NULL;
	pDWriteFactory->CreateTextFormat(wantFont.font, NULL, wantFont.thickness, wantFont.style, DWRITE_FONT_STRETCH_NORMAL, (FLOAT)wantFont.size, L"ko-kr", &pTextFormat);

	pTextFormat->SetTextAlignment(wantFont.horizontalAlign);
	pTextFormat->SetParagraphAlignment(wantFont.verticalAlign);

	int length = 0;
	while (text[length] != 0) ++length;

	ID2D1SolidColorBrush* brush;
	pRenderTarget->CreateSolidColorBrush(*wantFont.color, &brush);

	D2D1_POINT_2F imageCenter = D2D1::Point2F(posX + (width * 0.5f), posY + (height * 0.5f));
	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(angle, imageCenter));

	pRenderTarget->DrawText(text, length, pTextFormat, D2D1::RectF(posX, posY, width, height), brush);

	pTextFormat->Release();
	brush->Release();
}

inline void Write2Screen(const wchar_t* text, float posX, float posY, float width, float height, float angle, FontSource wantFont) {
	Write(text, posX, posY, width, height, angle, wantFont);
}

inline void Write2Field(const wchar_t* text, float posX, float posY, float width, float height, float angle, FontSource wantFont) {
	Write(text, posX - cameraX, posY - cameraY, width, height, angle, wantFont);
}


void Renderer::Draw(float pos_X, float pos_Y, float scale_X, float scale_Y, float alpha, float angle, bool ignoreCamera) {
	if (src == nullptr) return;

	if (src->GetType() == SourceType::Animator) {
		Sprite* currentSprite = ((Animation*)src)->GetSprite(totalTime);
		
		DWORD currentTime = timeGetTime();
		totalTime += (currentTime - lastDrawTime);
		lastDrawTime = currentTime;

		if (currentSprite == nullptr) return;

		currentSprite->Draw(pos_X, pos_Y, scale_X, scale_Y, alpha, angle, ignoreCamera);
	}
	else {
		src->Draw(pos_X, pos_Y, scale_X, scale_Y, alpha, angle, ignoreCamera);
	};
}


void NineSlice::Draw(float pos_X, float pos_Y, float size_X, float size_Y, float alpha, float angle, bool ignoreCamera) {
	float halfX = size_X / 2.0f;
	float halfY = size_Y / 2.0f;

	float marginLeft = abs(innerRect.left - outerRect.left) * sourceScale;
	float marginRight = abs(outerRect.right - innerRect.right) * sourceScale;
	float marginTop = abs(outerRect.top - innerRect.top) * sourceScale;
	float marginBottom = abs(innerRect.bottom - outerRect.bottom) * sourceScale;

	float overX = max(0, (marginLeft + marginRight) - size_X) / 2.0f;
	float overY = max(0, (marginTop + marginBottom) - size_Y) / 2.0f;

	marginLeft -= overX;
	marginRight -= overX;
	marginTop -= overY;
	marginBottom -= overY;

	float middleWidth = size_X - marginLeft - marginRight;
	float middleHeight = size_Y - marginTop - marginBottom;

	float cameraShiftX = ignoreCamera ? 0 : cameraX;
	float cameraShiftY = ignoreCamera ? 0 : cameraY;

	D2D1_POINT_2F imageCenter = D2D1::Point2F(pos_X - cameraShiftX, pos_Y - cameraShiftY);
	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(angle, imageCenter));

	D2D1_RECT_F drawLocation = D2D1_RECT_F();
	D2D1_RECT_F srcLocation = D2D1_RECT_F();

	srcLocation.left = outerRect.left;
	srcLocation.right = innerRect.left;
	srcLocation.top = outerRect.top;
	srcLocation.bottom = innerRect.top;
	

	drawLocation.left = pos_X - halfX - cameraShiftX;
	drawLocation.right = drawLocation.left + marginLeft;

	drawLocation.top = pos_Y - halfY - cameraShiftY;
	drawLocation.bottom = drawLocation.top + marginTop;

	//           그림 그리기        그림,        위치,        투명도,         비트맵 보간(크기에 따라 색깔 보정)    , 위에서 찾은 그릴 위치
	pRenderTarget->DrawBitmap(src->GetSource(), drawLocation, alpha, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, srcLocation);
	

	// 중간 위
	if (middleWidth > 0) {
		srcLocation.left = innerRect.left;
		srcLocation.right = innerRect.right;

		drawLocation.left = drawLocation.right - 1;
		drawLocation.right = drawLocation.left + middleWidth + 1;

		pRenderTarget->DrawBitmap(src->GetSource(), drawLocation, alpha, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, srcLocation);
	}
	
	// 오른쪽 위
	srcLocation.left = innerRect.right;
	srcLocation.right = outerRect.right;

	drawLocation.left = drawLocation.right - 1;
	drawLocation.right = drawLocation.left + marginRight + 1;
	pRenderTarget->DrawBitmap(src->GetSource(), drawLocation, alpha, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, srcLocation);
	
	// 중간
	if (middleHeight > 0) {
		// 오른쪽 중간
		srcLocation.top = innerRect.top;
		srcLocation.bottom = innerRect.bottom;

		drawLocation.top = drawLocation.bottom - 1;
		drawLocation.bottom = drawLocation.top + middleHeight + 1;
		pRenderTarget->DrawBitmap(src->GetSource(), drawLocation, alpha, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, srcLocation);
		
		// 중간 중간
		if (middleWidth > 0) {
			srcLocation.left = innerRect.left;
			srcLocation.right = innerRect.right;

			drawLocation.right = drawLocation.left + 1;
			drawLocation.left = drawLocation.right - middleWidth - 1;
			pRenderTarget->DrawBitmap(src->GetSource(), drawLocation, alpha, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, srcLocation);
		};

		// 왼쪽 중간
		srcLocation.left = outerRect.left;
		srcLocation.right = innerRect.left;

		drawLocation.right = drawLocation.left + 1;
		drawLocation.left = drawLocation.right - marginLeft;
		pRenderTarget->DrawBitmap(src->GetSource(), drawLocation, alpha, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, srcLocation);
	}
	else {
		drawLocation.left = pos_X - halfX - cameraShiftX;
		drawLocation.right = drawLocation.left + marginLeft;

		srcLocation.left = outerRect.left;
		srcLocation.right = innerRect.left;
	}

	
	//왼쪽 아래
	srcLocation.top = innerRect.bottom;
	srcLocation.bottom = outerRect.bottom;

	drawLocation.top = drawLocation.bottom - 1;
	drawLocation.bottom = drawLocation.top + marginBottom + 1;
	pRenderTarget->DrawBitmap(src->GetSource(), drawLocation, alpha, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, srcLocation);

	//중간 아래
	if (middleWidth > 0) {
		srcLocation.left = innerRect.left;
		srcLocation.right = innerRect.right;

		drawLocation.left = drawLocation.right - 1;
		drawLocation.right = drawLocation.left + middleWidth + 1;
		pRenderTarget->DrawBitmap(src->GetSource(), drawLocation, alpha, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, srcLocation);
	};

	//오른쪽 아래
	srcLocation.left = innerRect.right;
	srcLocation.right = outerRect.right;

	drawLocation.left = drawLocation.right - 1;
	drawLocation.right = drawLocation.left + marginRight + 1;
	pRenderTarget->DrawBitmap(src->GetSource(), drawLocation, alpha, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, srcLocation);
}


void Sprite::Draw(float pos_X, float pos_Y, float scale_X, float scale_Y, float alpha, float angle, bool ignoreCamera) {
	float halfX = ((srcLocation.right - srcLocation.left) / 2) * scale_X;
	float halfY = ((srcLocation.bottom - srcLocation.top) / 2) * scale_Y;

	//카메라 위치 계산
	float cameraShiftX = ignoreCamera ? 0 : cameraX;
	float cameraShiftY = ignoreCamera ? 0 : cameraY;

	//실제로 그릴 위치를 확인
	D2D1_RECT_F drawLocation;

	//현재 위치랑 크기 절반을 가져와서 그리는 위치를 확인
	drawLocation.left = pos_X - halfX - cameraShiftX;
	drawLocation.right = pos_X + halfX - cameraShiftX;

	drawLocation.top = pos_Y - halfY - cameraShiftY;
	drawLocation.bottom = pos_Y + halfY - cameraShiftY;

	D2D1_POINT_2F imageCenter = D2D1::Point2F(pos_X - cameraShiftX, pos_Y - cameraShiftY);
	//pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(pos_X,pos_Y) * D2D1::Matrix3x2F::Rotation(angle, imageCenter));
	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(angle, imageCenter));
	
	//실제로 그림 그리기        그림,        위치,        투명도,         비트맵 보간(크기에 따라 색깔 보정)    , 위에서 찾은 그릴 위치
	pRenderTarget->DrawBitmap(srcBitmap, drawLocation, alpha, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, srcLocation);
}

void Animation::Draw(float pos_X, float pos_Y, float scale_X, float scale_Y, float alpha, float angle, bool ignoreCamera) {};

Sprite* Animation::GetSprite(DWORD animTime) {
	int currentIndex = (int)(animTime * speed / 1000);

	if (loop)								{ currentIndex %= spriteNumber; }
	else if (currentIndex >= spriteNumber)	{ currentIndex = spriteNumber - 1; }

	return sprites[currentIndex];
}

Animation* AnimationFind(wstring name) {
	auto finder = animationMap->find(name);
	if (finder == animationMap->end()) return nullptr;
	return &finder->second;
};
Sprite* SpriteFind(wstring name) {
	auto finder = spriteMap->find(name);
	if (finder == spriteMap->end()) return nullptr;
	return &finder->second;
};
NineSlice* NineSliceFind(wstring name) {
	auto finder = nineSliceMap->find(name);
	if (finder == nineSliceMap->end()) return nullptr;
	return &finder->second;
};

ID2D1Bitmap* BitMapFind(wstring name) {
	auto finder = bitmapMap->find(name);
	if (finder == bitmapMap->end()) return nullptr;
	return finder->second;
};