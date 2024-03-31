#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <time.h> 



struct staff *createlist()//创建链表 
{
	struct staff* headnode = (struct staff*)malloc(sizeof(struct staff));
	headnode->next = NULL;
	headnode->staff_id = 0;
	s = headnode;
	return headnode;
}

void addstaff(struct staff *f,int staff_id,char *staff_name,int staff_star,char *idt)//增加员工 
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

void info_staff(struct staff* f) //展示员工信息 /
{
	f = f->next;
	printf("*******************************\n");
	printf("#工号\t姓名\t星级\t职业  #\n");
	while(f != NULL)
	{
		printf("#%d\t%s\t%d\t%s#\n",f->staff_id,f->staff_name,f->staff_star,f->idt);
		f = f->next;
	}
	printf("*******************************\n\n");
}

void firestaff(struct staff *f,char* staff_name)//开除员工 
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
		printf("删除成功\n");
	}else printf("操作无效，请检查是否正确\n\n");
}

int staffsearch(struct staff* f,char* staff_name)//搜索员工 
{
	struct staff* list=f;//此处list用于保存原链表的首地址 
	int word=0;
	char name[30],idt[15],i[100],j[100];
	int id,star;
	printf("********************************************************\n");
	printf("#                        搜索结果                      #\n");
	printf("#员工姓名\t员工ID\t\t员工星级\t员工职业#\n#\t\t\t\t\t#\n");
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
			printf("#        是否将该员工填进菜单？         #\n");
			printf("#                 1.是                  #\n");
			printf("#                 0.否                  #\n");
			printf("*****************************************\n\n");
			scanf("%s",i) ;
			if(strcmp(i,"1")==0){
				printf("请完善信息:\n");
				printf("员工id：");
				scanf("%d",&id);
				printf("员工星级:");
				scanf("%d",&star);
				printf("员工职业:");
				scanf("%s",idt);
				addstaff(list,id,name,star,idt);	
			//	info_staff(list);
				break;
			}else if(strcmp(i,"1")!=0&&strcmp(i,"0")!=0)
			{
				printf("您只能输入0/1\n\n"); 
			}else break;
		}	
	}else{
		while(1){
			printf("*****************************************\n");
			printf("#        是否需要修改该员工信息？       #\n");
			printf("#                 1.是                  #\n");
			printf("#                 0.否                  #\n");
			printf("*****************************************\n");
			scanf("%s",i) ;
			system("cls");
			if(i[1]!=0){
				printf("您只能输入0/1\n\n");
			}else{
				if(i[0]-'0'==1){
					while(1){
						printf("*****************************************\n");
						printf("#          还需要修改哪个项目？         #\n");
						printf("#               0.不改了                #\n");
						printf("#                 1.id                  #\n");
						printf("#                2.职业                 #\n");
						printf("*****************************************\n\n");
						scanf("%s",j) ;
						if(j[1]!=0){
							system("cls");
							printf("您只能输入0/1/2\n\n");
						}else{
							if(j[0]-'0'==0)break; 
							switch(j[0]-'0'){
								case 1:
									printf("请填写修改后的id：");
									scanf("%d",&f->staff_id);
									printf("修改成功\n");
									printf("*****************************************\n");
									printf("#%s\t%d\t\t%d\t%s#\n#\t\t\t\t\t#\n",f->staff_name,f->staff_id,f->staff_star,f->idt);
									printf("*****************************************\n");
									break;
								case 2:
									printf("请填写修改后的种类：");
									scanf("%s",f->idt);
									printf("修改成功\n");
									printf("*****************************************\n");
									printf("#%s\t%d\t\t%d\t%s#\n#\t\t\t\t\t#\n",f->staff_name,f->staff_id,f->staff_star,f->idt);
									printf("*****************************************\n");
									break;
								default:
									printf("您只能输入0/1/2\n\n"); break;	
							}
						}
					}
				}else printf("您只能输入0/1\n\n");
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
	printf("#         欢迎进入员工管理模块          #\n");
	printf("*****************************************\n\n");
}

void choice_staffmanage(struct staff* f)//员工管理总菜单 
{
	system("cls");
	int ret,id,star;
	char name[30],idt[15],choice[100];
	struct staff* list=f;//此处list用于保存原链表的首地址 
	while(1){
		printstaffmanage();
		f=list;//每次循环均需将f恢复指向原链表的首地址  
		info_staff(list); 
		printf("*****************************************\n");
		printf("#               员工管理                #\n");
		printf("#\t\t\t\t\t#\n");
		printf("#              0.退出模块               #\n");
		printf("#           1.查询与增加员工            #\n");
		printf("#              2.删除员工               #\n");
		printf("*****************************************\n");
		scanf("%s",choice);
		if(choice[1]!=0){
			system("cls");
			printf("您只能输入0/1/2\n\n");
		}else{
			if(choice[0]=='0'){
				system("cls");
				break;
			}
			switch(choice[0]-'0')
			{
				case 0:	break;
				case 1:
					printf("输入员工信息：\n");
					printf("员工名称：");
					scanf("%s",name);
					system("cls");
					staffsearch(f,name);
				//	system("pause");
					system("cls");
					break;
				case 2:
					printf("请写出您需要删除的员工：\n");
					scanf("%s",name);
					firestaff(f,name);
				//	info_staff(f);
					system("pause");
					system("cls");
					break;
				default:
					system("cls");
					printf("您只能输入0/1/2\n\n");break;
			}
		}
	}
}









