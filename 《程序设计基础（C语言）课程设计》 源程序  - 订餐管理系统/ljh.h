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

FILE *food;//用于存储菜单于文本文件中 

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
	printf("\t欢迎进入订餐管理系统          \n");
	printf("\t请选择您需要的服务           \n");
	printf("\t0.退出系统               \n");
	printf("\t1.客户端登录              \n");
	printf("\t2.管理员登录              \n");
	printf("\t3.查询帮助               \n");
	printf("============================================\n");
}


void printmealmanage()
{
	printf("*****************************************\n");
	printf("#         欢迎进入菜单管理模块          #\n");
	printf("*****************************************\n\n");
}

int givenum(char* kind)
{
	int end=0;
	if(strcmp("主食",kind)==0)end+=100;
	else if(strcmp("荤菜",kind)==0)end+=200;
	else if(strcmp("素菜",kind)==0)end+=300;
	else if(strcmp("甜品",kind)==0)end+=400;
	else if(strcmp("小吃",kind)==0)end+=500;
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
//	printf("正在打开文件，请稍后......\n");
	if(food==NULL)//要是没打开就直接return 
	{
		printf("文件打开失败\n");
		return;
	}
//	else printf("文件打开成功，开始同步菜品信息\n"); 
	while(!feof(food))//从头开始读文件，直到读到结尾 
	{
		node=(struct meal *)malloc(sizeof(struct meal));//分配地址 
		//↓将文件里的数据存到数组里 
		fscanf(food,"%s%s%s%s%s",node->order,node->name,node->kind,node->cprice,node->crank);
		node->num=cl_CtoN(node->order); 
		node->rank=cl_CtoN(node->crank);
		node->price=CtoF(node->cprice);
		insertEntry(haxi_meal,node->name,node);//添加进入哈希表 
		insertEntry(haxi_meal,node->order,node);
		node->next=pre->next;//插入数据 
		pre->next=node;//同上 
		pre=pre->next;//同上	
//		printf("%s\n",pre->name);//看一眼插入了啥 
	}	
	meal_end=pre;
	sort(meal_head,NULL,"meal",meal_kind_cmp);
//	printf("菜品信息同步结束\n");
	fclose(food);
}

void printmeal(struct meal* s)//打印菜单 
{
	start_menu();
	s=meal_head->next; 
	fflush(stdin);
	printf("*****************************************\n");
	printf("#序号\t菜名\t\t种类\t单价/元\t#\n#\t\t\t\t\t#\n");
    while(s!=NULL)
    {
        if(strlen(s->name)<8) printf("#%d\t%s\t\t%s\t%.2f\t#\n",s->num,s->name,s->kind,s->price);
		else printf("#%d\t%s\t%s\t%.2f\t#\n",s->num,s->name,s->kind,s->price);
        s=s->next;
    }
    printf("*****************************************\n\n");
}

void addmeal(char *name,char *kind,float price)//在链表中增加元素（菜品） 
{
	fflush(stdin);
	int word=0;
	struct meal* frontnode=meal_end;
	char order[10],cprice[50],ckind[30]={0};
	if (kind[1]==0){
		switch(kind[0]-'0'){
			case 1:strcpy(ckind,"主食");word=1;break;
			case 2:strcpy(ckind,"荤菜");word=1;break; 
			case 3:strcpy(ckind,"素菜");word=1;break;
			case 4:strcpy(ckind,"甜品");word=1;break;
			case 5:strcpy(ckind,"小吃");word=1;break;
			default:printf("种类输入有误！\n"); break; 
		}
	}else {
		printf("种类输入有误！\n"); 
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
//		printf("正在打开文件，请稍后......\n");
  		food=fopen("menu.txt","a");
  		if(food==NULL)
		{
			printf("文件打开失败,无法添加。\n");
			return;
		}
//		else printf("文件打开成功，开始添加菜品信息\n");
//    printf("\n%d   %s     %s     %.2f     %d\n",newnode->num,name,kind,price,newnode->rank);
		fprintf(food,"\n%d   %s     %s     %.2f     %d",newnode->num,name,ckind,price,newnode->rank);
		
		insertEntry(haxi_meal,newnode->name,newnode);//插入哈希表 
		
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
		printf("#             请填写新的密码            #\n");
		printf("*****************************************\n");
		our_scanf_str(newmkey,20);
//		system("cls");
		if(strcmp("0",newmkey)==0){
			printf("不能将密码设为0！\n");
			system("pause");
			return;
		}
		printf("*****************************************\n");
		printf("#          请再填写一遍新的密码         #\n");
		printf("*****************************************\n");
		our_scanf_str(newmkey2,20);
		if(strcmp(newmkey,newmkey2)==0) {
			printf("修改成功！\n");
			fkey=fopen("managekey.txt","w+");
			strcpy(managekey,newmkey);
			while(*(newmkey+i)!=0){
				fputc(*(newmkey+i),fkey);
				i++;
			}
			system("pause");
			break;
		}else{
			printf("两次密码不一致\n\n");
			system("pause");
			system("cls");
		}
	}
	fclose(fkey);
} 

