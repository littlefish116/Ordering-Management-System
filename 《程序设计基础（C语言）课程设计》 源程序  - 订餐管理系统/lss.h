/*#include<stdio.h>
#include<stdlib.h>
#include<string.h>*/
    
void helpmenu(){
        //�����˵����ú��������
     printf("============================================\n");
     printf("\t���ã���ʲô����Ϊ������\n"); 
	 printf("\t1.��ϵͳ�Ķ���֮��\n"); 
     printf("\t2.�������ı�������\n"); 
     printf("\t3.�����Ŷӵĸ���ϵͳӦ��\n"); 
     printf("\t4.�������ǻ���ϵ�������\n");
     printf("\t5.�����ŶӼ�������Ա��Ϣ\n");
     printf("\t0.������һ�˵�����\n");
     printf("============================================\n");
     printf("����������ѡ��0~5   \n");
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
          		printf("�ڱ��ογ�����У�����ѡ���˶��͹���ϵͳΪ���⡣\n"); 
				printf("�������ǵ�ϵͳ�У���������ֻ�Ƕ��͹�����ô�򵥣�\n\n");   
				printf("����ϵͳ����֮����������˿͵�ͬʱҲ�������ڲ�������Ա��\n");   	
				printf("ͨ��������ķ����Ӷ��ﵽ����Ŀ�ġ�\n\n");     	
				printf("��ϵͳ���ܲ������һ�����Ͳ���ҵ��appһ����\n");    	
				printf("��ʵ���������������е��ϸ������������������У�\n\n");	
				printf("�ӹ˿ͷ������������Ǵ��ճ��Ļ�Ա�ƶȵ��������ͣ�\n");		
				printf("��ÿ���ۿ۵�������Ʒ�����ײʹ����ٵ��˿Ͷ�ϵͳ�����۵�Ӧ�о��С�\n");		
				printf("�ڲ�ͬʱ��δ򿪴�ϵͳ����ᷢ�����ǲ���Ϊ�˿�׼����ҹ��ģʽ��\n");	
				printf("ͬʱ���ڷ�����ڼ䣬�������������ůɫ���Ľ��棬�Ӷ���˿͵�ʳ�����һ�ֹ�����\n");		
				printf("�������Ͳ�ϵͳ�У������ṩ�˶�λ����Ա���˿�ѡ���ͬʱ�����������ʹ�ʱ��Ԥ����\n\n");		
				printf("����ϵͳ�Ľ��������ֻ��һ��������ĵ�͹��ߣ�\n");		
				printf("���ǻ������˹��λ�Լ����λ���˵�ϸ�ڴ����Ӷ�ʹ����ϵͳ������ҵ������ʵ����\n\n");			
				printf("��ϵͳҲ���Դӹ�����Ա�ĽǶȳ�����\n");		
				printf("ʹ�ù����˺Ž��������棬�Ӷ�ʵ����Ա������Ա����Ϣ�޸ġ�\n\n"); 
              	printf("������һ�����밴0\n"); 
             	scanf("%s",x);
              	if(strcmp(x,"0")==0)break;
			}
              break;
          case 2:
          	while(1){
          		system("cls");
          		printf("�������ǵ�ϵͳ�о����\n");
              	printf("1����  2���ܺ�  3���ǳ���  4�����ϼӺ�\n");
              	our_scanf_str(z,1);
              	printf("������һ�����밴0\n");
             	our_scanf_str(x,1);
              	if(strcmp(x,"0")==0)break;
			}
              break;
          case 3:
          	while(1){
          		system("cls");
          		printf("����ϵͳӦ�����ڿ����У���δ���⿪��\n");
             	printf("������һ�����밴0\n");
             	our_scanf_str(x,1);
              	if(strcmp(x,"0")==0)break;
			}
              break;
          case 4:
          	while(1){
          		system("cls");
          		printf("�����΢�ţ�1085155831��ɨ���ά�� �����\n"); 
          		ShellExecute(NULL, "open","��ά��.png",NULL,NULL,SW_SHOWNA );
			    printf("������һ�����밴0\n");
             	our_scanf_str(x,1);
              	if(strcmp(x,"0")==0)break;
			}
              break;
         case  5:
         	while(1){
          		system("cls");
          		printf("�������Ŷ�Ϊ����B236�ŶӶ���������\n��Ȩ���У�\n��ð�ؾ�\n");
             	printf("������Ա:\n�����\n����\n����ط\n����˧\n(���������Ⱥ�)\n");
			    printf("������һ�����밴0\n");
             	our_scanf_str(x,1);
              	if(strcmp(x,"0")==0)break;
			}
              break;
         case  0:
         	 break; 
        default:
        	system("cls");
			printf("��ֻ������0~5��6������֮һ\n\n");
			system("pause"); 
		}
	  }
    	
    }
}
