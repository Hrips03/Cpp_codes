/*
Detect a cycle in a linked list. Note that the head pointer may be 'NULL' if the list is empty.

A Node is defined as: 
    struct Node {
        int data;
        struct Node* next;
    }
*/
#include <bits/stdc++.h>
using namespace std;

struct Node {
        int data;
        struct Node* next;
};

bool has_cycle(Node* head) {
    if (head == NULL || head->next == NULL) 
        return 0;

    Node* temp1 = head;
    Node* temp2 = head->next;

    while (temp2 != NULL && temp2->next != NULL) { 
        if (temp1 == temp2) 
            return 1;
        temp1 = temp1->next;
        temp2 = temp2->next->next; 
    }

    return 0;
}