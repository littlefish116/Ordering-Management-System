/*#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<windows.h>
#include"haxibiao.h"*/
typedef struct Customer{
	char order[10];
	char name[50];
	char phone[50];
	char address[130];
	char vip[2];
	char password[35];
	struct Customer *next;
}Customer;
Customer *customer_end,*customer_head;

table *haxi_customer;//顾客数据的哈希表 

void customer_to_txt()
{
	FILE *cl_fp=NULL;//把链表里的内容覆盖到文件里 
	//	printf("正在打开文件，请稍后......\n");
		cl_fp=fopen("customer.txt","wb");//二进制只写模式打开文件，打开的时候就把文件里的内容全删了
	//大概只能用二进制只写模式（也可能我孤陋寡闻了），不然txt文件的格式会从原先设定的ANSI转换成UTF-8
	//这个编译器环境用UTF-8遇到汉字会乱码的（不是很理解反正，但总不能用宽字符wchar来的orz） 
		if(cl_fp==NULL)
		{
	//		printf("文件打开失败\n");
			return;
		}
	//	else
	//	printf("文件打开成功，开始删除顾客信息\n");//实际上是把之前链表里存的删除过的顾客信息录进去 
		int num=0;
		Customer *node;
		node=customer_head->next;//第一位顾客 
		while(node->next!=NULL)//最后一个顾客先别录，这个程序的文件结尾是回车那还是有一点小麻烦的 
		{
			//记得++num，表示下一位顾客的序号 
			fprintf(cl_fp,"%d,     %s     %s     %s     %s     %s\n",++num,node->name,node->phone,node->password,node->address,node->vip);
			node=node->next;
		}
		//最后一位顾客不整回车 
		fprintf(cl_fp,"%d,     %s     %s     %s     %s     %s",++num,node->name,node->phone,node->password,node->address,node->vip);
	//	printf("删除结束\n");
		fclose(cl_fp);//记得关文件 
		return;
}

void our_scanf_str(char *str,int len)//str表示要接收数据的变量，回车键结束 
{
	int n,zifunum,judge=0;//n表示输入的字符串的长度，judge用于判断是否跳出循环,len表示最多可以接收的数据，超出len的部分会被清理掉 
	char v;//接受输入的信息用的 
	while(judge==0)
	{
		fflush(stdin);
		v=getchar();
		n=0;
		zifunum=0;
		str[0]=v;
		if(str[n]<0)//对汉字的处理 
		{
			++n;
			str[n]=getchar();
		}
		while(str[n]!='\n'&&str[n]!='\r'&&zifunum<=len)
		{
			++n;
			++zifunum;
			str[n]=getchar();
			if(str[n]<0)//对汉字的处理 
			{
				++n;
				str[n]=getchar();
			}
		}
		fflush(stdin);
		if(str[n]=='\n'||str[n]=='\r')
		str[n]='\0';
		else
		str[n+1]='\0';
		if(zifunum<=len&&zifunum!=0)
			judge=1;
		else
			judge=0;
		if(judge==0)
		{
			printf("您只能输入%d个以内字符或数字，且不能直接输入回车键，请重新输入\n",len);
		}
		//system("pause");
	}
	fflush(stdin);
	return;
}

int cl_strlen(char c[])//能分辨汉字的strlen（因为汉字的ASCII码是负数而且占两个char的空间 
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
}//strlen挺方便的但是怕越界，所以下面的strlen之后都会改成别的

int cl_CtoN(char c[])//数字字符串转化为数字（数字以外的字符会被跳过 
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

char *cl_NtoC(int x)
{
	int temp,len=0,i;
	char str[20];
	temp=x;
	do{
		temp/=10;
		++len;
	}while(temp);
	temp=x;
	for(i=1;i<=len;++i)
	{
		str[len-i]=(temp%10)+'0';
		temp/=10;
	}
	str[len]='\0';
	
	return str;
}

