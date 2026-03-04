#pragma once
#include <string>
#include <iostream>

template<typename DataType>
class LinkedList
{
private:

	struct Node
	{
		DataType data;
		Node* next;
		Node(DataType d) : data(d), next(nullptr) {}
		Node() : data(), next(nullptr) {}
	};

	Node* head;
	Node* tail;
	int listSize;
public:

	//Construct a Linked List with a starting node
	LinkedList();
	~LinkedList();

	//Push the input data to a new node at the back of the list
	void PushBack(DataType data);

	
	struct Iterator
	{
		Iterator(Node* node) : currentNode(node) {} //when an itterator is made a node is passed in using the .Begin or .End functions

		//Overrides the ++ operator to move to the next node in the list. Returns the current location.
		Iterator operator++();

		//Overrides the * operator to output the data stored at the current node
		DataType operator*();

		//Overrides the != and == operators to allow Iterators to be compaired to eachother
		bool operator!=(const Iterator& other);
		bool operator==(const Iterator& other);

	private:
		friend class LinkedList;
		Node* currentNode;
	};

	//Search the list for the input data or location then remove it. 
	//Returns true if successful.
	//Errors on Empty List
	Iterator Remove(Iterator data);
	bool Remove(DataType data);
	bool Remove(int location);

	//Returns an Iterator storing the Head node
	Iterator Begin();

	//Returns an Iterator storing Nullptr
	Iterator End();
};

#pragma region LinkedList
template<typename DataType>
LinkedList<DataType>::LinkedList() : listSize(1)
{
	head = new Node();
	tail = head;
}

template<typename DataType>
void LinkedList<DataType>::PushBack(DataType data)
{
	Node* newNode = new Node(data); //create a new node with the input data

	tail->next = newNode; //insert new node at the end of the list
	tail = newNode; //store the newly made node as the tail node
	listSize += 1;
}

template<typename DataType>
inline typename LinkedList<DataType>::Iterator LinkedList<DataType>::Remove(Iterator it)
{
	Node* data = it.currentNode;
	Node temp = m_head;
	while (temp.next != data)
	{
		if (temp.next == nullptr)
		{
			return it;
		}
		temp = temp.next;

	}

	temp.next = data.next;
	delete data;
	if (temp.next == nullptr)
	{
		tail = temp;
	}
	return Iterator(temp);
}

template<typename DataType>
bool LinkedList<DataType>::Remove(DataType data)
{
	Node* temp = head;

	//Check if the head node is deleted as a different process needs to occur as there is no node before the head to connect the next one to
	if (data == temp->data) 
	{
		Node* cached = head; //cache the current head node so we dont cause a memory leak

		head = temp->next; //sets the head to the next node in the list

		std::cout << "Successfully located: " << data << ". Now removing it." << std::endl;
		delete cached;
		listSize -= 1;
		return true;
	}

	//Check if the tail node is deleted as a different process needs to occur as there is no node after the tail to connect the previous one to so it instead connects to nullptr
	else if (data == tail->data)
	{
		while (temp->next != tail && temp->next->next != nullptr) //search the entire list until the tail is located 
		{
			temp = temp->next;
		}
		Node* cached = temp->next; //store the current tail so we dont cause a memory leak
		temp->next = nullptr; //remove the current node from the list
		tail = temp; //set the new stored tail node

		std::cout << "Successfully located: " << data << ". Now removing it." << std::endl;
		delete cached;
		listSize -= 1;
		return true;
	}

	else
	{
		while (temp->next->data != data) //search the entire list for the input data
		{
			temp = temp->next;

			if (temp->next == nullptr)
			{
				std::cout << data << " not found for removal " << std::endl;
				return false; //break out of the function if no data matching data is located to the input
			}
		}
		Node* cached = temp->next; //caches the data in the node we are deleting so we dont create a memory leak
		temp->next = temp->next->next; //connect the current node which is the one before the one being deleted to the one after the one being deleted
		delete cached; //deleted the cached node
		listSize -= 1;
		return true;

	}
}

template<typename DataType>
bool LinkedList<DataType>::Remove(int location)
{

}
#pragma endregion

#pragma region Iterator


template<typename DataType>
typename LinkedList<DataType>::Iterator LinkedList<DataType>::Begin()
{
	return Iterator(head); //the returned Iterator has a copy of the node, not the original as the data is not being modified
}

template<typename DataType>
typename LinkedList<DataType>::Iterator LinkedList<DataType>::End()
{
	return Iterator(nullptr);
}


template<typename DataType>
typename LinkedList<DataType>::Iterator LinkedList<DataType>::Iterator::operator++()
{
	currentNode = currentNode->next;

	return currentNode;
}

template<typename DataType>
DataType LinkedList<DataType>::Iterator::operator*()
{
	return currentNode->data;
}

template<typename DataType>
bool LinkedList<DataType>::Iterator::operator!=(const Iterator& other)
{
	return currentNode != other.currentNode;
}

template<typename DataType>
bool LinkedList<DataType>::Iterator::operator==(const Iterator& other)
{
	return currentNode == other.currentNode;
}

#pragma endregion
