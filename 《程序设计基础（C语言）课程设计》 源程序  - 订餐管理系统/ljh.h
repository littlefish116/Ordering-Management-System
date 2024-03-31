/*#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "cl.h"
#include "lzy-n.h"
#include "lss.h"*/
char managekey[30];
FILE *fkey;

//#include "sort.h"

FILE *food;//���ڴ洢�˵����ı��ļ��� 

int meal_kind_cmp(struct meal *a,struct meal *b)
{
	if(a->order[0]==b->order[0])
	if(a->order[2]==b->order[2])return a->price<b->price;
	else return a->order[2]<b->order[2];
	else return a->order[0]<b->order[0];
}

void printtitle_forum()
{
	printf("============================================\n");
	printf("\t��ӭ���붩�͹���ϵͳ          \n");
	printf("\t��ѡ������Ҫ�ķ���           \n");
	printf("\t0.�˳�ϵͳ               \n");
	printf("\t1.�ͻ��˵�¼              \n");
	printf("\t2.����Ա��¼              \n");
	printf("\t3.��ѯ����               \n");
	printf("============================================\n");
}


void printmealmanage()
{
	printf("*****************************************\n");
	printf("#         ��ӭ����˵�����ģ��          #\n");
	printf("*****************************************\n\n");
}

int givenum(char* kind)
{
	int end=0;
	if(strcmp("��ʳ",kind)==0)end+=100;
	else if(strcmp("���",kind)==0)end+=200;
	else if(strcmp("�ز�",kind)==0)end+=300;
	else if(strcmp("��Ʒ",kind)==0)end+=400;
	else if(strcmp("С��",kind)==0)end+=500;
	struct meal* node=meal_head->next;
	while(node->next!=NULL){
		if(strcmp(kind,node->kind)==0)end+=1;
		node=node->next;
	}
	if(strcmp(kind,node->kind)==0)end+=1; 
	end+=1;
	return end;
}

void start_menu()
{
	iniHashTable(haxi_meal);
	meal_head=(struct meal *)malloc(sizeof(struct meal));
	meal_head->next=NULL;
	struct meal *node,*pre=meal_head;
	FILE *food=NULL;
	food=fopen("menu.txt","r");
//	printf("���ڴ��ļ������Ժ�......\n");
	if(food==NULL)//Ҫ��û�򿪾�ֱ��return 
	{
		printf("�ļ���ʧ��\n");
		return;
	}
//	else printf("�ļ��򿪳ɹ�����ʼͬ����Ʒ��Ϣ\n"); 
	while(!feof(food))//��ͷ��ʼ���ļ���ֱ��������β 
	{
		node=(struct meal *)malloc(sizeof(struct meal));//�����ַ 
		//�����ļ�������ݴ浽������ 
		fscanf(food,"%s%s%s%s%s",node->order,node->name,node->kind,node->cprice,node->crank);
		node->num=cl_CtoN(node->order); 
		node->rank=cl_CtoN(node->crank);
		node->price=CtoF(node->cprice);
		insertEntry(haxi_meal,node->name,node);//��ӽ����ϣ�� 
		insertEntry(haxi_meal,node->order,node);
		node->next=pre->next;//�������� 
		pre->next=node;//ͬ�� 
		pre=pre->next;//ͬ��	
//		printf("%s\n",pre->name);//��һ�۲�����ɶ 
	}	
	meal_end=pre;
	sort(meal_head,NULL,"meal",meal_kind_cmp);
//	printf("��Ʒ��Ϣͬ������\n");
	fclose(food);
}

void printmeal(struct meal* s)//��ӡ�˵� 
{
	start_menu();
	s=meal_head->next; 
	fflush(stdin);
	printf("*****************************************\n");
	printf("#���\t����\t\t����\t����/Ԫ\t#\n#\t\t\t\t\t#\n");
    while(s!=NULL)
    {
        if(strlen(s->name)<8) printf("#%d\t%s\t\t%s\t%.2f\t#\n",s->num,s->name,s->kind,s->price);
		else printf("#%d\t%s\t%s\t%.2f\t#\n",s->num,s->name,s->kind,s->price);
        s=s->next;
    }
    printf("*****************************************\n\n");
}

