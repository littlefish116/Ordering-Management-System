/*#include<stdio.h>
#include<string.h>
#include<malloc.h>*/
   



void staff_menu()
{
	printf("********************************************************************\n");
	printf("|                     ��ӭ����Ա������ϵͳ��                        |\n");
	printf("|                     �밴�ղ���ָ�����й���                       |\n");
	printf("********************************************************************\n");
}

int st_strlen(char c[])//�ֱܷ溺�ֵ�strlen����Ϊ���ֵ�ASCII���Ǹ�������ռ����char�Ŀռ� 
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
}
//strlenͦ����ĵ�����Խ�磬���������strlen֮�󶼻�ĳɱ�ģ��ο�����mima_judge()�ĵ�82~85�� 
int id_judge(char s[])//�жϵ绰���Ƿ�Ϸ��������Ƿ�ע�����1�ǺϷ���0���Ϸ� 
{
	int i;
	int judge=1;//judge�Ǽ�¼�ϲ��Ϸ��õ�
		for(i=0;i<strlen(s);++i)
		if(s[i]<'0'||s[i]>'9')//���ﺺ�־ͱ����ȥ�� 
		{
			judge=0;
			break;
		}
	
	return judge;
}
int st_CtoN(char c[])//�����ַ���ת��Ϊ���֣�����������ַ��ᱻ���� 
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

