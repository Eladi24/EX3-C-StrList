#include "StrList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct _node
{
    char *_data;
    struct _node *_next;
} Node;

struct _StrList
{
    Node *_head;
    size_t _size
};

Node *Node_alloc(char *data, Node *next)
{
    Node *p = (Node *)malloc(sizeof(Node));

    if (p == NULL)
    {
        // Failed to acllocate memory
        return NULL;
    }

    p->_data = (char *)malloc(strlen(data) + 1);

    if (p->_data == NULL)
    {
        free(p);
        return NULL;
    }

    strcpy(p->_data, data);
    p->_next = next;
    return p;
}

void Node_free(Node *node)
{
    if (node == NULL)
        return;
    free(node->_data);
    free(node);
}

StrList *StrList_alloc()
{
    StrList *p = (StrList *)malloc(sizeof(StrList));

    if (p == NULL) {
        return NULL;
    }

    p->_head = NULL;
    p->_size = 0;
    return p;
}

void StrList_free(StrList *StrList)
{
    if (StrList == NULL)
        return;
    Node *p1 = StrList->_head;
    Node *p2;
    while (p1)
    {
        p2 = p1;
        p1 = p1->_next;
        Node_free(p2);
    }
    free(StrList);
}

size_t StrList_size(const StrList *StrList)
{
    return StrList->_size;
}

void StrList_insertLast(StrList *StrList, const char *data)
{
    Node *new_node = Node_alloc(data, NULL);
    Node *last = StrList->_head;

    if (StrList->_head == NULL)
    {
        StrList->_head = new_node;
        StrList->_size++;
        return;
    }

    while (last->_next != NULL)
    {
        last = last->_next;
    }

    last->_next = new_node;
    StrList->_size++;
}

Node *StrList_findAt(StrList *StrList, int index)
{
    if (index >= StrList->_size)
        return NULL;

    Node *current = StrList->_head;

    int count = 0;

    while (count < index)
    {
        current = current->_next;
        count++;
    }

    return current;
}

void StrList_insertAt(StrList *StrList, const char *data, int index)
{
    if (index > StrList->_size)
        return;

    int count = 0;
    Node *prev = StrList->_head;

    if (index == 0)
    {
        Node *new_node = Node_alloc(data, StrList->_head);
        StrList->_head = new_node;
        StrList->_size++;
        return;
    }

    while (count < index - 1)
    {
        prev = prev->_next;
        count++;
    }

    Node *new_node = Node_alloc(data, prev->_next);
    prev->_next = new_node;
    StrList->_size++;
}

char *StrList_firstData(const StrList *StrList)
{
    return StrList->_head->_data;
}

void StrList_print(const StrList *StrList)
{
    const Node *p = StrList->_head;
    while (p)
    {
        printf("(%s)->", p->_data);
        p = p->_next;
    }
    printf("|| size:%zu\n", StrList->_size);
}

void StrList_printAt(const StrList *Strlist, int index)
{
    Node *node = StrList_findAt(Strlist, index);
    if (node != NULL)
    {
        printf("%s\n", node->_data);
    }
    else
    {
        printf("Illigal index\n");
    }
}

int StrList_printLen(const StrList *Strlist)
{
    int len = 0;
    Node *node = Strlist->_head;
    while (node != NULL)
    {
        len += strlen(node->_data);
        node = node->_next;
    }

    return len;
}

int StrList_count(StrList *StrList, const char *data)
{
    int count = 0;
    Node *node = StrList->_head;
    while (node != NULL)
    {
        if (strcmp(data, node->_data) == 0)
        {
            count++;
        }
        node = node->_next;
    }

    return count;
}

void StrList_remove(StrList *StrList, const char *data)
{
    int count = 0;
    Node *node = StrList->_head;
    Node *prev = NULL;
    while (node != NULL)
    {
        if (strcmp(node->_data, data) == 0)
        {
            if (prev == NULL)
            {
                StrList->_head = node->_next;
            }
            else
            {
                prev->_next = node->_next;
            }

            Node *temp = node;
            node = node->_next;
            Node_free(temp);
            StrList->_size--;
        }
        else
        {
            prev = node;
            node = node->_next;
        }
    }
}

