/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include"jiegouti.h"*/

void iniHashTable(table *t)//初始化哈希表 
{
	int i; 
	if(t==NULL)	return;
	
	for( i=0;i<64;++i)
	{
		t->bucket[i].key=NULL;
		t->bucket[i].address=NULL;
		t->bucket[i].next=NULL;
	}
	return;
}

void freeHashTable(table *t)//释放哈希表 
{
	int i;
	if(t==NULL) return;//如果哈希表是空的就不用释放了 
	entry *e,*ep;
	for(i=0;i<64;++i)
	{
		e=&(t->bucket[i]);
		while(e->next!=NULL)
		{
			ep=e->next;
			e->next=ep->next;
			free(ep->key);
			free(ep->address);
			free(ep);
		}
	}
}

//哈希散列方法函数
int keyToIndex(char* key)
{
    int index , len , i;
    if (key == NULL)return -1;

    len = strlen(key);
    index = (int)key[0];
    for (i = 1; i<len; ++i) {
        index *= 1103515245 + (int)key[i];
    }
    index >>= 25;//int的范围是正负2^31，定义了2^6=64个桶，所以要根据二进制表示方法右移31-6=25位 
    index &= (64 - 1);//对64取余 
    return index;
}

//哈希表中插入或修改数据 
void* insertEntry(table* t , char* key , void* address)//从哈希表t中找key对应的value 
{
    int index;
    entry* e , *ep;

    if (t == NULL || key == NULL || address == NULL) {//输入格式有误情况 
			return NULL;
    }

    index = keyToIndex(key);//转码行为 
    //key值如果在哈希表里不存在就插入 
    if (t->bucket[index].key == NULL) {//如果key值不存在就插入 
        t->bucket[index].key = strdup(key);//把key拷贝给哈希表里的那个key 
        t->bucket[index].address = address;//同上，拷贝value 
		return address;
    }
    //下面else这一串是修改原有的key对应的value 
    else {//key值存在要继续找next，因为不同的key值可能对应相同的index，这些不同的key值用链表储存 
		e = ep = &(t->bucket[index]);//开头,ep是e的前置节点 
        while (e != NULL) { //先从已有的找
            if (strcmp(e->key , key) == 0) {
                //找到key所在，替换值
                e->address=address;
                return e->address;   //插入完成了
            }
            ep = e;//没找到就接着往下找 
            e = e->next;
        } // end while(e...

        //key值在哈希表里不存在就插入 
		//没有在当前桶中找到
        //创建条目加入
        e = (entry*)malloc(sizeof (entry));
        e->key = strdup(key);
        e->address=address;
        e->next = NULL;
        ep->next = e;
    }
    return e->address;
}

//在哈希表中查找key对应的value
//找到了返回value的地址，没找到返回NULL
void* findValueByKey(table* t , char* key)
{
    int index;
    const entry* e;
    if (t == NULL || key == NULL) {
        return NULL;
    }
    index = keyToIndex(key);//转码行为 
    e = &(t->bucket[index]);
    if (e->key == NULL) return NULL;//这个桶还没有元素
    while (e != NULL) {
        if (0 == strcmp(key , e->key)) {
            return e->address;    //找到了，返回值
        }
        e = e->next;
    }
    return NULL;
}

//在哈希表中查找key对应的entry
//找到了返回entry，并将其从哈希表中移除
//没找到返回NULL
//记得释放要移除的entry的空间 
void removeEntry(table* t , char* key)
{
    int index;
    entry* e,*ep,*pre;   //查找的时候，把ep作为返回值,pre用来记录e的前置节点 
    if (t == NULL || key == NULL) {//格式不正确，不给数据就没法查 
        return;
    }
    index = keyToIndex(key);//转码行为 
    e = &(t->bucket[index]);
    pre=e; 
    while (e != NULL) {
        if (0 == strcmp(key , e->key)) {
            //如果是桶的第一个
            if (e == &(t->bucket[index])) {
                //如果这个桶有两个或以上元素
                //交换第一个和第二个，然后移除第二个
                ep = e->next;
                if (ep != NULL) {
                    entry tmp = *e; //做浅拷贝交换
                    *e = *ep;//相当于链表的头节点已经移除
                    *ep = tmp;  //这就是移除下来的链表头节点
                    ep->next = NULL;
                    free(ep->key);//释放空间
//                    free(ep->address);
					free(ep); 
                }
                else {//这个桶只有第一个元素
                    ep = (entry*)malloc(sizeof(entry));
                    *ep = *e;
                    e->key = NULL;
					e->address = NULL;
                    e->next = NULL;
                }
            }
            else {
                //如果不是桶的第一个元素
                ep = pre;
                ep->next = e->next;
                e->next = NULL;
                ep = e;
            }
            return;
        }// end if(strcmp...
        e = e->next;
    }
    return;
}
