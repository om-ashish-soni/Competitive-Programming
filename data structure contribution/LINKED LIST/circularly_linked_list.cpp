#include<iostream>
using namespace std;
class Node{
    public:
    int val;
    Node *link;
    Node(){
        this->val=-1;
        this->link=NULL;
    }
    Node(int x){
        this->val=x;
        this->link=NULL;
    }
};
class CircularlyLinkedList{
    Node *head=NULL;
    Node *listHead;
    Node *tail=NULL;
    public:
    CircularlyLinkedList(){
        listHead=(Node *)malloc(sizeof(Node));
        listHead->val=-1;
        listHead->link=NULL;
        head = listHead;
    }
    Node* begin(){
        return head;
    }
    Node* end(){
        return tail;
    }
    void insertAtFront(int x){
        Node *newNode=(Node *)malloc(sizeof(Node));
        if(NULL == newNode){
            printf("bad alloc__ could not insert a node_");
            exit(0);
        }
        if(NULL == listHead->link){
            tail=newNode;
        }
        newNode->val=x;
        newNode->link=listHead->link;
        listHead->link=newNode;
        tail->link=newNode;
    }
    Node* insertAtFrontWithoutListHead(int x){
        Node *directHead=listHead->link;
        Node *newNode=(Node *)malloc(sizeof(Node));
        if(NULL == newNode){
            printf("bad alloc__ could not insert a node_");
            exit(0);
        }
        if(NULL == directHead){
            tail=newNode;
        }
        newNode->val=x;
        newNode->link=directHead;
        directHead=newNode;
        listHead->link=directHead;//just for maintaing program nothing else
        tail->link=newNode; 
        return newNode;
    }
    void insertAtLast(int x){
        Node *newNode=(Node *)malloc(sizeof(Node));
        if(NULL == newNode){
            printf("bad alloc__ could not insert a node_");
            exit(0);
        }
        if(NULL == listHead->link){
            tail=newNode;
        }
        newNode->val=x;
        tail->link=newNode;
        tail=newNode;
        tail->link=listHead->link;
    }
    void insertAtLastWithoutListHead(int x){
        Node* directHead=listHead->link;
        Node* newNode=(Node *)malloc(sizeof(Node));
        if(NULL == newNode){
            printf("bad alloc__ could not insert a node_");
            exit(0);
        }
        if(NULL == directHead){
            directHead=newNode;
            listHead->link=directHead;//only for maintaining program nothing else
            tail=newNode;       
        }
        newNode->val=x;
        tail->link=newNode;
        tail=newNode;
        tail->link=directHead;
    }
    void deleteFromEnd(){
        if(NULL == tail){
            printf("list is empty\n");
            exit(0);
        }
        if(listHead->link == tail){
            free(tail);
            listHead->link=NULL;
            tail=NULL;
            return;
        }
        Node *current=listHead->link;
        while(current->link != tail){
            current=current->link;

        }
        current->link=listHead->link;
        free(tail);
        tail=current;
    }
    void deleteFromFront(){
        if(NULL == tail){
            printf("list is empty\n");
            exit(0);
        }
        if(listHead->link == tail){
            free(tail);
            listHead->link=NULL;
            tail=NULL;
            return;
        }
        Node *front=listHead->link;
        listHead->link=front->link;
        free(front);
        tail->link=listHead->link;
    }
    void deleteAtAddress(Node* address){
        Node *first=listHead->link;
        Node *current=first;
        if(NULL == first){
            printf("list is empty\n");
            return;
        }
        if(address == tail){
            return this->deleteFromEnd();
        }else if(address==listHead->link){
            return this->deleteFromFront();
        }
        while(current->link != tail && address != current->link){
            current=current->link;
        }
        if(tail == current->link){
            printf("node with given address is not present in the list\n");
            return;
        }
        Node *temp=(current->link)->link;
        free(current->link);
        current->link=temp;
    }
    void deleteAtAddressWithoutListHead(Node* address){
        Node *directHead=listHead->link;
        Node *first=directHead;
        Node *current=first;
        if(NULL == first){
            printf("list is empty\n");
            return;
        }
        if(address == tail){
            return this->deleteFromEnd();
        }else if(address==directHead){
            return this->deleteFromFront();
        }
        while(current->link != tail && address != current->link){
            current=current->link;
        }
        if(tail == current->link){
            printf("node with given address is not present in the list\n");
            return;
        }
        Node *temp=(current->link)->link;
        free(current->link);
        current->link=temp;
    }
    void deleteWithIndex(int index){
        Node *first=listHead->link;
        Node *current=first;
        if(NULL == first){
            printf("list is empty\n");
            return;
        }
        if(index == -1){
            return this->deleteFromEnd();
        }else if(index == 0){
            return this->deleteFromFront();
        }
        while(current != tail && index>0){
            current=current->link;
            index--;
        }
        if(index!=0){
            printf("Element with given index is not present in the list\n");
            return;
        }
        return this->deleteAtAddress(current);
    }
    void deleteWithIndexWithoutListHead(int index){
        Node *directHead=listHead->link;
        Node *first=directHead;
        Node *current=first;
        if(NULL == first){
            printf("list is empty\n");
            return;
        }
        if(index == -1){
            return this->deleteFromEnd();
        }else if(index == 0){
            return this->deleteFromFront();
        }
        while(current != tail && index>0){
            current=current->link;
            index--;
        }
        if(index!=0){
            printf("Element with given index is not present in the list\n");
            return;
        }
        return this->deleteAtAddress(current);
    }
    void deleteWithValueWithoutListHead(int x){
        Node *directHead=listHead->link;
        Node *first=directHead;
        Node *current=first;
        int value=current->val;
        if(NULL == first){
            printf("list is empty\n");
            return;
        }
        
        while(current != tail && x != value){
            current=current->link;
            value=current->val;
        }
        if(x != value){
            printf("Element with given index is not present in the list\n");
            return;
        }
        if(current == directHead){
            return this->deleteFromFront();
        }else if(current == tail){
            return this->deleteFromEnd();
        }
        
        return this->deleteAtAddress(current);
    }
    void deleteWithValue(int x){
        Node *first=listHead->link;
        Node *current=first;
        int value=current->val;
        if(NULL == first){
            printf("list is empty\n");
            return;
        }
        
        while(current != tail && x != value){
            current=current->link;
            value=current->val;
        }
        if(x != value){
            printf("Element with given index is not present in the list\n");
            return;
        }
        if(current == listHead->link){
            return this->deleteFromFront();
        }else if(current == tail){
            return this->deleteFromEnd();
        }
        
        return this->deleteAtAddress(current);
    }
    void print(){
        Node *first=listHead->link;
        Node *current=first;
        if(NULL == first){
            printf("list is empty");
            exit(0);
        }
        do{
            cout<<current->val<<" ";
            current=current->link;
        }while(first != current);
        cout<<endl;
    }
    void swap(int &x,int &y){
        int temp=x;
        x=y;
        y=temp;
    }
    void sort(){
        Node *first=listHead->link;
        Node *current=first;
        Node *next=current->link;
        if(NULL == first || first == tail){
            return;
        }
        do{
            int &small=current->val;
            next=current->link;
            while(first != next){
                int &large=next->val;
                // cout<<small<<" "<<large<<endl;
                if(small>large) swap(small,large);
                next=next->link;
            }
            // cout<<endl<<"-------------"<<endl;
            current=current->link;
        }while(first != current);
    }
};
int main(){
    CircularlyLinkedList cList;
    {
    	Node* address4=cList.insertAtFrontWithoutListHead(8);
	    Node* address3=cList.insertAtFrontWithoutListHead(9);
	    Node* address2=cList.insertAtFrontWithoutListHead(4);
	    Node* address1=cList.insertAtFrontWithoutListHead(2);
    }
	    
    {
    	// cout<<address<<endl;
        // cList.deleteWithIndex(-2);
    }
    {
    	cList.insertAtLast(10);
        cList.insertAtLast(3);
        cList.insertAtLast(6);
        cList.insertAtLast(5);
        cList.insertAtLast(7);
        cList.insertAtFront(1);
        cList.print();
        cList.sort();
        cList.print();
    }
    return 0;
}