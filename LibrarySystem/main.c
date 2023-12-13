/**
 * @file main.c
 * @author haiji
 * @brief 图书馆管理系统项目
 * @version 0.1
 * @date 2023-12-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include<stdio.h>
#include<string.h>
/**
 * @brief 账号定义和相关函数
 * 
 */
#define MAX_NAME    7
#define MAX_PASSWORD    7
#define ID_BASE 10020  //用户起始id
#define ID_ADD  1
typedef struct Users{
    int id;    //用户id
    char name[MAX_NAME];    //用户名字
    char pw[MAX_PASSWORD];  //用户密码
}Users;
void ShowAboutLogin();
int IsLogin(int num);
void Enroll();
void Login();

/**
 * @brief 注册登录页面显示
 * 
 */
void ShowAboutLogin(){
    printf("*******************************\n");
    printf("******* 欢迎使用LibSys ********\n");
    printf("******* 注册，请输入 1 ********\n");
    printf("******* 登录，请输入 2 ********\n");
    printf("*******************************\n");
}

int IsLogin(int num){
    if(num == 1){
        Enroll();
    }else if(num == 2){
        Login();
    }else
    printf("输入无效\n");
    return 0;
}

/**
 * @brief 注册
 * 
 */
void Enroll(){
    Users NewUser, TempUser;
    FILE *fp;   //访问文件的指针
    int get_time = 0;

    if((fp = fopen("users", "r")) == NULL){ //以只读方式打开users.txt
        printf("无效注册\n");
        return;
    }

    printf("\t欢迎来到注册页面!\n");
    printf("\t请输入用户名, 至多六位\n");
    scanf("%6s", &NewUser.name);

    while (fread(&TempUser, sizeof(Users), 1, fp) == 1) {
        if (strcmp(NewUser.name, TempUser.name) == 0) {
            printf("\t此用户名已存在,请重新注册!\n");
            fclose(fp);
            return;
        }
        get_time ++;
    }
    fclose(fp);

    printf("\t请输入密码, 至多六位\n");
	scanf("%6s", &NewUser.pw);

    NewUser.id = ID_BASE + ID_ADD * get_time;

    if((fp = fopen("users", "a")) == NULL){ //以写方式打开users.txt， w会覆盖原文件内容，这里用a
        printf("\t账号注册失败,请重试\n");
        return;
    }
    fwrite(&NewUser, sizeof(Users), 1, fp);
	printf("\t账号注册成功!\n");
    printf("\t您的id是: %d\n", NewUser.id);
	fclose(fp);
	fp = NULL;
    return;
}

/**
 * @brief 登录
 * 
 */
void Login(){
    Users OldUser, TempUser;
    FILE *fp;   //访问文件的指针

    if((fp = fopen("users", "r")) == NULL){ //以只读方式打开users.txt
        printf("无效登录\n");
        return;
    }   

    printf("\t欢迎来到登录页面!\n");
    printf("\t请输入用户名\n");
    scanf("%6s", &OldUser.name);

    while (fread(&TempUser, sizeof(Users), 1, fp) == 1) {
        if (strcmp(OldUser.name, TempUser.name) == 0) {
            printf("\t请输入密码, 至多六位\n");
	        scanf("%6s", &OldUser.pw);
            if(strcmp(OldUser.pw, TempUser.pw) == 0){
                printf("\t账号登录成功!\n");  
                printf("\t欢迎%s!\n", TempUser.name);  
                printf("\t您的id为%d!\n", TempUser.id);  
                fclose(fp);
                //todo:登录之后的菜单显示  
                return;
            }
            else{
                printf("\t密码输入错误,请重试!\n");  
                fclose(fp);
                return;                
            }
        }
    }
    printf("\t此账号未注册,注册请输入1,退出操作请输入0\n");

    int get_status;
    scanf("%d", &get_status);

    if(get_status == 1) Enroll();
    return;
}

/**
 * @brief 主函数
 * 
 * @return int 
 */
int main(){
    ShowAboutLogin();
    int login_flag;
    scanf("%d", &login_flag);
    IsLogin(login_flag);
    return 0;
}