#include <iostream>
#include <string>

using namespace std;

struct Node{
	string name;
	int id;
	Node* next
}

class List{
	private:
		Node *head, *tail;
		int amount;
	public:
		List(){
			head = nullptr;
			tail = nullptr;
			amount = 0;
		}
		void add(Node* element){
			if(head == nullptr){
				head = element;
				tail = element;
				amount += 1;
			}else{C
				tail->next = element;
				tail = tail->next;
			}
			
		}
		void remove(Node* element){
			Node *temp = head;
			while(temp->id != element->id){
				temp = temp->next;
			}
			temp->prev->next = temp->next;
			delete temp;
		}
		void sortAlphabet();
		void sortUp();
		void sortDown();
		void switchRing();
		void switchStart();
	
}

int main(){
	
}
