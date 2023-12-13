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
/**
 * @brief �˺Ŷ������غ���
 * 
 */
#define MAX_NAME    7
#define MAX_PASSWORD    7
#define ID_BASE 10020  //�û���ʼid
#define ID_ADD  1
typedef struct Users{
    int id;    //�û�id
    char name[MAX_NAME];    //�û�����
    char pw[MAX_PASSWORD];  //�û�����
}Users;
void ShowAboutLogin();
int IsLogin(int num);
void Enroll();
void Login();

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

    if((fp = fopen("users", "r")) == NULL){ //��ֻ����ʽ��users.txt
        printf("��Чע��\n");
        return;
    }

    printf("\t��ӭ����ע��ҳ��!\n");
    printf("\t�������û���, ������λ\n");
    scanf("%6s", &NewUser.name);

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
	scanf("%6s", &NewUser.pw);

    NewUser.id = ID_BASE + ID_ADD * get_time;

    if((fp = fopen("users", "a")) == NULL){ //��д��ʽ��users.txt�� w�Ḳ��ԭ�ļ����ݣ�������a
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

    if((fp = fopen("users", "r")) == NULL){ //��ֻ����ʽ��users.txt
        printf("��Ч��¼\n");
        return;
    }   

    printf("\t��ӭ������¼ҳ��!\n");
    printf("\t�������û���\n");
    scanf("%6s", &OldUser.name);

    while (fread(&TempUser, sizeof(Users), 1, fp) == 1) {
        if (strcmp(OldUser.name, TempUser.name) == 0) {
            printf("\t����������, ������λ\n");
	        scanf("%6s", &OldUser.pw);
            if(strcmp(OldUser.pw, TempUser.pw) == 0){
                printf("\t�˺ŵ�¼�ɹ�!\n");  
                printf("\t��ӭ%s!\n", TempUser.name);  
                printf("\t����idΪ%d!\n", TempUser.id);  
                fclose(fp);
                //todo:��¼֮��Ĳ˵���ʾ  
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