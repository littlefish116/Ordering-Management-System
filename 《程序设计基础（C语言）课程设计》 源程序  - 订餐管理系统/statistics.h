/*#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <time.h> 
#include "ljh.h"*/
typedef struct Bill{
	char phone[20];//顾客的电话号 
	time_t t;//用来转换成点餐时间 
	struct tm *tim;//点餐时间 
	char ctim[200];//同上 
	char cus_name[20]; 
	int num;//点了几道菜 
	char diandan[201][50];//点的什么菜 
	int in_or_out;//店内还是店外点的单，店内是0，店外是1
	char waimai_staff_id[20];//谁送的外卖，没人送就是空的 
	char waimai_staff_name[20];//同上 
	float value;//交易金额 
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
		printf("顾客姓名：%s\n",node->cus_name);
		printf("顾客电话：%s\n",node->phone);
		printf("点餐时间：%s",node->ctim);
		printf("点餐信息：%d道菜\n          ",node->num);
		for(i=1;i<node->num;++i)
		{
			printf("%s,",node->diandan[i]);
		}
		printf("%s",node->diandan[node->num]);
		printf("\n");
		printf("交易金额：%.2f\n",node->value);
		if(node->in_or_out==1)
		{
			printf("点单形式：外卖\n");
			printf("快递员工号：%s\n",node->waimai_staff_id);
			printf("快递员姓名：%s\n",node->waimai_staff_name);
		}
		else
		{
			printf("点单形式：店内就餐\n");
		}
		printf("——————————————————————————\n");
		node=node->next;
	}
	system("pause");
	return;
}

void bill_to_txt()
{
	int i;
	FILE *bill_fp=NULL;//把链表里的内容覆盖到文件里 
	//	printf("正在打开文件，请稍后......\n");
		bill_fp=fopen("bill.txt","wb");//二进制只写模式打开文件，打开的时候就把文件里的内容全删了
	//大概只能用二进制只写模式（也可能我孤陋寡闻了），不然txt文件的格式会从原先设定的ANSI转换成UTF-8
	//这个编译器环境用UTF-8遇到汉字会乱码的（不是很理解反正，但总不能用宽字符wchar来的orz） 
		if(bill_fp==NULL)
		{
			printf("文件打开失败\n");
			return;
		}
	//	else
	//	printf("文件打开成功，开始删除顾客信息\n");//实际上是把之前链表里存的删除过的顾客信息录进去 
		Bill *node;
		node=bill_head->next;//第一位顾客 
		while(node->next!=NULL)//最后一个顾客先别录，这个程序的文件结尾是回车那还是有一点小麻烦的 
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
		//最后一位顾客不整回车 
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
	//	printf("删除结束\n");
		fclose(bill_fp);//记得关文件 

//——————————————————————————————————————	
	
	FILE *bill_fp2=NULL;//把链表里的内容覆盖到文件里 
	//	printf("正在打开文件，请稍后......\n");
		bill_fp2=fopen("bill2.txt","wb");//二进制只写模式打开文件，打开的时候就把文件里的内容全删了
	//大概只能用二进制只写模式（也可能我孤陋寡闻了），不然txt文件的格式会从原先设定的ANSI转换成UTF-8
	//这个编译器环境用UTF-8遇到汉字会乱码的（不是很理解反正，但总不能用宽字符wchar来的orz） 
		if(bill_fp2==NULL)
		{
			printf("文件打开失败\n");
			return;
		}
	//	else
	//	printf("文件打开成功，开始删除顾客信息\n");//实际上是把之前链表里存的删除过的顾客信息录进去 
		node=bill_head->next;//第一位顾客 
		while(node->next!=NULL)//最后一个顾客先别录，这个程序的文件结尾是回车那还是有一点小麻烦的 
		{
			fprintf(bill_fp2,"用户电话：%s\n",node->phone);
			
			fprintf(bill_fp2,"用户姓名：%s\n",node->cus_name);
//			printf("%s\n",node->phone);
			fprintf(bill_fp2,"订单时间：%s",node->ctim);
			fprintf(bill_fp2,"点餐数量：%d\n",node->num);
			
			fprintf(bill_fp2,"点餐信息：");
			for(i=1;i<node->num;++i)
			{
				fprintf(bill_fp2,"%s  ",node->diandan[i]);
			}
			fprintf(bill_fp2,"%s\n",node->diandan[node->num]);
			fprintf(bill_fp2,"店内or外卖（店内0，外卖1）：%d\n",node->in_or_out);
			if(node->in_or_out==1)
			{
				fprintf(bill_fp2,"外卖员信息工号：%s\n外卖员姓名：%s\n",node->waimai_staff_id,node->waimai_staff_name);
			}
			fprintf(bill_fp2,"交易金额：%.2f\n",node->value);
			fprintf(bill_fp2,"----------------------------------------\n");
			node=node->next;
			
		}
		//最后一位顾客不整回车 
		
		
		fprintf(bill_fp2,"用户电话：%s\n",node->phone);
		
		fprintf(bill_fp2,"用户姓名：%s\n",node->cus_name);
		
		fprintf(bill_fp2,"订单时间：%s",node->ctim);
		fprintf(bill_fp2,"点餐数量：%d\n",node->num);
		fprintf(bill_fp2,"点餐信息：\n");
		
		for( i=1;i<node->num;++i)
		{
			fprintf(bill_fp2,"%s  ",node->diandan[i]);
		}
		fprintf(bill_fp2,"%s\n",node->diandan[node->num]);
		fprintf(bill_fp2,"店内or外卖（店内0，外卖1）：%d\n",node->in_or_out);
		if(node->in_or_out==1)
		{
			fprintf(bill_fp2,"外卖员信息工号：%s\n外卖员姓名：%s\n",node->waimai_staff_id,node->waimai_staff_name);
		}
		fprintf(bill_fp2,"交易金额：%.2f\n",node->value);
		fprintf(bill_fp2,"----------------------------------------");
	//	printf("删除结束\n");
		fclose(bill_fp2);//记得关文件 
		return;
}

