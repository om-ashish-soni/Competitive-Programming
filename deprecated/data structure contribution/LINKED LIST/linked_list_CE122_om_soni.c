#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef
struct list_node
{   
    int item;
    struct list_node *next;
    
}node;
void insert_at_beginning(node **head_addr, int value);    //code 0
void insert_at_end(node **head_addr, int value);          //code 1
void delete_from_beginning(node **head_addr);             //code 2
void delete_from_end(node **head_addr);                   //code 3
void print_list(node **head_addr);                        //code 4
node *head=NULL;
node *tail=NULL;
int len=0;
void pop_at_index(int index){
    if(index<1 || index>len){
        if(len>0) printf("%d th index is not exist, plase enter index between 1 and %d\n",index,len);
        else printf("can not pop since list is empty\n");
        return;
    }
    node * node_ptr=head;
    if(index == 1){
        return delete_from_beginning(&head);
    }else if(index==len){
        return delete_from_end(&head);
    }
    for(int i=1;i<index-1;i++){
        node_ptr=node_ptr->next;
    }
    
    node * popped_node=(node_ptr->next);
    node_ptr->next=popped_node->next;
    free(popped_node);
    len--;
}
void pop_before_index(int index){
    if(index<2 || index>len){
        if(len>0) printf("%d th index is not exist, plase enter index between 2 and %d\n",index,len);
        else printf("can not pop since list is empty\n");
        return;
    }
    node * node_ptr=head;
    if(index==2){
        return delete_from_beginning(&head);
    }
    for(int i=1;i<index-2;i++){
        node_ptr=node_ptr->next;
        
    }
    node * popped_node=(node_ptr->next);
    node_ptr->next=popped_node->next;
    free(popped_node);
    len--;
}
void pop_after_index(int index){
    if(index<1 || index>=len){
        if(len>0) printf("%d th index is not exist, plase enter index between 1 and %d\n",index,len-1);
        else printf("can not pop since list is empty\n");
        return;
    }
    node * node_ptr=head;
    if(index==len-1){
        return delete_from_end(&head);
    }
    for(int i=1;i<index-1;i++){
        node_ptr=node_ptr->next;
    }
    node * popped_node=(node_ptr->next);
    node_ptr->next=popped_node->next;
    free(popped_node);
    len--;
    
}
void update_at_index(int index,int value){
    if(index>len || index<=0){
        if(len>0) printf("please enter valid index between 1 and %d\n",len);
        else printf("can not update since list is empty\n");
        return;
    }
    node * node_ptr=head;
    for(int i=1;i<index;i++){
        node_ptr=node_ptr->next;
    }
    node_ptr->item=value;
}
void update_before_index(int index,int value){
    if(index>len || index<=1){
        if(len>0) printf("please enter valid index between 2 and %d\n",len);
        else printf("can not update since list is empty\n");
        return;
    }
    node * node_ptr=head;
    for(int i=1;i<index-1;i++){
        node_ptr=node_ptr->next;
    }
    node_ptr->item=value;
}
void update_after_index(int index,int value){
    if(index>=len || index<1){
        if(len>0) printf("please enter valid index between 1 and %d\n",len-1);
        else printf("can not update since list is empty\n");
        return;
    }
    node * node_ptr=head;
    for(int i=1;i<=index;i++){
        node_ptr=node_ptr->next;
    }
    node_ptr->item=value;
}
void insert_before_index(int index,int value){
    if(index>len || index<=0){
        printf("please enter valid index between 1 and %d\n",len);
        return;
    }
    node ** node_ptr=&head;
    if(index==1){
        return insert_at_beginning(&head,value);
        
    }
    for(int i=1;(*node_ptr) != NULL && i<index-1;i++){
        node_ptr=&((*node_ptr)->next);
    }
    
    if((*node_ptr) == NULL ){
        printf("%d th Index does not exist\n",index);
        return;
    }else{
        node *new_node=(node *)malloc(sizeof(node));
        new_node->item=value;
        new_node->next=(*node_ptr)->next;
        (*node_ptr)->next=new_node;
        len++;
    }
    
}
void insert_after_index(int index,int value){
    if(index>len || index<=0){
        printf("please enter valid index between 1 and %d\n",len);
        return;
    }
    node ** node_ptr=&head;
    if(index==len){
        return insert_at_end(&head,value);
    }
    for(int i=1;i<index;i++){
        node_ptr=&((*node_ptr)->next);
    }
    if((*node_ptr) == NULL){
        printf("%d th Index does not exist\n",index);
        return;
    }else{
         node *new_node=(node *) malloc(sizeof(node));
        new_node->item=value;
        new_node->next=(*node_ptr)->next;
        (*node_ptr)->next=new_node;
        len++;
    }
       
}
void insert_at_beginning(node **head_addr, int value){
        if(len==10){
            printf("List can not accommodate more than MAXSIZE elements");
            exit(0);
        }
        if(NULL == (*head_addr)){
            
            node* local_head= *head_addr;
            local_head=(node *)malloc(sizeof(node));
            *head_addr=local_head;
            local_head->item=value;
            tail=local_head;
            len++;
            // printf("%p first element %d\n",head,value);
            
        }else{
            node* new_head=(node *)malloc(sizeof(node));
            new_head->item=value;
            new_head->next=*head_addr;
            *head_addr=new_head;
            len++;
            // printf("%p pushing %d into the list\n",head,value);

        }   
        
        
    }    //code 0
    void insert_at_end(node **head_addr, int value){
        if(len==10){
            printf("List can not accommodate more than MAXSIZE elements");
            exit(0);
        }
        if(NULL == (*head_addr)){
            node* local_head= *head_addr;
            local_head=(node *)malloc(sizeof(node));
            *head_addr=local_head;
            local_head->item=value;
            tail=local_head;
            len++;
        }else{
            tail->next=(node *)malloc(sizeof(node));
            
            tail=(tail->next);
            tail->item=value;
            len++;
        }
        
        
    }         //code 1
    void delete_from_beginning(node **head_addr){
        if(len==0){
            printf("INVALID SEQUENCE OF COMMANDS");
            exit(0);
        }
        node * local_head=*head_addr;
        *head_addr=local_head->next;
        len--;
        free(local_head);
        if(len==0){
            tail=NULL;
            head=NULL;
        }

    }           //code 2
    void delete_from_end(node **head_addr){
        if(len==0){
            printf("INVALID SEQUENCE OF COMMANDS");
            exit(0);
        }
        node *local_head=*head_addr;
        while((local_head->next) != tail && (local_head->next) != NULL){
            local_head=local_head->next;
        }
        // printf("%p  %p\n",local_head,tail);
        free(tail);
        tail=local_head;

        local_head->next=NULL;
        len--;
        if(len==0){
            tail=NULL;
            head=NULL;
        }
    }                 //code 3
    void print_list(node **head_addr){
        
        node * local_head=*head_addr;
        if(NULL != local_head){
            while(NULL != local_head ){
                printf("%d ",(local_head->item));
                local_head=(local_head->next);

            }
        }else{
            printf("List is Empty");
            exit(0);
        }
    }
