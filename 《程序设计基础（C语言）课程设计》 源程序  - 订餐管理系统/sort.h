void* once_compair(void *tbegin,void *tend,char s[],int ccmp())//解释起来挺麻烦来着。。。挑着bug看就行
{
    if(strcmp(s,"meal")==0)//识别是哪种数据类型（算是有点笨的做法orz
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
                if(p->next!=q)//从这里开始是bug，交换节点数据的（顺带一提改成对x单独交换是能过的，但是通用性就少了
                {//（虽然本来通用性就不多orz
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
            }//到这里bug结束
            qf=q;
            q=qf->next;
        }
        return pf;
    }
}
void sort(void *cbegin,void *cend,char s[],int ccmp())
{
    if(strcmp(s,"meal")==0)//识别是哪种数据类型
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
