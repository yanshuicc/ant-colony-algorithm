#include <stdlib.h> 
#include<fstream>  
#include<iostream>
#include <stdio.h>  
#include <windows.h>  
#include <algorithm>
#include<math.h> 
using namespace std;
//输出测试保存数据
#define OUT_DATA

//属性数目
#define ATT_NUM		7

// 节点总数目  (8+4+8+32+16+16+2)
#define NODE_NUM	86

// 路径总数 (4+2+2+3+3+4+2)
#define LEVEL_NUM	20

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

//用户属性分布概率
int user_p[ATT_NUM][5] = {
						{35,80,95,100,-1},
						{69,100,-1},
						{42,100,-1},
						{15,95,100,-1},
						{40,55,100,-1},
						{24,49,79,100,-1},
						{21,100,-1} };

//属性分级
int user_level[ATT_NUM] = { 4,2,2,3,3,4,2 };

//随机数序列
int rand_int[TOTAL*LEVEL_NUM*ANT_NUM]; 

void Initial_ant();
double AverageInitialCredit();
double init_credit(int i, int m);
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
	int current;
	int allowed[ATT_NUM];
	int Tour[LEVEL_NUM][2];//当前路径
	int Node_Tour[LEVEL_NUM];
}ant[ANT_NUM];



int cmp(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;  //升序排序
}

double init_credit(int i,int m) {
	int sum = 0;
	int nodes[LEVEL_NUM];
	int c = 0;
	for (int j = 0; j < ATT_NUM; j++) {
		for (int k = 0; k < LEVEL_NUM; k++) {
			if (ant[m].Tour[k][0] == j) {
				nodes[c++] = ant[m].Tour[k][1];
			}
		}
		qsort(nodes+c-user_level[j], user_level[j], sizeof(int), cmp);
	}

	for (int j = 0; j < ATT_NUM; j++) {
		int v = user[i][j];
		int f = 0;
		for (int k = 0; k < j; k++) {
			f += user_level[k];
		}
		sum+=nodes[f + v-1];
	}
	return (double)sum;
}

double fitness() {
	int num;
	double fit[ANT_NUM];
	for (int i = 0; i < ANT_NUM; i++)
		fit[i] = -1;
	for (int m = 0; m < ANT_NUM; m++) {
		num = 0;
		for (int i = 1; i < USER_NUM; i++) {
			double init_credit_v = init_credit(i, m);
			if (init_credit_v < AverageInitialCredit_v &&
				user[i][6] == 1)
				num = num + 1;
			if (init_credit_v > AverageInitialCredit_v &&
				user[i][6] == 2)
				num = num + 1;
		}
		fit[m] = (double)num / USER_NUM;
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
	
	int seed = GetTickCount();
	for (int i = 0; i<TOTAL; i++) {
		for (int j = 0; j < LEVEL_NUM; j++) {
			for (int k = 0; k < ANT_NUM; k++) {
    			srand(seed);
    			seed=rand();
    			rand_int[i*j*ANT_NUM+j*ANT_NUM+k]=seed;
//    			printf("%d %d\n",i*j*ANT_NUM+k,seed);
			}
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
	return sum / ATT_NUM;
	//return sum / ATT_NUM;
}

void Initial_ant() {
	int seed = GetTickCount();
	for (int i = 0; i < ANT_NUM; i++) {
		srand(seed);
		int random_v = rand();
		seed = random_v + i;
		int Node_start = random_v % NODE_NUM;
		int start = Att[Node_start][0];
		for (int j = 0; j < ATT_NUM; j++)
		{
			ant[i].allowed[j] = user_level[j];
		}
		ant[i].Node_Tour[0] = Node_start;
		ant[i].Tour[0][0] = Att[Node_start][0];
		ant[i].Tour[0][1] = Att[Node_start][1];
		ant[i].allowed[ant[i].Tour[0][0]]--;
		for (int j = 1; j < LEVEL_NUM; j++) {
			ant[i].Node_Tour[j] = -1;
			ant[i].Tour[j][0] = ant[i].Tour[j][1] = -1;
		}
		ant[i].current = 0;
	}
}

int FeelPheromone(int ant_num,int rand_v) {
	int next_node = -1;
	//Pheromone分母
	double sum= 0.0;
	bool flag;
	int current = ant[ant_num].current;
	int current_node = ant[ant_num].Node_Tour[current];
	for (int next = 0; next < NODE_NUM; next++)
		if (ant[ant_num].allowed[Att[next][0]] > 0) {
			flag = FALSE;
			for (int i = 0; ant[ant_num].Node_Tour[i] != -1&&i<LEVEL_NUM; i++)
			{
				if (next == ant[ant_num].Node_Tour[i]) {
					flag = TRUE;
					break;
				}
			}
			if (flag) {
				continue;
			}
			sum += pow(tau[current_node][next], alpha) * pow(eta[current_node][next], beta);
		}

  
	double p=(double)(rand_v%1000)/1000;
//	if(ant_num==1)
//		printf("%d %lf\n",rand_v,p);
	double probability = 0.0;

	for (int next = 0; next < NODE_NUM; next++) {
		if (ant[ant_num].allowed[Att[next][0]] > 0) {
			flag = FALSE;
			for (int i = 0; ant[ant_num].Node_Tour[i] != -1 && i<LEVEL_NUM; i++)
			{
				if (next == ant[ant_num].Node_Tour[i]){
					flag = TRUE;
					break;
				}
			}
			if (flag) {
				continue;
			}
			double a = pow(tau[current_node][next], alpha) * pow(eta[current_node][next], beta);
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
			tau[i][j] *=  rou;
		}
	}
	for (int i = 0; i < ANT_NUM; i++) {
		for (int j = 0; j < LEVEL_NUM-1; j++)
		{
			int a = ant[i].Node_Tour[j];
			int b = ant[i].Node_Tour[j+1];
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

int main() {
	ofstream roads("roads.txt");
	InitialParameters();
	ImportSamples();
	AverageInitialCredit_v = AverageInitialCredit();
	double fit[TOTAL];
	for (int i = 0; i<TOTAL; i++) {
		Initial_ant();
		for (int j = 0; j < LEVEL_NUM-1; j++) {
			for (int k = 0; k < ANT_NUM; k++) {
				int pass = FeelPheromone(k,rand_int[i*j*ANT_NUM+j*ANT_NUM+k]);
				if (pass == -1) {
					cout << "error" << endl;
					system("PAUSE");
					return 0;
				}
				//else {
				//	if (k == 1&& i==0)
				//	{
				//		cout << "i times:" << i << ";  j forward:" << j << ";  k ant:" << k << ";  passed:" << pass << endl;
				//	}
				//}
				ant[k].Node_Tour[j+1] = pass;
				ant[k].allowed[Att[pass][0]]--;
				ant[k].Tour[j+1][0] = Att[pass][0];
				ant[k].Tour[j+1][1] = Att[pass][1];
				ant[k].current++;
			}
		}
		/*out every ant node*/
		for (int j = 0; j < ANT_NUM; j++) 
		{
			for (int k = 0; k < LEVEL_NUM;k++)
				roads << ant[j].Node_Tour[k] << " ";
			roads << endl;
		}

		UpdatePheromone();
		fit[i] = fitness();
	}
	roads.close();
	double result = MaxSolution(fit);
	printf("%lf", result);
	system("PAUSE");
	return 0;
}
