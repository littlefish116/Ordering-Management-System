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

     
void printad()//随机生成广告 
{
	printf("============================================\n");
	int i,ad;
	i=rand();
	ad=i%7;
	switch(ad)
	{
		case 1:printf("不咸不淡，味道真是好极了！\n这喝汤，多是一件美事！--老冯鸡汤馆\n");break;
		case 2:printf("炫迈在广西砂糖橘面前，就只能当弟弟。\n--助力广西乡村振兴【公益宣传】\n");break; 
		case 3:printf("疫情未结束，防控莫大意！\n进出人员密集场所请正确佩戴口罩！\n【公益宣传】\n");break; 
		case 4:printf("咱们的瓜都是从大棚里摘的，\n瓜子儿和瓜囊儿都是金子做的。--华强の瓜店\n");break;
		case 5:printf("【广告位招租】\n");break;
		case 6:printf("你好骚啊！品如之家，女人的衣柜。--品如之家\n");break;
		case 0:printf("超大的房子户型，一流的法语教学，\n好康的影片鉴赏，超勇的你值得拥有。--杰哥教育\n");break;
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
	 
    srand((unsigned)time(NULL));//生成随机数以生成广告 
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
		printf("现在是%d年%0.2d月%0.2d日%0.2d时%0.2d分  ",1900+p->tm_year,1+p->tm_mon,p->tm_mday,p->tm_hour,p->tm_min);
		if(p->tm_hour>=6&&p->tm_hour<9) {
			printf("早上好！\n早餐时间到了！美好而奋斗的一天从早餐开始！\n");
			system("COLOR 6F ");
		}else if(p->tm_hour>=11&&p->tm_hour<14){
			printf("中午好！\n午餐时间到了！美味佳肴是犒劳奋斗者的最佳选择！\n");
			system("COLOR 6F ");
		}else if(p->tm_hour>=17&&p->tm_hour<20){
			printf("晚上好！\n晚餐时间到了！让美味佳肴，犒劳辛劳的您。\n");
			system("COLOR 6F ");  
		}else if (p->tm_hour>=9&&p->tm_hour<11){ 
			printf("上午好！\n工作累了吗，来点好吃的为您续力吧！\n");
			system("COLOR 3F ");//
		}else if (p->tm_hour>=14&&p->tm_hour<17){
			printf("下午好！\n来点下午茶，续能一整天。\n");
			system("COLOR 3F ");
		}else if (p->tm_hour>=20&&p->tm_hour<23){
			printf("晚上好！\n夜深了，夜宵也许可以打消您心中的寂寞。\n"); 
			system("COLOR 8F ");  
		}else{
			printf("晚上好！\n睡吧！咱打烊了~\n"); 
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
					printf("餐馆已打烊！请于每日6-23点进行订餐。\n谢谢您的支持，祝您晚安。\n"); 
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
				printf("您只能输入0/1/2/3\n\n");
				break;
		}
		if(choice[0]-'0'==0)break;
	}	        
	printf("============================================\n");
	printf("\t欢迎您再次使用该系统，再见！     \n");
	printf("============================================\n");
	
	fclose(fkey);
	system("pause");
    return 0;
}