void addmeal(char *name,char *kind,float price)//������������Ԫ�أ���Ʒ�� 
{
	fflush(stdin);
	int word=0;
	struct meal* frontnode=meal_end;
	char order[10],cprice[50],ckind[30]={0};
	if (kind[1]==0){
		switch(kind[0]-'0'){
			case 1:strcpy(ckind,"��ʳ");word=1;break;
			case 2:strcpy(ckind,"���");word=1;break; 
			case 3:strcpy(ckind,"�ز�");word=1;break;
			case 4:strcpy(ckind,"��Ʒ");word=1;break;
			case 5:strcpy(ckind,"С��");word=1;break;
			default:printf("������������\n"); break; 
		}
	}else {
		printf("������������\n"); 
	}
	if(word==1){
		struct meal* newnode=(struct meal*)malloc(sizeof(struct meal));
    	newnode->next=meal_head->next;
    	meal_head->next=newnode;
    	fflush(stdin);
    	newnode->num=givenum(ckind);
    	strcpy(newnode->name,name);
    
    	strcpy(newnode->kind,ckind);
    	newnode->price=price;
    	newnode->rank=0;
    	meal_end=newnode;
    	fflush(stdin);
//		printf("���ڴ��ļ������Ժ�......\n");
  		food=fopen("menu.txt","a");
  		if(food==NULL)
		{
			printf("�ļ���ʧ��,�޷���ӡ�\n");
			return;
		}
//		else printf("�ļ��򿪳ɹ�����ʼ��Ӳ�Ʒ��Ϣ\n");
//    printf("\n%d   %s     %s     %.2f     %d\n",newnode->num,name,kind,price,newnode->rank);
		fprintf(food,"\n%d   %s     %s     %.2f     %d",newnode->num,name,ckind,price,newnode->rank);
		
		insertEntry(haxi_meal,newnode->name,newnode);//�����ϣ�� 
		
		fclose(food); 
		int len=0,temp=newnode->num,i;
		float ftemp;
		while(newnode->num)
		{
			++len;
			newnode->num/=10;
		}
		newnode->num=temp;
		for(i=0;i<len;++i)
		{
			order[len-i]=temp%10+'0';
			temp/=10;
		}
		order[len]='\0';
		strcpy(newnode->order,order);
	}
    	
}

void managekey_change()
{
	system("cls");
	char newmkey[40],newmkey2[40];
	int i=0;
	while(1){
		printf("*****************************************\n");
		printf("#             ����д�µ�����            #\n");
		printf("*****************************************\n");
		our_scanf_str(newmkey,20);
//		system("cls");
		if(strcmp("0",newmkey)==0){
			printf("���ܽ�������Ϊ0��\n");
			system("pause");
			return;
		}
		printf("*****************************************\n");
		printf("#          ������дһ���µ�����         #\n");
		printf("*****************************************\n");
		our_scanf_str(newmkey2,20);
		if(strcmp(newmkey,newmkey2)==0) {
			printf("�޸ĳɹ���\n");
			fkey=fopen("managekey.txt","w+");
			strcpy(managekey,newmkey);
			while(*(newmkey+i)!=0){
				fputc(*(newmkey+i),fkey);
				i++;
			}
			system("pause");
			break;
		}else{
			printf("�������벻һ��\n\n");
			system("pause");
			system("cls");
		}
	}
	fclose(fkey);
} 