float CtoF(char c[])//数字字符串转化为实数
{
	
	float r=0,d=1;
	int i,k,n=strlen(c);
	for(i=0;c[i]!='.'&&c[i]!='\0';i++);
	k=i;
	for(i=0;i<k;i++)
	{
		r*=10;
		r+=c[i]-'0';
	}
	for(i=k+1;i<n;i++)
	{
		d*=10;
		r+=1.0*(c[i]-'0')/d;
	}
	return r;
}

float our_scanf_float(int mmax)//输入小数并检测 
{
	long long x;
	int i,len=0,t,judge,v;//len表示mmax的位数 
	char str[60],ts[60];
	float r=0,d=1;
	int k,n;
	t=mmax;
	do
	{
		t/=10;
		++len;
	}while(t!=0);
	while(1)
	{
		r=0;d=1;v=0;
		judge=1;//1合法，2不合法 
		printf("请输入一个小于%d的非负小数（最多支持6位小数）：",mmax);
		our_scanf_str(str,len+7);
		n=strlen(str);
		if(str[0]<'0'||str[0]>'9')
		{
			printf("请不要输入负数或无关信息\n");
			continue;
		}
		if(judge==1)
		for(i=0;str[i]!='\0';++i)
		{
			if(str[i]<'0'||str[i]>'9')
			{
				if(str[i]!='.')
				{
					printf("请不要输入无关信息\n");
					judge=0;
					break; 
				}
				else
				++v;
			}
		}
		if(v>=2)
		printf("请不要输入无关信息\n");
		if(judge==0)
		continue;
		for(i=0;str[i]!='.'&&str[i]!='\0';++i);
		strcpy(ts,str);
		ts[i]='\0';
		x=cl_CtoN(ts);
		if(x>mmax)
		{
			printf("输入的数字太大，请重新输入\n");
			continue;
		}
		else
		{
			if(str[i]=='\0')
				return x;
		}
		for(i=0;str[i]!='.';i++);
		k=i;
		if(i+1==n)
		{
			printf("请不要输入无关信息\n");
			continue;
		}
		
		if(i+6<=n)
		{
			printf("小数位数超过6位，请重新输入\n");
			continue;
		}
		for(i=0;i<k;i++)
		{
			r*=10;
			r+=str[i]-'0';
		}
		n=strlen(str);
		for(i=k+1;i<n;i++)
		{
			d*=10;
			r+=1.0/d*(str[i]-'0');
		}
		if(r>mmax)
		{
			printf("输入的数字太大，请重新输入\n");
			continue;
		}
		
		return r;
	}
}

void FtoC(char s1[],float a)
{
	int num,times=1,after_num=0,i;
		float v,t;
		char s2[100];
		num=(int)a;
		int len=0,temp=num;
		while(num)
		{
			++len;
			num/=10;
		}
		num=temp;
		for(i=1;i<=len;++i)
		{
			s1[len-i]=num%10+'0';
			num/=10;
		}
		s1[len++]='.';
		s1[len++]='\0';
		v=(int)a;
		while(a!=v&&after_num<2)
		{
			times*=10;
			t=a*times;
			s2[after_num]=((int)t)%10+'0';
			v+=(s2[after_num]-'0')*1.0/times;
			++after_num;
		}
		if(after_num<2)
		{
			for(i=after_num;i<2;++i)
			s2[i]='0';
		}
		s2[2]='\0';
		strcat(s1,s2);
		s1[++len]='\0';
		return ;
}

int phone_judge(char s[])//判断电话号是否合法（不是是否被注册过）1是合法，0不合法 
{
	int num,i;//num是判断电话号长度用的（没考虑汉字算两个不过后面汉字的情况会被唰下去
	int judge=1;//judge是记录合不合法用的
	num=strlen(s);
	if(num!=11)//不是11位就唰下去（汉字一个顶俩所以除外 
	{
		judge=0;
	}
	else
	{
		for(i=0;i<11;++i)
		if(s[i]<'0'||s[i]>'9')//这里汉字就被唰下去了 
		{
			judge=0;
			break;
		}
	}
	return judge;
}

