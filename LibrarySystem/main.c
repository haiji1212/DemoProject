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
#define MAX_ID  7
#define MAX_PASSWORD    7
typedef struct Users{
    char id[MAX_ID];    //用户id
    char pw[MAX_PASSWORD];  //用户密码
}Users;
void ShowAboutLogin();
int IsLogin(int num);
void Enroll();

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
        //TODO:注册
        Enroll();
    }else if(num == 2){
        //TODO:登录
    }else
    printf("输入无效\n");
    return 0;
}

/**
 * @brief 注册函数
 * 
 */
void Enroll(){
    Users NewUser, TempUser;
    FILE *fp;   //访问文件的指针

    if((fp = fopen("users.txt", "r")) == NULL){ //以只读方式打开users.txt
        printf("无效注册\n");
        return;
    }

    printf("\t欢迎来到注册页面!\n");
    printf("\t请输入 ID, 至多六位\n");
    scanf("%6s", &NewUser.id);

    while (fread(&TempUser, sizeof(Users), 1, fp) == 1) {
        if (strcmp(NewUser.id, TempUser.id) == 0) {
            printf("\t此id已存在,请重新注册!\n");
            fclose(fp);
            return;
        }
    }
    fclose(fp);

    printf("\t请输入 密码, 至多六位\n");
	scanf("%6s", &NewUser.pw);

    if((fp = fopen("users.txt", "a")) == NULL){ //以写方式打开users.txt， w会覆盖原文件内容，这里用a
        printf("\t账号注册失败,请重试\n");
        return;
    }

    fwrite(&NewUser, sizeof(Users), 1, fp);
	printf("\t账号注册成功!\n");
	fclose(fp);
	fp = NULL;
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