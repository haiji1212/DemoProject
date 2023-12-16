/**
 * @file main.c
 * @author haiji
 * @brief ͼ��ݹ���ϵͳ��Ŀ
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
 * @brief �˺Ŷ������غ���
 * 
 */
#define MAX_NAME    7
#define MAX_PASSWORD    7
#define ID_BASE 10020  //�û���ʼid
#define ID_ADD  1
#define ADMIN_NAME  "admin"   //����Ա����
#define ADMIN_PW    "123456"    //����Ա����
typedef struct Users{
    int id;    //�û�id
    char name[MAX_NAME];    //�û�����
    char pw[MAX_PASSWORD];  //�û�����
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
 * @brief ͼ�鶨�����غ���
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
    int index;  //�鼮������
    char libname[MAX_LIB_NAME];    //�鼮����
    char authorname[MAX_LIB_AUTHOR];    //��������
    char publishname[MAX_LIB_PUBLISH];  //����������
    enum LibCategory category;  //�鼮���
    int num;    //�鼮������
}Libs;

/**
 * @brief ע���¼ҳ����ʾ
 * 
 */
void ShowAboutLogin(){
    printf("*******************************\n");
    printf("******* ��ӭʹ��LibSys ********\n");
    printf("******* ע�ᣬ������ 1 ********\n");
    printf("******* ��¼�������� 2 ********\n");
    printf("*******************************\n");
}

int IsLogin(int num){
    if(num == 1){
        Enroll();
    }else if(num == 2){
        Login();
    }else
    printf("������Ч\n");
    return 0;
}

/**
 * @brief ע��
 * 
 */
void Enroll(){
    Users NewUser, TempUser;
    FILE *fp;   //�����ļ���ָ��
    int get_time = 0;

    if((fp = fopen("users", "r")) == NULL){ //��ֻ����ʽ��users
        printf("��Чע��\n");
        return;
    }

    printf("\t��ӭ����ע��ҳ��!\n");
    printf("\t�������û���, ������λ\n");
    scanf("%6s", NewUser.name);

    while (fread(&TempUser, sizeof(Users), 1, fp) == 1) {
        if (strcmp(NewUser.name, TempUser.name) == 0) {
            printf("\t���û����Ѵ���,������ע��!\n");
            fclose(fp);
            return;
        }
        get_time ++;
    }
    fclose(fp);

    printf("\t����������, ������λ\n");
	scanf("%6s", NewUser.pw);

    NewUser.id = ID_BASE + ID_ADD * get_time;

    if((fp = fopen("users", "a")) == NULL){ //��д��ʽ��users�� w�Ḳ��ԭ�ļ����ݣ�������a
        printf("\t�˺�ע��ʧ��,������\n");
        return;
    }
    fwrite(&NewUser, sizeof(Users), 1, fp);
	printf("\t�˺�ע��ɹ�!\n");
    printf("\t����id��: %d\n", NewUser.id);
	fclose(fp);
	fp = NULL;
    return;
}

/**
 * @brief ��¼
 * 
 */
void Login(){
    Users OldUser, TempUser;
    FILE *fp;   //�����ļ���ָ��

    if((fp = fopen("users", "r")) == NULL){ //��ֻ����ʽ��users
        printf("��Ч��¼\n");
        return;
    }   

    printf("\t��ӭ������¼ҳ��!\n");
    printf("\t�������û���\n");
    scanf("%6s", OldUser.name);

    while (fread(&TempUser, sizeof(Users), 1, fp) == 1) {
        if (strcmp(OldUser.name, TempUser.name) == 0) {
            printf("\t����������, ������λ\n");
	        scanf("%6s", OldUser.pw);
            if(strcmp(OldUser.pw, TempUser.pw) == 0){
                printf("\t�˺ŵ�¼�ɹ�!\n");  
                printf("\t��ӭ%s!\n", TempUser.name);  
                printf("\t����idΪ%d!\n", TempUser.id);  
                fclose(fp);
                //todo:��¼֮��Ĳ˵���ʾ
                if(strcmp(TempUser.name, ADMIN_NAME) == 0){   //����ǹ���Ա���������Աҳ��
                    ShowAtAdmin();
                }  
                return;
            }
            else{
                printf("\t�����������,������!\n");  
                fclose(fp);
                return;                
            }
        }
    }
    printf("\t���˺�δע��,ע��������1,�˳�����������0\n");

    int get_status;
    scanf("%d", &get_status);

    if(get_status == 1) Enroll();
    return;
}