void deletemeal(struct meal* s,char *name)//ɾ����Ʒ 
{
	system("cls");
	struct meal *pre,*front,*node;
	char ckind[30];
	
	pre=meal_head;
	node=meal_head->next;
	while(node!=NULL)
	{
		if(strcmp(node->name,name)==0)
		{
			break;
		}
		pre=pre->next;
		node=node->next;
	}
	
	int num=0,cnum;
	
	
	if(node==NULL)
	{
		printf("ɾ����Ч\n");
		system("pause");
		return;
	}
	strcpy(ckind,node->kind);
	pre->next=node->next;
	removeEntry(haxi_meal,name);
	free(node);
	node=pre->next;
	while(node!=NULL)
	{
		
		
		if(strcmp(node->kind,ckind)!=0)
		{
			break;
		}
		else
		{
			if(node->order[2]!='0')
			{
				--node->order[2];
			}
			else
			{
				--node->order[1];
				node->order[2]='9';
			}
			--node->num;
	//		printf("%s %s",node->name,node->order);
		}
		node=node->next;
	}system("pause");
	
		
		food=fopen("menu.txt","wb");
		if(food==NULL){
			printf("�ļ��޷��򿪣��޷��������У�\n");
			return;
		}
		node=meal_head->next;
		while(node->next!=NULL) 
		{
			fprintf(food,"%d     %s     %s     %s     %s\n",node->num,node->name,node->kind,node->cprice,node->crank);
			node=node->next;
		}
		fprintf(food,"%d     %s     %s     %s     %s",node->num,node->name,node->kind,node->cprice,node->crank);
//	printf("ɾ������\n");
		fclose(food);//�ǵù��ļ� 
//		start_menu();
//	else printf("ɾ����Ч!\n\n");	 
}

void searchprice(struct meal* s,float low,float high)//�����۸����� 
{
	int word=0;
	s=s->next;
	system("cls");
	fflush(stdin);
	printf("*****************************************\n");
	printf("#               �������                #\n");
	printf("#���\t����\t\t����\t����\t#\n#\t\t\t\t\t#\n");
	while(s!=NULL)
	{
		if(s->price>=low&&s->price<=high){
			if(strlen(s->name)<8) printf("#%d\t%s\t\t%s\t%.2f\t#\n",s->num,s->name,s->kind,s->price);
			else printf("#%d\t%s\t%s\t%.2f\t#\n",s->num,s->name,s->kind,s->price);
			word=1;
		}
        s=s->next;
	}
	if(word==0)printf("#              Not  Found               #\n");
	printf("*****************************************\n\n");
	system("pause");
	system("cls");
}

