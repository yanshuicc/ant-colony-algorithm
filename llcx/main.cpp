#include <stdlib.h> 
#include<fstream>  
#include<iostream>
#include <stdio.h>  
#include <windows.h>  
#include <algorithm>
using namespace std;
//输出测试保存数据
#define OUT_DATA
//属性数目
#define ATT_NUM		7

// 节点数目 
#define NODE_NUM	92

//客户数量
#define USER_NUM	1000

//蚂蚁数量
#define ANT_NUM		10

// 运行次数
#define TOTAL		30

// alpha
#define ALPHA		1.5

//beta
#define BETA		1.0

// rou
#define ROU			0.7

//tau
#define TAU			3.0

//eta
#define ETA			1.0


int user_p[ATT_NUM][5] = {
						{35,80,95,100,-1},
						{69,100,-1},
						{42,100,-1},
						{15,95,100,-1},
						{40,55,100,-1},
						{24,49,79,100,-1},
						{21,100,-1} };

double AverageInitialCredit();
double init_credit(int i);
double fitness();
void InitialParameters();

char Att_name[ATT_NUM][8] = { "age.txt","sex.txt","mar.txt","edu.txt","hos.txt","pay.txt","owe.txt" };

// 属性对应的属性范围最大值
int r[ATT_NUM] = { 8,4,8,32,16,16,2 };

// 第p个属性域的信用权重为 m的节点
int Att[NODE_NUM][2]={
              {0,1},{0,2},{0,3},{0,4},{0,5},{0,6},{0,7},{0,8},
              {1,1},{1,2},{1,3},{1,4},
              {2,1},{2,2},{2,3},{2,4},{2,5},{2,6},{2,7},{2,8},
              {3,1},{3,2},{3,3},{3,4},{3,5},{3,6},{3,7},{3,8},{3,9},{3,10},{3,11},{3,12},{3,13},{3,14},{3,15},{3,16},
              {3,17},{3,18},{3,19},{3,20},{3,21},{3,22},{3,23},{3,24},{3,25},{3,26},{3,27},{3,28},{3,29},{3,30},{3,31},{3,32},
              {4,1},{4,2},{4,3},{4,4},{4,5},{4,6},{4,7},{4,8},{4,9},{4,10},{4,11},{4,12},{4,13},{4,14},{4,15},{4,16},
              {5,1},{5,2},{5,3},{5,4},{5,5},{5,6},{5,7},{5,8},{5,9},{5,10},{5,11},{5,12},{5,13},{5,14},{5,15},{5,16},
			  {6,1},{6,2}
                  };
//节点间信息素强度 和 下一节点期望 
double tau[NODE_NUM][NODE_NUM],eta[NODE_NUM][NODE_NUM];


int user[USER_NUM][ATT_NUM];	// 一千个客户
int user_credit[USER_NUM];

double alpha;
double beta;
double rou;

//平均初始信用度
double AverageInitialCredit_v;

int Tour[TOTAL][2];

struct Ant {
	int start, current;
	int allowed[ATT_NUM];
	int Tour[ATT_NUM][2];//当前路径
	int Node_Tour[ATT_NUM];
}ant[ANT_NUM];

double init_credit(int i) {
	int seed = GetTickCount();
	int sum = 0;
	for (int j = 0; j < ATT_NUM; j++) {
		srand(seed);
		int random_v = rand();
		seed = j * random_v;
		sum += random_v%r[i];
	}
	return (double)sum;
}

double fitness() {
	int num = 0;
	double fit[ANT_NUM];
	for (int m = 1; m < ANT_NUM; m++) {
		for (int i = 1; i < USER_NUM; i++) {
			if (init_credit(i) < AverageInitialCredit_v &&
				user[i][6] == 1)
				num = num + 1;
			if (init_credit(i) > AverageInitialCredit_v &&
				user[i][6] == 2)
				num = num + 1;
		}
		fit[m] = num / USER_NUM;
	}
	for (int i = 0; i < ANT_NUM; i++) {
		if (fit[i] > fit[0])
			fit[0] = fit[i];
	}
	return fit[0];
}

void InitialParameters() {
	cout << "InitialParameters()" << endl;
	cout << "alpha: " << ALPHA << " beta: " << BETA << " rou: " << ROU << " tau: " << TAU << " eta: " << ETA << endl;;
	alpha = ALPHA;
	beta = BETA;
	rou = ROU;
	for (int i = 0; i < NODE_NUM; i++) {
		for (int j = 0; j < NODE_NUM; j++) {
			tau[i][j] = TAU;
			eta[i][j] = ETA;
		}
	}
}

