#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//���
//�� ����
//�÷��̾� ��
//�������� �׼�
#define LANDN 34
#define PLAYERN 2
#define STARTCURRENCY 2000000

//�� ���� �迭
//����:0���� �ʱ�ȭ
//������:�ڿ� -1�� �ʱ�ȭ
int price[LANDN] = { 0 };
int owner[LANDN];

//�÷��̾� ���� �迭
//��ġ
//����
//�ε��� �ڱ�
int position[PLAYERN] = { 0 };
int currency[PLAYERN] = { 0 };
int asset[PLAYERN] = { 0 };

//���÷��� �Լ�
//�� ���� ����
//�÷��̾� ���� ����
//�� ���� ���� �Լ�
void showmap();
void showplayer();
void show();

//�ε��� �ڱ� �հ� �Լ�
int assetsum(int p);

//�ʱ�ȭ �Լ�
//�� ������: -1
//�÷��̾� ����: ���۰�
void initialize();

//�ֻ��� �Ѱ� ��� ��ȯ �Լ�
int dice();

//�÷��̾� �̵� �Լ�
//�μ��� �÷��̾� �̵�
//�Լ� ���ο��� �ֻ��� �Լ� ȣ��
void move(int p);

//�÷��� �Լ� �� �ϸ��� ȣ��
void play(int i);
//�� �Լ�: �Ͽ� �ش��ϴ� �÷��̾� �ൿ ��ƾ
void turn(int p);

//�� ���� �Լ�:�μ��� �÷��̾� �� ��ġ �� ����
void buy(int p);
//����� ���� �Լ�:�μ��� �÷��̾� �� ��ġ �� �� ���� ����
void toll(int p);
//�� �μ� �Լ�: �μ��� �÷��̾� �� ��ġ �� �� �ι� ���� �� ������ ����
void acquisite(int p);
//���� �Լ�: �μ��� �÷��̾� �� ��ġ ���� �� ����
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

//�� �Լ�: �Ͽ� �ش��ϴ� �÷��̾� �ൿ ��ƾ
void turn(int p)
{
	printf("-----�÷��̾� %2d �� ��-------\n", p);
	move(p);
	toll(p);
	buy(p);
	acquisite(p);
	invest(p);
}

//���� �Լ�: �μ��� �÷��̾� �� ��ġ ���� �� ����
void invest(int p)
{
	int investflag = 0;
	int investcost;
	if (owner[position[p]] ==p)
	{
		printf("�÷��̾� %d��. %d ° ���� �����ϰڽ��ϱ�? 0.�ƴϿ�/1.��:",p, position[p]);
		scanf("%d", &investflag);
	}
	if (investflag)
	{
		printf("�÷��̾� %d��. %d ° ���� �󸶸� �����ϰڽ��ϱ�?:",p,position[p]);
		scanf("%d", &investcost);
		price[position[p]] += investcost;
		currency[p] -= investcost;
		printf("�÷��̾� %d �� %d ° ���� %d���� �����߽��ϴ�.\n", p, position[p],investcost);
		show();
	}
	
}

//�� �μ� �Լ�: �μ��� �÷��̾� �� ��ġ �� �� �ι� ���� �� ������ ����
void acquisite(int p)
{
	int acquisiteflag=0;
	if (owner[position[p]] >= 0 && owner[position[p]] != p)
	{
		printf("�÷��̾� %d��. �÷��̾� %d���Լ� %d ° ���� �μ��ϰڽ��ϱ�? 0.�ƴϿ�/1.��:", p, owner[position[p]], position[p]);
		scanf(" %d", &acquisiteflag);
	}
	if (acquisiteflag)
	{
		printf("�÷��̾� %d�� �÷��̾� %d���Լ� %d ° ���� �μ��մϴ�.\n", p, owner[position[p]], position[p]);
		currency[p] -= price[position[p]]*2;
		currency[owner[p]] += price[position[p]] * 2;
		owner[position[p]] = p;
		show();
	}

}
//�� ���� �Լ�:�μ��� �÷��̾� �� ��ġ �� ����
void buy(int p)
{
	int buyflag=0;
	if (owner[position[p]] < 0)
	{
		printf("�÷��̾� %d��. %d ° ���� �����ϰڽ��ϱ�? 0.�ƴϿ�/1.��:",p, position[p]);
		scanf("%d", &buyflag);
	}
	if (buyflag)
	{
		owner[position[p]] = p;
		printf("�÷��̾� %d �� %d ° ���� �����߽��ϴ�.\n", p, position[p]);
		show();
	}

}

//����� ���� �Լ�:�μ��� �÷��̾� �� ��ġ �� �� ���� ����
void toll(int p)
{
	if (owner[ position[p] ] >= 0 && owner[ position[p] ] != p)
	{
		printf("�÷��̾� %d �� %d ���� �÷��̾� %d���� �����մϴ�.\n", p, price[position[p]]/2, owner[p]);
		currency[p] -= price[position[p]]/2;
		currency[owner[p]] += price[position[p]]/2;
		
		show();
	}
}

//�÷��� �Լ� �� �ϸ��� ȣ��
void play(int i)
{
	int p = i%PLAYERN;
	printf("-----%3d° �÷���----------\n", i);
	turn(p);
}

//�÷��̾� �̵� �Լ�
//�μ��� �÷��̾� �̵�
//�Լ� ���ο��� �ֻ��� �Լ� ȣ��
void move(int p)
{
	int dice1, dice2;
	int sum;
	dice1 = dice();
	dice2 = dice();
	sum = dice1 + dice2;
	printf("�ֻ���1+�ֻ���2==%2d\n", sum);
	position[p] = (position[p] + sum) % LANDN;
	show();
}

//�ֻ��� �Ѱ� ��� ��ȯ �Լ�
int dice()
{
	int result;
	char buffer;
	srand(time(NULL));
	printf("�ֻ����� �������� �ƹ� ���̳� �Է�:");
	scanf(" %c", &buffer);
	result = rand() % 6 + 1;
	printf("���� ��:%2d\n", result);
	return result;
}

//�ε��� �ڱ� �հ� �Լ�
int assetsum(int p)
{
	int ass=0;
	for (int i = 0; i < LANDN; i++)
	{
		if (owner[i] == p)	ass += price[i];
	}
	return ass;
}

//�ʱ�ȭ �Լ�
//�� ������: -1
//�÷��̾� ����: ���۰�
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

//���÷��� �Լ�

//��, �÷��̾� ���� ���� �Լ�
void show()
{
	printf("========================================\n");
	showmap();
	printf("----------------------------------------\n");
	showplayer();
	printf("========================================\n");
}

//�÷��̾� ���� ����
void showplayer()
{
	for (int i = 0; i < PLAYERN; i++)
	{
		printf("�÷��̾� %2d\n", i);
		asset[i] = assetsum(i);
		printf("����ġ:%2d ����: %10d �ε���:%10d ����+�ε���==%d\n", position[i], currency[i], asset[i], currency[i]+asset[i]);
	}
}

//�� ���� ����
void showmap()
{
	for (int i = 0; i < LANDN; i++)
	{
		printf("����ȣ:%2d ����:%10d ������:%2d ", i, price[i], owner[i]);
		printf("�湮��:");
		for (int j = 0; j < PLAYERN; j++)
		{
			if (i == position[j])
				printf(" %d", j);
		}
		printf("\n");
	}
}



