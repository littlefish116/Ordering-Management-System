struct staff{
	char staff_id[10];  //员工工号
    char staff_name[30];  //员工姓名
    char staff_idt[15];  //员工职业 
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
    entry bucket[64];  //先默认定义64个桶
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
};//定义菜的属性 

typedef struct jilu{
	float value;
	int num;
}jilu;


table *haxi_staff;
struct staff *staff_end,*staff_head;
struct meal *meal_head,*meal_end;//用于标记链表中的元素 
table *haxi_meal;//定义一个哈希表 
