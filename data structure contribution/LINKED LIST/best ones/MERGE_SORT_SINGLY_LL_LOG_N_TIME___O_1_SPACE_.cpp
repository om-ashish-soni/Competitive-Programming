#include <bits/stdc++.h>
using namespace std;
 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
 
int lengthOf(ListNode *head){
    int len=0;
    while(head){
        len++;
        head=head->next;
    }
    return len;
}
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2,int len1,int len2) {
    ListNode *head;
    if(len1 && len2){
        if(l1->val<=l2->val){
            head=l1;
            l1=l1->next;
            len1--;
        }else if(l1->val > l2->val){
            head=l2;
            l2=l2->next;
            len2--;
        }
        ListNode *last=head;
        
        
        while(len1 && len2  ){
            if(l1->val <= l2->val){
                last->next=l1;
                last=l1;
                l1=l1->next;//OK
                len1--;
            }else{
                last->next=l2;
                last=l2;
                l2=l2->next;
                len2--;
            }
        }
        if(len1 ){ last->next=l1;len1--;}
        if(len2 ){ last->next=l2;len2--;}
        return head;
    }else{
        if(l1 == NULL) return l2;
        else return l1;
    }
}
ListNode* mergeSort(ListNode* head,double len){
    int len1=ceil(len/2.0);
    int len2=len-len1;
    int temp=len1;
    ListNode *l1=head;
    ListNode *l2=head;
    while(temp){
        temp--;
        l2=l2->next;
    }
    if(len1 > 1) l1=mergeSort(l1,len1);
    if(len2 > 1) l2=mergeSort(l2,len2);
    return mergeTwoLists(l1,l2,len1,len2);
}
void repair(ListNode * head ,int len){
    for(int i=0;i<len-1;i++){
        head=head->next;
    }
    if(head) head->next=NULL;
}
void printList(ListNode *head){
    while(head){
        cout<<head->val<<" ";
        head=head->next;
    }
    cout<<endl;
}
ListNode* sortList(ListNode* head) {
    double len=lengthOf(head);
    head= mergeSort(head,len);
    repair(head,len);
    return head;
}
int main(){
    ListNode* head=NULL;
    ListNode* current=head;
    head=current=new ListNode;
    current->val=5;
    current->next=new ListNode;

    current=current->next;
    current->val=4;
    current->next=new ListNode;

    current=current->next;
    current->val=1;
    current->next=new ListNode;
    current=current->next;
    current->val=3;
    current->next=new ListNode;

    current=current->next;
    current->val=2;
    current->next=NULL;
    cout<<"before sorting"<<endl;
    printList(head);
    head=sortList(head);
    cout<<"after sorting"<<endl;
    printList(head);
    return 0;
}