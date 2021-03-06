// ConsoleApplication6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <chrono>
#include <stdexcept>
#include <math.h>

#ifndef NODE
#define NODE

extern long long numberOfOps;

class Node
{
public:
	int _data;
	Node* next = NULL;               //+1

	Node();
	Node(int data);
	~Node();
};

#endif


Node::Node()
{
	_data = 0;            //+1
}

Node::Node(int data)
{
	_data = data;             //+1
}

Node::~Node()
{
}


#ifndef QUEUE
#define QUEUE

class Queue
{
private:
	Node * head = NULL;      //+1
	Node* tail = NULL;       //+1
	int length = 0;          //+1
public:
	Queue();
	~Queue();
	void add(int data);
	int remove();
	void addNode(Node* node);
	Node* removeNode();
	int getTail();
	bool isEmpty();
	int getLength();
	void clear();

	int& get(int index);
	void set(int index, int data);
	int& operator[](unsigned int index);    //+1

	void sort();
	void sort(int n);

	bool sortTest(int n);
};

#endif

Queue::Queue()
{
}

Queue::~Queue()
{
	clear();
}

void Queue::add(int data)
{
	if (head == NULL && tail == NULL)
	{
		head = new Node(data);          //+1
		tail = head;                    //+1
	}
	else
	{
		Node* temp = new Node(data);
		head->next = temp;
		head = temp;                    //+E(1;n)3
	}
	length++;
}

int Queue::remove()
{
	if (isEmpty())
	{
		throw std::logic_error("Cannot remove from an empty queue.");
	}
	length--;
	if (head == tail)
	{
		int returnValue = head->_data;
		delete head;
		head = NULL;
		tail = NULL;
		return returnValue;               //+5
	}
	else
	{
		Node* temp = tail;
		tail = temp->next;
		int returnValue = temp->_data;
		delete temp;
		return returnValue;               //+E(1;n)5
	}
}

void Queue::addNode(Node* node)
{
	if (head == NULL && tail == NULL)
	{
		head = node;
		tail = node;
	}
	else
	{
		head->next = node;
		head = node;
	}
	length++;
}

Node* Queue::removeNode()
{
	Node* returnValue = tail;
	tail = tail->next;
	length--;
	if (length == 0)
	{
		head = NULL;
		tail = NULL;
	}
	return returnValue;
}

int Queue::getTail()
{
	return tail->_data;
}

bool Queue::isEmpty()
{
	return length == 0;
}

int Queue::getLength()
{
	return length;
}

void Queue::clear()
{
	while (!isEmpty())
	{
		remove();
	}
}

int& Queue::get(int index)
{
	Queue temp;
	int lengthOfQueue = length;
	for (int i = 0; i < index; i++)
	{
		temp.addNode(removeNode());
	}
	Node* tempNode = removeNode();
	int& returnValue = tempNode->_data;
	for (int i = 0; i <= lengthOfQueue - index - 2; i++)
	{
		temp.addNode(removeNode());
	}
	for (int i = 0; i < index; i++)
	{
		addNode(temp.removeNode());
	}
	addNode(tempNode);
	for (int i = 0; i <= lengthOfQueue - index - 2; i++)
	{
		addNode(temp.removeNode());
	}
	return returnValue;
}

void Queue::set(int index, int data)
{
	Queue temp;
	int lengthOfQueue = length;
	for (int i = 0; i < index; i++)
	{
		temp.addNode(removeNode());
	}
	tail->_data = data;
	for (int i = 0; i <= lengthOfQueue - index - 1; i++)
	{
		temp.addNode(removeNode());
	}
	for (int i = 0; i < lengthOfQueue; i++)
	{
		addNode(temp.removeNode());
	}
}

int& Queue::operator[](unsigned int index)
{
	return get(index);
}

void Queue::sort()
{
	sort(length);
}

void Queue::sort(int n)
{
	int x, left, right, sred;

	for (int i = 1; i < n; i++)
	{
		if (get(i - 1) > get(i))
		{
			x = get(i);
			left = 0;
			right = i - 1;
			do {
				sred = (left + right) / 2;
				if (get(sred) < x)   left = sred + 1;
				else right = sred - 1;
			} while (left <= right);

			for (int j = i - 1; j >= left; j--) set(j + 1, get(j));
			set(left, x);
		}
	}
}


double runSort(int arr[], int elementCount, int times)
{
	double curTime = 0;
	for (int j = 0; j < times; j++)
	{
		Queue queue;
		for (int k = 0; k < elementCount; k++)
		{
			queue.add(arr[k]);
		}
		auto t1 = std::chrono::high_resolution_clock::now();
		queue.sort(elementCount);
		auto t2 = std::chrono::high_resolution_clock::now();
		curTime += std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
	}
	curTime /= times;
	return curTime;
}

void experiment()
{
	const int max_n = 1000;
	int arr[max_n];
	srand(time(NULL));
	for (int i = 0; i < max_n; i++)
	{
		arr[i] = rand();
	}
	for (int i = 100; i <= max_n; i += 100)
	{
		double theoretical = 40 * pow(i, 3);
		double theoreticalBigO = pow(i, 3);
		double time = runSort(arr, i, 3);
		long long numberOfOps = 1 /*int+(int*i)*/;
		// TODO: 
		double c1 = theoretical / time;
		double c2 = theoreticalBigO / time;
		double c3 = theoretical / numberOfOps;
		double c4 = theoreticalBigO / numberOfOps;
		std::cout << "N = " << i
			<< "\tf(N) = " << theoretical
			<< "\tO(f(N)) = " << theoreticalBigO
			<< "\tT(N) = " << time
			<< "\tN_op = " << numberOfOps << std::endl
			<< "c1 = " << c1
			<< "\tc2 = " << c2
			<< "\tc3 = " << c3
			<< "\tc4 = " << c4 << std::endl;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	experiment();
	getchar();
	return 0;
}
