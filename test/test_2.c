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
void less_tran(AdjMatrix *G);//中转次数最少
void Dijkstra(AdjMatrix *G,int startFlag,int endFlag,int dist[],int path[][MAX]);//计算最短路线
/*int Create(AdjMatrix *G) {
    int i,j,k,weight,vex1,vex2;
    char city[20];
   // FILE *fp;
    int sum = 0;
    fp = fopen("City.txt","ab");
    fprintf(fp,"ID                  Name\n");
    printf("请输入交通图中的城市数目和路线总数:\n");
    scanf("%d%d",&G->vexnum,&G->arcnum);
    for(i = 1; i <= MAX; i++)
        for(j = 1; j <= MAX; j++)
                G->arcs[i][j] = 0; //初始化
    printf("请输入交通图中的%d个城市名\n",G->vexnum);
    for(i = 1; i <= G->vexnum; i++) {
        printf("请输入第%d各城市的名称:",i);
        scanf("%s",G->vex[i].name);
        fprintf(fp,"%d                %s\n",i,G->vex[i].name);
    }
    fclose(fp);
    printf("请输入交通图中的%d条路线:\n",G->arcnum);
    for(k = 0; k < G->arcnum&&sum<=G->arcnum; k++) {
        int n;
        printf("\nNo.%d边坐标:\n",k+1);
        printf("请输入该城市所能到达的总路线数目:\n");
        scanf("%d",&n);
        sum+=n;
        for(i = 1; i <= n; i++){
        printf("请输入点坐标\n(1 1)\n");
        scanf("%d",&vex1);     
        scanf("%d",&vex2);
        printf("两城市间的距离:");
        scanf("%d",&weight);
        G->arcs[vex1][vex2] = weight;
      //  G->arcs[vex2][vex1] = weight;//有向图
        
        }

    }
        printf("邻接矩阵:\n");
    for(i = 1; i <= G->vexnum; i++){
                for(j = 1; j <= G->vexnum; j++)
                printf("%4d ",G->arcs[i][j]);
                printf("\n");
            
    }

}*/
//按照文件创建图
int Create(AdjMatrix *G) {
    FILE *c,*t;
    c = fopen("City.txt","r");
    t =fopen("Time.txt","r");
    int i,j;
    for(i = 1; i <= MAX; i++)
        for(j = 1; j <= MAX; j++)
                G->Flag[i][j] = 0; //初始化
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
            G->Flag[m[i]][n[i]] = 1;
    //输出
    for(i = 1; i <= G->vexnum; i++)
    {      for(j = 1; j <= G->vexnum; j++)
            printf("%4d",G->Flag[i][j]);
            printf("\n");
    }
  }

//建立时刻表
 
