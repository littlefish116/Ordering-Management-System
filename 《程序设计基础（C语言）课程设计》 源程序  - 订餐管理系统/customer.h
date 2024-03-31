//#include"statistics.h"

//while(scanf("%s",i)!=EOF){
//			if(strcmp(i,"0")==0)break;
//			
//			 
//		} 

void change_address(struct Customer *c)
{
	int judge,i;
	char tmp[4],new_address[130];
	while(1)
	{
		system("cls");
		printf("您当期的地址为：%s\n",c->address); 
		printf("（地址长度应为60位以内，不能输入空格）\n");
		printf("请输入您要更改的地址（扣0返回上一级）:");
		our_scanf_str(new_address,60);
		if(new_address[0]=='0'&&new_address[1]=='\0')
		{
			return;
		}
		judge=1;
		for(i=0;new_address[i]!='\0';++i)//地址格式正确返回1，否则返回0 
		{
			if(new_address[i]==' ')
			{
				judge=0;
				break;
			}
		}
		if(judge==0)
		{
			printf("地址格式有误，请重新输入\n");
			system("pause");
		}
		else
		{
			while(1)
			{
				printf("您确定将地址修改为【%s】吗",new_address);
				printf("1、是  2、否\n");
				our_scanf_str(tmp,1);
				if(tmp[0]!='1'&&tmp[0]!='2')
				{
					printf("请输入数字1或2\n");
				}
				else
				break;
			}
			if(tmp[0]=='1')
			{
				printf("地址更改成功！");
				break;
			}
			else
			{
				while(1)
				{
					printf("请问您是否要重新修改地址\n");
					printf("1、是  2、否\n");
					our_scanf_str(tmp,1);
					if(tmp[0]=='1')
					{
						change_address(c);
						return;
					}
					else if(tmp[0]=='2')
					{
						return;
					}
					else
					{
						printf("请您输入数字1或2\n");
					}
				}
			}
		}
	}
	strcpy(c->address,new_address);
	customer_to_txt();
	system("pause");
	return;
}

jilu get_food(char s[][50])
{
	system("cls");
	jilu t={0,0};
	printmeal(meal_head);
	int n=0,i;//点了n个菜 
	char temp[4];
	float value=0;
	struct meal *tmp;
	printf("请选择您要选择的菜品名称\n扣0结束点餐\n");
	while(1)//顾客点单太多会越界，但这里没有控制 
	{ 
		if(n>200)
		{
			printf("您点的餐太多了，本店难以承受，因此取消了您的订单，十分抱歉\n");
			return t;
		}
		our_scanf_str(s[++n],20);
		if(s[n][0]=='0'&&s[n][1]=='\0')
		{
			--n;
			if(n==0)
			{
				printf("您还没有点餐\n");
			}
			else
			{
				printf("您点的菜有：\n");
				for(i=1;i<=n;++i)
				{
					tmp=(struct meal*)findValueByKey(haxi_meal,s[i]);
					strcpy(s[i],tmp->name);
					printf("%d、%s\n",i,tmp->name);
				}
			}
			printf("\n请问您是否要结束点单\n");
			printf("1、是\t2、否\n");
			while(1)
			{
				our_scanf_str(temp,1);
				if(temp[0]=='1'||temp[0]=='2')
				break;
				else
				{
					printf("您只能输入1或2两个数字");
				}
			}
			if(temp[0]=='1')
			{
				for(i=1;i<=n;++i)
				{
					tmp=(struct meal*)findValueByKey(haxi_meal,s[i]);
					value+=tmp->price;
				}
				printf("点单结束\n");
				system("pause");
				t.num=n;
				t.value=value;
				return t;
			}
			else if(temp[0]=='2')
			{
				printf("请继续点餐\n");
				continue;
			}
		}
		tmp=(struct meal*)findValueByKey(haxi_meal,s[n]);
		if(tmp==NULL)
		{
			--n;
			printf("没有这道菜，请输入正确的菜品名称\n");
		}
		else
		{
			printf("【%s】点单成功，请继续点单（扣0结束点单）\n",tmp->name);
		}
	}
}

