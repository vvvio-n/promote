#pragma once
#ifndef __SQ_QUEUE_H__
#define __SQ_QUEUE_H__

#include <functional>  // 包含 std::function

// 定义 Status 类型（如果尚未定义）
// enum Status {
//     SUCCESS,
//     OVER_FLOW,
//     UNDER_FLOW
// };

// 循环队列模板类
template<class ElemType>
class SeqQueue {
protected:
    // 循环队列的数据成员:
    int front;										// 队头指针 
    int rear;											// 队尾指针 
    int maxSize;										// 队列的最大容量 
    ElemType* elems;									// 元素存储空间

public:
    //  循环队列的方法声明及重载编译系统默认方法声明:
    SeqQueue(int size = DEFAULT_SIZE);				// 构造函数
    virtual ~SeqQueue();							// 析构函数
    int GetLength() const;							// 求队列的长度			 
    bool IsEmpty() const;							// 判断队列是否为空
    void Clear();									// 将队列清空
    void Traverse(const std::function<void(const ElemType&)>& Visit) const;	// 遍历队列
    Status EnQueue(const ElemType e);					// 入队
    Status DelQueue(ElemType& e);						// 出队
    Status GetHead(ElemType& e) const;				// 取队首元素
    SeqQueue(const SeqQueue<ElemType>& s);			// 复制构造函数
    SeqQueue<ElemType>& operator =(const SeqQueue<ElemType>& s); // 赋值语句重载
};

// 循环队列类的实现部分
template<class ElemType>
SeqQueue<ElemType>::SeqQueue(int size)
// 操作结果：构造一个最大容量为size的空队列
{
    maxSize = size;						// 队列的最大容量
    elems = new ElemType[maxSize];		// 分配新的存储空间
    front = 0;
    rear = 0;
}

template<class ElemType>
SeqQueue<ElemType>::~SeqQueue()
// 操作结果：销毁队列
{
    delete[]elems;					// 释放队列的存储空间
}

template <class ElemType>
int SeqQueue<ElemType>::GetLength() const
// 操作结果：返回队列中元素个数
{
    return (rear - front + maxSize) % maxSize;
}

template<class ElemType>
bool SeqQueue<ElemType>::IsEmpty() const
// 操作结果：如队列为空，则返回true，否则返回false
{
    return front == rear;
}

template<class ElemType>
void SeqQueue<ElemType>::Clear()
// 操作结果：清空队列
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
// 操作结果：将元素e追加到队尾,如成功则返加SUCCESS,如队列已满将返回OVER_FLOW
{
    if ((rear + 1) % maxSize == front) // 队列已满
        return OVER_FLOW;
    else {	// 操作成功
        elems[rear] = e;	// 将元素e追加到队尾 
        rear = (rear + 1) % maxSize;
        return SUCCESS;
    }
}

template<class ElemType>
Status SeqQueue<ElemType>::DelQueue(ElemType& e)
// 操作结果：如队列非空,删除队头元素,并用e返回队头元素,函数返回SUCCESS,否则
// 函数返回UNDER_FLOW
{
    if (IsEmpty())	 // 队列空
        return UNDER_FLOW;
    else { // 操作成功
        e = elems[front];	// 用e返回队头元素
        front = (front + 1) % maxSize;
        return SUCCESS;
    }
}

template<class ElemType>
Status SeqQueue<ElemType>::GetHead(ElemType& e) const
// 操作结果：如队列非空,用e返回队首元素,函数返回SUCCESS,否则函数返回UNDER_FLOW
{
    if (IsEmpty())	 // 队列空
        return UNDER_FLOW;
    else { // 队列非空,操作成功
        e = elems[front];	// 用e返回队首元素
        return SUCCESS;
    }
}

template<class ElemType>
SeqQueue<ElemType>::SeqQueue(const SeqQueue<ElemType>& s)
// 操作结果：由队列s构造新队列--复制构造函数
{
    maxSize = s.maxSize;			    // 队列的最大容量 
    elems = new ElemType[maxSize];		// 分配存储空间
    front = s.front;				    // 复制队头指针 
    rear = s.rear;				    // 复制队尾指针 
    for (int i = front; i != rear; i = (i + 1) % maxSize) {
        elems[i] = s.elems[i];
    }
}

template<class ElemType>
SeqQueue<ElemType>& SeqQueue<ElemType>::operator =(const SeqQueue<ElemType>& s)
// 操作结果：将队列s赋值给当前队列--赋值语句重载
{
    if (&s != this) {
        delete[]elems;					// 释放已有存储空间
        maxSize = s.maxSize;			    // 队列的最大容量 
        elems = new ElemType[maxSize];		// 分配存储空间
        front = s.front;				    // 复制队头指针 
        rear = s.rear;				    // 复制队尾指针 
        for (int i = front; i != rear; i = (i + 1) % maxSize) {
            elems[i] = s.elems[i];
        }
    }
    return *this;
}

#endif // __SQ_QUEUE_H__
