void* once_compair(void *tbegin,void *tend,char s[],int ccmp())//��������ͦ�鷳���š���������bug������
{
    if(strcmp(s,"meal")==0)//ʶ���������������ͣ������е㱿������orz
    {
        struct meal *p,*pf,*q,*qf,*t,*cend,*mid;
        pf=(struct meal *)tbegin;
        p=pf->next;
        qf=p;
        cend=(struct meal *)tend;
        q=qf->next;
        mid=p;
        while(q!=cend)
        {
            if(ccmp(q,mid))
            {
                if(p!=q)
                if(p->next!=q)//�����￪ʼ��bug�������ڵ����ݵģ�˳��һ��ĳɶ�x�����������ܹ��ģ�����ͨ���Ծ�����
                {//����Ȼ����ͨ���ԾͲ���orz
                    t=p->next;
                    pf->next=p->next;
                    qf->next=q->next;
                    p->next=q->next;
                    q->next=t;
                    qf->next=p;
                    pf->next=q;
                }
                else
                {
                    p->next=q->next;
                    q->next=p;
                    pf->next=q;
                    qf=pf->next;
                }
                p=pf->next;
                q=qf->next;
                pf=p;
                p=p->next;
            }//������bug����
            qf=q;
            q=qf->next;
        }
        return pf;
    }
}
void sort(void *cbegin,void *cend,char s[],int ccmp())
{
    if(strcmp(s,"meal")==0)//ʶ����������������
    {
        struct meal *t,*t2,*begin,*end;
        begin=(struct meal *)cbegin;
        end=(struct meal *)cend;
        if(begin!=end&&begin->next!=end&&begin->next->next!=end)
        {
            t=(struct meal *)once_compair(cbegin,cend,s,ccmp);
			t2=t->next;
            if(t!=begin)
            {
				sort(t,cend,s,ccmp);
				sort(cbegin,t2,s,ccmp);
			}
            else
            {
				sort(t2,cend,s,ccmp);
			}
        }
    }
    return;
}