int searchkind(struct meal* s,char* kind)//������Ʒ����
{
	int word=0,min=1000,max=99;
	struct meal *mealkind_head,*mealkind_end,*k;
	char ckind[5]={0};
	system("cls");
	printf("*****************************************\n");
	printf("#               �������                #\n");
	printf("#���\t����\t\t����\t����\t#\n#\t\t\t\t\t#\n");
	if (kind[1]==0){
		switch(kind[0]-'0'){
			case 1:strcpy(ckind,"��ʳ");break;
			case 2:strcpy(ckind,"���");break; 
			case 3:strcpy(ckind,"�ز�");break;
			case 4:strcpy(ckind,"��Ʒ");break;
			case 5:strcpy(ckind,"С��");break;
			default:word=0;break; 
		}
	}
	fflush(stdin);
	s=s->next;
	while(s!=NULL)
	{
//		if(strcmp(s->kind,ckind)==0&&word==0){
//			struct meal* newnode=(struct meal*)malloc(sizeof(struct meal));
//			fflush(stdin);
//			newnode->num=s->num;
//			strcpy(newnode->name,s->name);
//			strcpy(newnode->kind,ckind);
//			newnode->price=s->price;
////			newnode=s;
//			newnode->next=NULL;
//			min=newnode->num;max=newnode->num;
//			mealkind_head=newnode;mealkind_end=newnode;
//			word=1;
////			printf("\n666\n");
//		}else if(strcmp(s->kind,ckind)==0&&word==1){
//			struct meal* newnode=(struct meal*)malloc(sizeof(struct meal));
//			fflush(stdin);
//			newnode->num=s->num;
//			strcpy(newnode->name,s->name);
//			strcpy(newnode->kind,ckind);
//			newnode->price=s->price;
////			newnode=s;
//			newnode->next=NULL;
//			if(newnode->num<min){
//				newnode->next=mealkind_head;
//				mealkind_head=newnode;
//				min=mealkind_head->num;
//			}
//			else if(newnode->num>max){
//				newnode=mealkind_end->next;
//				mealkind_end=newnode;
//				max=mealkind_end->num;
//			}else{
//				k=mealkind_head;
//				while(k!=NULL&&k->next->num<newnode->num){
//					k=k->next;
//				}
//				newnode->next=k->next;
//				k->next=newnode;
//			}
//			printf("\n999\n");
//		}
		if(strcmp(s->kind,ckind)==0)
		{
			if(strlen(s->name)<8) printf("#%d\t%s\t\t%s\t%.2f\t#\n",s->num,s->name,s->kind,s->price);
			else printf("#%d\t%s\t%s\t%.2f\t#\n",s->num,s->name,s->kind,s->price);
			word=1;
		}
        s=s->next;
//        printf("\n%d %d\n",min,max);
	}
//	if(word==1){
//		k=mealkind_head;
//		while(k!=NULL){
//			if(strlen(k->name)<8) printf("#%d\t%s\t\t%s\t%.2f\t#\n",k->num,k->name,k->kind,k->price);
//			else printf("#%d\t%s\t%s\t%.2f\t#\n",k->num,k->name,k->kind,k->price);
//			k=k->next;
//		}
//	}
	if(word==0)printf("#              Not  Found               #\n");
	printf("*****************************************\n\n");
	system("pause");
	system("cls");
	return word;	
}

