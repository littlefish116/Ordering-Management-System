/*#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <time.h> 
#include "ljh.h"*/
typedef struct Bill{
	char phone[20];//�˿͵ĵ绰�� 
	time_t t;//����ת���ɵ��ʱ�� 
	struct tm *tim;//���ʱ�� 
	char ctim[200];//ͬ�� 
	char cus_name[20]; 
	int num;//���˼����� 
	char diandan[201][50];//���ʲô�� 
	int in_or_out;//���ڻ��ǵ����ĵ���������0��������1
	char waimai_staff_id[20];//˭�͵�������û���;��ǿյ� 
	char waimai_staff_name[20];//ͬ�� 
	float value;//���׽�� 
	struct Bill *next;
}Bill;
Bill *bill_head,*bill_end;
table *haxi_bill; 

void print_bill()
{
	system("cls");
	int i; 
	Bill *node=bill_head->next;
	while(node!=NULL)
	{
		printf("�˿�������%s\n",node->cus_name);
		printf("�˿͵绰��%s\n",node->phone);
		printf("���ʱ�䣺%s",node->ctim);
		printf("�����Ϣ��%d����\n          ",node->num);
		for(i=1;i<node->num;++i)
		{
			printf("%s,",node->diandan[i]);
		}
		printf("%s",node->diandan[node->num]);
		printf("\n");
		printf("���׽�%.2f\n",node->value);
		if(node->in_or_out==1)
		{
			printf("�㵥��ʽ������\n");
			printf("���Ա���ţ�%s\n",node->waimai_staff_id);
			printf("���Ա������%s\n",node->waimai_staff_name);
		}
		else
		{
			printf("�㵥��ʽ�����ھͲ�\n");
		}
		printf("����������������������������������������������������\n");
		node=node->next;
	}
	system("pause");
	return;
}

