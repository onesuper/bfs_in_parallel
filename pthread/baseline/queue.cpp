template<class QElmType>  
struct qnode  
{  
    struct qnode *prev, *next;  
    QElmType data;  
};  
  
template<class QElmType>  
class safe_queue  
{  
public:  
    safe_queue()   
    {  
        m_front = new qnode<QElmType>;  
        m_front->next = 0;  
        m_rear = m_front;  
    }  
    ~safe_queue() {}  
    void destroy()  
    {  
        while (m_front)  
        {  
            m_rear = m_front->next;  
            delete m_front;  
            m_front = m_rear;  
        }  
    }  
    //将新的节点放入队列尾部  
    bool push(QElmType e)  
    {  
        //新建一个节点  
        struct qnode<QElmType> *p = new qnode<QElmType>;  
        if (!p)  
            return false;  
        p->next = 0;  
        while (1)  
        {  
            struct qnode<QElmType> *rear = m_rear;  
            p->prev = rear;  
            //如果队列没有改变将p赋值给m_rear，否则继续循环  
            if (InterlockedCompareExchangePointer((volatile PVOID *)&m_rear,   
                p, rear) == rear)  
            {  
                rear->next = p;  
                rear->data = e;  
                break;  
            }  
        }  
        return true;  
    }  
    //从队列头部取出一个节点  
    bool pop(QElmType *e)  
    {  
        while (1)  
        {  
            struct qnode<QElmType> *front = m_front;  
            if (front == m_rear)  
                return false;  
            //如果队列位置没有变将m_front指向下一个位置,否则继续循环  
            if(InterlockedCompareExchangePointer((volatile PVOID *)&m_front,  
                m_front->next, front) == front)  
            {  
                *e = front->data;  
                delete front;  
                return true;  
            }  
        }  
        return true;  
    }  
private:  
    struct qnode<QElmType> *m_front, *m_rear;  
};  