void Set_time(AdjMatrix *G){
    int i, j;
    Time time;
   // FILE *tp;
    tp = fopen("Time.txt","wb");
    fprintf(tp,"startCity \tendCity \tnum \tstartTime  \tendTime  \ttotalTime  \t money\tdistance\n");
    for(i = 1; i <= G->vexnum; i++)
        for(j = 1; j <= G->vexnum; j++)
    {
        if(G->Flag[i][j]!=0) //两个顶点之间有路径

        {
            printf("请输入%s---->%s之间的时刻表信息\n",G->vex[i].name,G->vex[j].name);
            printf("请输入车次(K222)\n");
            scanf("%s",time.num);
            printf("请输入开始时间(16时25分)\n");
            scanf("%s",time.startTime);
            printf("请输入结束时间(16时25分)\n");
            scanf("%s",time.endTime);
            printf("请输入总时长(分钟):\n");
            scanf("%d",&time.totalTime);
            printf("请输入金额(100)\n");
            scanf("%d",&time.money);
          //  fputs(G->vex[i].name,tp);
           // fputs(G->vex[j].name,tp);
            fprintf(tp,"%s   \t %s    \t%s    \t%s   \t%s    \t%d    \t%d    \t%d\n",G->vex[i].name,G->vex[j].name,time.num,time.startTime,time.endTime,time.totalTime,time.money,time.distance);
        }
        
    }
    fclose(tp);
}
//显示交通信息
void Show_G(AdjMatrix *G) {
    char ch;
    FILE *t,*c;
    t = fopen("Time.txt","r");
    c = fopen("City.txt","r");
    printf("**********城市交通路线总信息为:************\n");
    printf("ID          Name\n");
   /* int i,j;
    for(i = 1; i <= G->vexnum; i++)
        for(j = 1; j <= G->vexnum; j++)
    if(G->arcs[i][j]!=0){
        printf("\t\t%s---------->%s:      %dkm\t\t\n",G->vex[i].name,G->vex[j].name,G->arcs[i][j]);
        */
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
    //AdjMatrix *G;
    char c[20];
    int weight;
    int count;
   // FILE *fp;
    int flag = 1;
    fp = fopen("City.txt","a+");
   // fprintf(fp,"ID                Name\n");
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
        fprintf(fp,"%d               %s\n",count+2,c);
        strcpy(G->vex[count+2].name , c);
        printf("请输入距离:\n");
        scanf("%d",&weight);
        G->Flag[count+1][count+2] = weight;
        G->vexnum+=2;
        G->arcnum+=1;
        printf("要继续添加吗(0表示结束)?\n");
	scanf("%d",&flag);
        if(flag==0){
            Show_G(G);
            City_show();
        } 
        else{ 
        printf("请输入要添加的城市名称\n");
        scanf("%s",city.name);
        }
    }
    fclose(fp);
    return 1;
}
//添加时刻表
void add_Time(AdjMatrix *G) {
  //  AdjMatrix *G;
    Time time;
   // FILE *tp;
    tp = fopen("Time.txt","a+");
    int i,j;
    int flag =1;
    int choice;
    printf("请输入要添加时刻的对应坐标(1 2)\n");
	scanf("%d%d",&i,&j);
       
    if(G->Flag[i][j]==0) //两个顶点之间没有路径
        {   printf("请输入车次(K222)\n");
            scanf("%s",time.num);
            printf("请输入开始时间(16:25)\n");
            scanf("%s",time.startTime);
            printf("请输入结束时间(16:25)\n");
            scanf("%s",time.endTime);
            printf("请输入总时长(分钟):\n");
            scanf("%d",&time.totalTime);
            printf("请输入金额(100)\n");
            scanf("%d",&time.money);
            fprintf(tp,"%s   \t%s    \t%s    \t%s   \t%s    \t%d    \t%d    \t%d\n",G->vex[i].name,G->vex[j].name,time.num,time.startTime,time.endTime,time.totalTime,G->vexnum+1,time.money);
        printf("还要继续添加吗？(0表示结束)\n");
        scanf("%d",&flag);
         while(flag!=0){
             add_Time(G);
            }
         if(flag == 0){
            fclose(tp);
            Show_G(G);
            Time_show();
        }
    else {
        printf("该城市间已有时刻表\n");
        printf("\t\t*************\t\t\n");
        printf("\t\t1 返回上一层\t\t\n");
        printf("\t\t2 修改时刻信息\t\\t\n");
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

    fclose(tp);
}}

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
void delete_CityById(AdjMatrix *G){
    int deleteID;
    printf("请输入你要删除的城市ID:\n");
    scanf("%d",&deleteID);
    FILE *fSource,*fpTemp;
    fSource = fopen("City.txt","r");//原文件
    fpTemp = fopen("Temp.txt","w");//临时文件
    char buf[4096]; //每读取一行放到该数组中
    int i = 0;
    while(!feof(fSource)) {
        i++;
        if(i == deleteID)
        {
            fgets(buf,sizeof(buf),fSource);//移动文件指针
        }
        else{
            fgets(buf,sizeof(buf),fSource);
            fprintf(fpTemp,"%s",buf);
        }
        fclose(fSource);
        fclose(fpTemp);
        fpTemp = fopen("Temp.txt","r");
        //清空原文件
        fSource =fopen("City.txt","wb");
        fclose(fSource);
        
        fSource = fopen("City.txt","a");
        while(!feof(fpTemp))
        {
            fgets(buf,sizeof(buf),fpTemp);
            fprintf(fp,"%s",buf);
        }
        fclose(fSource);
        fclose(fpTemp);
       // system("ERASE Temp.txt");
        Show_G(G);
    }

}
void delete_CityByName(AdjMatrix *G){
    char deleteName[20];
    printf("请输入要删除的城市名称:\n");
    scanf("%s",deleteName);
    int found = 0;

}
//查询城市信息
void search_City(AdjMatrix *G) {
    char searchCity[20];
    printf("请输入要查询的城市名称\n");
    scanf("%s",searchCity);
    int i;
    int flag = 0;
    for(i = 1; i <= G->vexnum; i++)
        if(strcmp(searchCity,G->vex[i].name) == 0)
            flag = i;
    if(flag!=0) {
        for(i = 1; i <= G->vexnum; i++)
        if(G->Flag[flag][i]!=0){
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
}
//修改时刻信息
void modify_Time(AdjMatrix *G) {
    
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
        case 2:printf("修改时刻信息\n");break;
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
    printf("\t\t3 中转次数最少\t\t\n");
    printf("\t\t4 返回主界面\t\t\n");
    printf("\t\t0 退出系统\t\t\n");
    printf("\t\t**********************\t\t\n");
    printf("请输入你的选择\n");
    scanf("%d",&choice);
    while(choice!=1&&choice!=2&&choice!=3&&choice!=4&&choice!=0) {
        printf("对不起，您输入的选择有误,请重新输入\n");
        scanf("%d",&choice);
    }
    switch(choice) {
        case 1:lees_road(&G);break;
       // case 2://less_money(&G);break;
       // case 3://less_tran(&G);break;
        case 4:show();break;
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

void lees_road(AdjMatrix *G) {
    int i,j;
    int dist[MAX],path[MAX][MAX] = {0};
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
        
  //  printf("%d   %d\n",startFlag,endFlag);
    if(endFlag!=0 && startFlag!=0)
        Dijkstra(G,startFlag,endFlag,dist,path);
    else
    {
        printf("对不起，你输入的城市信息有误\n");
        User_show();
    }
}
//采用Dijkstra算法求从起点到终点城市的最短路径
void Dijkstra(AdjMatrix *G, int startFlag,int endFlag,int dist[], int path[][MAX])
{
    int mindist,i,j,k,t =1;
    printf("计算最短路线:\n");
    printf("%d\n",G->vexnum);
    for(i = 1; i <= G->vexnum; i++) 
    {
        dist[i] = G->Flag[startFlag][i]; //初始化
        if(G->Flag[startFlag][i] != 0)
                path[i][1] = startFlag;
    }

    path[startFlag][0] = 1;
    for(i = 2; i <= G->vexnum; i++) 
    {
        mindist = 0;
        for(j = 1; j <= G->vexnum; j++)
        {
            if(!path[j][0]&&dist[j]>mindist)//选择权值最小的路线
            {
                k = j;
                mindist = dist[j];
            }
            if(mindist == 0) break;
            path[k][0] = 1;
            for(j = 1; j <= G->vexnum; j++)//修改路线
            {
                if(!path[j][0]&&G->Flag[k][j]!=0&&dist[k]+G->Flag[k][j]<dist[j])
                {
                    dist[j] = dist[k] + G->Flag[k][j];
                    t =1;
                    while(path[k][t] != 0) //记录最新的最短路线
                    {
                        path[j][t] == path[k][t];
                        t++;
                    }
                    path[j][t] = k;
                }
            }
        }
    }
    
    for(i = 1; i <= G->vexnum; i++)
    
    if(i == endFlag) return;
    printf("%s------->%s的最短路线为:从%s", G->vex[startFlag].name,G->vex[endFlag].name,G->vex[startFlag].name);
       for(j = 2;path[i][j]!=0; j++)
         
        printf("-->%s",G->vex[path[i][j]].name);
   printf("-->%s,距离为%dkm\n",G->vex[endFlag].name,dist[i]);
    
    User_show();
}
//计算最省钱路线
void less_money(AdjMatrix *G) {
    
}
int main() {
  //  AdjMatrix G;
    
    Show_G(&G);//显示交通信息
    Create(&G);//建立无向图
    //Set_time(&G);//建立时刻表
    
    show(); //主界面   
}
