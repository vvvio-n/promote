#pragma once
#ifndef __SQ_QUEUE_H__
#define __SQ_QUEUE_H__

#include <functional>  // ���� std::function

// ���� Status ���ͣ������δ���壩
// enum Status {
//     SUCCESS,
//     OVER_FLOW,
//     UNDER_FLOW
// };

// ѭ������ģ����
template<class ElemType>
class SeqQueue {
protected:
    // ѭ�����е����ݳ�Ա:
    int front;										// ��ͷָ�� 
    int rear;											// ��βָ�� 
    int maxSize;										// ���е�������� 
    ElemType* elems;									// Ԫ�ش洢�ռ�

public:
    //  ѭ�����еķ������������ر���ϵͳĬ�Ϸ�������:
    SeqQueue(int size = DEFAULT_SIZE);				// ���캯��
    virtual ~SeqQueue();							// ��������
    int GetLength() const;							// ����еĳ���			 
    bool IsEmpty() const;							// �ж϶����Ƿ�Ϊ��
    void Clear();									// ���������
    void Traverse(const std::function<void(const ElemType&)>& Visit) const;	// ��������
    Status EnQueue(const ElemType e);					// ���
    Status DelQueue(ElemType& e);						// ����
    Status GetHead(ElemType& e) const;				// ȡ����Ԫ��
    SeqQueue(const SeqQueue<ElemType>& s);			// ���ƹ��캯��
    SeqQueue<ElemType>& operator =(const SeqQueue<ElemType>& s); // ��ֵ�������
};

// ѭ���������ʵ�ֲ���
template<class ElemType>
SeqQueue<ElemType>::SeqQueue(int size)
// �������������һ���������Ϊsize�Ŀն���
{
    maxSize = size;						// ���е��������
    elems = new ElemType[maxSize];		// �����µĴ洢�ռ�
    front = 0;
    rear = 0;
}

template<class ElemType>
SeqQueue<ElemType>::~SeqQueue()
// ������������ٶ���
{
    delete[]elems;					// �ͷŶ��еĴ洢�ռ�
}

template <class ElemType>
int SeqQueue<ElemType>::GetLength() const
// ������������ض�����Ԫ�ظ���
{
    return (rear - front + maxSize) % maxSize;
}

template<class ElemType>
bool SeqQueue<ElemType>::IsEmpty() const
// ��������������Ϊ�գ��򷵻�true�����򷵻�false
{
    return front == rear;
}

template<class ElemType>
void SeqQueue<ElemType>::Clear()
// �����������ն���
{
    front = 0;
    rear = 0;
}

template <class ElemType>
void SeqQueue<ElemType>::Traverse(const std::function<void(const ElemType&)>& Visit) const {
    for (int i = front; i != rear; i = (i + 1) % maxSize) {
        Visit(elems[i]);
    }
    if (!IsEmpty()) {
        Visit(elems[rear]);
    }
}

template<class ElemType>
Status SeqQueue<ElemType>::EnQueue(const ElemType e)
// �����������Ԫ��e׷�ӵ���β,��ɹ��򷵼�SUCCESS,���������������OVER_FLOW
{
    if ((rear + 1) % maxSize == front) // ��������
        return OVER_FLOW;
    else {	// �����ɹ�
        elems[rear] = e;	// ��Ԫ��e׷�ӵ���β 
        rear = (rear + 1) % maxSize;
        return SUCCESS;
    }
}

template<class ElemType>
Status SeqQueue<ElemType>::DelQueue(ElemType& e)
// �������������зǿ�,ɾ����ͷԪ��,����e���ض�ͷԪ��,��������SUCCESS,����
// ��������UNDER_FLOW
{
    if (IsEmpty())	 // ���п�
        return UNDER_FLOW;
    else { // �����ɹ�
        e = elems[front];	// ��e���ض�ͷԪ��
        front = (front + 1) % maxSize;
        return SUCCESS;
    }
}

template<class ElemType>
Status SeqQueue<ElemType>::GetHead(ElemType& e) const
// �������������зǿ�,��e���ض���Ԫ��,��������SUCCESS,����������UNDER_FLOW
{
    if (IsEmpty())	 // ���п�
        return UNDER_FLOW;
    else { // ���зǿ�,�����ɹ�
        e = elems[front];	// ��e���ض���Ԫ��
        return SUCCESS;
    }
}

template<class ElemType>
SeqQueue<ElemType>::SeqQueue(const SeqQueue<ElemType>& s)
// ����������ɶ���s�����¶���--���ƹ��캯��
{
    maxSize = s.maxSize;			    // ���е�������� 
    elems = new ElemType[maxSize];		// ����洢�ռ�
    front = s.front;				    // ���ƶ�ͷָ�� 
    rear = s.rear;				    // ���ƶ�βָ�� 
    for (int i = front; i != rear; i = (i + 1) % maxSize) {
        elems[i] = s.elems[i];
    }
}

template<class ElemType>
SeqQueue<ElemType>& SeqQueue<ElemType>::operator =(const SeqQueue<ElemType>& s)
// ���������������s��ֵ����ǰ����--��ֵ�������
{
    if (&s != this) {
        delete[]elems;					// �ͷ����д洢�ռ�
        maxSize = s.maxSize;			    // ���е�������� 
        elems = new ElemType[maxSize];		// ����洢�ռ�
        front = s.front;				    // ���ƶ�ͷָ�� 
        rear = s.rear;				    // ���ƶ�βָ�� 
        for (int i = front; i != rear; i = (i + 1) % maxSize) {
            elems[i] = s.elems[i];
        }
    }
    return *this;
}

#endif // __SQ_QUEUE_H__
