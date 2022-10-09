#include "D2d.h"

FontSource baseFont(D2D1::ColorF::Black);

void SetInfo() {
	map<wstring, wstring>* bitmapLocationMap = new map<wstring, wstring>();


	//비트맵을 만들 경로를 지정합니다 ===========================================
	//                             이름              파일 경로

	bitmapLocationMap->insert({ L"주인공기본",  L"Sprites/Characters/BlueWitch/B_witch_idle.png" });
	bitmapLocationMap->insert({ L"주인공걷기", L"Sprites/Characters/BlueWitch/B_witch_run.png" });

	//========================================================================
	



	bitmapMap = new map<wstring, ID2D1Bitmap*>();
	for (auto iter = bitmapLocationMap->begin(); iter != bitmapLocationMap->end(); iter++) {
		ID2D1Bitmap* result;

		CreateBmpFromPng(pRenderTarget, iter->second.c_str(), &result);
		bitmapMap->insert({ iter->first, result });
	};

	spriteMap = new map<wstring, Sprite>();

	//스프라이트 내용을 지정합니다 =============================================
	//              스프라이트이름              그림 이름		  x, y			가로,	세로

	spriteMap->insert({ L"주인공기본0",     Sprite(L"주인공기본", 0, 0, 32, 48) });
	spriteMap->insert({ L"주인공기본1",     Sprite(L"주인공기본", 0, 48, 32, 48) });
	spriteMap->insert({ L"주인공기본2",     Sprite(L"주인공기본", 0, 96, 32, 48) });
	spriteMap->insert({ L"주인공기본3",     Sprite(L"주인공기본", 0, 144, 32, 48) });
	spriteMap->insert({ L"주인공기본4",     Sprite(L"주인공기본", 0, 192, 32, 48) });
	spriteMap->insert({ L"주인공기본5",     Sprite(L"주인공기본", 0, 240, 32, 48) });

	spriteMap->insert({ L"주인공걷기0",     Sprite(L"주인공걷기", 0, 0, 32, 48) });
	spriteMap->insert({ L"주인공걷기1",     Sprite(L"주인공걷기", 0, 48, 32, 48) });
	spriteMap->insert({ L"주인공걷기2",     Sprite(L"주인공걷기", 0, 96, 32, 48) });
	spriteMap->insert({ L"주인공걷기3",     Sprite(L"주인공걷기", 0, 144, 32, 48) });
	spriteMap->insert({ L"주인공걷기4",     Sprite(L"주인공걷기", 0, 192, 32, 48) });
	spriteMap->insert({ L"주인공걷기5",     Sprite(L"주인공걷기", 0, 240, 32, 48) });
	spriteMap->insert({ L"주인공걷기6",     Sprite(L"주인공걷기", 0, 288, 32, 48) });
	spriteMap->insert({ L"주인공걷기7",     Sprite(L"주인공걷기", 0, 332, 32, 48) });

	// 
	//========================================================================






	animationMap = new map<wstring, Animation>();
	//애니메이션 내용을 지정합니다 =============================================
	//                    애니메이션 이름         몇 장,      스프라이트 이름들,					속도,         반복

	//wstring animTest[] { L"주인공기본0",L"주인공기본1",L"주인공기본2",L"주인공기본3",L"주인공기본4",L"주인공기본5" };
	//animationMap->insert({ L"주인공기본",   Animation(6,  animTest,	3) });

	animationMap->insert({ L"주인공기본",   Animation(6,  new wstring[] {L"주인공기본0",L"주인공기본1",L"주인공기본2",L"주인공기본3",L"주인공기본4",L"주인공기본5"},	10) });
	animationMap->insert({ L"주인공걷기",   Animation(8,  new wstring[] {L"주인공걷기0",L"주인공걷기1",L"주인공걷기2",L"주인공걷기3",L"주인공걷기4",L"주인공걷기5",L"주인공걷기6",L"주인공걷기7"},	10) });

	//========================================================================






	nineSliceMap = new map<wstring, NineSlice>();


	//나인슬라이스 내용을 지정합니다 =============================================
	//                       이름            스프라이트이름    상 하 좌 우     이미지배율

	//nineSliceMap->insert({ L"버튼",   NineSlice(L"테스트",     10, 10, 10, 10, 1.5) });
	
	//========================================================================

	bitmapLocationMap->clear();
	delete bitmapLocationMap;
}

map<wstring, ID2D1Bitmap*>* bitmapMap;
map<wstring, Sprite>* spriteMap;
map<wstring, Animation>* animationMap;
map<wstring, NineSlice>* nineSliceMap;