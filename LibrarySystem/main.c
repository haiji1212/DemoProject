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
#include<stdlib.h>
#include<time.h>
/**
 * @brief 账号定义和相关函数
 * 
 */
#define MAX_NAME    7
#define MAX_PASSWORD    7
#define ID_BASE 10020  //用户起始id
#define ID_ADD  1
#define ADMIN_NAME  "admin"   //管理员名称
#define ADMIN_PW    "123456"    //管理员密码
typedef struct Users{
    int id;    //用户id
    char name[MAX_NAME];    //用户名字
    char pw[MAX_PASSWORD];  //用户密码
}Users;
void ShowAboutLogin();
int IsLogin(int num);
void Enroll();
void Login();
void ChangePW();
void ShowAtAdmin();
void ShowAtUser();
void ScanBook();
void DeleteBook();
void AddBook();
void ScanUser();

/**
 * @brief 图书定义和相关函数
 * 
 */
#define MAX_LIB_NAME    20
#define MAX_LIB_AUTHOR  20
#define MAX_LIB_PUBLISH 20
enum LibCategory{
    Science = 1,
    Business,   //2
    Poetry,     //3
    Cookbook,   //4
    Fiction,    //5
};
typedef struct Libs{
    int index;  //书籍索引号
    char libname[MAX_LIB_NAME];    //书籍名称
    char authorname[MAX_LIB_AUTHOR];    //作者名称
    char publishname[MAX_LIB_PUBLISH];  //出版商名称
    enum LibCategory category;  //书籍类别
    int num;    //书籍进库量
}Libs;

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

    if((fp = fopen("users", "r")) == NULL){ //以只读方式打开users
        printf("无效注册\n");
        return;
    }

    printf("\t欢迎来到注册页面!\n");
    printf("\t请输入用户名, 至多六位\n");
    scanf("%6s", NewUser.name);

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
	scanf("%6s", NewUser.pw);

    NewUser.id = ID_BASE + ID_ADD * get_time;

    if((fp = fopen("users", "a")) == NULL){ //以写方式打开users， w会覆盖原文件内容，这里用a
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

    if((fp = fopen("users", "r")) == NULL){ //以只读方式打开users
        printf("无效登录\n");
        return;
    }   

    printf("\t欢迎来到登录页面!\n");
    printf("\t请输入用户名\n");
    scanf("%6s", OldUser.name);

    while (fread(&TempUser, sizeof(Users), 1, fp) == 1) {
        if (strcmp(OldUser.name, TempUser.name) == 0) {
            printf("\t请输入密码, 至多六位\n");
	        scanf("%6s", OldUser.pw);
            if(strcmp(OldUser.pw, TempUser.pw) == 0){
                printf("\t账号登录成功!\n");  
                printf("\t欢迎%s!\n", TempUser.name);  
                printf("\t您的id为%d!\n", TempUser.id);  
                fclose(fp);
                //todo:登录之后的菜单显示
                if(strcmp(TempUser.name, ADMIN_NAME) == 0){   //如果是管理员，进入管理员页面
                    ShowAtAdmin();
                }  
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
 * @brief 修改密码
 * 
 */
void ChangePW(){
    Users OldUser, TempUser;
    FILE *fp;   //访问文件的指针

    if((fp = fopen("users", "r+")) == NULL){ //以读写方式打开users
        printf("无效操作\n");
        return;
    }   

    printf("确认需要修改密码吗?\n");
    printf("确认的话,请再输入用户名进行确认:");
    scanf("%6s", OldUser.name);  

    while (fread(&TempUser, sizeof(Users), 1, fp) == 1) {
        if (strcmp(OldUser.name, TempUser.name) == 0) {
            printf("\t请输入新密码\n");
            scanf("%s", OldUser.pw);
            OldUser.id = TempUser.id;
            if(strcmp(OldUser.pw, TempUser.pw) == 0){   //新密码与原密码一致
                printf("新密码与原密码一致，请重新操作\n");
                return;
            }
            fseek(fp, -(int)(sizeof(Users)), SEEK_CUR); //从当前文件指针位置开始计算偏移
            fwrite(&OldUser, sizeof(Users), 1, fp);
            printf("\t密码修改成功!\n");
            fclose(fp);
            fp = NULL;
            break;
        }
    }
    return;
}

/**
 * @brief 管理者页面显示
 * 
 */
void ShowAtAdmin(){
    printf("*************************************\n");
    printf("************* 您好 Admin ************\n");
    printf("******** 浏览图书库存,请输入 1 ********\n");
    printf("********** 删除图书,请输入 2 *********\n");
    printf("********** 添加图书,请输入 3 *********\n");
    printf("******** 浏览用户信息,请输入 4 ********\n");
    printf("*************************************\n");
    int get_num;
    scanf("%d", &get_num);
    if(get_num == 1){   //浏览图书库存
        ScanBook();
    }else if(get_num == 2){ //删除图书
        DeleteBook();
    }else if(get_num == 3){ //添加图书
        AddBook();
    }else if(get_num == 4){     //浏览用户信息
        ScanUser();
    }else{
        printf("操作无效!\n");
        return;
    }
}

/**
 * @brief 浏览图书信息
 * 
 */
void ScanBook(){
    Libs TempBook;
    FILE *fp;   //访问文件的指针

    if((fp = fopen("libs", "r")) == NULL){ //以只读方式打开libs
        printf("操作失败,请重试!\n");
        return;
    }   
    printf("*****LibSys 当前书籍*****\n");
    printf("ID\t书名\t\t\t作者\t\t\t出版社\t\t\t类别\t\t\t库存量\n");
    while (fread(&TempBook, sizeof(Libs), 1, fp) == 1) {
        char temp_category[10];
        switch(TempBook.category){
            case Science:
                strcpy(temp_category, "Science");
                break;
            case Business:
                strcpy(temp_category, "Business");
                break;
            case Poetry:
                strcpy(temp_category, "Poetry");
                break;
            case Cookbook:
                strcpy(temp_category, "Cookbook");
                break;
            case Fiction:
                strcpy(temp_category, "Fiction");
                break;
            default:
                break;
        }
        printf("%d\t%-20s\t%-20s\t%-20s\t%-20s\t%-10d\n", TempBook.index, TempBook.libname, TempBook.authorname, TempBook.publishname, temp_category, TempBook.num);
    }
    fclose(fp);
    return;
}

/**
 * @brief 删除图书
 * 
 */
void DeleteBook(){
    Libs OldBook, TempBook;
    FILE *fp1, *fp2;   //访问文件的指针

    if((fp1 = fopen("libs", "r")) == NULL){ //以只读方式打开libs
        printf("无效操作,请重试!\n");
        return;
    }

    if((fp2 = fopen("templibs", "w")) == NULL){ //以只写方式新建templibs
        printf("无效操作,请重试!\n");
        return;
    }

    printf("请输入需要删除的图书书名\n");
    printf("删除图书:");
    scanf("%20s", OldBook.libname);

    while (fread(&TempBook, sizeof(Libs), 1, fp1) == 1) {
        if (strcmp(OldBook.libname, TempBook.libname) != 0) {   //当前图书不是目标书籍
            fwrite(&TempBook, sizeof(Libs), 1, fp2);
        }
    }
    fclose(fp1);
    fclose(fp2);
    remove("libs");
    rename("templibs","libs");
    printf("删除成功！\n");
    return;
}

/**
 * @brief 添加图书
 * 
 */
void AddBook(){
    Libs NewBook, TempBook;
    FILE *fp;   //访问文件的指针
    srand(time(NULL));  //设置种子值

    if((fp = fopen("libs", "r")) == NULL){ //以只读方式打开libs
        printf("无效操作,请重试!\n");
        return;
    }

    printf("请输入新入库图书信息\n");
    printf("新入库图书:");
    scanf("%20s", NewBook.libname);

    while (fread(&TempBook, sizeof(Libs), 1, fp) == 1) {
        if (strcmp(NewBook.libname, TempBook.libname) == 0) {
            printf("书库已有此书\n");
            //todo:若书库有这本书，则更新书籍数量信息
            fclose(fp);
            return;
        }
    }
    fclose(fp);

    printf("作者:");
	scanf("%20s", NewBook.authorname);
    printf("出版社:");
	scanf("%20s", NewBook.publishname);
    printf("Science:1; Business:2; Poetry:3; Cookbook:4; Fiction:5\n");
    printf("图书类别:");
	scanf("%d", &NewBook.category);
    printf("入库数量:");
	scanf("%d", &NewBook.num);

    // 生成一个在 [0, RAND_MAX] 范围内的随机整数
    NewBook.index = rand();;

    if((fp = fopen("libs", "a")) == NULL){ //以写方式打开libs， w会覆盖原文件内容，这里用a
        printf("\t添加失败,请重试\n");
        return;
    }
    fwrite(&NewBook, sizeof(Libs), 1, fp);
	printf("\t添加成功!\n");
	fclose(fp);
	fp = NULL;
    return;    
}

/**
 * @brief 浏览用户信息
 * 
 */
void ScanUser(){
    Users TempUser;
    FILE *fp;   //访问文件的指针

    if((fp = fopen("users", "r")) == NULL){ //以只读方式打开users
        printf("操作失败,请重试!\n");
        return;
    }   
    printf("*****LibSys 用户名单*****\n");
    printf("ID\t用户名\t密码\n");
    while (fread(&TempUser, sizeof(Users), 1, fp) == 1) {
        printf("%d\t%s\t%s\n", TempUser.id, TempUser.name, TempUser.pw);
    }
    fclose(fp);
    return;
}

/**
 * @brief 普通用户页面显示
 * 
 */
void ShowAtUser(){
    printf("*******************************\n");
    printf("******* 您好 xx ********\n");   //TODO:需要传入实际用户信息
    printf("******* 浏览图书库存,请输入 1 ********\n");
    printf("******* 图书查询,请输入 2 ********\n");
    printf("******* 借阅图书,请输入 3 ********\n");
    printf("******* 修改密码,请输入 4 ********\n");
    printf("*******************************\n");
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