void ImportSamples() {
	cout << "ImportSamples()" << endl;
	int seed = GetTickCount();
	for (int i = 0; i < ATT_NUM; i++) {
		for (int j = 0; j<USER_NUM; j++) {
			srand(seed);
			int random_v = rand() % 100;
			seed = random_v + i*j + rand();
			for (int k = 0; user_p[i][k] != -1; k++)
				if (random_v < user_p[i][k]) {
					user[j][i] = k+1;
					break;
				}
		}
	}
#ifdef OUT_DATA
	ofstream data("data.txt");
	for (int i = 0; i < USER_NUM; i++)
	{
		for (int j = 0; j < ATT_NUM; j++) {
			data << user[i][j] << " ";
		}
		data << endl;
	}
	data.close();

	for (int i = 0; i < ATT_NUM; i++) {
		ofstream data(Att_name[i]);
		for (int j = 0; j < USER_NUM; j++) {
			data << user[j][i] << " ";
		}
		data.close();
	}
#endif
}

double AverageInitialCredit() {
	double sum = 0;
	for (int i = 0; i < ATT_NUM; i++) {
		sum += r[i];
	}
	cout << "AverageInitialCredit() return " << sum / ATT_NUM << endl;
	return sum / ATT_NUM;
}

void Initial_ant() {
	int seed = GetTickCount();
	for (int i = 0; i < ANT_NUM; i++) {
		srand(seed);
		int random_v = rand();
		seed = random_v * i;
		ant[i].start = ant[i].current = random_v % NODE_NUM;
		for (int j = 0; j < NODE_NUM; j++)
		{
			if (ant[i].start != j && Att[j][0]!=Att[ant[i].start][0])
				ant[i].allowed[j] = 1;
			else
				ant[i].allowed[j] = 0;
		}
		for (int j = 0; j < ATT_NUM; j++) {
			ant[i].Node_Tour[j] = -1;
			ant[i].Tour[j][0] = ant[i].Tour[j][1] = -1;
		}
	}
}

int FeelPheromone(int ant_num) {
	int next_node = -1;
	//Pheromone分母
	double sum= 0.0;
	int current = ant[ant_num].current;
	for (int i = 0; i < NODE_NUM; i++)
		if (ant[ant_num].allowed[i]) {
			sum += pow(tau[current][i], alpha) * pow(eta[current][i], beta);
		}

	srand((unsigned)GetTickCount());
	double p=(double)(rand()%100)/100;
	double probability = 0.0;

	for (int next = 0; next < NODE_NUM; next++) {
		if (current != next && ant[ant_num].allowed[next]==1) {
			double a = pow(tau[current][next], alpha) * pow(eta[current][next], beta);
			probability +=  a / sum;
			if(probability >= p || (p > 0.9999 && probability > 0.9999))
			{
				next_node = next;
				break;
			}
		}
	}
    return next_node;
}

void UpdatePheromone(){
	for (int i = 0; i < NODE_NUM; i++)
	{
		for (int j = 0; j < NODE_NUM; j++)
		{
			tau[i][j] *= (1 - rou);
		}
	}
	for (int i = 0; i < ANT_NUM; i++) {
		for (int j = 0; j < ATT_NUM; j++)
		{
			int a = ant[i].Tour[j][0];
			int b = ant[i].Tour[j][1];
			tau[a][b] += 1;
		}
	}
}

double MaxSolution(double fit[]){
	for (int i = 0; i < TOTAL; i++)
		if (fit[i] > fit[0])
			fit[0] = fit[i];
	return fit[0];
}

int test(){
	double fit[TOTAL];
    for(int i=0;i<TOTAL;i++){
		Initial_ant();
		for (int j = 0; j < NODE_NUM; j++) {
			for (int k = 0; k < ANT_NUM; k++) {
				int pass = FeelPheromone(k);
				ant[k].allowed[pass] = 0;
			}
		}

		UpdatePheromone();
		fit[i] = fitness();
	}        
	double result = MaxSolution(fit);
	printf("%lf",result);
    return 0;
}

int main() {
	InitialParameters();
	ImportSamples();
	AverageInitialCredit_v = AverageInitialCredit();
	double fit[TOTAL];
	for (int i = 0; i<TOTAL; i++) {
		Initial_ant();
		for (int j = 0; j < NODE_NUM; j++) {
			for (int k = 0; k < ANT_NUM; k++) {
				int pass = FeelPheromone(k);
				ant[k].allowed[pass] = 0;
			}
		}
	}
	system("PAUSE");
	return 0;
}