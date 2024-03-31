#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <time.h> 



struct staff *createlist()//�������� 
{
	struct staff* headnode = (struct staff*)malloc(sizeof(struct staff));
	headnode->next = NULL;
	headnode->staff_id = 0;
	s = headnode;
	return headnode;
}

void addstaff(struct staff *f,int staff_id,char *staff_name,int staff_star,char *idt)//����Ա�� 
{
	struct staff* frontnode=s,*list;
    list=f;
    struct staff* newnode = (struct staff*)malloc(sizeof(struct staff));
    frontnode->next=newnode;
    newnode->next=NULL;
    newnode->staff_id=frontnode->staff_id+1;
	strcpy(newnode->staff_name,staff_name);
	newnode->staff_star=staff_star;
	strcpy(newnode->idt,idt);
	newnode->next = NULL;
	s = newnode;
}

void info_staff(struct staff* f) //չʾԱ����Ϣ /
{
	f = f->next;
	printf("*******************************\n");
	printf("#����\t����\t�Ǽ�\tְҵ  #\n");
	while(f != NULL)
	{
		printf("#%d\t%s\t%d\t%s#\n",f->staff_id,f->staff_name,f->staff_star,f->idt);
		f = f->next;
	}
	printf("*******************************\n\n");
}

void firestaff(struct staff *f,char* staff_name)//����Ա�� 
{
	struct staff *front,*list;
	list = f;
	do {
		front = f;
		f = f->next;
	}while (f!=NULL&&strcmp(f->staff_name,staff_name)!=0);
	if (f!=NULL)	
	{
		front->next=f->next;
		free(f); 
		front=front->next;
		while(front!=NULL)
		{
			front->staff_id--;
			front=front->next;
		}
		printf("ɾ���ɹ�\n");
	}else printf("������Ч�������Ƿ���ȷ\n\n");
}

int staffsearch(struct staff* f,char* staff_name)//����Ա�� 
{
	struct staff* list=f;//�˴�list���ڱ���ԭ������׵�ַ 
	int word=0;
	char name[30],idt[15],i[100],j[100];
	int id,star;
	printf("********************************************************\n");
	printf("#                        �������                      #\n");
	printf("#Ա������\tԱ��ID\t\tԱ���Ǽ�\tԱ��ְҵ#\n#\t\t\t\t\t#\n");
	while(f!=NULL)
	{
		if(strcmp(f->staff_name,staff_name)==0){
			printf("#%s\t%d\t\t%d\t%s#\n#\t\t\t\t\t#\n",f->staff_name,f->staff_id,f->staff_star,f->idt);
			word=1;
		}
        f=f->next;
	}
	if(word==0) printf("#                      Not  Found                      #\n");
	printf("********************************************************\n\n");
	if(word==0)
	{
		while(1){
			printf("#        �Ƿ񽫸�Ա������˵���         #\n");
			printf("#                 1.��                  #\n");
			printf("#                 0.��                  #\n");
			printf("*****************************************\n\n");
			scanf("%s",i) ;
			if(strcmp(i,"1")==0){
				printf("��������Ϣ:\n");
				printf("Ա��id��");
				scanf("%d",&id);
				printf("Ա���Ǽ�:");
				scanf("%d",&star);
				printf("Ա��ְҵ:");
				scanf("%s",idt);
				addstaff(list,id,name,star,idt);	
			//	info_staff(list);
				break;
			}else if(strcmp(i,"1")!=0&&strcmp(i,"0")!=0)
			{
				printf("��ֻ������0/1\n\n"); 
			}else break;
		}	
	}else{
		while(1){
			printf("*****************************************\n");
			printf("#        �Ƿ���Ҫ�޸ĸ�Ա����Ϣ��       #\n");
			printf("#                 1.��                  #\n");
			printf("#                 0.��                  #\n");
			printf("*****************************************\n");
			scanf("%s",i) ;
			system("cls");
			if(i[1]!=0){
				printf("��ֻ������0/1\n\n");
			}else{
				if(i[0]-'0'==1){
					while(1){
						printf("*****************************************\n");
						printf("#          ����Ҫ�޸��ĸ���Ŀ��         #\n");
						printf("#               0.������                #\n");
						printf("#                 1.id                  #\n");
						printf("#                2.ְҵ                 #\n");
						printf("*****************************************\n\n");
						scanf("%s",j) ;
						if(j[1]!=0){
							system("cls");
							printf("��ֻ������0/1/2\n\n");
						}else{
							if(j[0]-'0'==0)break; 
							switch(j[0]-'0'){
								case 1:
									printf("����д�޸ĺ��id��");
									scanf("%d",&f->staff_id);
									printf("�޸ĳɹ�\n");
									printf("*****************************************\n");
									printf("#%s\t%d\t\t%d\t%s#\n#\t\t\t\t\t#\n",f->staff_name,f->staff_id,f->staff_star,f->idt);
									printf("*****************************************\n");
									break;
								case 2:
									printf("����д�޸ĺ�����ࣺ");
									scanf("%s",f->idt);
									printf("�޸ĳɹ�\n");
									printf("*****************************************\n");
									printf("#%s\t%d\t\t%d\t%s#\n#\t\t\t\t\t#\n",f->staff_name,f->staff_id,f->staff_star,f->idt);
									printf("*****************************************\n");
									break;
								default:
									printf("��ֻ������0/1/2\n\n"); break;	
							}
						}
					}
				}else printf("��ֻ������0/1\n\n");
			}
			system("pause");
			system("cls");
		}
	}
	return word;
}

void printstaffmanage()
{
	printf("*****************************************\n");
	printf("#         ��ӭ����Ա������ģ��          #\n");
	printf("*****************************************\n\n");
}

void choice_staffmanage(struct staff* f)//Ա�������ܲ˵� 
{
	system("cls");
	int ret,id,star;
	char name[30],idt[15],choice[100];
	struct staff* list=f;//�˴�list���ڱ���ԭ������׵�ַ 
	while(1){
		printstaffmanage();
		f=list;//ÿ��ѭ�����轫f�ָ�ָ��ԭ������׵�ַ  
		info_staff(list); 
		printf("*****************************************\n");
		printf("#               Ա������                #\n");
		printf("#\t\t\t\t\t#\n");
		printf("#              0.�˳�ģ��               #\n");
		printf("#           1.��ѯ������Ա��            #\n");
		printf("#              2.ɾ��Ա��               #\n");
		printf("*****************************************\n");
		scanf("%s",choice);
		if(choice[1]!=0){
			system("cls");
			printf("��ֻ������0/1/2\n\n");
		}else{
			if(choice[0]=='0'){
				system("cls");
				break;
			}
			switch(choice[0]-'0')
			{
				case 0:	break;
				case 1:
					printf("����Ա����Ϣ��\n");
					printf("Ա�����ƣ�");
					scanf("%s",name);
					system("cls");
					staffsearch(f,name);
				//	system("pause");
					system("cls");
					break;
				case 2:
					printf("��д������Ҫɾ����Ա����\n");
					scanf("%s",name);
					firestaff(f,name);
				//	info_staff(f);
					system("pause");
					system("cls");
					break;
				default:
					system("cls");
					printf("��ֻ������0/1/2\n\n");break;
			}
		}
	}
}









