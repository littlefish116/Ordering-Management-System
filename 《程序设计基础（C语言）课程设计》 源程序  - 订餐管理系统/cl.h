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

table *haxi_customer;//�˿����ݵĹ�ϣ�� 

void customer_to_txt()
{
	FILE *cl_fp=NULL;//������������ݸ��ǵ��ļ��� 
	//	printf("���ڴ��ļ������Ժ�......\n");
		cl_fp=fopen("customer.txt","wb");//������ֻдģʽ���ļ����򿪵�ʱ��Ͱ��ļ��������ȫɾ��
	//���ֻ���ö�����ֻдģʽ��Ҳ�����ҹ�ª�����ˣ�����Ȼtxt�ļ��ĸ�ʽ���ԭ���趨��ANSIת����UTF-8
	//���������������UTF-8�������ֻ�����ģ����Ǻ���ⷴ�������ܲ����ÿ��ַ�wchar����orz�� 
		if(cl_fp==NULL)
		{
	//		printf("�ļ���ʧ��\n");
			return;
		}
	//	else
	//	printf("�ļ��򿪳ɹ�����ʼɾ���˿���Ϣ\n");//ʵ�����ǰ�֮ǰ��������ɾ�����Ĺ˿���Ϣ¼��ȥ 
		int num=0;
		Customer *node;
		node=customer_head->next;//��һλ�˿� 
		while(node->next!=NULL)//���һ���˿��ȱ�¼�����������ļ���β�ǻس��ǻ�����һ��С�鷳�� 
		{
			//�ǵ�++num����ʾ��һλ�˿͵���� 
			fprintf(cl_fp,"%d,     %s     %s     %s     %s     %s\n",++num,node->name,node->phone,node->password,node->address,node->vip);
			node=node->next;
		}
		//���һλ�˿Ͳ����س� 
		fprintf(cl_fp,"%d,     %s     %s     %s     %s     %s",++num,node->name,node->phone,node->password,node->address,node->vip);
	//	printf("ɾ������\n");
		fclose(cl_fp);//�ǵù��ļ� 
		return;
}

void our_scanf_str(char *str,int len)//str��ʾҪ�������ݵı������س������� 
{
	int n,zifunum,judge=0;//n��ʾ������ַ����ĳ��ȣ�judge�����ж��Ƿ�����ѭ��,len��ʾ�����Խ��յ����ݣ�����len�Ĳ��ֻᱻ����� 
	char v;//�����������Ϣ�õ� 
	while(judge==0)
	{
		fflush(stdin);
		v=getchar();
		n=0;
		zifunum=0;
		str[0]=v;
		if(str[n]<0)//�Ժ��ֵĴ��� 
		{
			++n;
			str[n]=getchar();
		}
		while(str[n]!='\n'&&str[n]!='\r'&&zifunum<=len)
		{
			++n;
			++zifunum;
			str[n]=getchar();
			if(str[n]<0)//�Ժ��ֵĴ��� 
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
			printf("��ֻ������%d�������ַ������֣��Ҳ���ֱ������س���������������\n",len);
		}
		//system("pause");
	}
	fflush(stdin);
	return;
}

int cl_strlen(char c[])//�ֱܷ溺�ֵ�strlen����Ϊ���ֵ�ASCII���Ǹ�������ռ����char�Ŀռ� 
{
	int i,len=0;
	for(i=0;c[i]!='\0';++i)
	{
		if(len>60)//���ȳ���60����������Ϊ����ĺϷ����ݳ������60��������Ҫ���Ը� 
		break;
		if(c[i]<0)//ASCII��С��0���Ǻ��֣�ռ������λ������++i 
		{
			++i;
		}
		++len;//һ����ͳ�Ƴ��Ⱦ�+1 
	}
	return len;
}//strlenͦ����ĵ�����Խ�磬���������strlen֮�󶼻�ĳɱ��

int cl_CtoN(char c[])//�����ַ���ת��Ϊ���֣�����������ַ��ᱻ���� 
{
	int r=0,n=strlen(c),i;//r��Ҫ���ص����� 
	for(i=0;i<n;++i)
	{
		if(c[i]<'0'||c[i]>'9')//�ж��Ƿ������֣����Ǿ����� 
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

float CtoF(char c[])//�����ַ���ת��Ϊʵ��
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

float our_scanf_float(int mmax)//����С������� 
{
	long long x;
	int i,len=0,t,judge,v;//len��ʾmmax��λ�� 
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
		judge=1;//1�Ϸ���2���Ϸ� 
		printf("������һ��С��%d�ķǸ�С�������֧��6λС������",mmax);
		our_scanf_str(str,len+7);
		n=strlen(str);
		if(str[0]<'0'||str[0]>'9')
		{
			printf("�벻Ҫ���븺�����޹���Ϣ\n");
			continue;
		}
		if(judge==1)
		for(i=0;str[i]!='\0';++i)
		{
			if(str[i]<'0'||str[i]>'9')
			{
				if(str[i]!='.')
				{
					printf("�벻Ҫ�����޹���Ϣ\n");
					judge=0;
					break; 
				}
				else
				++v;
			}
		}
		if(v>=2)
		printf("�벻Ҫ�����޹���Ϣ\n");
		if(judge==0)
		continue;
		for(i=0;str[i]!='.'&&str[i]!='\0';++i);
		strcpy(ts,str);
		ts[i]='\0';
		x=cl_CtoN(ts);
		if(x>mmax)
		{
			printf("���������̫������������\n");
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
			printf("�벻Ҫ�����޹���Ϣ\n");
			continue;
		}
		
		if(i+6<=n)
		{
			printf("С��λ������6λ������������\n");
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
			printf("���������̫������������\n");
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

int phone_judge(char s[])//�жϵ绰���Ƿ�Ϸ��������Ƿ�ע�����1�ǺϷ���0���Ϸ� 
{
	int num,i;//num���жϵ绰�ų����õģ�û���Ǻ����������������溺�ֵ�����ᱻ���ȥ
	int judge=1;//judge�Ǽ�¼�ϲ��Ϸ��õ�
	num=strlen(s);
	if(num!=11)//����11λ�����ȥ������һ���������Գ��� 
	{
		judge=0;
	}
	else
	{
		for(i=0;i<11;++i)
		if(s[i]<'0'||s[i]>'9')//���ﺺ�־ͱ����ȥ�� 
		{
			judge=0;
			break;
		}
	}
	return judge;
}

/*int phone_exist(char s[])//�жϵ绰���Ƿ��ѱ�ע�ᣬ��ע�᷵��1�����򷵻�0
{
	int judge=0;//������¼�绰���Ƿ�ע���õ� 
	struct Customer *node=customer_head->next;//�˿͵����ݴ�ͷ��һ�ε�β��һ�� 
	while(node!=NULL)
	{
		if(strcmp(node->phone,s)==0)//����˿͵ĵ绰��=Ҫ��ĵ绰�� 
		{
			judge=1;
			break;//�ҵ��Ͳ����� 
		}
		node=node->next;
	}
	return judge;
}*/

int mima_judge(char c[])//�ж������ʽ�Ƿ���ȷ����ȷ����1�����򷵻�0
{//�����ʽ������Ϊ6~16�����߽磩��ֻ���д�Сд��ĸ������ 
	int i,n,judge=1;//i����forѭ����n�����жϳ��ȣ�judge������¼�Ƿ�Ϸ� 
	for(i=0;c[i]!='\0';++i) 
	if(i>16)//����strlen����Ϊ��Խ��
	break;
	n=i;
	if(n<6||n>16)//����Խ�磨����һ��������ָռ�ÿռ䣩������ᴦ�� 
	return 0;
	for(i=0;i<n;++i)
	{
		if(('0'<=c[i]&&c[i]<='9')||('a'<=c[i]&&c[i]<='z')||('A'<=c[i]&&c[i]<='Z'))//����Ҫ����ַ������� 
		continue;
		else
		judge=0;
	}
	return judge;
}

void search_customer()//Ѱ�ҵ�һ�˿�
{
	
	int judge;//��¼Ҫ�ҵĹ˿��Ƿ���� 
	char v='1';//��¼�Ƿ�Ҫ���ҹ˿ͣ�Ҫ�Ļ���1����Ҫ�Ļ���2 
	char s[30],c[20],choice[5];//��¼�˿�������֮�����ϰ��յ绰�Ų�ѯ�ģ� 
	struct Customer *node;
	printf("��ѡ�����Ĳ�ѯ��ʽ(��0�˳�)\n");
	printf("1.����    2.�绰\n");
	our_scanf_str(choice,1);
	switch(choice[0]-'0')
	{
		case 0:
			return;
		case 1: 
			while(v=='1')
			{
				system("cls");
				printf("��������Ҫ��ѯ�Ĺ˿͵�����: ");
				our_scanf_str(s,7);//����˿���Ϣ 
				judge=0;//Ĭ��Ҫ�ҵĹ˿Ͳ����� 
				node=customer_head->next;
				while(node!=NULL)
				{
					if(strcmp(node->name,s)==0)
					{
						judge=1;
						printf("-----------------------------�ָ���--------------------------\n"); 
						printf("������%s\n�绰��%s\n���룺%s\n��ַ��%s\n�û��Ǽ���%s\n",node->name,node->phone,node->password,node->address,node->vip);
					}
					node=node->next;
				}
				if(judge==0)//û�ҵ������ 
				{
					printf("-----------------------------�ָ���--------------------------\n"); 
					printf("δ��ѯ���˿���Ϣ\n");
				}
				while(1)
				{
					printf("�����Ƿ�Ҫ������ѯ\n");
					printf("1.��    2.��\n");
					our_scanf_str(c,1);//c��ʱ������¼�Ƿ�����������ѯ����Ϊc��ʱû�� 
					if(strlen(c)!=1||(c[0]!='1'&&c[0]!='2'))
					{
						printf("������������������\n"); 
					}
					else if(c[0]=='1')
					{
						break;
					}
					else if(c[0]=='2')
					{
						printf("лл����ʹ��\n");
						return;
					}
				}
			}
			break;
		case 2:
			while(v=='1')
			{
					printf("��������Ҫ��ѯ�Ĺ˿͵ĵ绰: ");
					our_scanf_str(s,11);//����˿���Ϣ 
					node=findValueByKey(haxi_customer,s);
					if(node!=NULL)
					{
						printf("-----------------------------�ָ���--------------------------\n"); 
						printf("������%s\n�绰��%s\n���룺%s\n��ַ��%s\n�û��Ǽ���%s\n",node->name,node->phone,node->password,node->address,node->vip);
					}
					else
					{
						printf("-----------------------------�ָ���--------------------------\n"); 
						printf("δ��ѯ���˿���Ϣ\n");
					}
					
					while(1)
					{
						fflush(stdin);
						printf("�����Ƿ�Ҫ������ѯ\n");
						printf("1.��    2.��\n");
						our_scanf_str(c,1);//c��ʱ������¼�Ƿ�����������ѯ����Ϊc��ʱû�� 
						if(strlen(c)!=1||(c[0]!='1'&&c[0]!='2'))
						{
							printf("������������������\n"); 
						}
						else if(c[0]=='1')
						{
							break;
						}
						else if(c[0]=='2')
						{
							printf("лл����ʹ��\n");
							return;
						}
					}
			} 
		default:
			printf("��ֻ������0\1\2�е�����\n");
	} 
	
}

void print_customer()//��ӡ���й˿���Ϣ 
{
	struct Customer *node=customer_head->next;
//	printf("������ӡ���й˿͵���Ϣ\n");
//	Sleep(2000);//��2�����һ�е������Ϣ 
	while(node!=NULL)
	{
		printf("-----------------------------�ָ���--------------------------\n"); 
		printf("������%s\n�绰��%s\n���룺%s\n��ַ��%s\n�û��Ǽ���%s\n",node->name,node->phone,node->password,node->address,node->vip);
		node=node->next;
	}
}

void cshlr()//��ʼ��¼�루���ı���Ĺ˿���Ϣ¼��ȥ������洢�˿���Ϣ 
{
	iniHashTable(haxi_customer);
	customer_head=(struct Customer *)malloc(sizeof(struct Customer));//��һλ�˿�ǰ���ͷָ�� 
	customer_head->next=NULL;//����ָ��NULL
	struct Customer *node,*pre=customer_head;//node�ǰѹ˿���Ϣ����һ��һ������ģ�pre�Ǽ�¼ǰһ���˿���Ϣ�� 
	FILE *cl_fp=NULL;//���ļ� 
//	printf("���ڴ��ļ������Ժ�......\n");
	cl_fp=fopen("customer.txt","r");
	if(cl_fp==NULL)//Ҫ��û�򿪾�ֱ��return 
	{
//		printf("�ļ���ʧ��\n");
		return;
	}
//	else
//	printf("�ļ��򿪳ɹ�����ʼͬ���˿���Ϣ\n"); 
	while(!feof(cl_fp))//��ͷ��ʼ���ļ���ֱ��������β 
	{
		node=(struct Customer *)malloc(sizeof(struct Customer));//�����ַ 
		//�����ļ�������ݴ浽������ 
		fscanf(cl_fp,"%s%s%s%s%s%s",node->order,node->name,node->phone,node->password,node->address,node->vip);
		insertEntry(haxi_customer,node->name,node);
		insertEntry(haxi_customer,node->phone,node);
		insertEntry(haxi_customer,node->order,node);
		node->next=pre->next;//�������� 
		pre->next=node;//ͬ�� 
		pre=pre->next;//ͬ�� 
//		printf("%s\n",pre->name);//��һ�۲�����ɶ 
	}
	customer_end=pre;//��¼���һλ�˿���Ϣ 
//	printf("�˿���Ϣͬ������\n");
	fclose(cl_fp);
}

void cl_insert_customer()//ע���˻� 
{
	system("cls");
	int num,judge,i;//num->�ַ��������Լ���ʱ�����ˣ�����������Ƚ��� 
	//order����ţ���ʾ���ǵڼ�λ�˿ͣ�name��������password�����룬phone�ǵ绰�ţ�vip�ǵȼ���
	//str����������������ݣ����Ĵ�һ���ֹ����̫��Խ�����bug��str������ٴ��ݸ�order��Щ���� 
	//����Ȼ���ǻ�Խ�磬֮��ῴ����getchar�Ż�һ�£������ȴպ���
	char str[1000000],order[10],name[50],password[50],address[130],phone[50],vip[2];
	vip[0]='0';
//	FILE *cl_fp=NULL;
//	cl_fp=fopen("customer.txt","a");
	while(1)//����˿����� 
	{
		judge=1;//��¼�����Ƿ�Ϸ� 
		printf("��������������������Ϊ2-7����");
		our_scanf_str(str,7);;//�������������� 
		num=cl_strlen(str);//cl_strlen�ܴ���һ������ռ�����ռ�����⣬����ֵ���ַ������� 
		if(num>7||num<2)//�������Ȳ��Ϸ������� 
		judge=0;
		else//�������ȺϷ���� 
		for(i=0;i<num;++i)
		if(name[i]==' ')//����ʲô�������о��ǲ����пո�Ȼ�Ҷ��ļ����鷳�ģ�����ɧһ�� 
		{
			judge=0;
		}
		if(judge==1)//�Ϸ����˳�����Ȼ������ѭ�� 
		break;
		else
		printf("��ʽ��������������\n");
	}
	strcpy(name,str); //��str�����ݴ���name 
	while(1)//����˿��ֻ��� 
	{
		printf("����������11λ�ֻ��ţ�");
		our_scanf_str(str,11);//�����ֻ��� 
		judge=phone_judge(str);//�ж��ֻ����Ƿ�Ϸ�������עûע�ᣩ���Ϸ���1�����Ϸ���0 
		if(judge==0)
		{
			printf("�ֻ��Ÿ�ʽ��������������\n");//�������judge�����е�С��ͻ���Բ��Ϸ���ֱ�Ӽ���ѭ�� 
			continue; 
		}
		else
		{
			if(findValueByKey(haxi_customer,str)!=NULL)//�ж��ֻ����Ƿ���ڣ�������1��������0 
			judge=1;
			else
			judge=0;
		}
		if(judge==0)
		break;
		else
		printf("�ֻ��Ÿ�ʽ������ֻ�����ע�ᣬ����������\n"); 
	}
	strcpy(phone,str);//��str�����ݴ���phone 
	while(1)//��д���� 
	{
		//����Ϸ�������� 
		printf("����д��������\n#��֧�����ּ���Сд��ĸ\n#���볤��ӦΪ6-16λ\n����: "); 
		our_scanf_str(str,16);//�������� 
		judge=mima_judge(str);//�Ϸ���1���Ϸ���0 
		if(judge==0)
		{
			printf("�����ʽ��������������\n");//���Ϸ��ͽ���ѭ��ֱ����Ϸ��� 
		}
		else
		break;
	}
	strcpy(password,str);//��str�����ݴ���password 
	while(1)//��д�ջ���ַ 
	{
		printf("�����������ջ���ַ����֧��<=60�֣���");
		our_scanf_str(str,60);//�����ջ���ַ 
		judge=1;//��¼�ջ���ַ���Ϸ���1�����Ϸ���0��Ĭ�ϺϷ� 
		if(cl_strlen(str)>60)
		{
			printf("����60���ˣ�����������\n");
		}
		else
		{
			num=strlen(str);
			for(i=0;i<num;++i)
			{
				if(str[i]==' ')
				{
					judge=0;
					printf("�����пո�����������\n"); 
					break;
				}
			}
		} 
		if(judge==1)//�Ϸ�������ѭ�� 
		break;
	}
	strcpy(address,str);//str�����ݴ���address 
	printf("ע���Ϊ���긶�ѻ�Ա������Żݣ�����Ϊ�����Ա��Ȩ��\n");
	printf("1�Ǽ��û��ڱ����һ�������������\n2�Ǽ��û������\n3�Ǽ��û��������\n");
	while(1)//ע���Ա 
	{
		printf("�������Ƿ��������Ϊ���긶�ѻ�Ա��\n"); 
		printf("�����롰1�������ǡ������롰2�������񡱣�\n");
		our_scanf_str(str,1);//����1��2�����Ҳ�о���֮��ᱻ৵� 
		if(strcmp(str,"1")==0)//���Ҫע���Ϊvip 
		{
			while(1)
			{
				printf("��ѡ����Ҫע���VIP�ȼ�\n");
				gets(str);//����ѡ���Ϊ����VIP��ֻ����1~3�ǣ����������� 
				if(strlen(str)!=1)//����1λ���ǲ��Ϸ��� 
				{
					printf("��ʽ��������������\n");//���Ϸ�������ѭ��ֱ���Ϸ� 
				}
				else
				{
					if('1'<=str[0]&&str[0]<='3')//�Ϸ��Ͱ�str�����ݴ���vip 
					{
						strcpy(vip,str);
						printf("��ϲ����Ϊ�����%c�Ǽ��û���ף���ò���죡\n",str[0]);
						ShellExecute(NULL, "open","��ά��.png",NULL,NULL,SW_SHOWNA );
						printf("��ɨ���ά�벢��2Сʱ����ɺ���֧�����������ϵͳ�Ὣ������Ϊ����û�\n");
						break;
					}
					else
					{
						printf("��ʽ��������������\n");
					}
				}
			}
			break;
		}
		else if(strcmp(str,"2")==0)//Ҫ�ǲ��뵱VIP�Ͱ�VIP �ȼ�����0 
		{
			vip[0]='0';
			vip[1]='\0';//˳�ּ��˸������õı�ʶ�� 
			printf("��ϲ����Ϊ��������û���ף���ڱ����ò���죡\n");
			break;
		}
	}
	strcpy(order,customer_end->order);//�����һλ�˿͵���ſ���order���� 
	num=strlen(order);//ת�������� 
	order[num-1]='\0';//��Ϊorder���и�������������˵��12λ�˿͵�order���ǡ�12���� 
	num=cl_CtoN(order);//ת���ɹ� 
	++num;//��ż�һλ 
	//����������ǿ�һ��¼���������ʲô���� 
	printf("\n%d,   %s     %s     %s     %s     %d\n\n",num,name,phone,password,address,vip[0]-'0');
	//�������¼������ 
//	fprintf(cl_fp,"\n%d,   %s     %s     %s     %s     %d",num,name,phone,password,address,vip[0]-'0');
//	fclose(cl_fp);//�ǵù��ļ���Ȼ¼����ȥ 
	
	
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
	
	insertEntry(haxi_customer,node->name,node);//����ͬ������ϣ�� 
	insertEntry(haxi_customer,node->phone,node);
	
	customer_to_txt();//������¼�뵽�ļ��� 
	cshlr();
	system("pause");
}
void delete_customer()//ɾ���˿���Ϣ 
{
	int judge=0;//judge������¼�жϵĸ��������Ƿ�Ϸ���num������¼��numλ�˿ͣ������õ�numʱ�����׶��� 
	char phone[25];//��¼�绰�ţ�����һ���Խ�磬���ڿ�����getchar�Ż�һ�� 
	struct Customer *pre,*node;//pre��¼ǰһ���ڵ㣬node��ǰ�ڵ㣬�ӵ�һλ�˿Ϳ�ʼ 
	/*while(judge==0)//�����ֻ��Ų��ж��ֻ��Ÿ�ʽ�Ƿ�Ϸ������ǲ����Ƿ�ע��� 
	{
		system("cls");
		printf("�������ֻ���\n");
		our_scanf_str(phone,11);//����һ���ַ������ֻ��� 
		judge=phone_judge(phone);//�ж��ֻ��Ÿ�ʽ�Ƿ���ȷ�ĺ�������ȷ��1������ȷ��0 
		if(judge==0)printf("�ֻ��Ÿ�ʽ��������������\n");
		else break;
	}*/
	printf("�������ֻ���\n");
	our_scanf_str(phone,11);//����һ���ַ������ֻ��� 
	node=(Customer*)findValueByKey(haxi_customer,phone);
	if(node!=NULL)//�ж��ֻ����Ƿ�ע�����ע�����1��������0 
	judge=1;
	else
	judge=0;
	
	if(judge==0)//û��ע������ 
	{
		printf("���ֻ���δע��\n");
	}
	else//��ע������������node=�Ǹ��˿� 
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
		pre->next=node->next;//������ɾ���� 
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
	printf("#         ��ӭ����˿͹���ģ��          #\n");
	printf("*****************************************\n\n");
}

void custom_mohu()
{
	system("cls");
	int v=0;
	char s[20];
	printf("��������Ҫ��ѯ�Ĺ˿͵�����:\n");
	our_scanf_str(s,7);
	Customer *tmp=customer_head->next;
	printf("����������������������������\n");
	printf("����Ϊ�����Ϣ��\n");
	while(tmp!=NULL)
	{
		if(strstr(tmp->name,s)!=NULL)
		{
			++v;
			printf("��������������������������������������������������������\n");
			printf("%d��\n������%s\n���룺%s\n�绰��%s\n��ַ��%s\n�Ǽ���%s\n",v,tmp->name,tmp->password,tmp->phone,tmp->address,tmp->vip);
		}
		tmp=tmp->next;
	}
	if(v==0)
	{
		printf("��������������������������������������������������������\n");
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
		c=list;//ÿ��ѭ�����轫c�ָ�ָ��ԭ������׵�ַ  
		print_customer(); 
		printf("============================================\n");
		printf("\t�˿͹���                \n");
		printf("\t\t\t\t\t\n");
		printf("\t0.�˳�ģ��               \n");
		printf("\t1.Ѱ�ҹ˿�               \n");
		printf("\t2.ɾ���˿�               \n");
		printf("\t3.ģ�������˿�           \n");
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
				printf("��ֻ������0/1/2/3\n\n");break;
		}
	}
}