void bill_to_txt()
{
	int i;
	FILE *bill_fp=NULL;//������������ݸ��ǵ��ļ��� 
	//	printf("���ڴ��ļ������Ժ�......\n");
		bill_fp=fopen("bill.txt","wb");//������ֻдģʽ���ļ����򿪵�ʱ��Ͱ��ļ��������ȫɾ��
	//���ֻ���ö�����ֻдģʽ��Ҳ�����ҹ�ª�����ˣ�����Ȼtxt�ļ��ĸ�ʽ���ԭ���趨��ANSIת����UTF-8
	//���������������UTF-8�������ֻ�����ģ����Ǻ���ⷴ�������ܲ����ÿ��ַ�wchar����orz�� 
		if(bill_fp==NULL)
		{
			printf("�ļ���ʧ��\n");
			return;
		}
	//	else
	//	printf("�ļ��򿪳ɹ�����ʼɾ���˿���Ϣ\n");//ʵ�����ǰ�֮ǰ��������ɾ�����Ĺ˿���Ϣ¼��ȥ 
		Bill *node;
		node=bill_head->next;//��һλ�˿� 
		while(node->next!=NULL)//���һ���˿��ȱ�¼�����������ļ���β�ǻس��ǻ�����һ��С�鷳�� 
		{
			fprintf(bill_fp,"%s\n",node->phone);
			fprintf(bill_fp,"%s\n",node->cus_name);
			fprintf(bill_fp,"%ld\n",node->t);
			fprintf(bill_fp,"%d\n",node->num);
			for(i=1;i<node->num;++i)
			{
				fprintf(bill_fp,"%s  ",node->diandan[i]);
			}
			fprintf(bill_fp,"%s\n",node->diandan[node->num]);
			fprintf(bill_fp,"%d\n",node->in_or_out);
			if(node->in_or_out==1)
			{
				fprintf(bill_fp,"%s\n%s\n",node->waimai_staff_id,node->waimai_staff_name);
			}
			fprintf(bill_fp,"%.2f\n",node->value);
			fprintf(bill_fp,"----------------------------------------\n");
			node=node->next;
		}
		//���һλ�˿Ͳ����س� 
		fprintf(bill_fp,"%s\n",node->phone);
		fprintf(bill_fp,"%s\n",node->cus_name);
		fprintf(bill_fp,"%ld\n",node->t);
		fprintf(bill_fp,"%d\n",node->num);
		for(i=1;i<node->num;++i)
		{
			fprintf(bill_fp,"%s  ",node->diandan[i]);
		}
		fprintf(bill_fp,"%s\n",node->diandan[node->num]);
		fprintf(bill_fp,"%d\n",node->in_or_out);
		if(node->in_or_out==1)
		{
			fprintf(bill_fp,"%s\n%s\n",node->waimai_staff_id,node->waimai_staff_name);
		}
		fprintf(bill_fp,"%.2f\n",node->value);
		fprintf(bill_fp,"----------------------------------------");
	//	printf("ɾ������\n");
		fclose(bill_fp);//�ǵù��ļ� 

//����������������������������������������������������������������������������	
	
	FILE *bill_fp2=NULL;//������������ݸ��ǵ��ļ��� 
	//	printf("���ڴ��ļ������Ժ�......\n");
		bill_fp2=fopen("bill2.txt","wb");//������ֻдģʽ���ļ����򿪵�ʱ��Ͱ��ļ��������ȫɾ��
	//���ֻ���ö�����ֻдģʽ��Ҳ�����ҹ�ª�����ˣ�����Ȼtxt�ļ��ĸ�ʽ���ԭ���趨��ANSIת����UTF-8
	//���������������UTF-8�������ֻ�����ģ����Ǻ���ⷴ�������ܲ����ÿ��ַ�wchar����orz�� 
		if(bill_fp2==NULL)
		{
			printf("�ļ���ʧ��\n");
			return;
		}
	//	else
	//	printf("�ļ��򿪳ɹ�����ʼɾ���˿���Ϣ\n");//ʵ�����ǰ�֮ǰ��������ɾ�����Ĺ˿���Ϣ¼��ȥ 
		node=bill_head->next;//��һλ�˿� 
		while(node->next!=NULL)//���һ���˿��ȱ�¼�����������ļ���β�ǻس��ǻ�����һ��С�鷳�� 
		{
			fprintf(bill_fp2,"�û��绰��%s\n",node->phone);
			
			fprintf(bill_fp2,"�û�������%s\n",node->cus_name);
//			printf("%s\n",node->phone);
			fprintf(bill_fp2,"����ʱ�䣺%s",node->ctim);
			fprintf(bill_fp2,"���������%d\n",node->num);
			
			fprintf(bill_fp2,"�����Ϣ��");
			for(i=1;i<node->num;++i)
			{
				fprintf(bill_fp2,"%s  ",node->diandan[i]);
			}
			fprintf(bill_fp2,"%s\n",node->diandan[node->num]);
			fprintf(bill_fp2,"����or����������0������1����%d\n",node->in_or_out);
			if(node->in_or_out==1)
			{
				fprintf(bill_fp2,"����Ա��Ϣ���ţ�%s\n����Ա������%s\n",node->waimai_staff_id,node->waimai_staff_name);
			}
			fprintf(bill_fp2,"���׽�%.2f\n",node->value);
			fprintf(bill_fp2,"----------------------------------------\n");
			node=node->next;
			
		}
		//���һλ�˿Ͳ����س� 
		
		
		fprintf(bill_fp2,"�û��绰��%s\n",node->phone);
		
		fprintf(bill_fp2,"�û�������%s\n",node->cus_name);
		
		fprintf(bill_fp2,"����ʱ�䣺%s",node->ctim);
		fprintf(bill_fp2,"���������%d\n",node->num);
		fprintf(bill_fp2,"�����Ϣ��\n");
		
		for( i=1;i<node->num;++i)
		{
			fprintf(bill_fp2,"%s  ",node->diandan[i]);
		}
		fprintf(bill_fp2,"%s\n",node->diandan[node->num]);
		fprintf(bill_fp2,"����or����������0������1����%d\n",node->in_or_out);
		if(node->in_or_out==1)
		{
			fprintf(bill_fp2,"����Ա��Ϣ���ţ�%s\n����Ա������%s\n",node->waimai_staff_id,node->waimai_staff_name);
		}
		fprintf(bill_fp2,"���׽�%.2f\n",node->value);
		fprintf(bill_fp2,"----------------------------------------");
	//	printf("ɾ������\n");
		fclose(bill_fp2);//�ǵù��ļ� 
		return;
}