int searchmeal(struct meal* s,char* name)//����/���/�޸Ĳ�Ʒ
{
	struct meal* list=s,*node;//�˴�list���ڱ���ԭ������׵�ַ 
	int word=0,num=0,judge=0,prenum;
	char i[100],j[100],cprice[50],ckind[30],prekind[30];
	char kind[20];
	float price;
	system("cls");
	printf("*****************************************\n");
	printf("#               �������                #\n");
	printf("#���\t����\t\t����\t����\t#\n#\t\t\t\t\t#\n");
	s=(struct meal*)findValueByKey(haxi_meal,name);
	if(s!=NULL){
			if(strlen(s->name)<8) printf("#%d\t%s\t\t%s\t%.2f\t#\n",s->num,s->name,s->kind,s->price);
			else printf("#%d\t%s\t%s\t%.2f\t#\n",s->num,s->name,s->kind,s->price);
			word=1;
		}
	if(word==0)printf("#              Not  Found               #\n");
	printf("*****************************************\n");
	system("pause");
	system("cls");
	if(word==0)
	{
		while(1){
			printf("*****************************************\n");
			printf("#        �Ƿ���Ӹò�Ʒ����˵���       #\n");
			printf("#                 1.��                  #\n");
			printf("#                 0.��                  #\n");
			printf("*****************************************\n\n");
			our_scanf_str(i,1);
			if(i[1]!=0){
				system("cls");
				printf("��������\n");
			}else{
				if(i[0]-'0'==1){
					printf("�벹��������Ϣ��\n");
					printf("��Ʒ���ࣺ");
					printf(" 1����ʳ��2����ˣ�3���زˣ�4����Ʒ��5��С��\n");
					our_scanf_str(kind,1);
					printf("��Ʒ���ۣ�");
					price=our_scanf_float(1000);
//					fflush(stdin);
					addmeal(name,kind,price);
					system("cls");	
					printf("��ӳɹ�\n\n");
//				printmeal(list);
					break;
				}else if(i[0]!=48&&i[0]!=49)
				{
					system("cls");
					printf("��ֻ������0/1\n\n"); 	
				}else {
				//	system("pause");
					system("cls");
					break;
				} 
			}
		}
	}
	else{
		while(1){
			printf("*****************************************\n");
			printf("#          �Ƿ���Ҫ�޸ĸò�Ʒ��         #\n");
			printf("#                 1.��                  #\n");
			printf("#                 0.��                  #\n");
			printf("*****************************************\n");
			our_scanf_str(i,1);
			system("cls");
			if(i[1]!=0){
				printf("��ֻ������0/1\n\n");
			}else{
				if(i[0]-'0'==1){
					while(1){
						
						printf("*****************************************\n");
						printf("#          ����Ҫ�޸��ĸ���Ŀ��         #\n");
						printf("#                0.����                 #\n");
						printf("#                1.����                 #\n");
						printf("#                2.����                 #\n");
						printf("#                3.����                 #\n");
						printf("*****************************************\n\n");
						our_scanf_str(j,1);
						if(j[1]!=0){
							system("cls");
							printf("��ֻ������0/1/2/3\n\n");
						}else{
							if(j[0]-'0'==0)break; 
							switch(j[0]-'0'){
								case 1:
									printf("����д�޸ĺ�Ĳ�����");
									while(1)
									{
										our_scanf_str(name,7);
										if(findValueByKey(haxi_meal,name)!=NULL)
										printf("�ò����ѱ�ע�ᣬ����������\n");
										else
										break;
									}
									removeEntry(haxi_meal,s->name);
									insertEntry(haxi_meal,name,s);
									strcpy(s->name,name);
									printf("�޸ĳɹ�\n");
									printf("*****************************************\n");
									printf("#%d\t%s\t%s\t��%.2f\t#\n",s->num,s->name,s->kind,s->price);
									printf("*****************************************\n");
									printf("���ڴ��ļ������Ժ�......\n");
									food=fopen("menu.txt","wb");
									if(food==NULL){printf("�ļ��޷��򿪣��޷��������У�\n");return;} 
									else printf("�ļ��򿪳ɹ�����ʼ�޸Ĳ�Ʒ��Ϣ\n");
									node=meal_head->next;
									while(node->next!=NULL) 
									{
										fprintf(food,"%d     %s     %s     %s     %s\n",node->num,node->name,node->kind,node->cprice,node->crank);
										node=node->next;
									}
									fprintf(food,"%d     %s     %s     %s     %s",node->num,node->name,node->kind,node->cprice,node->crank);
									fclose(food);//�ǵù��ļ� 
									system("pause");
									system("cls");
									break;
								case 2:
									printf("����д�޸ĺ�����ࣺ");
									printf(" 1����ʳ��2����ˣ�3���زˣ�4����Ʒ��5��С��\n");
									our_scanf_str(kind,1);
										if (kind[1]==0){
											switch(kind[0]-'0'){
												case 1:strcpy(ckind,"��ʳ");judge=1;break;
												case 2:strcpy(ckind,"���");judge=1;break; 
												case 3:strcpy(ckind,"�ز�");judge=1;break;
												case 4:strcpy(ckind,"��Ʒ");judge=1;break;
												case 5:strcpy(ckind,"С��");judge=1;break;
												default:printf("������������\n"); break; 
											}
										}else {
											printf("������������\n"); 
										//	printf("%d",strlen(s->kind)); 
										}
									if(judge==1){
										strcpy(prekind,s->kind);
										prenum=s->num;
										printf("�޸ĳɹ�\n");
										s->num=givenum(ckind);
										strcpy(s->kind,ckind);
										
										printf("*****************************************\n");
										if(strlen(s->name)<8)printf("#%d\t%s\t\t%s\t��%.2f\t#\n",s->num,s->name,s->kind,s->price);
										else printf("#%d\t%s\t%s\t��%.2f\t#\n",s->num,s->name,s->kind,s->price);
										printf("*****************************************\n");
										food=fopen("menu.txt","wb");
										if(food==NULL){printf("�ļ��޷��򿪣��޷��������У�\n");return;} 
										node=meal_head->next;
										while(node->next!=NULL) 
										{
											if(strcmp(prekind,node->kind)==0&&node->num>prenum)node->num-=1;
											fprintf(food,"%d     %s     %s     %s     %s\n",node->num,node->name,node->kind,node->cprice,node->crank);
											node=node->next;
										}
										if(strcmp(prekind,node->kind)==0&&node->num>prenum)node->num-=1;
										fprintf(food,"%d     %s     %s     %s     %s",node->num,node->name,node->kind,node->cprice,node->crank);
										fclose(food);//�ǵù��ļ� 
									}
									system("pause");
									system("cls");
									break;
								case 3:
									printf("����д�޸ĺ�ĵ��ۣ�");
									s->price=our_scanf_float(1000);
									printf("�޸ĳɹ�\n");
									printf("*****************************************\n");
									printf("#%d\t%s\t%s\t��%.2f\t#\n",s->num,s->name,s->kind,s->price);
									printf("*****************************************\n");
									FtoC(cprice,s->price);
									strcpy(s->cprice,cprice);
									food=fopen("menu.txt","wb");
									if(food==NULL){printf("�ļ��޷��򿪣��޷��������У�\n");return;} 
									node=meal_head->next;
									while(node->next!=NULL) 
									{
										fprintf(food,"%d     %s     %s     %s     %s\n",node->num,node->name,node->kind,node->cprice,node->crank);
										node=node->next;
									}
									fprintf(food,"%d     %s     %s     %s     %s",node->num,node->name,node->kind,node->cprice,node->crank);
									fclose(food);//�ǵù��ļ� 
									system("pause");
									system("cls");
									break;
								default:
									system("cls");
									printf("��ֻ������0/1/2/3\n\n"); break;	
							}
						}
					}
				}else if(i[0]-'0'==0){
				//	system("pause");
					system("cls");
					break;
				}
				else printf("��ֻ������0/1\n\n");
			}
			system("pause");
			system("cls");
		}
	}
	return word;
}

