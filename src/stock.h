#include <list>
#include <string>
#include <iostream>
using namespace std;

class Stock{
	public:
	  string name;
	  struct node{
		  string date;
		  string volume;
		  string low;
		  string close;
		  node *next;
		  //node *previous;
	  };
		node *head,*tail;
		Stock()
			{
				head = NULL;
				tail = NULL;
			}
		void add_node(string date,string close,string low,string volume)
			{
				node *tmp = new node;
				tmp->date = date;
				tmp->close = close;
				tmp->low = low;
				tmp->volume=volume;
				tmp->next = NULL;

				if(head == NULL)
				{
					head = tmp;
					tail = tmp;
				}
				else
				{
					tail->next = tmp;
					tail = tail->next;
				}
			}
		void Print()
		{
            while(head!= NULL){
            cout<< "date: " << head->date;
            cout<< ", close: " <<  head->close;
            cout<< ", low: " <<  head->low;
            cout<< ", volume: " <<  head->volume<<endl;
            head=head->next;
           }

		}
};

