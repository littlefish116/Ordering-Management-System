/*#include<stdio.h>
#include<stdlib.h>
#include<string.h>*/
    
void helpmenu(){
        //帮助菜单，用函数来完成
     printf("============================================\n");
     printf("\t您好，有什么可以为您服务？\n"); 
	 printf("\t1.本系统的独特之处\n"); 
     printf("\t2.留下您的宝贵评价\n"); 
     printf("\t3.我们团队的更多系统应用\n"); 
     printf("\t4.资助我们或联系广告招商\n");
     printf("\t5.制作团队及制作人员信息\n");
     printf("\t0.返回上一菜单界面\n");
     printf("============================================\n");
     printf("请输入您的选择：0~5   \n");
  }
  
void helpkeyDown(){
	
  	char x[50],y[50],z[50];
	char input[50];
    char helpkey[50];
    while(1){
    	system("cls");
    	helpmenu();
		our_scanf_str(helpkey,1);
		if (helpkey[0]=='0')break;
		else{
			switch(helpkey[0]-'0'){
          case 1:
          	while(1){
          		system("cls");
          		printf("在本次课程设计中，我们选择了订餐管理系统为主题。\n"); 
				printf("但在我们的系统中，并不仅仅只是订餐管理这么简单，\n\n");   
				printf("我们系统独特之处在于面向顾客的同时也面向着内部管理人员，\n");   	
				printf("通过主界面的分流从而达到两个目的。\n\n");     	
				printf("本系统功能层面就像一个大型餐饮业的app一样，\n");    	
				printf("现实生活中遇到的所有点餐细节问题基本都囊括其中，\n\n");	
				printf("从顾客方面来讲，我们从日常的会员制度到外卖配送，\n");		
				printf("从每日折扣到热销菜品，从套餐搭配再到顾客对系统的评价等应有尽有。\n");		
				printf("在不同时间段打开此系统，你会发现我们不仅为顾客准备了夜间模式，\n");	
				printf("同时还在饭点儿期间，我们特意设计了暖色调的界面，从而与顾客的食欲达成一种共鸣。\n");		
				printf("在外卖送餐系统中，我们提供了多位外卖员供顾客选择的同时还具有外卖送达时间预估。\n\n");		
				printf("我们系统的界面更不会只是一个冷冰冰的点餐工具，\n");		
				printf("我们还加入了广告位以及广告位加盟的细节处理，从而使整个系统更加商业化，现实化。\n\n");			
				printf("本系统也可以从管理人员的角度出发，\n");		
				printf("使用管理账号进入管理界面，从而实现人员流动及员工信息修改。\n\n"); 
              	printf("返回上一界面请按0\n"); 
             	scanf("%s",x);
              	if(strcmp(x,"0")==0)break;
			}
              break;
          case 2:
          	while(1){
          		system("cls");
          		printf("您对我们的系统感觉如何\n");
              	printf("1、好  2、很好  3、非常好  4、好上加好\n");
              	our_scanf_str(z,1);
              	printf("返回上一界面请按0\n");
             	our_scanf_str(x,1);
              	if(strcmp(x,"0")==0)break;
			}
              break;
          case 3:
          	while(1){
          		system("cls");
          		printf("更多系统应用尚在开发中，暂未对外开放\n");
             	printf("返回上一界面请按0\n");
             	our_scanf_str(x,1);
              	if(strcmp(x,"0")==0)break;
			}
              break;
          case 4:
          	while(1){
          		system("cls");
          		printf("请添加微信：1085155831或扫描二维码 发红包\n"); 
          		ShellExecute(NULL, "open","二维码.png",NULL,NULL,SW_SHOWNA );
			    printf("返回上一界面请按0\n");
             	our_scanf_str(x,1);
              	if(strcmp(x,"0")==0)break;
			}
              break;
         case  5:
         	while(1){
          		system("cls");
          		printf("本制作团队为五舍B236团队独立制作，\n版权所有，\n仿冒必究\n");
             	printf("制作人员:\n李锦豪\n常辽\n刘子胤\n刘少帅\n(排名不分先后)\n");
			    printf("返回上一界面请按0\n");
             	our_scanf_str(x,1);
              	if(strcmp(x,"0")==0)break;
			}
              break;
         case  0:
         	 break; 
        default:
        	system("cls");
			printf("您只能输入0~5这6个数字之一\n\n");
			system("pause"); 
		}
	  }
    	
    }
}