struct staff *choose_waimaiyuan(struct meal *s,struct staff *f,struct Customer *c)
{
	int num=0,x;//记录一共有num位外卖员 
	char choice[4],id[20],store[100][10],word=0;
	struct staff *tmp;
	while(1)
	{
		//system("cls");
		f=staff_head->next;
		printf("请问您是否要指定外卖员（扣0返回上一级）\n");
		printf("1、是  2、否\n");
		our_scanf_str(choice,1);
		if(choice[0]=='0')
		{
			return NULL;
		}
		else if(choice[0]=='1')
		{
			while(f!=NULL)
			{
				//printf("工号：%s，姓名：%s\n",f->staff_id,f->staff_name);
				if(strcmp(f->staff_idt,"外卖员")==0)
				{
					printf("工号：%s，姓名：%s\n",f->staff_id,f->staff_name);
					strcpy(store[num++],f->staff_id);
					word=1;
				}
				f=f->next;
			}
		//	printf("num=%d\n",num);
			/*			if(word==0){
				printf("暂时没有可用的外卖员\n");
				return NULL;
			}*/
			while(1)
			{
				printf("请选择您要指定的外卖员工号（扣0表示不指定外卖员）：");
				our_scanf_str(id,15);    
				if(id[0]=='0'&&id[1]=='\0')
				{
					printf("系统将随机为您分配外卖员！\n");
					x=rand()%num;
		//			printf("x=%d\n",x);
					tmp=(struct staff*)findValueByKey(haxi_staff,store[x]);
					printf("工号为%s 姓名为【%s】的外卖员将为您服务!\n",tmp->staff_id,tmp->staff_name);
					printf("如果对其服务有任何意见，请及时联系我们。\n");
					break;
				}
				f=(struct staff*)findValueByKey(haxi_staff,id);
				if(f==NULL)
				{
					printf("该外卖员不存在，请重新输入\n"); 
				}
				else
				{
					tmp=f;
					break;
				} 
			}
			break;
		}
		else if(choice[0]=='2')
		{
			while(f!=NULL)
			{
				if(strcmp(f->staff_idt,"外卖员")==0)
				{
					printf("工号：%s，姓名：%s\n",f->staff_id,f->staff_name);
					strcpy(store[num++],f->staff_id);
					word=1;
				}
				f=f->next;
			}
			printf("系统将随机为您分配外卖员！\n");
			x=rand()%num;
	//		printf("x=%d\n",x);
			//printf("系统将随机为您分配外卖员！\n");
			tmp=(struct staff*)findValueByKey(haxi_staff,store[x]);
			printf("工号为%s 姓名为【%s】的外卖员将为您服务!\n",tmp->staff_id,tmp->staff_name);
			printf("如果对其服务有任何意见，请及时联系我们。\n");
			break;
		}
		else
		{
			printf("请您输入数字1或2\n");
		}
	}
	while(1)
	{
		printf("系统默认您的收货地址为您用户信息里填写的地址：%s\n",c->address);
		printf("请问您是否要修改地址\n");
		printf("1、是  2、否\n");
		our_scanf_str(choice,1);
		if(choice[0]=='1')
		{
			change_address(c);
			fflush(stdin);
			break;
		}
		else if(choice[0]=='2')
		{
			break;
		}
		else
		{
			printf("请您输入数字1或2\n");
		}
	}
	return tmp;
}

float distance()
{
	float dis;
	printf("请输入您的收货地址距离我们饭店的距离（单位:km）\n");
	printf("（每公里收费1元配送费）\n");
	dis=our_scanf_float(10);
	return dis;
}