void searchmeal_unclear(char *name)//ģ������ 
{
	struct meal* s=meal_head;
	int word=0;
	system("cls");
	printf("*****************************************\n");
	printf("#               �������                #\n");
	printf("#���\t����\t\t����\t����\t#\n#\t\t\t\t\t#\n");
	s=s->next;
	while(s!=NULL)
	{
		if(strstr(s->name,name)!=NULL){
			if(strlen(s->name)<8) printf("#%d\t%s\t\t%s\t%.2f\t#\n",s->num,s->name,s->kind,s->price);
			else printf("#%d\t%s\t%s\t%.2f\t#\n",s->num,s->name,s->kind,s->price);
			word=1;
		}
		s=s->next;
	}
	if(word==0)printf("#              Not  Found               #\n");
	printf("*****************************************\n\n");
	system("pause");
	system("cls");
 } 

void choice_mealmanage(struct meal* s)//�˵����� 
{
	system("cls");
	char w[100]={0};
	float low,high,temp;
	char name[40],kind[20];
	float price;
	struct meal* list=meal_head;//�˴�list���ڱ���ԭ������׵�ַ 
	while(1){
		s=list;//ÿ��ѭ�����轫s�ָ�ָ��ԭ������׵�ַ  
		printmealmanage();
		printmeal(list);
		printf("*****************************************\n");
		printf("\t�˵�����                \n");
		printf("\n");
		printf("\t0.�˳�ģ��               \n");
		printf("\t1.ɾ����Ʒ               \n");
		printf("\t2.�۸���������             \n");
		printf("\t3.��Ʒ��������             \n");
		printf("\t4.��Ʒ��ȷ����/���/�޸�          \n");
		printf("\t5.��Ʒģ������          \n");
		printf("*****************************************\n");
		our_scanf_str(w,1);
		if(w[1]!=0){
			system("cls");
			printf("��ֻ������0/1/2/3/4/5\n\n");
		}
		else{
			switch(w[0]-'0')
			{
				case 0:break;
				case 1:
					printf("��д������Ҫɾ���Ĳ�Ʒ��\n");
					our_scanf_str(name,20);
					deletemeal(s,name);
					break;
				case 2:
					printf("��д������Ҫ�����ļ۸����䣺\n");
					low=our_scanf_float(100000);
					high=our_scanf_float(100000);
					if(low>high)
					{
						printf("�����ǰһ�������ں�һ������ϵͳ��Ϊ������%.2f~%.2fԪ����Ĳ�Ʒ\n",high,low);
						system("pause");
						temp=low;
						low=high;
						high=temp;
					}
					searchprice(s,low,high); 
					break;
				case 3:
					printf("��д������Ҫ�����Ĳ�Ʒ���ࣺ\n");
					printf(" 1����ʳ��2����ˣ�3���زˣ�4����Ʒ��5��С��\n");
					our_scanf_str(kind,1);
					searchkind(s,kind);
					break;
				case 4:
					printf("��д������ҪѰ�ҵĲ�Ʒ��\n");
					our_scanf_str(name,20);
					searchmeal(s,name);
					break;
				case 5:
					 printf("��д������Ҫ���ҵ�������1���ֻ����֣���\n");
					 while(1)
					 {
					 	our_scanf_str(name,20);
					 	if(name[0]=='\0')
					 	{
					 		printf("������������һ���ַ�\n");
					 		continue;
						}
						break;
					 }
					 searchmeal_unclear(name);
					 break;
				default:
					system("cls");
					printf("��ֻ������0/1/2/3/4/5\n\n");
					break;
			}
			if(w[0]-'0'==0)break; 
		}	
//		system("cls");
//		printmealmanage(); 
//		printad();
	}
}