void bill_in()//��ʼ��¼�루���ı�����˵���Ϣ¼��ȥ������洢�˿���Ϣ 
{
	iniHashTable(haxi_bill);
	int n,i;
	char ch[200];
	bill_head=(Bill *)malloc(sizeof(Bill));//��һλ�˿�ǰ���ͷָ�� 
	bill_head->next=NULL;//����ָ��NULL
	Bill *node,*pre=bill_head;//node�ǰѹ˿���Ϣ����һ��һ������ģ�pre�Ǽ�¼ǰһ���˿���Ϣ�� 
	FILE *bill_fp=NULL;//���ļ� 
//	printf("���ڴ��ļ������Ժ�......\n");
	bill_fp=fopen("bill.txt","r");
	if(bill_fp==NULL)//Ҫ��û�򿪾�ֱ��return 
	{
//		printf("�ļ���ʧ��\n");
		return;
	}
	else
//	printf("�ļ��򿪳ɹ�����ʼͬ���˿���Ϣ\n"); 
	while(!feof(bill_fp))//��ͷ��ʼ���ļ���ֱ��������β 
	{
		node=(Bill *)malloc(sizeof(Bill));//�����ַ 
		//�����ļ�������ݴ浽������ 
		fscanf(bill_fp,"%s",node->phone);
//		printf("%s\n",node->phone);
		fscanf(bill_fp,"%s",node->cus_name);
//		printf("%s\n",node->cus_name);
		fscanf(bill_fp,"%ld",&node->t);
//		printf("%ld\n",node->t);
		strcpy(node->ctim,ctime(&node->t));
//		printf("%s\n",node->ctim);
		fscanf(bill_fp,"%d",&node->num);
//		printf("%d\n",node->num);
		node->tim=localtime(&node->t);
		for(i=1;i<=node->num;++i)
		{
			fscanf(bill_fp,"%s",node->diandan[i]);
//			printf("%s\n",node->diandan[i]);
		}
		fscanf(bill_fp,"%d",&node->in_or_out);
//		printf("%d\n",node->in_or_out);
		if(node->in_or_out==1)//�������Ѿͼ�¼����Ա���������Ѳ���¼����Ա 
		fscanf(bill_fp,"%s%s",node->waimai_staff_id,node->waimai_staff_name);
		fscanf(bill_fp,"%f",&node->value);
//		printf("%f\n",node->value);
		fscanf(bill_fp,"%s",ch);
//		printf("%ld\n",&node->t);
		insertEntry(haxi_bill,node->ctim,node);
		node->next=pre->next;//�������� 
		pre->next=node;//ͬ�� 
		pre=pre->next;//ͬ�� 
//		printf("%s\n",pre->waimai_staff_name);//��һ�۲�����ɶ 
	}
	bill_end=pre;//��¼���һλ�˿���Ϣ 
//	bill_end->next=NULL;
//	printf("�˿���Ϣͬ������\n");
	fclose(bill_fp);
}

void insert_bill(char pho[],int n,char dd[][50],int io,struct staff *tmp,float v)//io=0�ǵ��ڣ�io=1�ǵ��� 
{
	Customer *cust;
	cust=(Customer*)findValueByKey(haxi_customer,pho);
	Bill *node=(Bill*)malloc(sizeof(Bill));
	int i;
	strcpy(node->phone,pho);
	strcpy(node->cus_name,cust->name);
	time(&node->t);
	strcpy(node->ctim,ctime(&node->t));
	node->tim=localtime(&node->t);
	node->num=n;
	for( i=1;i<=n;++i)
	strcpy(node->diandan[i],dd[i]);
	node->in_or_out=io;
	if(io==1)
	{
		strcpy(node->waimai_staff_id,tmp->staff_id);
		strcpy(node->waimai_staff_name,tmp->staff_name);
	} 
	node->value=v;
	strcpy(node->ctim,ctime(&node->t));
	node->tim=localtime(&node->t);
	printf("%s\n",node->ctim);
	bill_end->next=node;
	node->next=NULL;
//	printf("  name=%s\n",)
	bill_end=node;
	bill_to_txt();
	insertEntry(haxi_bill,node->ctim,node);
	return;
}

void hot_staff()
{
	int n=0,mmax=1,i;
	int store[10000]={0},tmp;
	char name[10000][20];
	Bill *node=bill_head->next;
	struct staff *f;
	while(node!=NULL)
	{
		if(node->in_or_out==1)
		{
			tmp=cl_CtoN(node->waimai_staff_id)-20220000;
//			printf("%d\n\n",tmp);
			++store[tmp];
			strcpy(name[tmp],node->waimai_staff_name);
		}		
		node=node->next;
	}
	for(i=1;i<10000;++i)
	{
		if(store[i]>store[mmax])
		mmax=i;
	}
	system("cls");
	printf("���ܻ�ӭ������ԱΪ��\n");
	for(i=1;i<10000;++i)
	{
		if(store[i]==store[mmax])
		printf("%s ",name[i]);
	}
	printf("\n");
	system("pause");
}