int main() {
    int code,value;
    int index;
    
    do{
        int res=scanf("%d",&code);
        if(res==-1){
            printf("INVALID SEQUENCE OF COMMANDS\n");
            break;
        }
        if(code == 0){
            scanf("%d",&value);
            insert_at_beginning(&head,value);
        }else if(code ==1 ){
            scanf("%d",&value);
            insert_at_end(&head,value);
        }else if(code==2){
            delete_from_beginning(&head);
        }else if(code==3){
            delete_from_end(&head);
        }else if(code==4){
            print_list(&head);
        }else if(code == 5){
            scanf("%d",&index);
            scanf("%d",&value);
            insert_before_index(index,value);
        }else if(code == 6){
            scanf("%d",&index);
            scanf("%d",&value);
            insert_after_index(index,value);
        }else if(code == 7){
            scanf("%d",&index);
            scanf("%d",&value);
            update_at_index(index,value);
        }else if(code == 8){
            scanf("%d",&index);
            scanf("%d",&value);
            update_before_index(index,value);
        }else if(code == 9){
            scanf("%d",&index);
            scanf("%d",&value);
            update_after_index(index,value);
        }else if(code == 10){
            scanf("%d",&index);
            pop_at_index(index);
        }else if(code==11){
            scanf("%d",&index);
            pop_before_index(index);
        }else if(code == 12){
            scanf("%d",&index);
            pop_after_index(index);
        }
        else{
            printf("INVALID SEQUENCE OF COMMANDS\n");
            scanf("%d",&value);
        }
        
    }while(4 != code);
    
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    return 0;
}