void DingCanJieMian(struct meal *s,struct staff *f,struct Customer *c)
{
	system("cls");
	time_t timep;
	struct tm *p;
	printf("******************************************\n");
	printf("#            欢迎来到订餐界面            #\n");
	printf("#               0.退出系统               #\n");
	printf("#               1.店内就餐               #\n");
	printf("#               2.外卖                   #\n");
	printf("******************************************\n\n");
	printf("【温馨提示】关于在本店的一切消费\n1星级用户享九五折，\n2星级用户享九折，\n3星级用户享八五折。\n");
	int judge=0,dh,d;
	char choice[4],need[201][50];
	float value;
	struct staff *tmp;
	struct jilu x;
	our_scanf_str(choice,1);
	switch(choice[0]-'0')
	{
		case 0:
			break;
		case 1:
			x=get_food(need);
			value=x.value;
			if(x.value==0)
			break;
			value*=(1-((c->vip[0]-'0')*0.05));
			printf("这次点单您共需支付%.2f元，请扫描二维码支付\n",value);
			ShellExecute(NULL, "open","二维码.png",NULL,NULL,SW_SHOWNA );
			insert_bill(c->phone,x.num,need,0,NULL,value);
			system("pause");
			break;
		case 2:
			
			x=get_food(need);
			value=x.value;
			if(x.value==0)
			break;
			tmp=choose_waimaiyuan(s,f,c);
			if(tmp==NULL)
			{
				judge=1;
				break;
			}
			printf("配送距离每1km需要支付1元配送费\n");
			printf("配送到达大约需要6分钟/公里\n");
			d=(int)distance();
			value+=d;
			time(&timep);
			timep+=d*6*60;
			p=localtime(&timep); 
			value*=(1-((c->vip[0]-'0')*0.05));
//			p->tm_min=(p->tm_min+6*(int)d)%60;
//			dh=(p->tm_min+6*(int)d)/60;
//			p->tm_hour=(p->tm_hour+dh)%24;
			printf("您的配餐大约在%0.2d:%0.2d送达\n",p->tm_hour,p->tm_min) ;
			printf("这次点单您共需支付%.2f元，请扫描二维码支付\n",value);
			ShellExecute(NULL, "open","二维码.png",NULL,NULL,SW_SHOWNA );
			insert_bill(c->phone,x.num,need,1,tmp,value);
			system("pause");
			break;
		default:
			printf("请您输入0~2中的一个数字\n");
			break;
	}
	if(judge==1)
	{
		DingCanJieMian(s,f,c);
		return;
	}
	printf("期待您的下次光临！\n");
	system("pause");
}

void choice_customer(struct meal *s,struct staff *f,struct Customer *c)
{
	system("cls");
	char i[5],kind[5];
	float low,high,temp;
	while(1){
//		total=0;
		printf("【%s级会员】 %s 您好，欢迎光临236餐馆！\n\n",c->vip,c->name); 
		printf("*****************************************\n");
		printf("#              请浏览菜单               #\n");
		printmeal(s);
//		scanf("%s",i);
		printf("============================================\n");
		printf("\t请扣数字进行操作               \n");
		printf("\t0.退出该界面              \n");	
		printf("\t1.查菜品区间              \n");
		printf("\t2.查菜品种类              \n");
		printf("\t3.订购餐品              \n");
		printf("============================================\n");
//		scanf("%s",i);
		our_scanf_str(i,1); 
		if(i[1]!=0){
			system("cls");
			printf("您只能输入0/1/2/3\n\n");
		} else if(strcmp(i,"0")==0)break;
		else{
			switch(i[0]-'0'){
				case 0:break;
				case 1:printf("请写出您需要搜索的价格区间：\n");
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
					searchprice(s,low,high); break;
				case 2:printf("请写出您需要搜索的菜品种类：\n");
					printf(" 1、主食，2、荤菜，3、素菜，4、甜品，5、小吃\n");
					our_scanf_str(kind,1);
					searchkind(s,kind);
					break;
				case 3:
					DingCanJieMian(s,f,c);
					break;
				default:break;
			}
		}
//		system("pause");
//		system("cls");
		break;
	}
}

void CustomStarChange(struct meal *s,struct staff *f,struct Customer *c)
{
	int n,judge=0;//n表示输入的字符串的长度，judge用于判断是否跳出循环 
	char v,ch;//接受输入的信息用的 
	while(judge==0)
	{
		system("cls");
		fflush(stdin);
		printf("(您可以输入0~3中的一个数字，表示您要成为的星级)\n");
		printf("请输入您要改变的星级(扣4返回上一级)：");
		v=getchar();
		n=1;
		ch=v;
		while(ch!='\n'&&ch!='\r'&&n<=2){
			ch=getchar();
			++n;
			//printf("n=%d,c=%c\n",n,ch);
		}
		fflush(stdin);
		if(n==2&&v=='4')
		{
			return;
		}
		if(n!=2||v<'0'||v>'3')
			judge=0;
		else
			judge=1;
		if(judge==0)
		{
			printf("您只能输入0~3中的一个数字，请重新输入\n");
		}
	}
	c->vip[0]=v;
	customer_to_txt();
	printf("星级变更成功，您现在已变更为%c星级用户\n",c->vip[0]);
	if(c->vip[0]!='0')
	{
		ShellExecute(NULL, "open","二维码.png",NULL,NULL,SW_SHOWNA );
		printf("请扫描二维码并在2小时内完成后续支付，否则默认您不进行星级变更\n");
	}
	system("pause");
	return;
}