void deletemeal(struct meal* s,char *name)//删除菜品 
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
		printf("删除无效\n");
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
			printf("文件无法打开，无法正常运行！\n");
			return;
		}
		node=meal_head->next;
		while(node->next!=NULL) 
		{
			fprintf(food,"%d     %s     %s     %s     %s\n",node->num,node->name,node->kind,node->cprice,node->crank);
			node=node->next;
		}
		fprintf(food,"%d     %s     %s     %s     %s",node->num,node->name,node->kind,node->cprice,node->crank);
//	printf("删除结束\n");
		fclose(food);//记得关文件 
//		start_menu();
//	else printf("删除无效!\n\n");	 
}

void searchprice(struct meal* s,float low,float high)//搜索价格区间 
{
	int word=0;
	s=s->next;
	system("cls");
	fflush(stdin);
	printf("*****************************************\n");
	printf("#               搜索结果                #\n");
	printf("#序号\t菜名\t\t种类\t单价\t#\n#\t\t\t\t\t#\n");
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

int searchkind(struct meal* s,char* kind)//搜索菜品种类
{
	int word=0,min=1000,max=99;
	struct meal *mealkind_head,*mealkind_end,*k;
	char ckind[5]={0};
	system("cls");
	printf("*****************************************\n");
	printf("#               搜索结果                #\n");
	printf("#序号\t菜名\t\t种类\t单价\t#\n#\t\t\t\t\t#\n");
	if (kind[1]==0){
		switch(kind[0]-'0'){
			case 1:strcpy(ckind,"主食");break;
			case 2:strcpy(ckind,"荤菜");break; 
			case 3:strcpy(ckind,"素菜");break;
			case 4:strcpy(ckind,"甜品");break;
			case 5:strcpy(ckind,"小吃");break;
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

int searchmeal(struct meal* s,char* name)//搜索/添加/修改菜品
{
	struct meal* list=s,*node;//此处list用于保存原链表的首地址 
	int word=0,num=0,judge=0,prenum;
	char i[100],j[100],cprice[50],ckind[30],prekind[30];
	char kind[20];
	float price;
	system("cls");
	printf("*****************************************\n");
	printf("#               搜索结果                #\n");
	printf("#序号\t菜名\t\t种类\t单价\t#\n#\t\t\t\t\t#\n");
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
			printf("#        是否添加该菜品进入菜单？       #\n");
			printf("#                 1.是                  #\n");
			printf("#                 0.否                  #\n");
			printf("*****************************************\n\n");
			our_scanf_str(i,1);
			if(i[1]!=0){
				system("cls");
				printf("操作错误\n");
			}else{
				if(i[0]-'0'==1){
					printf("请补充其他信息：\n");
					printf("菜品种类：");
					printf(" 1、主食，2、荤菜，3、素菜，4、甜品，5、小吃\n");
					our_scanf_str(kind,1);
					printf("菜品单价：");
					price=our_scanf_float(1000);
//					fflush(stdin);
					addmeal(name,kind,price);
					system("cls");	
					printf("添加成功\n\n");
//				printmeal(list);
					break;
				}else if(i[0]!=48&&i[0]!=49)
				{
					system("cls");
					printf("您只能输入0/1\n\n"); 	
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
			printf("#          是否需要修改该菜品？         #\n");
			printf("#                 1.是                  #\n");
			printf("#                 0.否                  #\n");
			printf("*****************************************\n");
			our_scanf_str(i,1);
			system("cls");
			if(i[1]!=0){
				printf("您只能输入0/1\n\n");
			}else{
				if(i[0]-'0'==1){
					while(1){
						
						printf("*****************************************\n");
						printf("#          还需要修改哪个项目？         #\n");
						printf("#                0.不用                 #\n");
						printf("#                1.菜名                 #\n");
						printf("#                2.种类                 #\n");
						printf("#                3.单价                 #\n");
						printf("*****************************************\n\n");
						our_scanf_str(j,1);
						if(j[1]!=0){
							system("cls");
							printf("您只能输入0/1/2/3\n\n");
						}else{
							if(j[0]-'0'==0)break; 
							switch(j[0]-'0'){
								case 1:
									printf("请填写修改后的菜名：");
									while(1)
									{
										our_scanf_str(name,7);
										if(findValueByKey(haxi_meal,name)!=NULL)
										printf("该菜名已被注册，请重新输入\n");
										else
										break;
									}
									removeEntry(haxi_meal,s->name);
									insertEntry(haxi_meal,name,s);
									strcpy(s->name,name);
									printf("修改成功\n");
									printf("*****************************************\n");
									printf("#%d\t%s\t%s\t￥%.2f\t#\n",s->num,s->name,s->kind,s->price);
									printf("*****************************************\n");
									printf("正在打开文件，请稍后......\n");
									food=fopen("menu.txt","wb");
									if(food==NULL){printf("文件无法打开，无法正常运行！\n");return;} 
									else printf("文件打开成功，开始修改菜品信息\n");
									node=meal_head->next;
									while(node->next!=NULL) 
									{
										fprintf(food,"%d     %s     %s     %s     %s\n",node->num,node->name,node->kind,node->cprice,node->crank);
										node=node->next;
									}
									fprintf(food,"%d     %s     %s     %s     %s",node->num,node->name,node->kind,node->cprice,node->crank);
									fclose(food);//记得关文件 
									system("pause");
									system("cls");
									break;
								case 2:
									printf("请填写修改后的种类：");
									printf(" 1、主食，2、荤菜，3、素菜，4、甜品，5、小吃\n");
									our_scanf_str(kind,1);
										if (kind[1]==0){
											switch(kind[0]-'0'){
												case 1:strcpy(ckind,"主食");judge=1;break;
												case 2:strcpy(ckind,"荤菜");judge=1;break; 
												case 3:strcpy(ckind,"素菜");judge=1;break;
												case 4:strcpy(ckind,"甜品");judge=1;break;
												case 5:strcpy(ckind,"小吃");judge=1;break;
												default:printf("种类输入有误！\n"); break; 
											}
										}else {
											printf("种类输入有误！\n"); 
										//	printf("%d",strlen(s->kind)); 
										}
									if(judge==1){
										strcpy(prekind,s->kind);
										prenum=s->num;
										printf("修改成功\n");
										s->num=givenum(ckind);
										strcpy(s->kind,ckind);
										
										printf("*****************************************\n");
										if(strlen(s->name)<8)printf("#%d\t%s\t\t%s\t￥%.2f\t#\n",s->num,s->name,s->kind,s->price);
										else printf("#%d\t%s\t%s\t￥%.2f\t#\n",s->num,s->name,s->kind,s->price);
										printf("*****************************************\n");
										food=fopen("menu.txt","wb");
										if(food==NULL){printf("文件无法打开，无法正常运行！\n");return;} 
										node=meal_head->next;
										while(node->next!=NULL) 
										{
											if(strcmp(prekind,node->kind)==0&&node->num>prenum)node->num-=1;
											fprintf(food,"%d     %s     %s     %s     %s\n",node->num,node->name,node->kind,node->cprice,node->crank);
											node=node->next;
										}
										if(strcmp(prekind,node->kind)==0&&node->num>prenum)node->num-=1;
										fprintf(food,"%d     %s     %s     %s     %s",node->num,node->name,node->kind,node->cprice,node->crank);
										fclose(food);//记得关文件 
									}
									system("pause");
									system("cls");
									break;
								case 3:
									printf("请填写修改后的单价：");
									s->price=our_scanf_float(1000);
									printf("修改成功\n");
									printf("*****************************************\n");
									printf("#%d\t%s\t%s\t￥%.2f\t#\n",s->num,s->name,s->kind,s->price);
									printf("*****************************************\n");
									FtoC(cprice,s->price);
									strcpy(s->cprice,cprice);
									food=fopen("menu.txt","wb");
									if(food==NULL){printf("文件无法打开，无法正常运行！\n");return;} 
									node=meal_head->next;
									while(node->next!=NULL) 
									{
										fprintf(food,"%d     %s     %s     %s     %s\n",node->num,node->name,node->kind,node->cprice,node->crank);
										node=node->next;
									}
									fprintf(food,"%d     %s     %s     %s     %s",node->num,node->name,node->kind,node->cprice,node->crank);
									fclose(food);//记得关文件 
									system("pause");
									system("cls");
									break;
								default:
									system("cls");
									printf("您只能输入0/1/2/3\n\n"); break;	
							}
						}
					}
				}else if(i[0]-'0'==0){
				//	system("pause");
					system("cls");
					break;
				}
				else printf("您只能输入0/1\n\n");
			}
			system("pause");
			system("cls");
		}
	}
	return word;
}

void searchmeal_unclear(char *name)//模糊查找 
{
	struct meal* s=meal_head;
	int word=0;
	system("cls");
	printf("*****************************************\n");
	printf("#               搜索结果                #\n");
	printf("#序号\t菜名\t\t种类\t单价\t#\n#\t\t\t\t\t#\n");
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

void choice_mealmanage(struct meal* s)//菜单管理 
{
	system("cls");
	char w[100]={0};
	float low,high,temp;
	char name[40],kind[20];
	float price;
	struct meal* list=meal_head;//此处list用于保存原链表的首地址 
	while(1){
		s=list;//每次循环均需将s恢复指向原链表的首地址  
		printmealmanage();
		printmeal(list);
		printf("*****************************************\n");
		printf("\t菜单管理                \n");
		printf("\n");
		printf("\t0.退出模块               \n");
		printf("\t1.删除菜品               \n");
		printf("\t2.价格区间搜索             \n");
		printf("\t3.菜品种类搜索             \n");
		printf("\t4.菜品精确搜索/添加/修改          \n");
		printf("\t5.菜品模糊搜索          \n");
		printf("*****************************************\n");
		our_scanf_str(w,1);
		if(w[1]!=0){
			system("cls");
			printf("您只能输入0/1/2/3/4/5\n\n");
		}
		else{
			switch(w[0]-'0')
			{
				case 0:break;
				case 1:
					printf("请写出您需要删掉的菜品：\n");
					our_scanf_str(name,20);
					deletemeal(s,name);
					break;
				case 2:
					printf("请写出您需要搜索的价格区间：\n");
					low=our_scanf_float(100000);
					high=our_scanf_float(100000);
					if(low>high)
					{
						printf("您输的前一个数大于后一个数，系统将为您搜索%.2f~%.2f元区间的菜品\n",high,low);
						system("pause");
						temp=low;
						low=high;
						high=temp;
					}
					searchprice(s,low,high); 
					break;
				case 3:
					printf("请写出您需要搜索的菜品种类：\n");
					printf(" 1、主食，2、荤菜，3、素菜，4、甜品，5、小吃\n");
					our_scanf_str(kind,1);
					searchkind(s,kind);
					break;
				case 4:
					printf("请写出您需要寻找的菜品：\n");
					our_scanf_str(name,20);
					searchmeal(s,name);
					break;
				case 5:
					 printf("请写出您需要查找的字样（1个字或多个字）：\n");
					 while(1)
					 {
					 	our_scanf_str(name,20);
					 	if(name[0]=='\0')
					 	{
					 		printf("请您至少输入一个字符\n");
					 		continue;
						}
						break;
					 }
					 searchmeal_unclear(name);
					 break;
				default:
					system("cls");
					printf("您只能输入0/1/2/3/4/5\n\n");
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
		printf("#         欢迎进入订餐管理模块          #\n");
		printf("#        请选择您需要进入的模块         #\n");
		printf("#              0.退出系统               #\n");
		printf("#              1.菜单管理               #\n");
		printf("#              2.员工管理               #\n");
		printf("#              3.顾客管理               #\n");
		printf("#              4.数据统计               #\n");
		printf("#              5.修改密码               #\n");
		printf("*****************************************\n\n");
		our_scanf_str(i,1);
		if(i[1]!=0){
			system("cls");
			printf("您只能输入0/1/2/3/4/5\n\n");
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
					printf("您只能输入0/1/2/3/4/5\n\n");
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
		printf("#          这里是订餐管理系统           #\n");
		printf("#          请先输入管理员密钥           #\n");
		printf("#             扣0退出系统               #\n");
		printf("*****************************************\n\n");
		our_scanf_str(i,20);
		if(i[0]=='0'&&i[1]==0)break;
		else if (strcmp(managekey,i)==0){
			if(choice_manage(s,f,c)==0)return;
		} 
		else{
			system("cls");
			printf("密码错误\n");
		}
		
	} 
}
