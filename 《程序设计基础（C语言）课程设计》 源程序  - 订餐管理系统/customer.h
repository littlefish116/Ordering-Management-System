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
		printf("�����ڵĵ�ַΪ��%s\n",c->address); 
		printf("����ַ����ӦΪ60λ���ڣ���������ո�\n");
		printf("��������Ҫ���ĵĵ�ַ����0������һ����:");
		our_scanf_str(new_address,60);
		if(new_address[0]=='0'&&new_address[1]=='\0')
		{
			return;
		}
		judge=1;
		for(i=0;new_address[i]!='\0';++i)//��ַ��ʽ��ȷ����1�����򷵻�0 
		{
			if(new_address[i]==' ')
			{
				judge=0;
				break;
			}
		}
		if(judge==0)
		{
			printf("��ַ��ʽ��������������\n");
			system("pause");
		}
		else
		{
			while(1)
			{
				printf("��ȷ������ַ�޸�Ϊ��%s����",new_address);
				printf("1����  2����\n");
				our_scanf_str(tmp,1);
				if(tmp[0]!='1'&&tmp[0]!='2')
				{
					printf("����������1��2\n");
				}
				else
				break;
			}
			if(tmp[0]=='1')
			{
				printf("��ַ���ĳɹ���");
				break;
			}
			else
			{
				while(1)
				{
					printf("�������Ƿ�Ҫ�����޸ĵ�ַ\n");
					printf("1����  2����\n");
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
						printf("������������1��2\n");
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
	int n=0,i;//����n���� 
	char temp[4];
	float value=0;
	struct meal *tmp;
	printf("��ѡ����Ҫѡ��Ĳ�Ʒ����\n��0�������\n");
	while(1)//�˿͵㵥̫���Խ�磬������û�п��� 
	{ 
		if(n>200)
		{
			printf("����Ĳ�̫���ˣ��������Գ��ܣ����ȡ�������Ķ�����ʮ�ֱ�Ǹ\n");
			return t;
		}
		our_scanf_str(s[++n],20);
		if(s[n][0]=='0'&&s[n][1]=='\0')
		{
			--n;
			if(n==0)
			{
				printf("����û�е��\n");
			}
			else
			{
				printf("����Ĳ��У�\n");
				for(i=1;i<=n;++i)
				{
					tmp=(struct meal*)findValueByKey(haxi_meal,s[i]);
					strcpy(s[i],tmp->name);
					printf("%d��%s\n",i,tmp->name);
				}
			}
			printf("\n�������Ƿ�Ҫ�����㵥\n");
			printf("1����\t2����\n");
			while(1)
			{
				our_scanf_str(temp,1);
				if(temp[0]=='1'||temp[0]=='2')
				break;
				else
				{
					printf("��ֻ������1��2��������");
				}
			}
			if(temp[0]=='1')
			{
				for(i=1;i<=n;++i)
				{
					tmp=(struct meal*)findValueByKey(haxi_meal,s[i]);
					value+=tmp->price;
				}
				printf("�㵥����\n");
				system("pause");
				t.num=n;
				t.value=value;
				return t;
			}
			else if(temp[0]=='2')
			{
				printf("��������\n");
				continue;
			}
		}
		tmp=(struct meal*)findValueByKey(haxi_meal,s[n]);
		if(tmp==NULL)
		{
			--n;
			printf("û������ˣ���������ȷ�Ĳ�Ʒ����\n");
		}
		else
		{
			printf("��%s���㵥�ɹ���������㵥����0�����㵥��\n",tmp->name);
		}
	}
}

struct staff *choose_waimaiyuan(struct meal *s,struct staff *f,struct Customer *c)
{
	int num=0,x;//��¼һ����numλ����Ա 
	char choice[4],id[20],store[100][10],word=0;
	struct staff *tmp;
	while(1)
	{
		//system("cls");
		f=staff_head->next;
		printf("�������Ƿ�Ҫָ������Ա����0������һ����\n");
		printf("1����  2����\n");
		our_scanf_str(choice,1);
		if(choice[0]=='0')
		{
			return NULL;
		}
		else if(choice[0]=='1')
		{
			while(f!=NULL)
			{
				//printf("���ţ�%s��������%s\n",f->staff_id,f->staff_name);
				if(strcmp(f->staff_idt,"����Ա")==0)
				{
					printf("���ţ�%s��������%s\n",f->staff_id,f->staff_name);
					strcpy(store[num++],f->staff_id);
					word=1;
				}
				f=f->next;
			}
		//	printf("num=%d\n",num);
			/*			if(word==0){
				printf("��ʱû�п��õ�����Ա\n");
				return NULL;
			}*/
			while(1)
			{
				printf("��ѡ����Ҫָ��������Ա���ţ���0��ʾ��ָ������Ա����");
				our_scanf_str(id,15);    
				if(id[0]=='0'&&id[1]=='\0')
				{
					printf("ϵͳ�����Ϊ����������Ա��\n");
					x=rand()%num;
		//			printf("x=%d\n",x);
					tmp=(struct staff*)findValueByKey(haxi_staff,store[x]);
					printf("����Ϊ%s ����Ϊ��%s��������Ա��Ϊ������!\n",tmp->staff_id,tmp->staff_name);
					printf("�������������κ�������뼰ʱ��ϵ���ǡ�\n");
					break;
				}
				f=(struct staff*)findValueByKey(haxi_staff,id);
				if(f==NULL)
				{
					printf("������Ա�����ڣ�����������\n"); 
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
				if(strcmp(f->staff_idt,"����Ա")==0)
				{
					printf("���ţ�%s��������%s\n",f->staff_id,f->staff_name);
					strcpy(store[num++],f->staff_id);
					word=1;
				}
				f=f->next;
			}
			printf("ϵͳ�����Ϊ����������Ա��\n");
			x=rand()%num;
	//		printf("x=%d\n",x);
			//printf("ϵͳ�����Ϊ����������Ա��\n");
			tmp=(struct staff*)findValueByKey(haxi_staff,store[x]);
			printf("����Ϊ%s ����Ϊ��%s��������Ա��Ϊ������!\n",tmp->staff_id,tmp->staff_name);
			printf("�������������κ�������뼰ʱ��ϵ���ǡ�\n");
			break;
		}
		else
		{
			printf("������������1��2\n");
		}
	}
	while(1)
	{
		printf("ϵͳĬ�������ջ���ַΪ���û���Ϣ����д�ĵ�ַ��%s\n",c->address);
		printf("�������Ƿ�Ҫ�޸ĵ�ַ\n");
		printf("1����  2����\n");
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
			printf("������������1��2\n");
		}
	}
	return tmp;
}

float distance()
{
	float dis;
	printf("�����������ջ���ַ�������Ƿ���ľ��루��λ:km��\n");
	printf("��ÿ�����շ�1Ԫ���ͷѣ�\n");
	dis=our_scanf_float(10);
	return dis;
}

void DingCanJieMian(struct meal *s,struct staff *f,struct Customer *c)
{
	system("cls");
	time_t timep;
	struct tm *p;
	printf("******************************************\n");
	printf("#            ��ӭ�������ͽ���            #\n");
	printf("#               0.�˳�ϵͳ               #\n");
	printf("#               1.���ھͲ�               #\n");
	printf("#               2.����                   #\n");
	printf("******************************************\n\n");
	printf("����ܰ��ʾ�������ڱ����һ������\n1�Ǽ��û�������ۣ�\n2�Ǽ��û�����ۣ�\n3�Ǽ��û�������ۡ�\n");
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
			printf("��ε㵥������֧��%.2fԪ����ɨ���ά��֧��\n",value);
			ShellExecute(NULL, "open","��ά��.png",NULL,NULL,SW_SHOWNA );
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
			printf("���;���ÿ1km��Ҫ֧��1Ԫ���ͷ�\n");
			printf("���͵����Լ��Ҫ6����/����\n");
			d=(int)distance();
			value+=d;
			time(&timep);
			timep+=d*6*60;
			p=localtime(&timep); 
			value*=(1-((c->vip[0]-'0')*0.05));
//			p->tm_min=(p->tm_min+6*(int)d)%60;
//			dh=(p->tm_min+6*(int)d)/60;
//			p->tm_hour=(p->tm_hour+dh)%24;
			printf("������ʹ�Լ��%0.2d:%0.2d�ʹ�\n",p->tm_hour,p->tm_min) ;
			printf("��ε㵥������֧��%.2fԪ����ɨ���ά��֧��\n",value);
			ShellExecute(NULL, "open","��ά��.png",NULL,NULL,SW_SHOWNA );
			insert_bill(c->phone,x.num,need,1,tmp,value);
			system("pause");
			break;
		default:
			printf("��������0~2�е�һ������\n");
			break;
	}
	if(judge==1)
	{
		DingCanJieMian(s,f,c);
		return;
	}
	printf("�ڴ������´ι��٣�\n");
	system("pause");
}

void choice_customer(struct meal *s,struct staff *f,struct Customer *c)
{
	system("cls");
	char i[5],kind[5];
	float low,high,temp;
	while(1){
//		total=0;
		printf("��%s����Ա�� %s ���ã���ӭ����236�͹ݣ�\n\n",c->vip,c->name); 
		printf("*****************************************\n");
		printf("#              ������˵�               #\n");
		printmeal(s);
//		scanf("%s",i);
		printf("============================================\n");
		printf("\t������ֽ��в���               \n");
		printf("\t0.�˳��ý���              \n");	
		printf("\t1.���Ʒ����              \n");
		printf("\t2.���Ʒ����              \n");
		printf("\t3.������Ʒ              \n");
		printf("============================================\n");
//		scanf("%s",i);
		our_scanf_str(i,1); 
		if(i[1]!=0){
			system("cls");
			printf("��ֻ������0/1/2/3\n\n");
		} else if(strcmp(i,"0")==0)break;
		else{
			switch(i[0]-'0'){
				case 0:break;
				case 1:printf("��д������Ҫ�����ļ۸����䣺\n");
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
					searchprice(s,low,high); break;
				case 2:printf("��д������Ҫ�����Ĳ�Ʒ���ࣺ\n");
					printf(" 1����ʳ��2����ˣ�3���زˣ�4����Ʒ��5��С��\n");
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
	int n,judge=0;//n��ʾ������ַ����ĳ��ȣ�judge�����ж��Ƿ�����ѭ�� 
	char v,ch;//�����������Ϣ�õ� 
	while(judge==0)
	{
		system("cls");
		fflush(stdin);
		printf("(����������0~3�е�һ�����֣���ʾ��Ҫ��Ϊ���Ǽ�)\n");
		printf("��������Ҫ�ı���Ǽ�(��4������һ��)��");
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
			printf("��ֻ������0~3�е�һ�����֣�����������\n");
		}
	}
	c->vip[0]=v;
	customer_to_txt();
	printf("�Ǽ�����ɹ����������ѱ��Ϊ%c�Ǽ��û�\n",c->vip[0]);
	if(c->vip[0]!='0')
	{
		ShellExecute(NULL, "open","��ά��.png",NULL,NULL,SW_SHOWNA );
		printf("��ɨ���ά�벢��2Сʱ����ɺ���֧��������Ĭ�����������Ǽ����\n");
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
		printf("�����볤��ӦΪ6~16λ��ֻ�ܰ������ּ���Сд��ĸ��\n");
		printf("��������Ҫ���ĵ����루��0������һ����:");
		our_scanf_str(new_password,16);
		if(new_password[0]=='0'&&new_password[1]=='\0')
		{
			return;
		}
		judge=mima_judge(new_password);//�����ʽ��ȷ����1�����򷵻�0 
		if(judge==0)
		{
			printf("�����ʽ��������������\n");
			system("pause");
		}
		else
		{
			strcpy(c->password,new_password);
			customer_to_txt();
			printf("������ĳɹ���");
			system("pause");
			return;
		}
	}
}

int customer_interface(struct meal *s,struct staff *f,struct Customer *c)
{
	char choice[5];
	printf("��¼�ɹ���\n\n");
	system("pause");
	while(1)
	{
		system("cls");
		printf("��%s����Ա�� %s ���ã���ӭ����236�͹ݣ�\n\n",c->vip,c->name); 
		printf("******************************************\n");
		printf("#            ��ӭ�����û�����            #\n");
		printf("#               0.�˳�ϵͳ               #\n");
		printf("#               1.����                   #\n");
		printf("#               2.�޸�����               #\n");
		printf("#               3.�޸�VIP�ȼ�            #\n");
		printf("#               4.�޸ĵ�ַ               #\n");
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
				printf("��ֻ������0/1/2/3/4\n\n");
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
		printf("�������ĵ绰(��0���˳�)��\n");
		our_scanf_str(i,11);
		if(strcmp(i,"0")==0) break; 
		c=(Customer*)findValueByKey(haxi_customer,i);
		if(c==NULL){
			printf("\n�޴��˺ţ���ע��\n");
			system("pause");
			system("cls");
			break;
		}
		printf("�����������룺\n");
		our_scanf_str(j,16);
		if(strcmp(c->password,j)==0){
			if(customer_interface(s,f,c)==0)return;//�����û��������� 
			system("cls");
		}
		else{
			system("cls");
			printf("�������\n");
		}
	}
}

void customerfirst(struct meal *s,struct staff *f,struct Customer *c)
{
	system("cls");
	char i[4];
	while(1){
		printf("*****************************************\n");
		printf("#        ��ӭ�����ͻ��˶��ͽ���         #\n");
		printf("#              0.�˳�ϵͳ               #\n");
		printf("#              1.ע���˻�               #\n");
		printf("#              2.��¼�˻�               #\n");
		printf("#              3.ע���˻�               #\n");
		printf("*****************************************\n\n");
		our_scanf_str(i,1);
		if(i[1]!=0){
			system("cls");
			printf("��ֻ������0/1/2/3\n\n");
		} 
		else{
			if(i[0]=='0')break;
			switch(i[0]-'0'){
				case 0:break;
				case 1:
					cl_insert_customer(); //�����˻�ע����� 
					system("cls");
					break;
				case 2:
					customerlogin(s,f,c);//�����˻���¼���� 
					system("cls");
					break;
				case 3:
					delete_customer();//ע���û����� 
					system("cls");
					break;
				default:
					system("cls");
					printf("��ֻ������0/1/2/3\n\n");
					break;
			}
		}
	} 
}
