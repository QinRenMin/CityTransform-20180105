/*************************************************************************
> File Name: Trans.c
> Author: QRM
> Mail: 
> Created Time: 2018年01月02日 星期二 16时17分48秒
 ************************************************************************/

#include<stdio.h>
#define MAX 20
#define INFINITY 32768
//城市信息
typedef struct {
    int ID;//城市唯一的ID
    char name[20];//城市名称
}City;

//图结构
typedef struct {
    int arcs[MAX][MAX]; //边集
    City vex[MAX]; //顶点集
    int vexnum; //顶点数目
    int arcnum; //边数目
}AdjMatrix; //邻接矩阵

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
}Time;
AdjMatrix G;
void show();//主界面
int Create(AdjMatrix *G);//创建图
void Set_time(AdjMatrix *G); //建立时刻表
void Master_show(); //管理界面
void User_show(); //用户界面
void City_show(); //城市信息界面
void Time_show(); //时刻表信息编辑
void Welcome_show();//退出界面
int add_City(); //添加城市信息
void add_Time();//添加时刻
void delete_City();//删除城市信息
int delete_CityById();//按照ID删除
int delete_CityByName();//按照名称删除

int Create(AdjMatrix *G) {
    int i,j,k,weight,vex1,vex2;
    char city[20];
    FILE *fp;
    fp = fopen("City.txt","wb1");
    fprintf(fp,"ID                  Name\n");
    printf("请输入交通图中的城市数目和路线总数:\n");
    scanf("%d%d",&G->vexnum,&G->arcnum);
    for(i = 1; i <= G->vexnum; i++)
        for(j = 1; j <= G->vexnum; j++)
                G->arcs[i][j] = 0; //初始化
    printf("请输入交通图中的%d个城市名\n",G->vexnum);
    for(i = 1; i <= G->vexnum; i++) {
        printf("请输入第%d各城市的名称:",i);
        scanf("%s",G->vex[i].name);
        fprintf(fp,"%d                %s\n",i,G->vex[i].name);
    }
    fclose(fp);
    printf("请输入交通图中的%d条路线:\n",G->arcnum);
    for(k = 0; k < G->arcnum; k++) {
        int n;
        printf("\nNo.%d边坐标:\n",k+1);
        printf("请输入该城市所能到达的总路线数目:\n");
        scanf("%d",&n);
        for(i = 1; i <= n; i++){
        
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

}
//建立时刻表

void Set_time(AdjMatrix *G){
    int i, j;
    Time time;
    FILE *tp;
    tp = fopen("Time.txt","wb");
    fprintf(tp,"startCity \tendCity \tnum \tstartTime  \tendTime  \ttotalTime  \ttran  money\n");
    for(i = 1; i <= G->vexnum; i++)
        for(j = 1; j <= G->vexnum; j++)
    {
        if(G->arcs[i][j]!=0) //两个顶点之间有路径
        {   printf("请输入车次(K222)\n");
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
            fprintf(tp,"%s   \t %s    \t%s    \t%s   \t%s    \t%d    \t%d    \t%d\n",G->vex[i].name,G->vex[j].name,time.num,time.startTime,time.endTime,time.totalTime,i,time.money);
        }
        
    }
    fclose(tp);
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
    printf("请输入你的选择：");
    scanf("%d",&choice);
    while(choice!=1 && choice!= 2&& choice!=3 && choice!=4 && choice!= 5) {
        printf("对不起,您输入的选择有误,请重新输入:");
        scanf("%d",&choice);
        printf("\n");
    }
    switch(choice) {
        case 1 :if( add_City()){
            printf("添加城市信息成功");
        } else {printf("添加城市信息失败\n");}; break;
        case 2 :delete_City(); break;
        case 3 : printf("3\n"); break;
       // case 4 : show_City(); break;
        case 5 : Master_show(); break;
        case 0 : Welcome_show(); break;
    }
}
//添加城市信息
int add_City() {
    City city;
    AdjMatrix *G;
    char c[20];
    int weight;
    int count;
    FILE *fp;
    fp = fopen("City.txt","wb");
   // fprintf(fp,"ID                Name\n");
    if(fp == NULL){
        return 0;
    }
    printf("请输入城市名称(输入0表示结束)\n");
   // scanf("%d",&city.ID);
    scanf("%s",city.name);
    while(city.name!=0){
        count = G->vexnum;
        fprintf(fp,"%d               %s\n",count+1,city.name);
        printf("请输入终点城市:\n");
        scanf("%s",c);
        printf("请输入距离:\n");
        scanf("%d",&weight);
        G->arcs[count+1][count+2] = weight;
        G->vexnum+=2;
        
        printf("请输入要添加的城市名称(0表示结束)");
        scanf("%s",city.name);
    }
    fclose(fp);
    return 1;
}
//添加时刻表
void add_Time() {
    AdjMatrix *G;
    Time time;
    FILE *tp;
    tp = fopen("Time.txt","wb");
    
    
        if(G->arcs[G->vexnum][G->vexnum]!=0) //两个顶点之间有路径
        {   printf("请输入车次(K222)\n");
            scanf("%s",time.num);
            printf("请输入开始时间(16时25分)\n");
            scanf("%s",time.startTime);
            printf("请输入结束时间(16时25分)\n");
            scanf("%s",time.endTime);
            printf("请输入总时长(分钟):\n");
            scanf("%d",&time.totalTime);
            printf("请输入金额(100)\n");
            scanf("%d",&time.money);
            fprintf(tp,"%s   \t %s    \t%s    \t%s   \t%s    \t%d    \t%d    \t%d\n",G->vex[G->vexnum].name,G->vex[G->vexnum].name,time.num,time.startTime,time.endTime,time.totalTime,G->vexnum+1,time.money);
        }
        
    
    fclose(tp);
}
//删除城市信息
void delete_City() {
    int choice;

    printf("\t\t****************\t\t");
    printf("\t\t1 按照ID删除\t\t\n");
    printf("\t\t2 按照名称删除\t\t\n");
    printf("\t\t3 返回上一层\t\t\n");
    printf("\t\t****************\t\t");
    
    printf("请输入你的选择:");
    scanf("%d",&choice);
    while(choice != 1&&choice !=2&&choice!=3){
        printf("对不起,您输入的选择有误,请重新输入\n");
        scanf("%d",&choice);
    }
    switch(choice) {
        case 1:if(delete_CityById()) printf("删除城市信息成功\n");
                else
                     printf("删除信息失败\n");break;
        case 2:if(delete_CityByName()) printf("删除城市信息成功\n");
                else
                    printf("删除信息失败\n");break;
        case 3:City_show();break;
    }
}
int delete_CityById(){
    int deleteID;
    printf("请输入你要删除的城市ID:\n");
    scanf("%d",&deleteID);
    FILE *fpSource,*fpTemp;
    int found = 0;

    return found;

}
int delete_CityByName(){
    char deleteName[20];
    printf("请输入要删除的城市名称:\n");
    scanf("%s",deleteName);
    int found = 0;

    return found;
}
//修改城市信息

void Time_show(){
    printf("时刻表信息编辑\n");

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

        printf("对不起,您输入的选择有误,请重新输入:");
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
    printf("用户咨询\n");
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
int main() {
  //  AdjMatrix G;
    Create(&G);//建立无向图
    Set_time(&G);//建立时刻表
    show(); //主界面
    
}