int id_exist(char s[])//�жϹ����Ƿ��ѱ�ע�ᣬ��ע�᷵��1�����򷵻�0
{
	int judge=0;//������¼�����Ƿ�ע���õ� 
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

void search_staff()//����Ա��
{
	int judge;//��¼Ҫ�ҵ�Ա���Ƿ���� 
	char v='1';//��¼�Ƿ�Ҫ����Ա����Ҫ�Ļ���1����Ҫ�Ļ���2 
	char c[30];//��¼Ա������
	struct staff *node;
	while(v=='1')
	{
		system("cls");
		printf("��������Ҫ���ҵ�Ա��������: ");
		our_scanf_str(c,12);//����Ա����Ϣ 
		judge=0;//Ĭ��Ҫ�ҵ�Ա�������� 
		
		node=(struct staff*)findValueByKey(haxi_staff,c);//��һλԱ��
		if(node!=NULL)//��ͷ���󰤸����Ƿ��з���������Ա�� 
		{
			judge=1;
		}  
		if(judge==0)//û�ҵ������ 
		{
			printf("-----------------------------�ָ���--------------------------\n"); 
			printf("δ���ҵ�Ա����Ϣ\n");
			printf("-----------------------------�ָ���--------------------------\n"); 
		}
		else//�ҵ������
		{
			printf("-----------------------------�ָ���--------------------------\n"); 
			printf("������%s\n���ţ�%s\nְҵ��%s\n",node->staff_name,node->staff_id,node->staff_idt);
		    printf("-----------------------------�ָ���--------------------------\n"); 
		}
		while(1)
		{
			printf("�����Ƿ�Ҫ������ѯ\n");
			printf("1.��    2.��\n");
			our_scanf_str(c,1);//c��ʱ������¼�Ƿ�����������ѯ����Ϊ��ʱû�� 
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
}
void print_staff()//��ӡ����Ա����Ϣ 
{
	struct staff *node=staff_head->next;
	int num=0;
//	printf("������ӡ����Ա������Ϣ\n");
//	Sleep(2000);//��2�����һ�е������Ϣ 
	while(node!=NULL)
	{
		printf("-----------------------------�ָ���--------------------------\n"); 
		printf("������%s\n���ţ�%s\nְҵ��%s\n",node->staff_name,node->staff_id,node->staff_idt);
		
		node=node->next;
		num++;
	}
	printf("-----------------------------�ָ���--------------------------\n"); 
	printf("\nĿǰӵ������%d��Ա������Ϣ��\n\n",num);
}
void sthlr()//��ʼ��¼�루���ı����Ա����Ϣ¼��ȥ������洢Ա����Ϣ 
{
	iniHashTable(haxi_staff);
	staff_head=(struct staff *)malloc(sizeof(struct staff));//��һλ�˿�ǰ���ͷָ�� 
	staff_head->next=NULL;//����ָ��NULL
	struct staff *node,*pre=staff_head;//node�ǰ�Ա����Ϣ����һ��һ������ģ�pre�Ǽ�¼ǰһ��Ա����Ϣ�� 
	FILE *st_fp=NULL;//���ļ� 
//	printf("���ڴ��ļ������Ժ�......\n");
	st_fp=fopen("staff.txt","r");
	if(st_fp==NULL)//Ҫ��û�򿪾�ֱ��return 
	{
//		printf("�ļ���ʧ��\n");
		return;
	}
	else
//	printf("�ļ��򿪳ɹ�����ʼͬ��Ա����Ϣ\n"); 
	while(!feof(st_fp))//��ͷ��ʼ���ļ���ֱ��������β 
	{
		node=(struct staff *)malloc(sizeof(struct staff));//�����ַ 
		//�����ļ�������ݴ浽������ 
		fscanf(st_fp,"%s%s%s",node->staff_id,node->staff_name,node->staff_idt);
		insertEntry(haxi_staff,node->staff_id,node);
		insertEntry(haxi_staff,node->staff_name,node);
		node->next=pre->next;//�������� 
		pre->next=node;//ͬ�� 
		pre=pre->next;//ͬ�� 
//		printf("%s\n",pre->staff_id);//��һ�۲�����ɶ 
	}
	staff_end=pre;//��¼���һλԱ����Ϣ 
//	printf("Ա����Ϣͬ������\n");
	fclose(st_fp);
}
void st_insert_staff()//����Ա��
{
	int num,judge,i;//num->�ַ��������Լ���ʱ�����ˣ�����������Ƚ��� 
	//order����ţ���ʾ���ǵڼ�λ�˿ͣ�name��������password�����룬phone�ǵ绰�ţ�vip�ǵȼ���
	//str����������������ݣ����Ĵ�һ���ֹ����̫��Խ�����bug��str������ٴ��ݸ�order��Щ���� 
	//����Ȼ���ǻ�Խ�磬֮��ῴ����getchar�Ż�һ�£������ȴպ���
	char str[30],staff_id[10],name[50],idt[50];
	FILE *st_fp=NULL;
	st_fp=fopen("staff.txt","a");
	while(1)//����Ա������ 
	{
		system("cls");
		judge=1;//��¼�����Ƿ�Ϸ� 
		printf("��������������������Ϊ2-7����");fflush(stdin);
		our_scanf_str(str,7);//�������������� 
		num=st_strlen(str);//cl_strlen�ܴ���һ������ռ�����ռ�����⣬����ֵ���ַ������� 
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

	strcpy(staff_id,give_stid(staff_id));
	printf("ϵͳ�����Ա������Ϊ��%s\n",staff_id);

	while(1)//��д���
	{
		printf("������Ա����ݣ���֧��12�����ڣ�����12�֣���");
		our_scanf_str(str,12);//�������
		judge=1;//��¼��ݣ��Ϸ���1�����Ϸ���0��Ĭ�ϺϷ� 
		if(st_strlen(str)>12)
		{
			printf("����12���ˣ�����������\n");
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
	strcpy(idt,str);//str�����ݴ���idt
	
//	strcpy(staff_id,staff_end->staff_id);//�����һλԱ���Ĺ��ſ���id���� 
//	num=strlen(staff_id);//ת�������� 
//	staff_id[num-1]='\0';//��Ϊid���и�������������˵��12λԱ����id���ǡ�12���� 
//	num=st_CtoN(staff_id);//ת���ɹ� 
//	++num;//��ż�һλ 
	
	//����������ǿ�һ��¼���������ʲô���� 
	printf("\n%s   %s     %s\n",staff_id,name,idt);
	//�������¼������ 
	fprintf(st_fp,"\n%s   %s     %s",staff_id,name,idt);
	fclose(st_fp);//�ǵù��ļ���Ȼ¼����ȥ 
	
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

void delete_staff()//ɾ��Ա����Ϣ 
{
	int judge=0,num=0;//judge������¼�жϵĸ��������Ƿ�Ϸ���num������¼��numλԱ���������õ�numʱ�����׶��� 
	char id[20];//��¼���ţ�����һ���Խ�磬���ڿ�����getchar�Ż�һ�� 
	int len=0,temp,i;
	char order[30];
	struct staff *pre=staff_head,*node=staff_head->next;//pre��¼ǰһ���ڵ㣬node��ǰ�ڵ㣬�ӵ�һλ�˿Ϳ�ʼ 
	while(judge==0)//�����ֻ��Ų��жϹ��Ÿ�ʽ�Ƿ�Ϸ������ǲ����Ƿ�ע��� 
	{
		system("cls");
		
		printf("�����빤��\n");//fflush(stdin);//getchar();
		
		our_scanf_str(id,8);//����һ���ַ���������
		
		judge=id_judge(id);//�жϹ��Ÿ�ʽ�Ƿ���ȷ�ĺ�������ȷ��1������ȷ��0 
		if(judge==0)
		printf("���Ÿ�ʽ��������������\n");
		else break;
	}
	
	judge=id_exist(id);//�жϹ����Ƿ�ע�����ע�����1��������0 

	if(judge==0)//û��ע������ 
	{
		printf("�˹�����δ��ʹ��\n");
		system("pause");return;
	}
	else//��ע�������������Ǹ�Ա��
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
		pre->next=node->next;//������ɾ���� 
		removeEntry(haxi_staff,node->staff_id);
		removeEntry(haxi_staff,node->staff_name);
		free(node);
		node->next=NULL;
		system("pause");
	}
	FILE *st_fp=NULL;//������������ݸ��ǵ��ļ��� 
	printf("���ڴ��ļ������Ժ�......\n");
	st_fp=fopen("staff.txt","wb");//������ֻдģʽ���ļ����򿪵�ʱ��Ͱ��ļ��������ȫɾ��
//���ֻ���ö�����ֻдģʽ��Ҳ�����ҹ�ª�����ˣ�����Ȼtxt�ļ��ĸ�ʽ���ԭ���趨��ANSIת����UTF-8
//���������������UTF-8�������ֻ�����ģ����Ǻ���ⷴ�������ܲ����ÿ��ַ�wchar����orz�� 
	if(st_fp==NULL)
	{
		printf("�ļ���ʧ��\n");
		return;
	}
	else
	printf("�ļ��򿪳ɹ�����ʼɾ��Ա����Ϣ\n");//ʵ�����ǰ�֮ǰ��������ɾ������Ա����Ϣ¼��ȥ 
	node=staff_head->next;//��һλԱ��
	while(node->next!=NULL)//���һ��Ա���ȱ�¼�����������ļ���β�ǻس��ǻ�����һ��С�鷳�� 
	{
		//�ǵ�++num����ʾ��һλԱ���Ĺ���
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
	//�����ΪԱ�������س� 
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
	
	printf("ɾ������\n");
	fclose(st_fp);//�ǵù��ļ� 
	sthlr();
	system("pause");
	return;
}
void staff_unclear(char *name)//ģ������ 
{
	struct staff* s=staff_head;
	int word=0;
	system("cls");
	printf("*************************************************\n");
	printf("#                   �������                    #\n");
	printf("#����\t\t����\t\tְҵ\t        #\n");
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
void manage()//�ܹ���ϵͳ
{
	char string[20],choice[4];
	while (1)
	{
	system("cls");	
	printf("\n");
	print_staff();
	printf("********************************************************************\n");
	printf("                        ��ѡ����Ҫ���еĲ���                        \n");
	printf("                        0.  �˳�����                                \n");
	printf("                        1.  ����Ա��                                \n");
	printf("                        2.  ����Ա��                                \n");
	printf("                        3.  ɾ��Ա��                                \n");
	printf("                        4.  ģ������                                \n");
	printf("********************************************************************\n");
	our_scanf_str(choice,1);
	if (choice[1]!=0){
		system("cls");
		printf("��ֻ������0/1/2/3/4\n\n");
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
			printf("������ؼ���:");
			our_scanf_str(string,8);
			staff_unclear(string);
			break;
		default:
			system("cls");
			printf("��ֻ������0/1/2/3/4\n\n");
			break;
		}
	}
	
	}	
}
