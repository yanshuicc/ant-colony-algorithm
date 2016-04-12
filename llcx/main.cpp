#include<list>
#include <stdlib.h> 
#include <time.h>
using namespace std;
/**
 * 属性数目
 */
#define ATT_NUM		7

/**
 * 属性域范围
 */
#define ATT_DOMAIN	5

/**
 * 节点数目 
 */
#define NODE_NUM 92

/**
 * 客户数量
 */
#define USER_NUM	1000

 /**
 * 蚂蚁数量
 */
#define ANT_NUM

/**
 * 运行时刻 
 */
#define TOTAL 10


enum ATT_NAME {
	age,
	sex,
	marry,
	edu,
	house,
	job,
	pay
};

// 第p个属性域的信用权重为 m的节点
int Att[NODE_NUM][2]={
              {0,1},{0,2},{0,3},{0,4},{0,5},{0,6},{0,7},{0,8},
              {1,1},{1,2},{1,3},{1,4},
              {2,1},{2,2},{2,3},{2,4},{2,5},{2,6},{2,7},{2,8},
              {3,1},{3,2},{3,3},{3,4},{3,5},{3,6},{3,7},{3,8},{3,9},{3,10},{3,11},{3,12},{3,13},{3,14},{3,15},{3,16},
              {3,17},{3,18},{3,19},{3,20},{3,21},{3,22},{3,23},{3,24},{3,25},{3,26},{3,27},{3,28},{3,29},{3,30},{3,31},{3,32},
              {4,1},{4,2},{4,3},{4,4},{4,5},{4,6},{4,7},{4,8},{4,9},{4,10},{4,11},{4,12},{4,13},{4,14},{4,15},{4,16},
              {5,1},{5,2},{5,3},{5,4},{5,5},{5,6},{5,7},{5,8},{5,9},{5,10},{5,11},{5,12},{5,13},{5,14},{5,15},{5,16},
              {6,1},{6,2},{6,3},{6,4},{6,5},{6,6},{6,7},{6,8},
                  };
//节点间信息素强度 和 下一节点期望 
dobule tau[NODE_NUM][NODE_NUM],eta[NODE_NUM][NODE_NUM];

int r[ATT_NUM] = {8,4,8,32,16,16,8};					// 属性对应的属性范围最大值
list<int[2]> allowed;
list<int[2]> passed;

int user[USER_NUM][ATT_NUM];	// 一千个客户
int user_credit[USER_NUM];

double alpha, beta;

int C[1000];	//
int O[1000];	//是否欠钱
int fit[1000];



int init_credit(int i) {
    srand((unsigned)time(NULL));
    int random_v = rand();
	int sum = 0;
	for (int j = 0; j < ATT_NUM; j++)
		sum += random_v%r[i];
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
void initial_ant(dboule tao, dobule) {

}

double FeelPheromone(int i, int j, int t) {
     if (i!=j){
        return (pow(tau[i][j],alpha) * pow(eta[i][j], beta));          
     }
     return 0;
}
void UpdatePheromone(){

}


void maxsolution(){
     
}

int main(){
    for(int i=0;i<TOTAL;i++){
		while(){
			FeelPheromone();
		}
		for(int j=0;j<ANT_NUM;j++){
			fitness();
		}
		UpdatePheromone();
		SaveRoundMaxSolution();
	}        
	maxsolution(); 
    return 0;
}