void change_password(struct meal *s,struct staff *f,struct Customer *c)
{
	int judge;
	char new_password[40];
	while(1)
	{
		system("cls");
		printf("（密码长度应为6~16位，只能包含数字及大小写字母）\n");
		printf("请输入您要更改的密码（扣0返回上一级）:");
		our_scanf_str(new_password,16);
		if(new_password[0]=='0'&&new_password[1]=='\0')
		{
			return;
		}
		judge=mima_judge(new_password);//密码格式正确返回1，否则返回0 
		if(judge==0)
		{
			printf("密码格式有误，请重新输入\n");
			system("pause");
		}
		else
		{
			strcpy(c->password,new_password);
			customer_to_txt();
			printf("密码更改成功！");
			system("pause");
			return;
		}
	}
}

int customer_interface(struct meal *s,struct staff *f,struct Customer *c)
{
	char choice[5];
	printf("登录成功！\n\n");
	system("pause");
	while(1)
	{
		system("cls");
		printf("【%s级会员】 %s 您好，欢迎光临236餐馆！\n\n",c->vip,c->name); 
		printf("******************************************\n");
		printf("#            欢迎来到用户界面            #\n");
		printf("#               0.退出系统               #\n");
		printf("#               1.订餐                   #\n");
		printf("#               2.修改密码               #\n");
		printf("#               3.修改VIP等级            #\n");
		printf("#               4.修改地址               #\n");
		printf("******************************************\n\n");
		our_scanf_str(choice,1);
		switch(choice[0]-'0')
		{
			case 0:
				break;
			case 1:
				choice_customer(s,f,c);
				break;
			case 2:
				change_password(s,f,c);
				break;
			case 3:
				CustomStarChange(s,f,c);
				break;
			case 4:
				change_address(c);
				break;
			default:
				printf("您只能输入0/1/2/3/4\n\n");
				break;
		}
		if(choice[0]=='0')
			break;
		if(choice[0]<'0'||choice[0]>'3')
			system("cls");
	}
	return 0;
}

void customerlogin(struct meal *s,struct staff *f,struct Customer *c)
{
	system("cls");
	char i[100],j[100];
//	struct Customer *list=c; 
	while(1){
		printf("输入您的电话(扣0可退出)：\n");
		our_scanf_str(i,11);
		if(strcmp(i,"0")==0) break; 
		c=(Customer*)findValueByKey(haxi_customer,i);
		if(c==NULL){
			printf("\n无此账号，请注册\n");
			system("pause");
			system("cls");
			break;
		}
		printf("输入您的密码：\n");
		our_scanf_str(j,16);
		if(strcmp(c->password,j)==0){
			if(customer_interface(s,f,c)==0)return;//进入用户操作界面 
			system("cls");
		}
		else{
			system("cls");
			printf("密码错误\n");
		}
	}
}

void customerfirst(struct meal *s,struct staff *f,struct Customer *c)
{
	system("cls");
	char i[4];
	while(1){
		printf("*****************************************\n");
		printf("#        欢迎来到客户端订餐界面         #\n");
		printf("#              0.退出系统               #\n");
		printf("#              1.注册账户               #\n");
		printf("#              2.登录账户               #\n");
		printf("#              3.注销账户               #\n");
		printf("*****************************************\n\n");
		our_scanf_str(i,1);
		if(i[1]!=0){
			system("cls");
			printf("您只能输入0/1/2/3\n\n");
		} 
		else{
			if(i[0]=='0')break;
			switch(i[0]-'0'){
				case 0:break;
				case 1:
					cl_insert_customer(); //进入账户注册界面 
					system("cls");
					break;
				case 2:
					customerlogin(s,f,c);//进入账户登录界面 
					system("cls");
					break;
				case 3:
					delete_customer();//注销用户界面 
					system("cls");
					break;
				default:
					system("cls");
					printf("您只能输入0/1/2/3\n\n");
					break;
			}
		}
	} 
}
