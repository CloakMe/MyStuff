// Queue.cpp : Defines the entry point for the console application.
//
//Present an implementation of a Queue (FIFO) object (with Put, Get and
//IsEmpty methods) using two Stack (LIFO) objects to store the Queue contents.
//A Stack object has Push, Pop and IsEmpty methods.
#include <iostream>

#define MAX_SIZE 10

template <class T>
class Stack 
{
    T values[MAX_SIZE];
    int counter;
  public:
    Stack ()
    {
        counter = 0;
    }

    void push(T value)
    {
        if(counter < MAX_SIZE)
            values[counter++] = value; 
        else
            throw;
    }

    T pop() 
    {
        if(counter > 0)
            return values[--counter]; 
        else
            throw;
    }

    bool IsEmpty() const
    {
        return (counter == 0);
    }
};

template <class T>
class Queue
{
    Stack<T> stackForPopping;
    Stack<T> stackForPushing;
public:
    void push(const T& value)
    {        
        stackForPushing.push(value);
    }

    T pop() 
    {
        if(stackForPopping.IsEmpty() && stackForPushing.IsEmpty())
            throw;
        if(stackForPopping.IsEmpty())
        {
            while(!stackForPushing.IsEmpty() )
            {
                T val = stackForPushing.pop();
                stackForPopping.push(val);
            }
        }
        
        return stackForPopping.pop();
    }

    bool IsEmpty() const
    {
        if(stackForPopping.IsEmpty() && stackForPushing.IsEmpty())
            return true;
    }

};

int main()
{
    Queue<int> q;
    //for(int i=0;i<MAX_SIZE;i++)
    //    q.push(i);

    q.push(1);
    q.push(2);
    q.push(3);
    std::cout<< q.pop() << std::endl; 
    std::cout<< q.pop() << std::endl; 
    std::cout<< q.pop() << std::endl; 

    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    std::cout<< s.pop() << std::endl; 
    std::cout<< s.pop() << std::endl; 
    std::cout<< s.pop() << std::endl; 
	return 0;
}