/**
 * @brief �޸�����
 * 
 */
void ChangePW(){
    Users OldUser, TempUser;
    FILE *fp;   //�����ļ���ָ��

    if((fp = fopen("users", "r+")) == NULL){ //�Զ�д��ʽ��users
        printf("��Ч����\n");
        return;
    }   

    printf("ȷ����Ҫ�޸�������?\n");
    printf("ȷ�ϵĻ�,���������û�������ȷ��:");
    scanf("%6s", OldUser.name);  

    while (fread(&TempUser, sizeof(Users), 1, fp) == 1) {
        if (strcmp(OldUser.name, TempUser.name) == 0) {
            printf("\t������������\n");
            scanf("%s", OldUser.pw);
            OldUser.id = TempUser.id;
            if(strcmp(OldUser.pw, TempUser.pw) == 0){   //��������ԭ����һ��
                printf("��������ԭ����һ�£������²���\n");
                return;
            }
            fseek(fp, -(int)(sizeof(Users)), SEEK_CUR); //�ӵ�ǰ�ļ�ָ��λ�ÿ�ʼ����ƫ��
            fwrite(&OldUser, sizeof(Users), 1, fp);
            printf("\t�����޸ĳɹ�!\n");
            fclose(fp);
            fp = NULL;
            break;
        }
    }
    return;
}

/**
 * @brief ������ҳ����ʾ
 * 
 */
void ShowAtAdmin(){
    printf("*************************************\n");
    printf("************* ���� Admin ************\n");
    printf("******** ���ͼ����,������ 1 ********\n");
    printf("********** ɾ��ͼ��,������ 2 *********\n");
    printf("********** ���ͼ��,������ 3 *********\n");
    printf("******** ����û���Ϣ,������ 4 ********\n");
    printf("*************************************\n");
    int get_flag = 0;   //����״ν���˲˵�
    while(1){
        if(get_flag){
            printf("********������һ��*********\n");
            printf("**** ���ͼ����,���� 1 ***\n");
            printf("**** ɾ��ͼ��,���� 2 ******\n");
            printf("**** ���ͼ��,���� 3 ******\n");
            printf("**** ����û���Ϣ,���� 4 ***\n");
            printf("**** ��������,�˳����� *****\n");
        }
        int get_num;
        scanf("%d", &get_num);
        get_flag = 1;
        switch(get_num){
            case 1: //���ͼ����
                ScanBook();
                break;
            case 2: //ɾ��ͼ��
                DeleteBook();
                break;
            case 3: //���ͼ��
                AddBook();
                break;
            case 4: //����û���Ϣ
                ScanUser();
                break;
            default:
                printf("�Զ��˳��ɹ�\n");
                return;
        }
    }
}

/**
 * @brief ���ͼ����Ϣ
 * 
 */
