//#include "cl.h"
//#include "ljh.h"
//#include "lzy.h"
/*#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <time.h> 
#include "jiegouti.h" 
#include "customer.h"  */ 
void statics_jiemian();
#include <stdio.h>  
#include <stdlib.h>
#include <math.h>      
#include <malloc.h>
#include <string.h>
#include <time.h> 
#include <windows.h>
#include "jiegouti.h"  
#include "haxibiao.h"
#include "cl.h"  
#include "lzy-n.h"
#include "lss.h"
#include "sort.h"
#include "ljh.h"  
#include "statistics.h"
#include "customer.h"

     
void printad()//������ɹ�� 
{
	printf("============================================\n");
	int i,ad;
	i=rand();
	ad=i%7;
	switch(ad)
	{
		case 1:printf("���̲�����ζ�����Ǻü��ˣ�\n�����������һ�����£�--�Ϸ뼦����\n");break;
		case 2:printf("�����ڹ���ɰ������ǰ����ֻ�ܵ��ܵܡ�\n--��������������ˡ�����������\n");break; 
		case 3:printf("����δ����������Ī���⣡\n������Ա�ܼ���������ȷ������֣�\n������������\n");break; 
		case 4:printf("���ǵĹ϶��ǴӴ�����ժ�ģ�\n���Ӷ��͹��Ҷ����ǽ������ġ�--��ǿ�ιϵ�\n");break;
		case 5:printf("�����λ���⡿\n");break;
		case 6:printf("���ɧ����Ʒ��֮�ң�Ů�˵��¹�--Ʒ��֮��\n");break;
		case 0:printf("����ķ��ӻ��ͣ�һ���ķ����ѧ��\n�ÿ���ӰƬ���ͣ����µ���ֵ��ӵ�С�--�ܸ����\n");break;
	}
	printf("============================================\n\n"); 
}
  
int main()
{
//	struct staff* list=createlist();
//	struct meal a;
	char choice[100]={0};
	haxi_meal=(table*)malloc(sizeof(table));
	haxi_customer=(table*)malloc(sizeof(table));
	haxi_staff=(table*)malloc(sizeof(table));
	haxi_bill=(table*)malloc(sizeof(table));
	 
    srand((unsigned)time(NULL));//��������������ɹ�� 
    time_t timep;               
	struct tm *p;  
	 
	fkey=fopen("managekey.txt","r+");
	fscanf(fkey,"%s",managekey);
	         
	cshlr();
	start_menu();     
	sthlr();      
	bill_in();
	bill_to_txt();   
//	printmeal(meal_head) ;  
	while(1){   
		time(&timep);
		p=localtime(&timep); 
		printad();
		printf("������%d��%0.2d��%0.2d��%0.2dʱ%0.2d��  ",1900+p->tm_year,1+p->tm_mon,p->tm_mday,p->tm_hour,p->tm_min);
		if(p->tm_hour>=6&&p->tm_hour<9) {
			printf("���Ϻã�\n���ʱ�䵽�ˣ����ö��ܶ���һ�����Ϳ�ʼ��\n");
			system("COLOR 6F ");
		}else if(p->tm_hour>=11&&p->tm_hour<14){
			printf("����ã�\n���ʱ�䵽�ˣ���ζ���������ͷܶ��ߵ����ѡ��\n");
			system("COLOR 6F ");
		}else if(p->tm_hour>=17&&p->tm_hour<20){
			printf("���Ϻã�\n���ʱ�䵽�ˣ�����ζ���ȣ��������͵�����\n");
			system("COLOR 6F ");  
		}else if (p->tm_hour>=9&&p->tm_hour<11){ 
			printf("����ã�\n��������������óԵ�Ϊ�������ɣ�\n");
			system("COLOR 3F ");//
		}else if (p->tm_hour>=14&&p->tm_hour<17){
			printf("����ã�\n��������裬����һ���졣\n");
			system("COLOR 3F ");
		}else if (p->tm_hour>=20&&p->tm_hour<23){
			printf("���Ϻã�\nҹ���ˣ�ҹ��Ҳ����Դ��������еļ�į��\n"); 
			system("COLOR 8F ");  
		}else{
			printf("���Ϻã�\n˯�ɣ��۴�����~\n"); 
			system("COLOR 87 ");//         
		}            
		printtitle_forum();     
		our_scanf_str(choice,1);         
		switch(choice[0]-'0'){    
			case 0:break;  
			case 1:
				if(p->tm_hour>=6&&p->tm_hour<23) 
				customerfirst(meal_head,staff_head,customer_head);
				else {
					printf("============================================\n");
					printf("�͹��Ѵ��ȣ�����ÿ��6-23����ж��͡�\nлл����֧�֣�ף������\n"); 
					printf("============================================\n");  
					system("pause"); 
				}   
				system("cls");  
				break; 
			case 2: 
				system("cls"); 
				managelogin(meal_head,staff_head,customer_head);
				system("cls"); 
				break; 
			case 3: 
			//	helpmenu();
				helpkeyDown();
				system("cls");  
				break;  
			default:
				system("cls");
				printf("��ֻ������0/1/2/3\n\n");
				break;
		}
		if(choice[0]-'0'==0)break;
	}	        
	printf("============================================\n");
	printf("\t��ӭ���ٴ�ʹ�ø�ϵͳ���ټ���     \n");
	printf("============================================\n");
	
	fclose(fkey);
	system("pause");
    return 0;
}
