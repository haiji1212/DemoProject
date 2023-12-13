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
#define MAX_ID  7
#define MAX_PASSWORD    7
typedef struct Users{
    char id[MAX_ID];    //�û�id
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

    if((fp = fopen("users.txt", "r")) == NULL){ //��ֻ����ʽ��users.txt
        printf("��Чע��\n");
        return;
    }

    printf("\t��ӭ����ע��ҳ��!\n");
    printf("\t������ ID, ������λ\n");
    scanf("%6s", &NewUser.id);

    while (fread(&TempUser, sizeof(Users), 1, fp) == 1) {
        if (strcmp(NewUser.id, TempUser.id) == 0) {
            printf("\t��id�Ѵ���,������ע��!\n");
            fclose(fp);
            return;
        }
    }
    fclose(fp);

    printf("\t������ ����, ������λ\n");
	scanf("%6s", &NewUser.pw);

    if((fp = fopen("users.txt", "a")) == NULL){ //��д��ʽ��users.txt�� w�Ḳ��ԭ�ļ����ݣ�������a
        printf("\t�˺�ע��ʧ��,������\n");
        return;
    }

    fwrite(&NewUser, sizeof(Users), 1, fp);
	printf("\t�˺�ע��ɹ�!\n");
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

    if((fp = fopen("users.txt", "r")) == NULL){ //��ֻ����ʽ��users.txt
        printf("��Ч��¼\n");
        return;
    }   

    printf("\t��ӭ������¼ҳ��!\n");
    printf("\t������ ID, ������λ\n");
    scanf("%6s", &OldUser.id);

    while (fread(&TempUser, sizeof(Users), 1, fp) == 1) {
        if (strcmp(OldUser.id, TempUser.id) == 0) {
            printf("\t������ ����, ������λ\n");
	        scanf("%6s", &OldUser.pw);
            if(strcmp(OldUser.pw, TempUser.pw) == 0){
                printf("\t�˺ŵ�¼�ɹ�!\n");  
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