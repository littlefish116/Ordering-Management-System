/*#include<stdio.h>
#include<string.h>
#include<malloc.h>*/
   



void staff_menu()
{
	printf("********************************************************************\n");
	printf("|                     欢迎来到员工管理系统！                        |\n");
	printf("|                     请按照操作指引进行工作                       |\n");
	printf("********************************************************************\n");
}

int st_strlen(char c[])//能分辨汉字的strlen（因为汉字的ASCII码是负数而且占两个char的空间 
{
	int i,len=0;
	for(i=0;c[i]!='\0';++i)
	{
		if(len>60)//长度超过60就跳掉（因为我这的合法数据长度最多60，后续需要可以改 
		break;
		if(c[i]<0)//ASCII码小于0就是汉字，占了两个位置所以++i 
		{
			++i;
		}
		++len;//一个字统计长度就+1 
	}
	return len;
}
//strlen挺方便的但是怕越界，所以下面的strlen之后都会改成别的，参考函数mima_judge()的第82~85行 
int id_judge(char s[])//判断电话号是否合法（不是是否被注册过）1是合法，0不合法 
{
	int i;
	int judge=1;//judge是记录合不合法用的
		for(i=0;i<strlen(s);++i)
		if(s[i]<'0'||s[i]>'9')//这里汉字就被唰下去了 
		{
			judge=0;
			break;
		}
	
	return judge;
}
int st_CtoN(char c[])//数字字符串转化为数字（数字以外的字符会被跳过 
{
	int r=0,n=strlen(c),i;//r是要返回的数字 
	for(i=0;i<n;++i)
	{
		if(c[i]<'0'||c[i]>'9')//判断是否是数字，不是就跳过 
		continue;
		r*=10;
		r+=c[i]-'0';
	}
	return r;
}

int id_exist(char s[])//判断工号是否已被注册，已注册返回1，否则返回0
{
	int judge=0;//用来记录工号是否被注册用的 
	struct staff *node;
	node=(struct staff*)findValueByKey(haxi_staff,s);
	if(node!=NULL)
	judge=1;
	return judge;
}

char* give_stid(char str[])
{
	int num,judge=1,i,temp;
	time_t timep;
	struct tm *p;
	time(&timep);
	p=localtime(&timep); 
	num=cl_CtoN(staff_end->staff_id);
	++num;
	str=cl_NtoC(num);
	temp=p->tm_year+1900;
	if(temp!=num/10000)
	judge=0;
	if(judge==0)
	{
		num=temp*10000+1;
		str=cl_NtoC(num);
	}
	return str;
}

