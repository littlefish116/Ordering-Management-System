/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include"jiegouti.h"*/

void iniHashTable(table *t)//��ʼ����ϣ�� 
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

void freeHashTable(table *t)//�ͷŹ�ϣ�� 
{
	int i;
	if(t==NULL) return;//�����ϣ���ǿյľͲ����ͷ��� 
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

//��ϣɢ�з�������
int keyToIndex(char* key)
{
    int index , len , i;
    if (key == NULL)return -1;

    len = strlen(key);
    index = (int)key[0];
    for (i = 1; i<len; ++i) {
        index *= 1103515245 + (int)key[i];
    }
    index >>= 25;//int�ķ�Χ������2^31��������2^6=64��Ͱ������Ҫ���ݶ����Ʊ�ʾ��������31-6=25λ 
    index &= (64 - 1);//��64ȡ�� 
    return index;
}

//��ϣ���в�����޸����� 
void* insertEntry(table* t , char* key , void* address)//�ӹ�ϣ��t����key��Ӧ��value 
{
    int index;
    entry* e , *ep;

    if (t == NULL || key == NULL || address == NULL) {//�����ʽ������� 
			return NULL;
    }

    index = keyToIndex(key);//ת����Ϊ 
    //keyֵ����ڹ�ϣ���ﲻ���ھͲ��� 
    if (t->bucket[index].key == NULL) {//���keyֵ�����ھͲ��� 
        t->bucket[index].key = strdup(key);//��key��������ϣ������Ǹ�key 
        t->bucket[index].address = address;//ͬ�ϣ�����value 
		return address;
    }
    //����else��һ�����޸�ԭ�е�key��Ӧ��value 
    else {//keyֵ����Ҫ������next����Ϊ��ͬ��keyֵ���ܶ�Ӧ��ͬ��index����Щ��ͬ��keyֵ�������� 
		e = ep = &(t->bucket[index]);//��ͷ,ep��e��ǰ�ýڵ� 
        while (e != NULL) { //�ȴ����е���
            if (strcmp(e->key , key) == 0) {
                //�ҵ�key���ڣ��滻ֵ
                e->address=address;
                return e->address;   //���������
            }
            ep = e;//û�ҵ��ͽ��������� 
            e = e->next;
        } // end while(e...

        //keyֵ�ڹ�ϣ���ﲻ���ھͲ��� 
		//û���ڵ�ǰͰ���ҵ�
        //������Ŀ����
        e = (entry*)malloc(sizeof (entry));
        e->key = strdup(key);
        e->address=address;
        e->next = NULL;
        ep->next = e;
    }
    return e->address;
}

//�ڹ�ϣ���в���key��Ӧ��value
//�ҵ��˷���value�ĵ�ַ��û�ҵ�����NULL
void* findValueByKey(table* t , char* key)
{
    int index;
    const entry* e;
    if (t == NULL || key == NULL) {
        return NULL;
    }
    index = keyToIndex(key);//ת����Ϊ 
    e = &(t->bucket[index]);
    if (e->key == NULL) return NULL;//���Ͱ��û��Ԫ��
    while (e != NULL) {
        if (0 == strcmp(key , e->key)) {
            return e->address;    //�ҵ��ˣ�����ֵ
        }
        e = e->next;
    }
    return NULL;
}

//�ڹ�ϣ���в���key��Ӧ��entry
//�ҵ��˷���entry��������ӹ�ϣ�����Ƴ�
//û�ҵ�����NULL
//�ǵ��ͷ�Ҫ�Ƴ���entry�Ŀռ� 
void removeEntry(table* t , char* key)
{
    int index;
    entry* e,*ep,*pre;   //���ҵ�ʱ�򣬰�ep��Ϊ����ֵ,pre������¼e��ǰ�ýڵ� 
    if (t == NULL || key == NULL) {//��ʽ����ȷ���������ݾ�û���� 
        return;
    }
    index = keyToIndex(key);//ת����Ϊ 
    e = &(t->bucket[index]);
    pre=e; 
    while (e != NULL) {
        if (0 == strcmp(key , e->key)) {
            //�����Ͱ�ĵ�һ��
            if (e == &(t->bucket[index])) {
                //������Ͱ������������Ԫ��
                //������һ���͵ڶ�����Ȼ���Ƴ��ڶ���
                ep = e->next;
                if (ep != NULL) {
                    entry tmp = *e; //��ǳ��������
                    *e = *ep;//�൱�������ͷ�ڵ��Ѿ��Ƴ�
                    *ep = tmp;  //������Ƴ�����������ͷ�ڵ�
                    ep->next = NULL;
                    free(ep->key);//�ͷſռ�
//                    free(ep->address);
					free(ep); 
                }
                else {//���Ͱֻ�е�һ��Ԫ��
                    ep = (entry*)malloc(sizeof(entry));
                    *ep = *e;
                    e->key = NULL;
					e->address = NULL;
                    e->next = NULL;
                }
            }
            else {
                //�������Ͱ�ĵ�һ��Ԫ��
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