/*int phone_exist(char s[])//判断电话号是否已被注册，已注册返回1，否则返回0
{
	int judge=0;//用来记录电话号是否被注册用的 
	struct Customer *node=customer_head->next;//顾客的数据从头做一次到尾查一次 
	while(node!=NULL)
	{
		if(strcmp(node->phone,s)==0)//如果顾客的电话号=要查的电话号 
		{
			judge=1;
			break;//找到就不找了 
		}
		node=node->next;
	}
	return judge;
}*/

int mima_judge(char c[])//判断密码格式是否正确，正确返回1，否则返回0
{//密码格式：长度为6~16（含边界），只能有大小写字母及数字 
	int i,n,judge=1;//i用来for循环，n用来判断长度，judge用来记录是否合法 
	for(i=0;c[i]!='\0';++i) 
	if(i>16)//不用strlen是因为怕越界
	break;
	n=i;
	if(n<6||n>16)//长度越界（汉字一个顶俩（指占用空间），下面会处理 
	return 0;
	for(i=0;i<n;++i)
	{
		if(('0'<=c[i]&&c[i]<='9')||('a'<=c[i]&&c[i]<='z')||('A'<=c[i]&&c[i]<='Z'))//符合要求的字符就跳过 
		continue;
		else
		judge=0;
	}
	return judge;
}