void search_staff()//查找员工
{
	int judge;//记录要找的员工是否存在 
	char v='1';//记录是否要查找员工，要的话是1，不要的话是2 
	char c[30];//记录员工姓名
	struct staff *node;
	while(v=='1')
	{
		system("cls");
		printf("请输入您要查找的员工的名称: ");
		our_scanf_str(c,12);//输入员工信息 
		judge=0;//默认要找的员工不存在 
		
		node=(struct staff*)findValueByKey(haxi_staff,c);//第一位员工
		if(node!=NULL)//从头往后挨个查是否有符合条件的员工 
		{
			judge=1;
		}  
		if(judge==0)//没找到的情况 
		{
			printf("-----------------------------分割线--------------------------\n"); 
			printf("未查找到员工信息\n");
			printf("-----------------------------分割线--------------------------\n"); 
		}
		else//找到的情况
		{
			printf("-----------------------------分割线--------------------------\n"); 
			printf("姓名：%s\n工号：%s\n职业：%s\n",node->staff_name,node->staff_id,node->staff_idt);
		    printf("-----------------------------分割线--------------------------\n"); 
		}
		while(1)
		{
			printf("请问是否要继续查询\n");
			printf("1.是    2.否\n");
			our_scanf_str(c,1);//c暂时用来记录是否用来继续查询（因为暂时没用 
			if(strlen(c)!=1||(c[0]!='1'&&c[0]!='2'))
			{
				printf("输入有误，请重新输入\n"); 
			}
			else if(c[0]=='1')
			{
				break;
			}
			else if(c[0]=='2')
			{
				printf("谢谢您的使用\n");
				return;
			}
		}
	}
}
void print_staff()//打印所有员工信息 
{
	struct staff *node=staff_head->next;
	int num=0;
//	printf("即将打印所有员工的信息\n");
//	Sleep(2000);//等2秒读上一行的输出信息 
	while(node!=NULL)
	{
		printf("-----------------------------分割线--------------------------\n"); 
		printf("姓名：%s\n工号：%s\n职业：%s\n",node->staff_name,node->staff_id,node->staff_idt);
		
		node=node->next;
		num++;
	}
	printf("-----------------------------分割线--------------------------\n"); 
	printf("\n目前拥有以上%d名员工的信息。\n\n",num);
}
void sthlr()//初始化录入（把文本里的员工信息录进去（链表存储员工信息 
{
	iniHashTable(haxi_staff);
	staff_head=(struct staff *)malloc(sizeof(struct staff));//第一位顾客前面的头指针 
	staff_head->next=NULL;//最后会指向NULL
	struct staff *node,*pre=staff_head;//node是把员工信息用来一个一个插入的，pre是记录前一个员工信息的 
	FILE *st_fp=NULL;//打开文件 
//	printf("正在打开文件，请稍后......\n");
	st_fp=fopen("staff.txt","r");
	if(st_fp==NULL)//要是没打开就直接return 
	{
//		printf("文件打开失败\n");
		return;
	}
	else
//	printf("文件打开成功，开始同步员工信息\n"); 
	while(!feof(st_fp))//从头开始读文件，直到读到结尾 
	{
		node=(struct staff *)malloc(sizeof(struct staff));//分配地址 
		//↓将文件里的数据存到数组里 
		fscanf(st_fp,"%s%s%s",node->staff_id,node->staff_name,node->staff_idt);
		insertEntry(haxi_staff,node->staff_id,node);
		insertEntry(haxi_staff,node->staff_name,node);
		node->next=pre->next;//插入数据 
		pre->next=node;//同上 
		pre=pre->next;//同上 
//		printf("%s\n",pre->staff_id);//看一眼插入了啥 
	}
	staff_end=pre;//记录最后一位员工信息 
//	printf("员工信息同步结束\n");
	fclose(st_fp);
}
void st_insert_staff()//增加员工
{
	int num,judge,i;//num->字符串长度以及临时工具人（工具人情况比较少 
	//order是序号，表示这是第几位顾客，name是姓名，password是密码，phone是电话号，vip是等级数
	//str用来接受输入的数据，开的大一点防止数据太大越界造成bug，str处理后再传递给order那些变量 
	//（虽然还是会越界，之后会看看用getchar优化一下，现在先凑合着
	char str[30],staff_id[10],name[50],idt[50];
	FILE *st_fp=NULL;
	st_fp=fopen("staff.txt","a");
	while(1)//输入员工姓名 
	{
		system("cls");
		judge=1;//记录姓名是否合法 
		printf("请输入您的姓名（长度为2-7）：");fflush(stdin);
		our_scanf_str(str,7);//输入姓名并处理 
		num=st_strlen(str);//cl_strlen能处理一个汉字占两个空间的问题，返回值是字符串长度 
		if(num>7||num<2)//姓名长度不合法就跳过 
		judge=0;
		else//姓名长度合法情况 
		for(i=0;i<num;++i)
		if(name[i]==' ')//网名什么都可以有就是不能有空格不然我读文件很麻烦的（简单牢骚一下 
		{
			judge=0;
		}
		if(judge==1)//合法就退出，不然就无限循环 
		break;
		else
		printf("格式有误，请重新输入\n");
	}
	strcpy(name,str); //把str的内容传给name 

	strcpy(staff_id,give_stid(staff_id));
	printf("系统分配的员工工号为：%s\n",staff_id);

	while(1)//填写身份
	{
		printf("请输入员工身份（仅支持12字以内，包括12字）：");
		our_scanf_str(str,12);//输入身份
		judge=1;//记录身份，合法是1，不合法是0，默认合法 
		if(st_strlen(str)>12)
		{
			printf("超出12字了，请重新输入\n");
		}
		else
		{
			num=strlen(str);
			for(i=0;i<num;++i)
			{
				if(str[i]==' ')
				{
					judge=0;
					printf("不能有空格，请重新输入\n"); 
					break;
				}
			}
		} 
		if(judge==1)//合法就跳出循环 
		break;
	}
	strcpy(idt,str);//str的内容传给idt
	
//	strcpy(staff_id,staff_end->staff_id);//把最后一位员工的工号拷到id里了 
//	num=strlen(staff_id);//转换成数字 
//	staff_id[num-1]='\0';//因为id里有个“，”，比如说第12位员工的id就是“12，” 
//	num=st_CtoN(staff_id);//转换成功 
//	++num;//序号加一位 
	
	//↓这玩意就是看一眼录入的数据是什么样的 
	printf("\n%s   %s     %s\n",staff_id,name,idt);
	//↓这个是录入数据 
	fprintf(st_fp,"\n%s   %s     %s",staff_id,name,idt);
	fclose(st_fp);//记得关文件不然录不进去 
	
	struct staff *node=(struct staff *)malloc(sizeof(struct staff));;
	staff_end->next=node;
	node->next=NULL;
//	int len=0,temp=num;
//	char order[30];
//	while(num)
//	{
//		++len;
//		num/=10;
//	}
//	num=temp;
//	for(i=1;i<=len;++i)
//	{
//		order[len-i]=num%10+'0';
//		num/=10;
//	}
//	order[len]='\0';
	strcpy(node->staff_name,name);
	strcpy(node->staff_id,staff_id);
	strcpy(node->staff_idt,idt);
	staff_end=node;
//	printf("\n%s   %s     %s\n",node->staff_id,node->staff_name,node->staff_idt);	
	insertEntry(haxi_staff,node->staff_id,node);
	insertEntry(haxi_staff,node->staff_name,node);
	system("pause");
}