void bill_in()//初始化录入（把文本里的账单信息录进去（链表存储顾客信息 
{
	iniHashTable(haxi_bill);
	int n,i;
	char ch[200];
	bill_head=(Bill *)malloc(sizeof(Bill));//第一位顾客前面的头指针 
	bill_head->next=NULL;//最后会指向NULL
	Bill *node,*pre=bill_head;//node是把顾客信息用来一个一个插入的，pre是记录前一个顾客信息的 
	FILE *bill_fp=NULL;//打开文件 
//	printf("正在打开文件，请稍后......\n");
	bill_fp=fopen("bill.txt","r");
	if(bill_fp==NULL)//要是没打开就直接return 
	{
//		printf("文件打开失败\n");
		return;
	}
	else
//	printf("文件打开成功，开始同步顾客信息\n"); 
	while(!feof(bill_fp))//从头开始读文件，直到读到结尾 
	{
		node=(Bill *)malloc(sizeof(Bill));//分配地址 
		//↓将文件里的数据存到数组里 
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
		if(node->in_or_out==1)//店外消费就记录外卖员，店内消费不记录外卖员 
		fscanf(bill_fp,"%s%s",node->waimai_staff_id,node->waimai_staff_name);
		fscanf(bill_fp,"%f",&node->value);
//		printf("%f\n",node->value);
		fscanf(bill_fp,"%s",ch);
//		printf("%ld\n",&node->t);
		insertEntry(haxi_bill,node->ctim,node);
		node->next=pre->next;//插入数据 
		pre->next=node;//同上 
		pre=pre->next;//同上 
//		printf("%s\n",pre->waimai_staff_name);//看一眼插入了啥 
	}
	bill_end=pre;//记录最后一位顾客信息 
//	bill_end->next=NULL;
//	printf("顾客信息同步结束\n");
	fclose(bill_fp);
}

void insert_bill(char pho[],int n,char dd[][50],int io,struct staff *tmp,float v)//io=0是店内，io=1是店外 
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
	printf("最受欢迎的外卖员为：\n");
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
	printf("最受欢迎的菜品为：\n");
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
	printf("菜品点单次数从多到少排名为：\n");
	for(i=0;i<1000;++i)
	{
		if(strcmp(ss[i].name," ")!=0)
		printf("姓名:%s\t点单次数:%d\n",ss[i].name,ss[i].store);
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
	printf("外卖员配送次数从多到少排名为：\n");
	for(i=0;i<10000;++i)
	{
		if(strcmp(ss[i].name," ")!=0)
		printf("姓名:%s\t配送次数:%d\n",ss[i].name,ss[i].store);
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
		printf("#         欢迎进入数据统计模块          #\n");
		printf("#        请选择您需要进入的模块         #\n");
		printf("#              0.退出系统               #\n");
		printf("#              1.最佳外卖员             #\n");
		printf("#              2.最热菜品               #\n");
		printf("#              3.外卖员排名             #\n");
		printf("#              4.菜单热销排名           #\n");
		printf("#              5.打印账单               #\n");
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
				printf("您只能输入0/1/2/3/4/5\n\n");
				break; 
		}
	}
}
