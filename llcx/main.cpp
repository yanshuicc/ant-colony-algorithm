#include<list>
using namespace std;
/**
 * ������Ŀ
 */
#define ATT_NUM		7

/**
 * ������Χ
 */
#define ATT_DOMAIN	5

/**
 * �ͻ�����
 */
#define USER_NUM	1000

 /**
 * ��������
 */
#define ANT_NUM


enum ATT_NAME {
	age,
	sex,
	marry,
	edu,
	house,
	job,
	pay,
	relationship				// �����й�ϵ
};

// ��p�������������Ȩ��Ϊ m�Ľڵ�
struct Node{
	int att_num;
	int weight;
}Att[ATT_NUM][32];

int r[ATT_NUM] = {8,4,8,32,16,16,8};					// ���Զ�Ӧ�����Է�Χ���ֵ
list<Node> allowed;
list<Node> passed;

int user[USER_NUM][ATT_NUM];	// һǧ���ͻ�
int user_credit[USER_NUM];

double alpha, beta;

int C[1000];	//
int O[1000];	//�Ƿ�ǷǮ
int fit[1000];



int init_credit(int i) {
	int sum = 0;
	for (int j = 0; j < ATT_NUM; j++)
		sum += ??;
	return sum;
}


int AVG_init_credit() {
	int sum = 0;
	for (int i = 0; i < ATT_NUM; i++) {
		sum += r[i];
	}
	return sum / ATT_NUM;
}

void fitness() {
	int I;
	int M, N= USER_NUM;
	int num = 0;
	for (int m = 1; m < M; m++) {
		for (int i = 1; i < USER_NUM; i++) {
			if (init_credit(i) < AVG_init_credit() &&
				O[i] == 1)
				num = num + 1;
			if (init_credit(i) > AVG_init_credit() &&
				O[i] == 0)
				num = num + 1;
		}
		fit[m] = num / USER_NUM;
	}
}

void InitialParameters() {
	alpha = 1.5;
	beta = 1.0;
	
}

void ImportSamples() {

}

void AverageInitialCredit() {

}

void CreateNodeDiagram() {

}


void selectNextNode() {

}

void init_ant() {

}

void run() {

}
