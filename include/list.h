#ifndef LIST_H
#define LIST_H

#include "common.h"

typedef struct RenderListNode RenderListNode;

typedef struct DoublyLinkedNode {
    struct DoublyLinkedNode *next;
    struct DoublyLinkedNode *previous;
} DoublyLinkedNode;
void RenderDrawFiveLinkedLists(void);
void ListInsertBefore(RenderListNode **head, RenderListNode *node,
                      RenderListNode *before);
void ListRemoveNode(RenderListNode **head, RenderListNode *target);
void ListPushFront(u8 *node, u8 **head, u8 **tail);
void ListRemoveNodeWithTail(RenderListNode *node, RenderListNode **head,
                            RenderListNode **tail);
void ListPushFrontDoublyLinked(DoublyLinkedNode *node, DoublyLinkedNode **last,
                               DoublyLinkedNode **first);
void ListDispatchCallbacks(u8 *owner);

#endif /* LIST_H */