void StrList_removeAt(StrList *StrList, int index)
{
    Node *node = StrList->_head;
    Node *prev = NULL;
    if (index == 0)
    {
        StrList->_head = node->_next;
    }
    else
    {
        node = StrList_findAt(StrList, index);
        prev = StrList_findAt(StrList, index - 1);
        prev->_next = node->_next;
    }

    Node_free(node);
    StrList->_size--;
}

int StrList_isEqual(const StrList *StrList1, const StrList *StrList2)
{
    if (StrList1->_size != StrList2->_size)
    {
        return 0;
    }
    else
    {
        Node *node_1 = StrList1->_head;
        Node *node_2 = StrList2->_head;

        while (node_1 != NULL)
        {
            if (strcmp(node_1->_data, node_2->_data) != 0)
            {
                return 0;
            }
            else
            {
                node_1 = node_1->_next;
                node_2 = node_2->_next;
            }
        }
    }

    return 1;
}

StrList *StrList_clone(const StrList *strList)
{
    StrList *cloned = StrList_alloc();
    const Node *origin = strList->_head;

    while (origin != NULL)
    {
        StrList_insertLast(cloned, origin->_data);
        origin = origin->_next;
    }

    return cloned;
}

void StrList_reverse(StrList *StrList)
{
    Node *prev = NULL;
    Node *current = StrList->_head;
    Node *next = NULL;

    while (current != NULL)
    {
        next = current->_next;
        current->_next = prev;
        prev = current;
        current = next;
    }

    StrList->_head = prev;
}


Node* SortedMerge(Node* a, Node* b) {
    Node* result = NULL;
    
    if (a == NULL) {
        return (b);
    } else if (b == NULL)
    {
        return(a);
    }
    
    if (strcmp(a->_data, b->_data) <= 0)
    {
        result = a;
        result->_next = SortedMerge(a->_next, b);
    } else {
        result = b;
        result->_next = SortedMerge(a,  b->_next);
    }

    return (result);
}

/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back
   halves, and return the two lists using the reference
   parameters. If the length is odd, the extra node should
   go in the front list. Uses the fast/slow pointer
   strategy. */

void FrontBackSplit(Node* source, Node** frontRef, Node** backRef) {
    Node* fast;
    Node* slow;
    slow = source;
    fast = source->_next;

    while (fast != NULL) {
        fast = fast ->_next;
        if (fast != NULL)
        {
            slow = slow->_next;
            fast = fast->_next;
        }
    }

    *frontRef = source;
    *backRef = slow->_next;
    slow->_next = NULL;
}

void MergeSort(Node** headRef) {
    Node* head = *headRef;
    Node* a;
    Node* b;

    if ((head == NULL) || head->_next == NULL)
    {
        return;
    }

    FrontBackSplit(head, &a, &b);
    StrList_sort(&a);
    StrList_sort(&b);
    *headRef = SortedMerge(a, b);
}

void StrList_sort(StrList* StrList) {
    MergeSort(&(StrList->_head));
}

int StrList_isSorted(StrList* StrList) {
    if (StrList == NULL)
    {
        return 1;
    }
    
    Node* current = StrList->_head;

    while (current->_next != NULL)
    {
        if (strcmp(current ->_data, current->_next->_data) > 0)
        {
            return 0;
        }
        current = current ->_next;
        
    }
    
    return 1;
}

void StrList_Scan(char** data) {
    int c;
    size_t len = 0;
    // Read characters one by one
    while ((c = getchar()) != '\n' && c != EOF)
    {
        // If the character is a whitespace, break the loop
        if (isspace(c))
        {
            break;
        }
        
        *data = realloc(*data, len + 2);
        if (*data == NULL)
        {
            return;
        }
        // Append the character to data
        (*data)[len++] = c;
    }
    (*data)[len] = '\0'; 
}
