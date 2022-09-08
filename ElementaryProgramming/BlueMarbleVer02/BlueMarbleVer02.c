#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//상수
//땅 개수
//플레이어 수
//시작현금 액수
#define LANDN 34
#define PLAYERN 2
#define STARTCURRENCY 2000000

//땅 정보 배열
//가격:0으로 초기화
//소유자:뒤에 -1로 초기화
int price[LANDN] = { 0 };
int owner[LANDN];

//플레이어 정보 배열
//위치
//현금
//부동산 자금
int position[PLAYERN] = { 0 };
int currency[PLAYERN] = { 0 };
int asset[PLAYERN] = { 0 };

//디스플레이 함수
//맵 정보 보기
//플레이어 정보 보기
//두 정보 통합 함수
void showmap();
void showplayer();
void show();

//부동산 자금 합계 함수
int assetsum(int p);

//초기화 함수
//땅 소유자: -1
//플레이어 현금: 시작값
void initialize();

//주사위 한개 결과 반환 함수
int dice();

//플레이어 이동 함수
//인수의 플레이어 이동
//함수 내부에서 주사위 함수 호출
void move(int p);

//플레이 함수 매 턴마다 호출
void play(int i);
//턴 함수: 턴에 해당하는 플레이어 행동 루틴
void turn(int p);

//땅 구입 함수:인수의 플레이어 현 위치 땅 구입
void buy(int p);
//통행료 지불 함수:인수의 플레이어 현 위치 땅 값 절반 지불
void toll(int p);
//땅 인수 함수: 인수의 플레이어 현 위치 땅 값 두배 지불 후 소유자 변경
void acquisite(int p);
//투자 함수: 인수의 플레이어 현 위치 땅의 값 증가
void invest(int p);

//////////////////////////////////////////////////////////////////////////////////
int main(void)
{
	initialize();
	show();
	
	for (int i = 0; i >= 0; i++) play(i);

	return 0;
}
//////////////////////////////////////////////////////////////////////////////////

//턴 함수: 턴에 해당하는 플레이어 행동 루틴
void turn(int p)
{
	printf("-----플레이어 %2d 의 턴-------\n", p);
	move(p);
	toll(p);
	buy(p);
	acquisite(p);
	invest(p);
}

//투자 함수: 인수의 플레이어 현 위치 땅의 값 증가
void invest(int p)
{
	int investflag = 0;
	int investcost;
	if (owner[position[p]] ==p)
	{
		printf("플레이어 %d님. %d 째 땅에 투자하겠습니까? 0.아니오/1.예:",p, position[p]);
		scanf("%d", &investflag);
	}
	if (investflag)
	{
		printf("플레이어 %d님. %d 째 땅에 얼마를 투자하겠습니까?:",p,position[p]);
		scanf("%d", &investcost);
		price[position[p]] += investcost;
		currency[p] -= investcost;
		printf("플레이어 %d 가 %d 째 땅에 %d원을 투자했습니다.\n", p, position[p],investcost);
		show();
	}
	
}

//땅 인수 함수: 인수의 플레이어 현 위치 땅 값 두배 지불 후 소유자 변경
void acquisite(int p)
{
	int acquisiteflag=0;
	if (owner[position[p]] >= 0 && owner[position[p]] != p)
	{
		printf("플레이어 %d님. 플레이어 %d에게서 %d 째 땅을 인수하겠습니까? 0.아니오/1.예:", p, owner[position[p]], position[p]);
		scanf(" %d", &acquisiteflag);
	}
	if (acquisiteflag)
	{
		printf("플레이어 %d가 플레이어 %d에게서 %d 째 땅을 인수합니다.\n", p, owner[position[p]], position[p]);
		currency[p] -= price[position[p]]*2;
		currency[owner[p]] += price[position[p]] * 2;
		owner[position[p]] = p;
		show();
	}

}
//땅 구입 함수:인수의 플레이어 현 위치 땅 구입
void buy(int p)
{
	int buyflag=0;
	if (owner[position[p]] < 0)
	{
		printf("플레이어 %d님. %d 째 땅을 구입하겠습니까? 0.아니오/1.예:",p, position[p]);
		scanf("%d", &buyflag);
	}
	if (buyflag)
	{
		owner[position[p]] = p;
		printf("플레이어 %d 가 %d 째 땅을 구입했습니다.\n", p, position[p]);
		show();
	}

}

//통행료 지불 함수:인수의 플레이어 현 위치 땅 값 절반 지불
void toll(int p)
{
	if (owner[ position[p] ] >= 0 && owner[ position[p] ] != p)
	{
		printf("플레이어 %d 가 %d 원을 플레이어 %d에게 지불합니다.\n", p, price[position[p]]/2, owner[p]);
		currency[p] -= price[position[p]]/2;
		currency[owner[p]] += price[position[p]]/2;
		
		show();
	}
}

//플레이 함수 매 턴마다 호출
void play(int i)
{
	int p = i%PLAYERN;
	printf("-----%3d째 플레이----------\n", i);
	turn(p);
}

//플레이어 이동 함수
//인수의 플레이어 이동
//함수 내부에서 주사위 함수 호출
void move(int p)
{
	int dice1, dice2;
	int sum;
	dice1 = dice();
	dice2 = dice();
	sum = dice1 + dice2;
	printf("주사위1+주사위2==%2d\n", sum);
	position[p] = (position[p] + sum) % LANDN;
	show();
}

//주사위 한개 결과 반환 함수
int dice()
{
	int result;
	char buffer;
	srand(time(NULL));
	printf("주사위를 굴리려면 아무 값이나 입력:");
	scanf(" %c", &buffer);
	result = rand() % 6 + 1;
	printf("나온 눈:%2d\n", result);
	return result;
}

//부동산 자금 합계 함수
int assetsum(int p)
{
	int ass=0;
	for (int i = 0; i < LANDN; i++)
	{
		if (owner[i] == p)	ass += price[i];
	}
	return ass;
}

//초기화 함수
//땅 소유자: -1
//플레이어 현금: 시작값
void initialize()
{
	for (int i = 0; i < LANDN; i++)
	{
		owner[i] = -1;
	}

	for (int i = 0; i < PLAYERN; i++)
	{
		currency[i] = STARTCURRENCY;
	}
}

//디스플레이 함수

//맵, 플레이어 정보 통합 함수
void show()
{
	printf("========================================\n");
	showmap();
	printf("----------------------------------------\n");
	showplayer();
	printf("========================================\n");
}

//플레이어 정보 보기
void showplayer()
{
	for (int i = 0; i < PLAYERN; i++)
	{
		printf("플레이어 %2d\n", i);
		asset[i] = assetsum(i);
		printf("현위치:%2d 현금: %10d 부동산:%10d 현금+부동산==%d\n", position[i], currency[i], asset[i], currency[i]+asset[i]);
	}
}

//맵 정보 보기
void showmap()
{
	for (int i = 0; i < LANDN; i++)
	{
		printf("땅번호:%2d 가격:%10d 소유자:%2d ", i, price[i], owner[i]);
		printf("방문자:");
		for (int j = 0; j < PLAYERN; j++)
		{
			if (i == position[j])
				printf(" %d", j);
		}
		printf("\n");
	}
}



