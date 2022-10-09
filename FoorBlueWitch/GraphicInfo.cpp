#include "D2d.h"

FontSource baseFont(D2D1::ColorF::Black);

void SetInfo() {
	map<wstring, wstring>* bitmapLocationMap = new map<wstring, wstring>();


	//��Ʈ���� ���� ��θ� �����մϴ� ===========================================
	//                             �̸�              ���� ���

	bitmapLocationMap->insert({ L"���ΰ��⺻",  L"Sprites/Characters/BlueWitch/B_witch_idle.png" });
	bitmapLocationMap->insert({ L"���ΰ��ȱ�", L"Sprites/Characters/BlueWitch/B_witch_run.png" });

	//========================================================================
	



	bitmapMap = new map<wstring, ID2D1Bitmap*>();
	for (auto iter = bitmapLocationMap->begin(); iter != bitmapLocationMap->end(); iter++) {
		ID2D1Bitmap* result;

		CreateBmpFromPng(pRenderTarget, iter->second.c_str(), &result);
		bitmapMap->insert({ iter->first, result });
	};

	spriteMap = new map<wstring, Sprite>();

	//��������Ʈ ������ �����մϴ� =============================================
	//              ��������Ʈ�̸�              �׸� �̸�		  x, y			����,	����

	spriteMap->insert({ L"���ΰ��⺻0",     Sprite(L"���ΰ��⺻", 0, 0, 32, 48) });
	spriteMap->insert({ L"���ΰ��⺻1",     Sprite(L"���ΰ��⺻", 0, 48, 32, 48) });
	spriteMap->insert({ L"���ΰ��⺻2",     Sprite(L"���ΰ��⺻", 0, 96, 32, 48) });
	spriteMap->insert({ L"���ΰ��⺻3",     Sprite(L"���ΰ��⺻", 0, 144, 32, 48) });
	spriteMap->insert({ L"���ΰ��⺻4",     Sprite(L"���ΰ��⺻", 0, 192, 32, 48) });
	spriteMap->insert({ L"���ΰ��⺻5",     Sprite(L"���ΰ��⺻", 0, 240, 32, 48) });

	spriteMap->insert({ L"���ΰ��ȱ�0",     Sprite(L"���ΰ��ȱ�", 0, 0, 32, 48) });
	spriteMap->insert({ L"���ΰ��ȱ�1",     Sprite(L"���ΰ��ȱ�", 0, 48, 32, 48) });
	spriteMap->insert({ L"���ΰ��ȱ�2",     Sprite(L"���ΰ��ȱ�", 0, 96, 32, 48) });
	spriteMap->insert({ L"���ΰ��ȱ�3",     Sprite(L"���ΰ��ȱ�", 0, 144, 32, 48) });
	spriteMap->insert({ L"���ΰ��ȱ�4",     Sprite(L"���ΰ��ȱ�", 0, 192, 32, 48) });
	spriteMap->insert({ L"���ΰ��ȱ�5",     Sprite(L"���ΰ��ȱ�", 0, 240, 32, 48) });
	spriteMap->insert({ L"���ΰ��ȱ�6",     Sprite(L"���ΰ��ȱ�", 0, 288, 32, 48) });
	spriteMap->insert({ L"���ΰ��ȱ�7",     Sprite(L"���ΰ��ȱ�", 0, 332, 32, 48) });

	// 
	//========================================================================






	animationMap = new map<wstring, Animation>();
	//�ִϸ��̼� ������ �����մϴ� =============================================
	//                    �ִϸ��̼� �̸�         �� ��,      ��������Ʈ �̸���,					�ӵ�,         �ݺ�

	//wstring animTest[] { L"���ΰ��⺻0",L"���ΰ��⺻1",L"���ΰ��⺻2",L"���ΰ��⺻3",L"���ΰ��⺻4",L"���ΰ��⺻5" };
	//animationMap->insert({ L"���ΰ��⺻",   Animation(6,  animTest,	3) });

	animationMap->insert({ L"���ΰ��⺻",   Animation(6,  new wstring[] {L"���ΰ��⺻0",L"���ΰ��⺻1",L"���ΰ��⺻2",L"���ΰ��⺻3",L"���ΰ��⺻4",L"���ΰ��⺻5"},	10) });
	animationMap->insert({ L"���ΰ��ȱ�",   Animation(8,  new wstring[] {L"���ΰ��ȱ�0",L"���ΰ��ȱ�1",L"���ΰ��ȱ�2",L"���ΰ��ȱ�3",L"���ΰ��ȱ�4",L"���ΰ��ȱ�5",L"���ΰ��ȱ�6",L"���ΰ��ȱ�7"},	10) });

	//========================================================================






	nineSliceMap = new map<wstring, NineSlice>();


	//���ν����̽� ������ �����մϴ� =============================================
	//                       �̸�            ��������Ʈ�̸�    �� �� �� ��     �̹�������

	//nineSliceMap->insert({ L"��ư",   NineSlice(L"�׽�Ʈ",     10, 10, 10, 10, 1.5) });
	
	//========================================================================

	bitmapLocationMap->clear();
	delete bitmapLocationMap;
}

map<wstring, ID2D1Bitmap*>* bitmapMap;
map<wstring, Sprite>* spriteMap;
map<wstring, Animation>* animationMap;
map<wstring, NineSlice>* nineSliceMap;