void delete_staff()//删除员工信息 
{
	int judge=0,num=0;//judge用来记录判断的各种数据是否合法，num用来记录第num位员工（后面用到num时就容易懂了 
	char id[20];//记录工号，开大一点防越界，后期可能拿getchar优化一下 
	int len=0,temp,i;
	char order[30];
	struct staff *pre=staff_head,*node=staff_head->next;//pre记录前一个节点，node当前节点，从第一位顾客开始 
	while(judge==0)//输入手机号并判断工号格式是否合法（就是不管是否被注册过 
	{
		system("cls");
		
		printf("请输入工号\n");//fflush(stdin);//getchar();
		
		our_scanf_str(id,8);//读入一行字符串当工号
		
		judge=id_judge(id);//判断工号格式是否正确的函数，正确是1，不正确是0 
		if(judge==0)
		printf("工号格式有误，请重新输入\n");
		else break;
	}
	
	judge=id_exist(id);//判断工号是否被注册过，注册过是1，否则是0 

	if(judge==0)//没被注册的情况 
	{
		printf("此工号尚未被使用\n");
		system("pause");return;
	}
	else//被注册过的情况，找那个员工
	{
		node=(struct staff*)findValueByKey(haxi_staff,id);

		int num,i;
		char tmpid[10];
		
		strcpy(tmpid,node->staff_id);
		
		num=cl_CtoN(tmpid)-1;
//		
//		if(num>0)
//		{
//			int len=0,temp=num;
//			while(temp)
//			{
//				++len;
//				temp/=10;
//			}
//			
//			temp=num;
//			for(i=1;i<=len;++i)
//			{
//				tmpid[len-i]=temp%10+'0';
//				temp/=10;
//			}
//			
//			tmpid[len]='\0';
//			pre=(struct staff*)findValueByKey(haxi_staff,tmpid);
//		}
		
		if(staff_head->next!=node)
		{
			strcpy(tmpid,cl_NtoC(num));
			pre=(struct staff*)findValueByKey(haxi_staff,tmpid);
		}
		else
		pre=staff_head;
		pre->next=node->next;//链表里删掉他 
		removeEntry(haxi_staff,node->staff_id);
		removeEntry(haxi_staff,node->staff_name);
		free(node);
		node->next=NULL;
		system("pause");
	}
	FILE *st_fp=NULL;//把链表里的内容覆盖到文件里 
	printf("正在打开文件，请稍后......\n");
	st_fp=fopen("staff.txt","wb");//二进制只写模式打开文件，打开的时候就把文件里的内容全删了
//大概只能用二进制只写模式（也可能我孤陋寡闻了），不然txt文件的格式会从原先设定的ANSI转换成UTF-8
//这个编译器环境用UTF-8遇到汉字会乱码的（不是很理解反正，但总不能用宽字符wchar来的orz） 
	if(st_fp==NULL)
	{
		printf("文件打开失败\n");
		return;
	}
	else
	printf("文件打开成功，开始删除员工信息\n");//实际上是把之前链表里存的删除过的员工信息录进去 
	node=staff_head->next;//第一位员工
	while(node->next!=NULL)//最后一个员工先别录，这个程序的文件结尾是回车那还是有一点小麻烦的 
	{
		//记得++num，表示下一位员工的工号
		fprintf(st_fp,"%s     %s     %s\n",node->staff_id,node->staff_name,node->staff_idt);
//		len=0,temp=num;
//		while(temp)
//		{
//			++len;
//			temp/=10;
//		}
//		temp=num;
//		for(i=1;i<=len;++i)
//		{
//			order[len-i]=temp%10+'0';
//			temp/=10;
//		}
//		order[len]=',';
//		order[len+1]='\0';
//		order[len]='\0';
//		strcpy(node->staff_id,order);
		node=node->next;
	}
	//最后以为员工不整回车 
		fprintf(st_fp,"%s     %s     %s",node->staff_id,node->staff_name,node->staff_idt);
//		len=0,temp=num;
//		while(num)
//		{
//			++len;
//			num/=10;
//		}
//		num=temp;
//		for(i=1;i<=len;++i)
//		{
//			order[len-i]=num%10+'0';
//			num/=10;
//		}
//		order[len]=',';
//		order[len+1]='\0';
//		order[len]='\0';
//		strcpy(node->staff_id,order);
	
	printf("删除结束\n");
	fclose(st_fp);//记得关文件 
	sthlr();
	system("pause");
	return;
}
void staff_unclear(char *name)//模糊查找 
{
	struct staff* s=staff_head;
	int word=0;
	system("cls");
	printf("*************************************************\n");
	printf("#                   搜索结果                    #\n");
	printf("#工号\t\t名称\t\t职业\t        #\n");
	s=s->next;
	while(s!=NULL)
	{
		if(strstr(s->staff_name,name)!=NULL){
			if(strlen(s->staff_name)<8) printf("#%s\t%s\t\t%s\t        #\n",s->staff_id,s->staff_name,s->staff_idt);
			else printf("#%s\t%s\t%s\t        #\n",s->staff_id,s->staff_name,s->staff_idt);
			word=1;
		}
		s=s->next;
	}
	if(word==0)printf("#                  Not  Found                   #\n");
	printf("*************************************************\n\n");
	system("pause");
	system("cls");
 }
void manage()//总管理系统
{
	char string[20],choice[4];
	while (1)
	{
	system("cls");	
	printf("\n");
	print_staff();
	printf("********************************************************************\n");
	printf("                        请选择需要进行的操作                        \n");
	printf("                        0.  退出界面                                \n");
	printf("                        1.  搜索员工                                \n");
	printf("                        2.  增加员工                                \n");
	printf("                        3.  删除员工                                \n");
	printf("                        4.  模糊搜索                                \n");
	printf("********************************************************************\n");
	our_scanf_str(choice,1);
	if (choice[1]!=0){
		system("cls");
		printf("您只能输入0/1/2/3/4\n\n");
	}else if (choice[0]=='0')break; 
	else{
		switch(choice[0]-'0') 
		{	
		case 0:
			break;
		case 1:
			search_staff();
			break;
		case 2:
			st_insert_staff();
			break;
		case 3:
			delete_staff();
			break;
		case 4:
			printf("请输入关键词:");
			our_scanf_str(string,8);
			staff_unclear(string);
			break;
		default:
			system("cls");
			printf("您只能输入0/1/2/3/4\n\n");
			break;
		}
	}
	
	}	
}