int choice_manage(struct meal *s,struct staff *f,struct Customer *c)
{
	system("cls");
	char i[100];
	while(1){
		printf("*****************************************\n");
		printf("#         ��ӭ���붩�͹���ģ��          #\n");
		printf("#        ��ѡ������Ҫ�����ģ��         #\n");
		printf("#              0.�˳�ϵͳ               #\n");
		printf("#              1.�˵�����               #\n");
		printf("#              2.Ա������               #\n");
		printf("#              3.�˿͹���               #\n");
		printf("#              4.����ͳ��               #\n");
		printf("#              5.�޸�����               #\n");
		printf("*****************************************\n\n");
		our_scanf_str(i,1);
		if(i[1]!=0){
			system("cls");
			printf("��ֻ������0/1/2/3/4/5\n\n");
		}else if (i[0]=='0'){
			system("cls");
	//		printf("wowo");
	//		return 0;
			break;
		}
		else{
			switch(i[0]-'0'){
				case 1:
					choice_mealmanage(s);
					system("cls");
					break;
				case 2:
					manage();
					system("cls");
					break;
				case 3:
					choice_customermanage(c);
					system("cls");
					break;
				case 4:
					statics_jiemian();
					system("cls");
					break;
				case 5:	
					managekey_change();
					system("cls");
					break;
				default:
					system("cls");
					printf("��ֻ������0/1/2/3/4/5\n\n");
					break;
			}
		}
	}
	printf("wowo");
	return i[0]-'0';
}

void managelogin(struct meal *s,struct staff *f,struct Customer *c)
{
	system("cls");
	char i[100];
	while(1){
		printf("*****************************************\n");
		printf("#          �����Ƕ��͹���ϵͳ           #\n");
		printf("#          �����������Ա��Կ           #\n");
		printf("#             ��0�˳�ϵͳ               #\n");
		printf("*****************************************\n\n");
		our_scanf_str(i,20);
		if(i[0]=='0'&&i[1]==0)break;
		else if (strcmp(managekey,i)==0){
			if(choice_manage(s,f,c)==0)return;
		} 
		else{
			system("cls");
			printf("�������\n");
		}
		
	} 
}
