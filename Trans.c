/*************************************************************************
> File Name: Trans.c
> Author: QRM
> Mail: 
> Created Time: 2018年01月02日 星期二 16时17分48秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 20
#define INFINITY 32768

//城市信息
typedef struct {
    int ID;//城市唯一的ID
    char name[20];//城市名称
}City;
//时刻表
typedef struct {
    char startCity[20]; //出发城市
    char endCity[20]; //到达城市
    char num[20];//车次
    char startTime[10]; //开始时间
    char endTime[10]; //结束时间
    int totalTime; //总时长
    int money; //金额
    int tran;//中转次数
    int distance;//距离
}Time;
//图结构
typedef struct {
    Time arcs[MAX]; //边集
    City vex[MAX]; //顶点集
    int vexnum; //顶点数目
    int arcnum; //边数目
    int Flag[MAX][MAX]; //矩阵标志
    int Money[MAX][MAX];
    int Time[MAX][MAX];
}AdjMatrix; //邻接矩阵


AdjMatrix G;
FILE *fp;
FILE *tp;
void show();//主界面
int Create(AdjMatrix *G);//创建图
void Set_time(AdjMatrix *G); //建立时刻表
void Show_G(AdjMatrix *G);//显示交通信息
void Master_show(); //管理界面
void User_show(); //用户界面
void City_show(); //城市信息界面
void Time_show(); //时刻表信息编辑
void Welcome_show();//退出界面
int  add_City(AdjMatrix *G); //添加城市信息
void modif_City(AdjMatrix *G); //修改城市信息
void add_Time(AdjMatrix *G);//添加时刻
void modify_Time(AdjMatrix *G);//修改时间
void search_City(AdjMatrix *G); //查询城市信息
void delete_City();//删除城市信息
void delete_CityById();//按照ID删除
void delete_CityByName();//按照名称删除
void lees_road(AdjMatrix *G);//路径最短
void less_money(AdjMatrix *G);//用钱最少
void less_tran(AdjMatrix *G);//时间次数最少
int FindMinDist(AdjMatrix *Graph, int dist[], int collected[]);
int Dijkstra(AdjMatrix *G,int dist[MAX], int path[MAX], int S);
int Dijkstra_M(AdjMatrix *G,int dist1[MAX], int path1[MAX], int S);
int Dijkstra_T(AdjMatrix *G,int dist2[MAX], int path2[MAX], int S);
//按照文件创建图
int Create(AdjMatrix *G) {
    FILE *c,*t;
    c = fopen("City.txt","r");
    t =fopen("Time.txt","r");
    int i,j;
    for(i = 1; i <= MAX; i++)
        for(j = 1; j <= MAX; j++){
                G->Flag[i][j] =INFINITY; //初始化
		G->Money[i][j] = INFINITY;}
    i = 1;
    if(c == NULL) 
    {
        printf("对不起，打开文件失败\n");
    }
    while(!feof(c))
    {
        fscanf(c,"%d",&G->vex[i].ID);
        fscanf(c,"%s",G->vex[i].name);
        i++;
    }
    G->vexnum = i-2;
    
    fclose(c);
    for(i = 1; i <= G->vexnum; i++)
        printf("%s  %d\n",G->vex[i].name,G->vex[i].ID);
    i =1;
    if(t == NULL)
        {
            printf("对不起，打开文件失败\n");
        }
        while(!feof(t))
    {
        fscanf(t,"%s %s %s %s %s %d %d %d",G->arcs[i].startCity,G->arcs[i].endCity,G->arcs[i].num,G->arcs[i].startTime,G->arcs[i].endTime,&G->arcs[i].totalTime,&G->arcs[i].money,&G->arcs[i].distance);
        i++;
    }
    G->arcnum = i -2;
    fclose(t);
    printf("城市总数目:%d 城市路线:%d\n",G->vexnum,G->arcnum);
    i = 1;
   //初始化
  
    //按照名称找ID，建立矩阵
    int m[20]={0};int n[20]; int k = 1;
    for(i = 1; i <= G->arcnum; i++){
        for(j = 1; j <= G->vexnum; j++)
            if(!strcmp(G->vex[j].name,G->arcs[i].startCity))
                {
                    
                    m[k++] = G->vex[j].ID;
                    break;
                }
    }
    
    k = 1;
    for(i = 1; i <= G->arcnum; i++)
    {
        for(j = 1; j <= G->vexnum; j++)
        if(!strcmp(G->vex[j].name,G->arcs[i].endCity))
        {   n[k++] = G->vex[j].ID;
            break;
        }
    }
    for(i = 1; i < k; i++)
            G->Flag[m[i]][n[i]] = G->arcs[i].distance;

   k = 1;
    for(i = 1; i <= G->arcnum; i++)
    {
        for(j = 1; j <= G->vexnum; j++)
        if(!strcmp(G->vex[j].name,G->arcs[i].endCity))
        {   n[k++] = G->vex[j].ID;
            break;
        }
    }
    for(i = 1; i < k; i++)
            G->Money[m[i]][n[i]] = G->arcs[i].money;
	k = 1;
    for(i = 1; i <= G->arcnum; i++)
    {
        for(j = 1; j <= G->vexnum; j++)
        if(!strcmp(G->vex[j].name,G->arcs[i].endCity))
        {   n[k++] = G->vex[j].ID;
            break;
        }
    }
    for(i = 1; i < k; i++)
            G->Money[m[i]][n[i]] = G->arcs[i].totalTime;
  }

//显示交通信息
void Show_G(AdjMatrix *G) {
    char ch;
    FILE *t,*c;
    t = fopen("Time.txt","r");
    c = fopen("City.txt","r");
    printf("**********城市交通路线总信息为:************\n");
    printf("ID           Name\n");       
    if(c == NULL) {
        printf("对不起，无法打开该文件\n");
    }
    else
    {
        fscanf(c,"%c",&ch);
        while(!feof(c))
        {
            putchar(ch);
            fscanf(c,"%c",&ch);
        }
        fclose(c);
    }
    printf("*******************************************\n\n\n\n");
    printf("*********************时刻表信息为:*****************************\n");
    printf("startCity  endCity    num   startTime   endTime   totalTime    money   distance\n");
    if(t == NULL) {
        printf("对不起，无法打开该文件\n");
    }
    else
    {
        fscanf(t,"%c",&ch);
        while(!feof(t))
        {
            putchar(ch);
            fscanf(t,"%c",&ch);
        }
        fclose(t);
    }
    printf("***************************************************************\n\n\n");
    
}
void Welcome_show() {
    printf("\t\t*****************\t\t\n");
    printf("\t\t    谢谢使用\t\t\n");
    printf("\t\t*****************\t\t\n");
}
void City_show() {
    int choice;
    printf("\t\t*****************\t\t\n");
    printf("\t\t1 添加\t\t\n");
    printf("\t\t2 删除\t\t\n");
    printf("\t\t3 修改\t\t\n");
    printf("\t\t4 查询\t\t\n");
    printf("\t\t5 返回上一层\t\t\n");
    printf("\t\t0 退出系统\t\t\n");
    printf("\t\t*****************\t\t\n");
    printf("请输入你的选择：\n");
    scanf("%d",&choice);
    while(choice!=1 && choice!= 2&& choice!=3 && choice!=4 && choice!= 5&&choice!=0) {
        printf("对不起,您输入的选择有误,请重新输入:\n");
        scanf("%d",&choice);
        printf("\n");
    }
    switch(choice) {
        case 1 : add_City(&G); break;
        case 2 : delete_City(); break;
        case 3 : modif_City(&G); break;
        case 4 : search_City(&G); break;
        case 5 : Master_show(); break;
        case 0 : Welcome_show(); break;
    }
}
//添加城市信息
int add_City(AdjMatrix *G) {
    City city;
    int choice;
    char c[20];
    int weight;
    int count;
    int flag = 1;
    fp = fopen("City.txt","a+");
    if(fp == NULL){
        return 0;
    }
    printf("请输入城市名称(输入0表示结束)\n");
    scanf("%s",city.name);
    while(flag!=0){
        count = G->vexnum;
        strcpy(G->vex[count+1].name, city.name);
        fprintf(fp,"%d               %s\n",count+1,city.name);
        printf("请输入终点城市:\n");
        scanf("%s",c);
        fprintf(fp,"%d               %s",count+2,c);
        strcpy(G->vex[count+2].name , c);
        printf("请输入距离:\n");
        scanf("%d",&weight);
        G->Flag[count+1][count+2] = weight;
        G->vexnum+=2;
        G->arcnum+=1;
        printf("要继续添加吗(0表示结束)?\n");
	scanf("%d",&flag);
        if(flag==0){
            //Show_G(G);
            City_show();
        } 
        else{ 
        printf("请输入要添加的城市名称\n");
        scanf("%s",city.name);
        }
    }
    fclose(fp);
    Show_G(G);
    return 1;
}
//添加时刻表
void add_Time(AdjMatrix *G) {
    tp = fopen("Time.txt","a+");
    int i,j;
    int flag =1;
    int choice;
    printf("请输入要添加时刻(即添加路线)的对应坐标(1 2)\n");
	scanf("%d%d",&i,&j);
    int count = G->arcnum +1;
    if(G->Flag[i][j]==INFINITY ) //两个顶点之间没有路径
        {   printf("请输入车次(K222)\n");
            scanf("%s",G->arcs[count].num);
            printf("请输入开始时间(16:25)\n");
            scanf("%s",G->arcs[count].startTime);
            printf("请输入结束时间(16:25)\n");
            scanf("%s",G->arcs[count].endTime);
            printf("请输入总时长(分钟):\n");
            scanf("%d",&G->arcs[count].totalTime);
            printf("请输入金额(100)\n");
            scanf("%d",&G->arcs[count].money);
            fprintf(tp,"%s    %s    %s    %s     %s     %d      %d      %d\n",G->vex[i].name,G->vex[j].name,G->arcs[count].num,G->arcs[count].startTime,G->arcs[count].endTime,G->arcs[count].totalTime,G->vexnum+1,G->arcs[count].money);
        fclose(tp);
         printf("还要继续添加吗？(0表示结束)\n");
        scanf("%d",&flag);
         while(flag!=0)
        {
            add_Time(G);
        }
    if(flag == 0)
        {
            Show_G(G);
            Time_show();
        }    
    }
    else 
    {
        printf("该城市间已有时刻表\n");
        printf("\t\t*************\t\t\n");
        printf("\t\t1 返回上一层\t\t\n");
        printf("\t\t2 修改时刻信息\t\t\n");
        printf("\t\t*************\t\t\n");
        scanf("%d",&choice);
        while(choice!=1&&choice!=2){
            printf("对不起，你输入的选择有误，请重新输入\n");
            scanf("%d",&choice);
        }
        switch(choice) {
            case 1:Time_show();break;
            case 2:printf("修改时刻信息\n");break;
            }
    }        
}

//删除城市信息
void delete_City() {
    int choice;

    printf("\t\t****************\t\t\n");
    printf("\t\t1 按照ID删除\t\t\n");
    printf("\t\t2 按照名称删除\t\t\n");
    printf("\t\t3 返回上一层\t\t\n");
    printf("\t\t****************\t\t");
    
    printf("请输入你的选择:");
    scanf("%d",&choice);
    while(choice != 1&&choice !=2&&choice!=3){
        printf("对不起,您输入的选择有误,请重新输入\n");
        scanf("%d",&choice);}
        switch(choice) {
        case 1:delete_CityById(&G);break;
        case 2:delete_CityByName(&G);break;
        case 3:City_show();break;
    }
}
//根据ID删除
void delete_CityById(AdjMatrix *G){
	int deleteID,i;
    printf("请输入你要删除的城市ID:\n");
    scanf("%d",&deleteID);
    int temp = 0;
    for(i = 1; i <= G->vexnum; i++)
	{
		if(G->vex[i].ID == deleteID)
			{
				temp = i;
				break;
			}
	}
    if(temp==0)
    {
        printf("输入的信息有误\n");
        Master_show();
    }
    else
    {
        for(i = temp; i<= G->vexnum-1; i++)
        {
            G->vex[i].ID = G->vex[i+1].ID;
            strcpy(G->vex[i].name,G->vex[i+1].name);
        }
    }
    G->vexnum -= 1;
    for(i = 1; i <= G->vexnum; i++)
    {
        printf("%d        %s\n",G->vex[i].ID,G->vex[i].name);
    }
    Master_show();
}
void delete_CityByName(AdjMatrix *G){
    char deleteName[20];
    int i;
    printf("请输入要删除的城市名称:\n");
    scanf("%s",deleteName);
    int found = 0;
    for(i = 1; i <= G->vexnum; i++)
    {
        if(strcmp(G->vex[i].name,deleteName) == 0)
        {
            found = i;break;
        }
    }
    if(found == 0)
    {
        printf("对不起，你输入的城市信息有误\n");
        Master_show();
    }
    else
    {
        for(i = found; i<= G->vexnum-1; i++)
        {
            G->vex[i].ID = G->vex[i+1].ID;
            strcpy(G->vex[i].name,G->vex[i+1].name);
        }
    }
    G->vexnum -= 1;
    for(i = 1; i <= G->vexnum; i++)
    {
        printf("%d        %s\n",G->vex[i].ID,G->vex[i].name);
    }
    Master_show();
}
//查询城市信息
void search_City(AdjMatrix *G) {
    char searchCity[20];
    printf("请输入要查询的出发城市名称\n");
    scanf("%s",searchCity);
    int i;
    int flag = 0;
    for(i = 1; i <= G->vexnum; i++)
        if(strcmp(searchCity,G->vex[i].name) == 0)
            flag = i;
    if(flag!=0) {
        for(i = 1; i <= G->vexnum; i++)
        if(G->Flag[flag][i]!=32768){
            printf("%s--------->%s:    %dkm\n",searchCity,G->vex[i].name,G->Flag[flag][i]);
            }

    }
    City_show();
}
//修改城市信息
void modif_City(AdjMatrix *G) {
    char city[20];
    int i;
    printf("请输入要修改的城市名称\n");
    scanf("%s",city);
    for(i = 1; i <= G->vexnum; i++) {
        if(strcmp(city,G->vex[i].name)==0)
        {
            printf("请输入该城市的更新信息\n");
            City_show();//不提供该模块，管理者可以通过添加和删除公功能实现
        }
    }
	City_show();
}
//修改时刻信息
void modify_Time(AdjMatrix *G) {
    char startCity[20];
    char endCity[20];
    int m,n;
    int i,j;
    int flag = 0;
    printf("请输入你要修改时刻的出发城市\n");
    scanf("%s",startCity);
    printf("请输入终点城市\n");
    scanf("%s",endCity);
    
    for(i = 1; i <= G->vexnum; i++) 
        if(!strcmp(startCity,G->vex[i].name))
    {
       m = i; flag = 1; break;
    }
    for(i = 1; i <= G->vexnum; i++)
    {
        if(!strcmp(endCity,G->vex[i].name))
        {
       n = i; flag = 1; break;
        }
    }
    if(flag == 0) 
    {
        printf("对不起，你输入的城市信息有误\n");
        Time_show();//进入时刻表主界面
    }
    for(i = 1; i <= G->arcnum; i++)
    {
        if(strcmp(startCity,G->arcs[i].startCity)==0&&strcmp(endCity,G->arcs[i].endCity)==0)
        {
            flag = i; break;
        }
    }
    printf("原有信息: ");
    printf("%s----->%s:%s %s %s %d %d %dkm\n",startCity,endCity,G->arcs[flag].num,G->arcs[flag].startTime,G->arcs[flag].endTime,G->arcs[flag].totalTime,G->arcs[flag].money,G->arcs[flag].distance);
    if(G->Flag[m][n]!=32768)
    {
        printf("请输入车次(K222)\n");
        scanf("%s",G->arcs[flag].num);
        printf("请输入开始时间(16:25)\n");
        scanf("%s",G->arcs[flag].startTime);
        printf("请输入结束时间(16:25)\n");
        scanf("%s",G->arcs[flag].endTime);
        printf("请输入总时长(分钟):\n");
        scanf("%d",&G->arcs[flag].totalTime);
        printf("请输入金额(100)\n");
        scanf("%d",&G->arcs[flag].money);
	printf("请输入距离\n");
	scanf("%d",&G->arcs[flag].distance);
        printf("更新信息后:\n");
       // printf("%s    %s    %s    %s     %s     %d      %d      %dkm\n",startCity,endCity,G->arcs[flag].num,G->arcs[flag].startTime,G->arcs[flag].endTime,G->arcs[flag].totalTime,G->arcs[flag].money,G->arcs[flag].distance);   
    }
    //Show_G(G);
    for(i = 1; i <= G->arcnum; i++)
    {
        printf("%s   %s   %s   %s   %s  %d  %d  %dkm\n",G->arcs[i].startCity,G->arcs[i].endCity,G->arcs[i].num,G->arcs[i].startTime,G->arcs[i].endTime,G->arcs[i].totalTime,G->arcs[i].money,G->arcs[i].distance);
    }
    Time_show();
}
//时刻表信息编辑界面

void Time_show(){
    int choice;
    printf("时刻表信息编辑\n");
    printf("\t\t*****************\t\t\n");
    printf("\t\t1 添加时刻信息\t\t\n");
    printf("\t\t2 修改时刻信息\t\t\n");
    printf("\t\t3 返回上一层\t\t\n");
    printf("\t\t4 返回主界面\t\t\n");
    printf("\t\t0 退出系统\t\t\n");
    printf("\t\t*****************\t\t\n");
    printf("请输入你的选择:\n");
    scanf("%d",&choice);
    
    while(choice!=1&&choice!=2&&choice!=3&&choice!=4&&choice!=0) {
        printf("对不起，你输入的选择有误，请重新输入\n");
        scanf("%d",&choice);
    }
    switch(choice) {
        case 1:add_Time(&G);break;
        case 2:modify_Time(&G);break;
        case 3:Master_show();break;
        case 4:show();break;
        case 0:Welcome_show();break;
    }
}
void Master_show() {
    int choice;
    printf("\t\t*****************\t\t\n");
    printf("\t\t1 城市信息编辑\t\t\n");
    printf("\t\t2 时刻表信息编辑\t\t\n");
    printf("\t\t3 返回上一层\t\t\n");
    printf("\t\t0 退出系统\t\t\n");
    printf("\t\t*****************\t\t\n");
    printf("请输入你的选择:(1 表示城市信息编辑,2 表示时刻表信息编辑，3 返回上一层,0表示退出系统)");
    scanf("%d",&choice);
    while(choice!=1&&choice!=2&&choice!=3&&choice!=0){

        printf("对不起,您输入的选择有误,请重新输入:\n");
        scanf("%d",&choice);}
        printf("\n");
        switch(choice) {
             case 1: City_show();break;
             case 2: Time_show();break;
             case 3:show();break;
             case 0:Welcome_show(); break;
             default:printf("对不起,您输入的选择有误,请重新输入");
    }
        
}
void User_show() {
    int choice;
    printf("\t\t******用户咨询界面****\t\t\n");
    printf("\t\t1 路线最短\t\t\n");
    printf("\t\t2 最省钱\t\t\n");
    printf("\t\t3 花费是时间次数最少\t\t\n");
    printf("\t\t4 查询城市信息\t\t\n");
    printf("\t\t5 返回主界面\t\t\n");
    printf("\t\t0 退出系统\t\t\n");
    printf("\t\t**********************\t\t\n");
    printf("请输入你的选择\n");
    scanf("%d",&choice);
    while(choice!=1&&choice!=2&&choice!=3&&choice!=4&&choice!=0&&choice!=5) {
        printf("对不起，您输入的选择有误,请重新输入\n");
        scanf("%d",&choice);
    }
    switch(choice) {
        case 1:lees_road(&G);break;
        case 2:less_money(&G);break;
        case 3:less_tran(&G);break;
        case 4: search_City(&G);break;
        case 5:show();break;
        case 0:Welcome_show();break;
    }
}
void show() {
    int choice;
    printf("\t\t*****************\t\t\n");
    printf("\t\t1 城市交通管理系统\t\t\n");
    printf("\t\t2 用户咨询系统\t\t\n");
    printf("\t\t0 退出系统\t\t\n");
    printf("\t\t*****************\t\t\n");
    printf("请输入你的选择:(1表示进入城市交通管理系统，2表示进入用户咨询系统，0表示退出\n)");
    scanf("%d",&choice);
    while(choice!=0&&choice!=1&&choice!=2) {
        printf("对不起,您输入的选择有误,请重新输入:");
        scanf("%d",&choice);
        printf("\n");
    }
    switch(choice) {
        case 1:Master_show(); break;
        case 2:User_show(); break;
        case 0:Welcome_show(); break;
        default:printf("对不起，您输入的选择有误，请重新输入：");
    }
}


//找出最小权值的顶点
int FindMinDist(AdjMatrix *Graph, int dist[], int collected[])
{
	int MinV, V;
	int MinDist = INFINITY;
	
	for(V = 1; V <= G.vexnum; V++){
		if(collected[V] == 0 && dist[V] < INFINITY ){
			MinDist = dist[V];
			MinV = V; 
		}
	}
	if(MinDist < INFINITY ) return MinV;
	else return -1;
}
//计算最短路径
int Dijkstra(AdjMatrix *G,int dist[MAX], int path[MAX], int S)
{
	int collected[MAX];
	int V, W,i;
	//初始化
	for(V = 1; V <= G->vexnum; V++){
		dist[V] = G->Flag[S][V];
		if(dist[V] < INFINITY ) path[V] = S;
		else path[V] = -1;
		collected[V] = 0;
	}
	while(1){
		V = FindMinDist(G, dist, collected);
		if(V == -1) break;
		collected[V] = 1;
		for(W = 1; W <= G->vexnum; W++){
			if(collected[W] == 0 && G->Flag[V][W] <INFINITY ){ 
				if(G->Flag[V][W] < 0) return 0;
				if(dist[V] + G->Flag[V][W] < dist[W]){ 
					dist[W] = dist[V] + G->Flag[V][W];
					path[W] = V;
				}
			}
		}
	}
	
	path[1] = -1;
	
	return 1;
}
void lees_road(AdjMatrix *G) {
    int i,j;
    int dist[MAX];
    int path[MAX];
    int startFlag = 0;
    int endFlag  = 0;
    char startCity[20],endCity[20];
    printf("请输入出发城市名称\n");
    scanf("%s",startCity);
    printf("请输入终点城市\n");
    scanf("%s",endCity);
    
    for(i =1; i <=G->vexnum; i++)
    {
        if(strcmp(startCity,G->vex[i].name) == 0)
        {
            startFlag = i;break;
        }
    }
    for(j = 1; j<=G->vexnum; j++)
        if(strcmp(endCity,G->vex[j].name) == 0)
    {
            endFlag = j; break;
    }
	//printf("出发城市:%s---", G->vex[startFlag].name);

	
	if(endFlag==0 || startFlag==0)	
    {
        printf("对不起，你输入的城市信息有误\n");
        User_show();}
	
	if(Dijkstra(G, dist, path, startFlag)){
		int temp = endFlag;
		if(path[temp] == -1){
			printf("%s<---", G->vex[temp].name);
			temp = path[temp];
		}
		printf("---%s", G->vex[startFlag].name);
		}
	printf("最短距离为%dkm\n",dist[endFlag]);
	User_show();
	
}
//计算最省钱路线
void less_money(AdjMatrix *G) {
    int i,j;
    int dist1[MAX];
    int path1[MAX];
    int startFlag = 0;
    int endFlag  = 0;
    char startCity[20],endCity[20];
    printf("请输入出发城市名称\n");
    scanf("%s",startCity);
    printf("请输入终点城市\n");
    scanf("%s",endCity);
    
    for(i =1; i <=G->vexnum; i++)
    {
        if(strcmp(startCity,G->vex[i].name) == 0)
        {
            startFlag = i;break;
        }
    }
    for(j = 1; j<=G->vexnum; j++)
        if(strcmp(endCity,G->vex[j].name) == 0)
    {
            endFlag = j; break;
    }
	//printf("出发城市:%s---", G->vex[startFlag].name);

	
	if(endFlag==0 || startFlag==0)	
    {
        printf("对不起，你输入的城市信息有误\n");
        User_show();}
	
	if(Dijkstra_M(G, dist1, path1, startFlag)){
		int temp = endFlag;
		if(path1[temp] == -1){
			printf("%s<---", G->vex[temp].name);
			temp = path1[temp];
		}
		printf("---%s", G->vex[startFlag].name);
		}
	printf("金额最少为%d元\n",dist1[endFlag]);
	User_show();
}
int Dijkstra_M(AdjMatrix *G,int dist1[MAX], int path1[MAX], int S)
{
	int collected[MAX];
	int V, W,i;
	//初始化
	for(V = 1; V <= G->vexnum; V++){
		dist1[V] = G->Money[S][V];
		if(dist1[V] < INFINITY ) path1[V] = S;
		else path1[V] = -1;
		collected[V] = 0;
	}
	while(1){
		V = FindMinDist(G, dist1, collected);
		if(V == -1) break;
		collected[V] = 1;
		for(W = 1; W <= G->vexnum; W++){
			if(collected[W] == 0 && G->Money[V][W] <INFINITY ){ 
				if(G->Flag[V][W] < 0) return 0;
				if(dist1[V] + G->Money[V][W] < dist1[W]){ 
					dist1[W] = dist1[V] + G->Money[V][W];
					path1[W] = V;
				}
			}
		}
	}
	
	path1[1] = -1;
	
	return 1;
}
void less_tran(AdjMatrix *G){
	 int i,j;
    int dist2[MAX];
    int path2[MAX];
    int startFlag = 0;
    int endFlag  = 0;
    char startCity[20],endCity[20];
    printf("请输入出发城市名称\n");
    scanf("%s",startCity);
    printf("请输入终点城市\n");
    scanf("%s",endCity);
    
    for(i =1; i <=G->vexnum; i++)
    {
        if(strcmp(startCity,G->vex[i].name) == 0)
        {
            startFlag = i;break;
        }
    }
    for(j = 1; j<=G->vexnum; j++)
        if(strcmp(endCity,G->vex[j].name) == 0)
    {
            endFlag = j; break;
    }
	//printf("出发城市:%s---", G->vex[startFlag].name);

	
	if(endFlag==0 || startFlag==0)	
    {
        printf("对不起，你输入的城市信息有误\n");
        User_show();}
	
	if(Dijkstra_T(G, dist2, path2, startFlag)){
		int temp = endFlag;
		if(path2[temp] == -1){
			printf("%s<---", G->vex[temp].name);
			temp = path2[temp];
		}
		printf("---%s", G->vex[startFlag].name);
		}
	printf("时间最少为%d分钟\n",dist2[endFlag]);
	User_show();
}
int Dijkstra_T(AdjMatrix *G,int dist2[MAX], int path2[MAX], int S)
{
	int collected[MAX];
	int V, W,i;
	//初始化
	for(V = 1; V <= G->vexnum; V++){
		dist2[V] = G->Money[S][V];
		if(dist2[V] < INFINITY ) path2[V] = S;
		else path2[V] = -1;
		collected[V] = 0;
	}
	while(1){
		V = FindMinDist(G, dist2, collected);
		if(V == -1) break;
		collected[V] = 1;
		for(W = 1; W <= G->vexnum; W++){
			if(collected[W] == 0 && G->Money[V][W] <INFINITY ){ 
				if(G->Flag[V][W] < 0) return 0;
				if(dist2[V] + G->Money[V][W] < dist2[W]){ 
					dist2[W] = dist2[V] + G->Money[V][W];
					path2[W] = V;
				}
			}
		}
	}
	
	path2[1] = -1;
	
	return 1;
}
int main() {
    
    Show_G(&G);//显示交通信息
    Create(&G);//建立无向图 
    show(); //主界面   
}