void ScanBook(){
    Libs TempBook;
    FILE *fp;   //�����ļ���ָ��

    if((fp = fopen("libs", "r")) == NULL){ //��ֻ����ʽ��libs
        printf("����ʧ��,������!\n");
        return;
    }   
    printf("*****LibSys ��ǰ�鼮*****\n");
    printf("ID\t����\t\t\t����\t\t\t������\t\t\t���\t\t\t�����\n");
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
 * @brief ɾ��ͼ��
 * 
 */
void DeleteBook(){
    Libs OldBook, TempBook;
    FILE *fp1, *fp2;   //�����ļ���ָ��

    if((fp1 = fopen("libs", "r")) == NULL){ //��ֻ����ʽ��libs
        printf("��Ч����,������!\n");
        return;
    }

    if((fp2 = fopen("templibs", "w")) == NULL){ //��ֻд��ʽ�½�templibs
        printf("��Ч����,������!\n");
        return;
    }

    printf("��������Ҫɾ����ͼ������\n");
    printf("ɾ��ͼ��:");
    scanf("%20s", OldBook.libname);

    while (fread(&TempBook, sizeof(Libs), 1, fp1) == 1) {
        if (strcmp(OldBook.libname, TempBook.libname) != 0) {   //��ǰͼ�鲻��Ŀ���鼮
            fwrite(&TempBook, sizeof(Libs), 1, fp2);
        }
    }
    fclose(fp1);
    fclose(fp2);
    remove("libs");
    rename("templibs","libs");
    printf("ɾ���ɹ���\n");
    return;
}

/**
 * @brief ���ͼ��
 * 
 */
void AddBook(){
    Libs NewBook, TempBook;
    FILE *fp;   //�����ļ���ָ��
    srand(time(NULL));  //��������ֵ

    if((fp = fopen("libs", "r")) == NULL){ //��ֻ����ʽ��libs
        printf("��Ч����,������!\n");
        return;
    }

    printf("�����������ͼ����Ϣ\n");
    printf("�����ͼ��:");
    scanf("%20s", NewBook.libname);

    while (fread(&TempBook, sizeof(Libs), 1, fp) == 1) {
        if (strcmp(NewBook.libname, TempBook.libname) == 0) {
            printf("������д���\n");
            //todo:��������Ȿ�飬������鼮������Ϣ
            fclose(fp);
            return;
        }
    }
    fclose(fp);

    printf("����:");
	scanf("%20s", NewBook.authorname);
    printf("������:");
	scanf("%20s", NewBook.publishname);
    printf("Science:1; Business:2; Poetry:3; Cookbook:4; Fiction:5\n");
    printf("ͼ�����:");
	scanf("%d", &NewBook.category);
    printf("�������:");
	scanf("%d", &NewBook.num);

    // ����һ���� [0, RAND_MAX] ��Χ�ڵ��������
    NewBook.index = rand();;

    if((fp = fopen("libs", "a")) == NULL){ //��д��ʽ��libs�� w�Ḳ��ԭ�ļ����ݣ�������a
        printf("\t���ʧ��,������\n");
        return;
    }
    fwrite(&NewBook, sizeof(Libs), 1, fp);
	printf("\t��ӳɹ�!\n");
	fclose(fp);
	fp = NULL;
    return;    
}

/**
 * @brief ����û���Ϣ
 * 
 */
void ScanUser(){
    Users TempUser;
    FILE *fp;   //�����ļ���ָ��

    if((fp = fopen("users", "r")) == NULL){ //��ֻ����ʽ��users
        printf("����ʧ��,������!\n");
        return;
    }   
    printf("*****LibSys �û�����*****\n");
    printf("ID\t�û���\t����\n");
    while (fread(&TempUser, sizeof(Users), 1, fp) == 1) {
        printf("%d\t%s\t%s\n", TempUser.id, TempUser.name, TempUser.pw);
    }
    fclose(fp);
    return;
}

/**
 * @brief ��ͨ�û�ҳ����ʾ
 * 
 */
void ShowAtUser(){
    printf("*******************************\n");
    printf("******* ���� xx ********\n");   //TODO:��Ҫ����ʵ���û���Ϣ
    printf("******* ���ͼ����,������ 1 ********\n");
    printf("******* ͼ���ѯ,������ 2 ********\n");
    printf("******* ����ͼ��,������ 3 ********\n");
    printf("******* �޸�����,������ 4 ********\n");
    printf("*******************************\n");
}

/**
 * @brief ������
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