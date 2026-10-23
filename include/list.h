#ifndef LIST_H
#define LIST_H

struct TrackSection;

#include "common.h"
#include "track.h"

typedef struct DoublyLinkedNode {
    struct DoublyLinkedNode *next;
    struct DoublyLinkedNode *previous;
} DoublyLinkedNode;
void RenderDrawFiveLinkedLists(void);
void ListInsertBefore(Face **head, Face *node, Face *before);
void ListRemoveNode(Face **head, Face *target);
void ListPushFront(u8 *node, u8 **head, u8 **tail);
void ListRemoveNodeWithTail(Face *node, Face **head, Face **tail);
void ListPushFrontDoublyLinked(DoublyLinkedNode *node, DoublyLinkedNode **last,
                               DoublyLinkedNode **first);
void ListDispatchCallbacks(struct TrackSection *owner);

#endif /* LIST_H */