void hot_menu()
{
	int n=0,mmax=1,i;
	int store[10000]={0},tmp;
	char name[10000][20];
	Bill *node=bill_head->next;
	struct meal *m;
	while(node!=NULL)
	{
		for(i=1;i<=node->num;++i)
		{
			m=(struct meal*)findValueByKey(haxi_meal,node->diandan[i]);
			if(m!=NULL)
			{
				tmp=m->num;
				++store[tmp];
				strcpy(name[tmp],node->diandan[i]);
			}
		}
		node=node->next;
	}
	for(i=1;i<10000;++i)
	{
		if(store[i]>=store[mmax])
		mmax=i;
	}
	printf("���ܻ�ӭ�Ĳ�ƷΪ��\n");
	for(i=1;i<10000;++i)
	{
		if(store[i]==store[mmax])
		{
			printf("%s ",name[i]);
		}
	}
	printf("\n");
	system("pause");
}

struct sst{
	int store;
	char name[20];
};

void sort_meal_time()
{
	int tmp,i,j,mmax;
	struct sst ss[1000],tss;
	for(i=0;i<1000;++i)
	{
		strcpy(ss[i].name," ");
		ss[i].store=0;
	}
	Bill *node=bill_head->next;
	struct meal *m;
	while(node!=NULL)
	{
		for(i=1;i<=node->num;++i)
		{
			m=(struct meal*)findValueByKey(haxi_meal,node->diandan[i]);
			if(m!=NULL)
			{
				
				tmp=cl_CtoN(m->order);
				++ss[tmp].store;
				strcpy(ss[tmp].name,m->name);
			}
		}
		node=node->next;
	}
	for(i=0;i<1000;++i)
	{
		mmax=i;
		for(j=i;j<1000;++j)
		{
			if(ss[j].name!=" "&&ss[j].store>ss[mmax].store)
			{
				mmax=j;
			}
		}
		tss=ss[i];
		ss[i]=ss[mmax];
		ss[mmax]=tss;
	}
//	system("cls");
	printf("��Ʒ�㵥�����Ӷൽ������Ϊ��\n");
	for(i=0;i<1000;++i)
	{
		if(strcmp(ss[i].name," ")!=0)
		printf("����:%s\t�㵥����:%d\n",ss[i].name,ss[i].store);
	}
	system("pause");
}

void sort_staff_time()
{
	int tmp,i,j,mmax;
	Bill *node=bill_head->next;
	struct sst ss[10000],tss;
	for(i=0;i<10000;++i)
	{
		strcpy(ss[i].name," ");
		ss[i].store=0;
	}
	while(node!=NULL)
	{
		if(node->in_or_out==1)
		{
			tmp=cl_CtoN(node->waimai_staff_id)-20220001;
			++ss[tmp].store;
			strcpy(ss[tmp].name,node->waimai_staff_name);
		}
		node=node->next;
	}
	for(i=0;i<10000;++i)
	{
		mmax=i;
		for(j=i;j<10000;++j)
		{
			if(ss[j].name!=" "&&ss[j].store>ss[mmax].store)
			{
				mmax=j;
			}
		}
		tss=ss[i];
		ss[i]=ss[mmax];
		ss[mmax]=tss;
	}
	system("cls");
	printf("����Ա���ʹ����Ӷൽ������Ϊ��\n");
	for(i=0;i<10000;++i)
	{
		if(strcmp(ss[i].name," ")!=0)
		printf("����:%s\t���ʹ���:%d\n",ss[i].name,ss[i].store);
	}
	system("pause");
}

void statics_jiemian()
{
	char choice[4];
	while(1)
	{
		system("cls");
		printf("*****************************************\n");
		printf("#         ��ӭ��������ͳ��ģ��          #\n");
		printf("#        ��ѡ������Ҫ�����ģ��         #\n");
		printf("#              0.�˳�ϵͳ               #\n");
		printf("#              1.�������Ա             #\n");
		printf("#              2.���Ȳ�Ʒ               #\n");
		printf("#              3.����Ա����             #\n");
		printf("#              4.�˵���������           #\n");
		printf("#              5.��ӡ�˵�               #\n");
		printf("*****************************************\n\n");
		our_scanf_str(choice,1);
		switch(choice[0]-'0')
		{
			case 0:
				return;
			case 1:
				hot_staff();
				system("cls");
				break;
			case 2:
				hot_menu();
				system("cls");
				break;
			case 3:
				sort_staff_time();
				system("cls");
				break;
			case 4:
				sort_meal_time();
				system("cls");
				break;
			case 5:
				print_bill();
				system("cls");
				break;
			default:
				system("cls");
				printf("��ֻ������0/1/2/3/4/5\n\n");
				break; 
		}
	}
}
