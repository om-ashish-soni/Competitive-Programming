/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        return (!head || !head->next) ?
            (head):
            (
                (head->next->val == head->val)?
                (deleteDuplicates(head->next)):
                (head->next=deleteDuplicates(head->next),head)
            )
        ;
    }
};