void search_customer()//寻找单一顾客
{
	
	int judge;//记录要找的顾客是否存在 
	char v='1';//记录是否要查找顾客，要的话是1，不要的话是2 
	char s[30],c[20],choice[5];//记录顾客姓名（之后会加上按照电话号查询的） 
	struct Customer *node;
	printf("请选择您的查询方式(扣0退出)\n");
	printf("1.姓名    2.电话\n");
	our_scanf_str(choice,1);
	switch(choice[0]-'0')
	{
		case 0:
			return;
		case 1: 
			while(v=='1')
			{
				system("cls");
				printf("请输入您要查询的顾客的名称: ");
				our_scanf_str(s,7);//输入顾客信息 
				judge=0;//默认要找的顾客不存在 
				node=customer_head->next;
				while(node!=NULL)
				{
					if(strcmp(node->name,s)==0)
					{
						judge=1;
						printf("-----------------------------分割线--------------------------\n"); 
						printf("姓名：%s\n电话：%s\n密码：%s\n地址：%s\n用户星级：%s\n",node->name,node->phone,node->password,node->address,node->vip);
					}
					node=node->next;
				}
				if(judge==0)//没找到的情况 
				{
					printf("-----------------------------分割线--------------------------\n"); 
					printf("未查询到顾客信息\n");
				}
				while(1)
				{
					printf("请问是否要继续查询\n");
					printf("1.是    2.否\n");
					our_scanf_str(c,1);//c暂时用来记录是否用来继续查询（因为c暂时没用 
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
			break;
		case 2:
			while(v=='1')
			{
					printf("请输入您要查询的顾客的电话: ");
					our_scanf_str(s,11);//输入顾客信息 
					node=findValueByKey(haxi_customer,s);
					if(node!=NULL)
					{
						printf("-----------------------------分割线--------------------------\n"); 
						printf("姓名：%s\n电话：%s\n密码：%s\n地址：%s\n用户星级：%s\n",node->name,node->phone,node->password,node->address,node->vip);
					}
					else
					{
						printf("-----------------------------分割线--------------------------\n"); 
						printf("未查询到顾客信息\n");
					}
					
					while(1)
					{
						fflush(stdin);
						printf("请问是否要继续查询\n");
						printf("1.是    2.否\n");
						our_scanf_str(c,1);//c暂时用来记录是否用来继续查询（因为c暂时没用 
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
		default:
			printf("您只能输入0\1\2中的数字\n");
	} 
	
}

void print_customer()//打印所有顾客信息 
{
	struct Customer *node=customer_head->next;
//	printf("即将打印所有顾客的信息\n");
//	Sleep(2000);//等2秒读上一行的输出信息 
	while(node!=NULL)
	{
		printf("-----------------------------分割线--------------------------\n"); 
		printf("姓名：%s\n电话：%s\n密码：%s\n地址：%s\n用户星级：%s\n",node->name,node->phone,node->password,node->address,node->vip);
		node=node->next;
	}
}

void cshlr()//初始化录入（把文本里的顾客信息录进去（链表存储顾客信息 
{
	iniHashTable(haxi_customer);
	customer_head=(struct Customer *)malloc(sizeof(struct Customer));//第一位顾客前面的头指针 
	customer_head->next=NULL;//最后会指向NULL
	struct Customer *node,*pre=customer_head;//node是把顾客信息用来一个一个插入的，pre是记录前一个顾客信息的 
	FILE *cl_fp=NULL;//打开文件 
//	printf("正在打开文件，请稍后......\n");
	cl_fp=fopen("customer.txt","r");
	if(cl_fp==NULL)//要是没打开就直接return 
	{
//		printf("文件打开失败\n");
		return;
	}
//	else
//	printf("文件打开成功，开始同步顾客信息\n"); 
	while(!feof(cl_fp))//从头开始读文件，直到读到结尾 
	{
		node=(struct Customer *)malloc(sizeof(struct Customer));//分配地址 
		//↓将文件里的数据存到数组里 
		fscanf(cl_fp,"%s%s%s%s%s%s",node->order,node->name,node->phone,node->password,node->address,node->vip);
		insertEntry(haxi_customer,node->name,node);
		insertEntry(haxi_customer,node->phone,node);
		insertEntry(haxi_customer,node->order,node);
		node->next=pre->next;//插入数据 
		pre->next=node;//同上 
		pre=pre->next;//同上 
//		printf("%s\n",pre->name);//看一眼插入了啥 
	}
	customer_end=pre;//记录最后一位顾客信息 
//	printf("顾客信息同步结束\n");
	fclose(cl_fp);
}

void cl_insert_customer()//注册账户 
{
	system("cls");
	int num,judge,i;//num->字符串长度以及临时工具人（工具人情况比较少 
	//order是序号，表示这是第几位顾客，name是姓名，password是密码，phone是电话号，vip是等级数
	//str用来接受输入的数据，开的大一点防止数据太大越界造成bug，str处理后再传递给order那些变量 
	//（虽然还是会越界，之后会看看用getchar优化一下，现在先凑合着
	char str[1000000],order[10],name[50],password[50],address[130],phone[50],vip[2];
	vip[0]='0';
//	FILE *cl_fp=NULL;
//	cl_fp=fopen("customer.txt","a");
	while(1)//输入顾客姓名 
	{
		judge=1;//记录姓名是否合法 
		printf("请输入您的姓名（长度为2-7）：");
		our_scanf_str(str,7);;//输入姓名并处理 
		num=cl_strlen(str);//cl_strlen能处理一个汉字占两个空间的问题，返回值是字符串长度 
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
	while(1)//输入顾客手机号 
	{
		printf("请输入您的11位手机号：");
		our_scanf_str(str,11);//输入手机号 
		judge=phone_judge(str);//判断手机号是否合法（不管注没注册），合法是1，不合法是0 
		if(judge==0)
		{
			printf("手机号格式有误，请重新输入\n");//跟后面的judge含义有点小冲突所以不合法就直接继续循环 
			continue; 
		}
		else
		{
			if(findValueByKey(haxi_customer,str)!=NULL)//判断手机号是否存在（存在是1不存在是0 
			judge=1;
			else
			judge=0;
		}
		if(judge==0)
		break;
		else
		printf("手机号格式有误或手机号已注册，请重新输入\n"); 
	}
	strcpy(phone,str);//（str的内容传给phone 
	while(1)//填写密码 
	{
		//密码合法情况如下 
		printf("请填写您的密码\n#仅支持数字及大小写字母\n#密码长度应为6-16位\n密码: "); 
		our_scanf_str(str,16);//输入密码 
		judge=mima_judge(str);//合法是1不合法是0 
		if(judge==0)
		{
			printf("密码格式有误，请重新输入\n");//不合法就接着循环直到输合法了 
		}
		else
		break;
	}
	strcpy(password,str);//把str的内容传给password 
	while(1)//填写收货地址 
	{
		printf("请输入您的收货地址（仅支持<=60字）：");
		our_scanf_str(str,60);//输入收货地址 
		judge=1;//记录收货地址，合法是1，不合法是0，默认合法 
		if(cl_strlen(str)>60)
		{
			printf("超出60字了，请重新输入\n");
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
	strcpy(address,str);//str的内容传给address 
	printf("注册成为本店付费会员后会有优惠，以下为本店会员特权：\n");
	printf("1星级用户在本店的一切消费享九五折\n2星级用户享九折\n3星级用户享八五折\n");
	while(1)//注册会员 
	{
		printf("请问您是否有意向成为本店付费会员？\n"); 
		printf("（输入“1”代表“是”，输入“2”代表“否”）\n");
		our_scanf_str(str,1);//输入1或2（别的也行就是之后会被唰掉 
		if(strcmp(str,"1")==0)//如果要注册成为vip 
		{
			while(1)
			{
				printf("请选择您要注册的VIP等级\n");
				gets(str);//就是选想成为几星VIP，只能是1~3星，上面有提醒 
				if(strlen(str)!=1)//超出1位数是不合法的 
				{
					printf("格式有误，请重新输入\n");//不合法就无限循环直到合法 
				}
				else
				{
					if('1'<=str[0]&&str[0]<='3')//合法就把str的内容传给vip 
					{
						strcpy(vip,str);
						printf("恭喜您成为本店的%c星级用户，祝您用餐愉快！\n",str[0]);
						ShellExecute(NULL, "open","二维码.png",NULL,NULL,SW_SHOWNA );
						printf("请扫描二维码并在2小时内完成后续支付，否则后续系统会将您设置为免费用户\n");
						break;
					}
					else
					{
						printf("格式有误，请重新输入\n");
					}
				}
			}
			break;
		}
		else if(strcmp(str,"2")==0)//要是不想当VIP就把VIP 等级调成0 
		{
			vip[0]='0';
			vip[1]='\0';//顺手加了个结束用的标识符 
			printf("恭喜您成为本店免费用户，祝您在本店用餐愉快！\n");
			break;
		}
	}
	strcpy(order,customer_end->order);//把最后一位顾客的序号拷到order里了 
	num=strlen(order);//转换成数字 
	order[num-1]='\0';//因为order里有个“，”，比如说第12位顾客的order就是“12，” 
	num=cl_CtoN(order);//转换成功 
	++num;//序号加一位 
	//↓这玩意就是看一眼录入的数据是什么样的 
	printf("\n%d,   %s     %s     %s     %s     %d\n\n",num,name,phone,password,address,vip[0]-'0');
	//↓这个是录入数据 
//	fprintf(cl_fp,"\n%d,   %s     %s     %s     %s     %d",num,name,phone,password,address,vip[0]-'0');
//	fclose(cl_fp);//记得关文件不然录不进去 
	
	
	struct Customer *node=(struct Customer *)malloc(sizeof(struct Customer));;
	customer_end->next=node;
	node->next=NULL;
	int len=0,temp=num;
	while(num)
	{
		++len;
		num/=10;
	}
	num=temp;
	for(i=0;i<len;++i)
	{
		order[len-i]=num%10+'0';
		num/=10;
	}
	order[len]=',';
	order[len+1]='\0';
	strcpy(node->name,name);
	strcpy(node->phone,phone);
	strcpy(node->password,password);
	strcpy(node->address,address);
	strcpy(node->vip,vip);
	customer_end=node;
	
	insertEntry(haxi_customer,node->name,node);//数据同步到哈希表 
	insertEntry(haxi_customer,node->phone,node);
	
	customer_to_txt();//把数据录入到文件里 
	cshlr();
	system("pause");
}
void delete_customer()//删除顾客信息 
{
	int judge=0;//judge用来记录判断的各种数据是否合法，num用来记录第num位顾客（后面用到num时就容易懂了 
	char phone[25];//记录电话号，开大一点防越界，后期可能拿getchar优化一下 
	struct Customer *pre,*node;//pre记录前一个节点，node当前节点，从第一位顾客开始 
	/*while(judge==0)//输入手机号并判断手机号格式是否合法（就是不管是否被注册过 
	{
		system("cls");
		printf("请输入手机号\n");
		our_scanf_str(phone,11);//读入一行字符串当手机号 
		judge=phone_judge(phone);//判断手机号格式是否正确的函数，正确是1，不正确是0 
		if(judge==0)printf("手机号格式有误，请重新输入\n");
		else break;
	}*/
	printf("请输入手机号\n");
	our_scanf_str(phone,11);//读入一行字符串当手机号 
	node=(Customer*)findValueByKey(haxi_customer,phone);
	if(node!=NULL)//判断手机号是否被注册过，注册过是1，否则是0 
	judge=1;
	else
	judge=0;
	
	if(judge==0)//没被注册的情况 
	{
		printf("该手机号未注册\n");
	}
	else//被注册的情况，现在node=那个顾客 
	{
		int num,i;
		char order[10];
		strcpy(order,node->order);
		num=cl_CtoN(order)-1;
		if(num>0)
		{
			int len=0,temp=num;
			while(temp)
			{
				++len;
				temp/=10;
			}
			temp=num;
			for(i=1;i<=len;++i)
			{
				order[len-i]=temp%10+'0';
				temp/=10;
			}
			order[len]=',';
			order[len+1]='\0';
			pre=(Customer*)findValueByKey(haxi_customer,order);
		}
		else
		pre=customer_head;
		pre->next=node->next;//链表里删掉他 
		removeEntry(haxi_customer,node->order);
		removeEntry(haxi_customer,node->name);
		removeEntry(haxi_customer,node->phone);
		free(node);
	}
	customer_to_txt();
	cshlr();
	return;
}

void printcustomermanage()
{
	printf("*****************************************\n");
	printf("#         欢迎进入顾客管理模块          #\n");
	printf("*****************************************\n\n");
}

void custom_mohu()
{
	system("cls");
	int v=0;
	char s[20];
	printf("请输入您要查询的顾客的姓名:\n");
	our_scanf_str(s,7);
	Customer *tmp=customer_head->next;
	printf("——————————————\n");
	printf("以下为相关信息：\n");
	while(tmp!=NULL)
	{
		if(strstr(tmp->name,s)!=NULL)
		{
			++v;
			printf("————————————————————————————\n");
			printf("%d：\n姓名：%s\n密码：%s\n电话：%s\n地址：%s\n星级：%s\n",v,tmp->name,tmp->password,tmp->phone,tmp->address,tmp->vip);
		}
		tmp=tmp->next;
	}
	if(v==0)
	{
		printf("————————————————————————————\n");
		printf("NOT FOUND\n");
	}
	return;
}

void choice_customermanage(struct Customer *c)
{
	system("cls");
	char choice[5],s[20];
	struct Customer* list=c;
	while(1){
		printcustomermanage();
		c=list;//每次循环均需将c恢复指向原链表的首地址  
		print_customer(); 
		printf("============================================\n");
		printf("\t顾客管理                \n");
		printf("\t\t\t\t\t\n");
		printf("\t0.退出模块               \n");
		printf("\t1.寻找顾客               \n");
		printf("\t2.删除顾客               \n");
		printf("\t3.模糊搜索顾客           \n");
		printf("============================================\n");
		our_scanf_str(choice,1);
		if(choice[0]=='0'){
			system("cls");
			break;
		}
		switch(choice[0]-'0')
		{
			case 0:	break;
			case 1:
				search_customer();
				system("pause");
				system("cls");
				break;
			case 2:
				delete_customer();
				system("pause");
				system("cls");
				break;
			case 3:
				custom_mohu();
				system("pause");
				system("cls");
				break;
			default:
				system("cls");
				printf("您只能输入0/1/2/3\n\n");break;
		}
	}
}
