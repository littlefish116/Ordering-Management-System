struct staff{
	char staff_id[10];  //Ա������
    char staff_name[30];  //Ա������
    char staff_idt[15];  //Ա��ְҵ 
    struct staff *next;
};


struct hashEntry
{
    char* key;
    void* address;
    struct hashEntry* next;
};

typedef struct hashEntry entry;

struct hashTable
{
    entry bucket[64];  //��Ĭ�϶���64��Ͱ
};

typedef struct hashTable table;

struct meal{
	int num;
    char order[10];
    char name[30];
    char kind[20];
    char cprice[50];
    float price;
    int rank;
    char crank[60];
    struct meal *next;
};//����˵����� 

typedef struct jilu{
	float value;
	int num;
}jilu;


table *haxi_staff;
struct staff *staff_end,*staff_head;
struct meal *meal_head,*meal_end;//���ڱ�������е�Ԫ�� 
table *haxi_meal;//����һ����ϣ�� 
