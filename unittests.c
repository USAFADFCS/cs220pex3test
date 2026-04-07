/** test_linkedlist.c
 * ===========================================================
 * Unit tests for listAsLinkedList
 * ===========================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "listAsLinkedList.h"
#include "stackAsLinkedList.h"
#include "queueAsLinkedList.h"

// ===========================================================
// linkedListInit tests
// ===========================================================

int test_init_returns_non_null(void) {
    LinkedList* list = linkedListInit();
    if (list == NULL) return 1;
    if (list->head != NULL) return 1;
    if (list->tail != NULL) return 1;
    if (list->numberOfItems != 0) return 1;
    deleteLinkedList(list);
    return 0;
}

// ===========================================================
// createNode tests
// ===========================================================

int test_create_number_node(void) {
    Node* node = createNode(REAL_NUMBER, 3.14, '\0');
    if (node == NULL) return 1;
    if (fabs(node->number - 3.14) > 1e-9) return 1;
    if (node->dataType != REAL_NUMBER) return 1;
    if (node->next != NULL) return 1;
    free(node);
    return 0;
}

int test_create_operator_node(void) {
    Node* node = createNode(MATH_OPERATOR, 0.0, '+');
    if (node == NULL) return 1;
    if (node->operator != '+') return 1;
    if (node->dataType != MATH_OPERATOR) return 1;
    if (node->next != NULL) return 1;
    free(node);
    return 0;
}

// ===========================================================
// appendElementLinkedList tests
// ===========================================================

int test_append_to_empty_list(void) {
    LinkedList* list = linkedListInit();
    Node* node = createNode(REAL_NUMBER, 5.0, '\0');
    appendElementLinkedList(list, node);

    if (list->numberOfItems != 1) return 1;
    if (list->head != node) return 1;
    if (list->tail != node) return 1;
    if (node->next != NULL) return 1;
    deleteLinkedList(list);
    return 0;
}

int test_append_multiple_elements(void) {
    LinkedList* list = linkedListInit();
    Node* n1 = createNode(REAL_NUMBER, 1.0, '\0');
    Node* n2 = createNode(MATH_OPERATOR, 0.0, '+');
    Node* n3 = createNode(REAL_NUMBER, 2.0, '\0');

    appendElementLinkedList(list, n1);
    appendElementLinkedList(list, n2);
    appendElementLinkedList(list, n3);

    if (list->numberOfItems != 3) return 1;
    if (list->head != n1) return 1;
    if (list->tail != n3) return 1;
    if (n1->next != n2) return 1;
    if (n2->next != n3) return 1;
    if (n3->next != NULL) return 1;
    deleteLinkedList(list);
    return 0;
}

// ===========================================================
// lengthOfLinkedList tests
// ===========================================================

int test_length_empty_list(void) {
    LinkedList* list = linkedListInit();
    if (lengthOfLinkedList(list) != 0) return 1;
    deleteLinkedList(list);
    return 0;
}

int test_length_after_appends(void) {
    LinkedList* list = linkedListInit();
    for (int i = 0; i < 5; i++) {
        appendElementLinkedList(list, createNode(REAL_NUMBER, (double)i, '\0'));
    }
    if (lengthOfLinkedList(list) != 5) return 1;
    deleteLinkedList(list);
    return 0;
}

// ===========================================================
// getElementLinkedList tests
// ===========================================================

int test_get_first_element(void) {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 10.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 20.0, '\0'));

    Node* node = getElementLinkedList(list, 0);
    if (node == NULL) return 1;
    if (fabs(node->number - 10.0) > 1e-9) return 1;
    deleteLinkedList(list);
    return 0;
}

int test_get_last_element(void) {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 10.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 20.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 30.0, '\0'));

    Node* node = getElementLinkedList(list, 2);
    if (node == NULL) return 1;
    if (fabs(node->number - 30.0) > 1e-9) return 1;
    deleteLinkedList(list);
    return 0;
}

int test_get_middle_element(void) {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 10.0, '\0'));
    appendElementLinkedList(list, createNode(MATH_OPERATOR, 0.0, '*'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 30.0, '\0'));

    Node* node = getElementLinkedList(list, 1);
    if (node == NULL) return 1;
    if (node->operator != '*') return 1;
    if (node->dataType != MATH_OPERATOR) return 1;
    deleteLinkedList(list);
    return 0;
}

int test_get_invalid_position_negative(void) {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 1.0, '\0'));

    Node* node = getElementLinkedList(list, -1);
    if (node != NULL) return 1;
    deleteLinkedList(list);
    return 0;
}

int test_get_invalid_position_out_of_bounds(void) {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 1.0, '\0'));

    Node* node = getElementLinkedList(list, 5);
    if (node != NULL) return 1;
    deleteLinkedList(list);
    return 0;
}

int test_get_from_empty_list(void) {
    LinkedList* list = linkedListInit();
    Node* node = getElementLinkedList(list, 0);
    if (node != NULL) return 1;
    deleteLinkedList(list);
    return 0;
}

// ===========================================================
// deleteElementLinkedList tests
// ===========================================================

int test_delete_first_element(void) {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 10.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 20.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 30.0, '\0'));

    deleteElementLinkedList(list, 0);

    if (list->numberOfItems != 2) return 1;
    Node* first = getElementLinkedList(list, 0);
    if (first == NULL) return 1;
    if (fabs(first->number - 20.0) > 1e-9) return 1;
    deleteLinkedList(list);
    return 0;
}

int test_delete_last_element(void) {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 10.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 20.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 30.0, '\0'));

    deleteElementLinkedList(list, 2);

    if (list->numberOfItems != 2) return 1;
    if (list->tail == NULL) return 1;
    if (fabs(list->tail->number - 20.0) > 1e-9) return 1;
    deleteLinkedList(list);
    return 0;
}

int test_delete_middle_element(void) {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 10.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 20.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 30.0, '\0'));

    deleteElementLinkedList(list, 1);

    if (list->numberOfItems != 2) return 1;
    Node* second = getElementLinkedList(list, 1);
    if (second == NULL) return 1;
    if (fabs(second->number - 30.0) > 1e-9) return 1;
    deleteLinkedList(list);
    return 0;
}

int test_delete_only_element(void) {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 42.0, '\0'));

    deleteElementLinkedList(list, 0);

    if (list->numberOfItems != 0) return 1;
    if (list->head != NULL) return 1;
    if (list->tail != NULL) return 1;
    deleteLinkedList(list);
    return 0;
}

// ===========================================================
// insertElementLinkedList tests
// ===========================================================

int test_insert_at_beginning(void) {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 20.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 30.0, '\0'));

    Node* newNode = createNode(REAL_NUMBER, 10.0, '\0');
    insertElementLinkedList(list, 0, newNode);

    if (list->numberOfItems != 3) return 1;
    if (list->head != newNode) return 1;
    if (fabs(getElementLinkedList(list, 0)->number - 10.0) > 1e-9) return 1;
    if (fabs(getElementLinkedList(list, 1)->number - 20.0) > 1e-9) return 1;
    deleteLinkedList(list);
    return 0;
}

int test_insert_at_end(void) {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 10.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 20.0, '\0'));

    Node* newNode = createNode(REAL_NUMBER, 30.0, '\0');
    insertElementLinkedList(list, 2, newNode);

    if (list->numberOfItems != 3) return 1;
    if (list->tail != newNode) return 1;
    if (fabs(getElementLinkedList(list, 2)->number - 30.0) > 1e-9) return 1;
    deleteLinkedList(list);
    return 0;
}

int test_insert_in_middle(void) {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 10.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 30.0, '\0'));

    Node* newNode = createNode(MATH_OPERATOR, 0.0, '+');
    insertElementLinkedList(list, 1, newNode);

    if (list->numberOfItems != 3) return 1;
    Node* mid = getElementLinkedList(list, 1);
    if (mid == NULL) return 1;
    if (mid->operator != '+') return 1;
    deleteLinkedList(list);
    return 0;
}

int test_insert_into_empty_list(void) {
    LinkedList* list = linkedListInit();

    Node* newNode = createNode(REAL_NUMBER, 99.0, '\0');
    insertElementLinkedList(list, 0, newNode);

    if (list->numberOfItems != 1) return 1;
    if (list->head != newNode) return 1;
    if (list->tail != newNode) return 1;
    deleteLinkedList(list);
    return 0;
}

// ===========================================================
// changeElementLinkedList tests
// ===========================================================

int test_change_first_element(void) {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 10.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 20.0, '\0'));

    Node* replacement = createNode(REAL_NUMBER, 99.0, '\0');
    changeElementLinkedList(list, 0, replacement);

    if (list->numberOfItems != 2) return 1;
    if (fabs(getElementLinkedList(list, 0)->number - 99.0) > 1e-9) return 1;
    if (fabs(getElementLinkedList(list, 1)->number - 20.0) > 1e-9) return 1;
    deleteLinkedList(list);
    return 0;
}

int test_change_last_element(void) {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 10.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 20.0, '\0'));

    Node* replacement = createNode(MATH_OPERATOR, 0.0, '-');
    changeElementLinkedList(list, 1, replacement);

    if (list->numberOfItems != 2) return 1;
    Node* last = getElementLinkedList(list, 1);
    if (last->operator != '-') return 1;
    if (list->tail != replacement) return 1;
    deleteLinkedList(list);
    return 0;
}

int test_change_middle_element(void) {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 1.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 2.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 3.0, '\0'));

    Node* replacement = createNode(REAL_NUMBER, 42.0, '\0');
    changeElementLinkedList(list, 1, replacement);

    if (list->numberOfItems != 3) return 1;
    if (fabs(getElementLinkedList(list, 1)->number - 42.0) > 1e-9) return 1;
    if (fabs(getElementLinkedList(list, 0)->number - 1.0) > 1e-9) return 1;
    if (fabs(getElementLinkedList(list, 2)->number - 3.0) > 1e-9) return 1;
    deleteLinkedList(list);
    return 0;
}

// ===========================================================
// copyElement tests
// ===========================================================

int test_copy_number_node(void) {
    Node* original = createNode(REAL_NUMBER, 7.5, '\0');
    Node* copy = copyElement(original);

    if (copy == NULL) return 1;
    if (copy == original) return 1;
    if (fabs(copy->number - 7.5) > 1e-9) return 1;
    if (copy->dataType != REAL_NUMBER) return 1;
    if (copy->next != NULL) return 1;

    free(original);
    free(copy);
    return 0;
}

int test_copy_operator_node(void) {
    Node* original = createNode(MATH_OPERATOR, 0.0, '/');
    original->next = (Node*)0xDEADBEEF;
    Node* copy = copyElement(original);

    if (copy == NULL) return 1;
    if (copy->operator != '/') return 1;
    if (copy->dataType != MATH_OPERATOR) return 1;
    if (copy->next != NULL) return 1;

    original->next = NULL;
    free(original);
    free(copy);
    return 0;
}

int test_copy_null_node(void) {
    Node* copy = copyElement(NULL);
    if (copy != NULL) return 1;
    return 0;
}

// ===========================================================
// deleteLinkedList tests
// ===========================================================

int test_delete_empty_list(void) {
    LinkedList* list = linkedListInit();
    deleteLinkedList(list);
    return 0;
}

int test_delete_populated_list(void) {
    LinkedList* list = linkedListInit();
    for (int i = 0; i < 10; i++) {
        appendElementLinkedList(list, createNode(REAL_NUMBER, (double)i, '\0'));
    }
    deleteLinkedList(list);
    return 0;
}

// ===========================================================
// Integration / edge case tests
// ===========================================================

int test_mixed_node_types(void) {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 3.0, '\0'));
    appendElementLinkedList(list, createNode(MATH_OPERATOR, 0.0, '+'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 4.0, '\0'));
    appendElementLinkedList(list, createNode(MATH_OPERATOR, 0.0, '*'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 2.0, '\0'));

    if (lengthOfLinkedList(list) != 5) return 1;
    if (getElementLinkedList(list, 0)->dataType != REAL_NUMBER) return 1;
    if (getElementLinkedList(list, 1)->dataType != MATH_OPERATOR) return 1;
    if (getElementLinkedList(list, 2)->dataType != REAL_NUMBER) return 1;
    if (getElementLinkedList(list, 3)->dataType != MATH_OPERATOR) return 1;
    if (getElementLinkedList(list, 4)->dataType != REAL_NUMBER) return 1;
    deleteLinkedList(list);
    return 0;
}

int test_insert_then_delete_preserves_structure(void) {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 1.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 3.0, '\0'));

    insertElementLinkedList(list, 1, createNode(REAL_NUMBER, 2.0, '\0'));
    if (list->numberOfItems != 3) return 1;
    if (fabs(getElementLinkedList(list, 1)->number - 2.0) > 1e-9) return 1;

    deleteElementLinkedList(list, 1);
    if (list->numberOfItems != 2) return 1;
    if (fabs(getElementLinkedList(list, 0)->number - 1.0) > 1e-9) return 1;
    if (fabs(getElementLinkedList(list, 1)->number - 3.0) > 1e-9) return 1;
    deleteLinkedList(list);
    return 0;
}

int test_sequential_deletes_from_front(void) {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 1.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 2.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 3.0, '\0'));

    deleteElementLinkedList(list, 0);
    deleteElementLinkedList(list, 0);
    deleteElementLinkedList(list, 0);

    if (list->numberOfItems != 0) return 1;
    if (list->head != NULL) return 1;
    if (list->tail != NULL) return 1;
    deleteLinkedList(list);
    return 0;
}

// ===========================================================
// Stack tests
// ===========================================================

int test_stack_init(void) {
    StackAsLinkedList* stack = stackInit();
    if (stack == NULL) return 1;
    if (stack->numberOfItems != 0) return 1;
    deleteStack(stack);
    return 0;
}

int test_stack_push_single(void) {
    StackAsLinkedList* stack = stackInit();
    stackPush(stack, createNode(REAL_NUMBER, 10.0, '\0'));

    if (stackSize(stack) != 1) return 1;
    if (stackIsEmpty(stack)) return 1;
    deleteStack(stack);
    return 0;
}

int test_stack_push_multiple(void) {
    StackAsLinkedList* stack = stackInit();
    stackPush(stack, createNode(REAL_NUMBER, 1.0, '\0'));
    stackPush(stack, createNode(REAL_NUMBER, 2.0, '\0'));
    stackPush(stack, createNode(REAL_NUMBER, 3.0, '\0'));

    if (stackSize(stack) != 3) return 1;
    deleteStack(stack);
    return 0;
}

int test_stack_pop_returns_top(void) {
    StackAsLinkedList* stack = stackInit();
    stackPush(stack, createNode(REAL_NUMBER, 1.0, '\0'));
    stackPush(stack, createNode(REAL_NUMBER, 2.0, '\0'));
    stackPush(stack, createNode(REAL_NUMBER, 3.0, '\0'));

    Node* popped = stackPop(stack);
    if (popped == NULL) return 1;
    if (fabs(popped->number - 3.0) > 1e-9) return 1;
    if (stackSize(stack) != 2) return 1;
    free(popped);
    deleteStack(stack);
    return 0;
}

int test_stack_pop_lifo_order(void) {
    StackAsLinkedList* stack = stackInit();
    stackPush(stack, createNode(REAL_NUMBER, 10.0, '\0'));
    stackPush(stack, createNode(REAL_NUMBER, 20.0, '\0'));
    stackPush(stack, createNode(REAL_NUMBER, 30.0, '\0'));

    Node* n1 = stackPop(stack);
    Node* n2 = stackPop(stack);
    Node* n3 = stackPop(stack);

    if (fabs(n1->number - 30.0) > 1e-9) return 1;
    if (fabs(n2->number - 20.0) > 1e-9) return 1;
    if (fabs(n3->number - 10.0) > 1e-9) return 1;

    free(n1);
    free(n2);
    free(n3);
    deleteStack(stack);
    return 0;
}

int test_stack_pop_empty(void) {
    StackAsLinkedList* stack = stackInit();
    Node* popped = stackPop(stack);
    if (popped != NULL) return 1;
    deleteStack(stack);
    return 0;
}

int test_stack_peek(void) {
    StackAsLinkedList* stack = stackInit();
    stackPush(stack, createNode(REAL_NUMBER, 5.0, '\0'));
    stackPush(stack, createNode(REAL_NUMBER, 15.0, '\0'));

    Node* top = stackPeek(stack);
    if (top == NULL) return 1;
    if (fabs(top->number - 15.0) > 1e-9) return 1;
    if (stackSize(stack) != 2) return 1;  // peek should not remove
    deleteStack(stack);
    return 0;
}

int test_stack_peek_empty(void) {
    StackAsLinkedList* stack = stackInit();
    Node* top = stackPeek(stack);
    if (top != NULL) return 1;
    deleteStack(stack);
    return 0;
}

int test_stack_is_empty_true(void) {
    StackAsLinkedList* stack = stackInit();
    if (!stackIsEmpty(stack)) return 1;
    deleteStack(stack);
    return 0;
}

int test_stack_is_empty_false(void) {
    StackAsLinkedList* stack = stackInit();
    stackPush(stack, createNode(REAL_NUMBER, 1.0, '\0'));
    if (stackIsEmpty(stack)) return 1;
    deleteStack(stack);
    return 0;
}

int test_stack_is_full(void) {
    StackAsLinkedList* stack = stackInit();
    if (stackIsFull(stack)) return 1;  // should always be false
    stackPush(stack, createNode(REAL_NUMBER, 1.0, '\0'));
    if (stackIsFull(stack)) return 1;
    deleteStack(stack);
    return 0;
}

int test_stack_size(void) {
    StackAsLinkedList* stack = stackInit();
    if (stackSize(stack) != 0) return 1;
    stackPush(stack, createNode(REAL_NUMBER, 1.0, '\0'));
    if (stackSize(stack) != 1) return 1;
    stackPush(stack, createNode(REAL_NUMBER, 2.0, '\0'));
    if (stackSize(stack) != 2) return 1;
    Node* p = stackPop(stack);
    free(p);
    if (stackSize(stack) != 1) return 1;
    deleteStack(stack);
    return 0;
}

int test_stack_mixed_types(void) {
    StackAsLinkedList* stack = stackInit();
    stackPush(stack, createNode(REAL_NUMBER, 3.0, '\0'));
    stackPush(stack, createNode(MATH_OPERATOR, 0.0, '+'));
    stackPush(stack, createNode(REAL_NUMBER, 4.0, '\0'));

    Node* top = stackPop(stack);
    if (top == NULL) return 1;
    if (top->dataType != REAL_NUMBER) return 1;
    if (fabs(top->number - 4.0) > 1e-9) return 1;
    free(top);

    top = stackPop(stack);
    if (top == NULL) return 1;
    if (top->dataType != MATH_OPERATOR) return 1;
    if (top->operator != '+') return 1;
    free(top);

    deleteStack(stack);
    return 0;
}

// ===========================================================
// Queue tests
// ===========================================================

int test_queue_init(void) {
    QueueAsLinkedList* queue = queueInit();
    if (queue == NULL) return 1;
    if (queue->numberOfItems != 0) return 1;
    deleteQueue(queue);
    return 0;
}

int test_queue_enqueue_single(void) {
    QueueAsLinkedList* queue = queueInit();
    queueEnqueue(queue, createNode(REAL_NUMBER, 10.0, '\0'));

    if (queueSize(queue) != 1) return 1;
    if (queueIsEmpty(queue)) return 1;
    deleteQueue(queue);
    return 0;
}

int test_queue_enqueue_multiple(void) {
    QueueAsLinkedList* queue = queueInit();
    queueEnqueue(queue, createNode(REAL_NUMBER, 1.0, '\0'));
    queueEnqueue(queue, createNode(REAL_NUMBER, 2.0, '\0'));
    queueEnqueue(queue, createNode(REAL_NUMBER, 3.0, '\0'));

    if (queueSize(queue) != 3) return 1;
    deleteQueue(queue);
    return 0;
}

int test_queue_dequeue_returns_front(void) {
    QueueAsLinkedList* queue = queueInit();
    queueEnqueue(queue, createNode(REAL_NUMBER, 1.0, '\0'));
    queueEnqueue(queue, createNode(REAL_NUMBER, 2.0, '\0'));
    queueEnqueue(queue, createNode(REAL_NUMBER, 3.0, '\0'));

    Node* dequeued = queueDequeue(queue);
    if (dequeued == NULL) return 1;
    if (fabs(dequeued->number - 1.0) > 1e-9) return 1;
    if (queueSize(queue) != 2) return 1;
    free(dequeued);
    deleteQueue(queue);
    return 0;
}

int test_queue_dequeue_fifo_order(void) {
    QueueAsLinkedList* queue = queueInit();
    queueEnqueue(queue, createNode(REAL_NUMBER, 10.0, '\0'));
    queueEnqueue(queue, createNode(REAL_NUMBER, 20.0, '\0'));
    queueEnqueue(queue, createNode(REAL_NUMBER, 30.0, '\0'));

    Node* n1 = queueDequeue(queue);
    Node* n2 = queueDequeue(queue);
    Node* n3 = queueDequeue(queue);

    if (fabs(n1->number - 10.0) > 1e-9) return 1;
    if (fabs(n2->number - 20.0) > 1e-9) return 1;
    if (fabs(n3->number - 30.0) > 1e-9) return 1;

    free(n1);
    free(n2);
    free(n3);
    deleteQueue(queue);
    return 0;
}

int test_queue_dequeue_empty(void) {
    QueueAsLinkedList* queue = queueInit();
    Node* dequeued = queueDequeue(queue);
    if (dequeued != NULL) return 1;
    deleteQueue(queue);
    return 0;
}

int test_queue_peek(void) {
    QueueAsLinkedList* queue = queueInit();
    queueEnqueue(queue, createNode(REAL_NUMBER, 5.0, '\0'));
    queueEnqueue(queue, createNode(REAL_NUMBER, 15.0, '\0'));

    Node* front = queuePeek(queue);
    if (front == NULL) return 1;
    if (fabs(front->number - 5.0) > 1e-9) return 1;
    if (queueSize(queue) != 2) return 1;  // peek should not remove
    deleteQueue(queue);
    return 0;
}

int test_queue_peek_empty(void) {
    QueueAsLinkedList* queue = queueInit();
    Node* front = queuePeek(queue);
    if (front != NULL) return 1;
    deleteQueue(queue);
    return 0;
}

int test_queue_is_empty_true(void) {
    QueueAsLinkedList* queue = queueInit();
    if (!queueIsEmpty(queue)) return 1;
    deleteQueue(queue);
    return 0;
}

int test_queue_is_empty_false(void) {
    QueueAsLinkedList* queue = queueInit();
    queueEnqueue(queue, createNode(REAL_NUMBER, 1.0, '\0'));
    if (queueIsEmpty(queue)) return 1;
    deleteQueue(queue);
    return 0;
}

int test_queue_is_full(void) {
    QueueAsLinkedList* queue = queueInit();
    if (queueIsFull(queue)) return 1;  // should always be false
    queueEnqueue(queue, createNode(REAL_NUMBER, 1.0, '\0'));
    if (queueIsFull(queue)) return 1;
    deleteQueue(queue);
    return 0;
}

int test_queue_size(void) {
    QueueAsLinkedList* queue = queueInit();
    if (queueSize(queue) != 0) return 1;
    queueEnqueue(queue, createNode(REAL_NUMBER, 1.0, '\0'));
    if (queueSize(queue) != 1) return 1;
    queueEnqueue(queue, createNode(REAL_NUMBER, 2.0, '\0'));
    if (queueSize(queue) != 2) return 1;
    Node* d = queueDequeue(queue);
    free(d);
    if (queueSize(queue) != 1) return 1;
    deleteQueue(queue);
    return 0;
}

int test_queue_mixed_types(void) {
    QueueAsLinkedList* queue = queueInit();
    queueEnqueue(queue, createNode(REAL_NUMBER, 3.0, '\0'));
    queueEnqueue(queue, createNode(MATH_OPERATOR, 0.0, '+'));
    queueEnqueue(queue, createNode(REAL_NUMBER, 4.0, '\0'));

    Node* front = queueDequeue(queue);
    if (front == NULL) return 1;
    if (front->dataType != REAL_NUMBER) return 1;
    if (fabs(front->number - 3.0) > 1e-9) return 1;
    free(front);

    front = queueDequeue(queue);
    if (front == NULL) return 1;
    if (front->dataType != MATH_OPERATOR) return 1;
    if (front->operator != '+') return 1;
    free(front);

    deleteQueue(queue);
    return 0;
}

// ===========================================================
// Main test runner
// ===========================================================

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <test_name>\n", argv[0]);
        return 1;
    }

    /* linkedListInit */
    if (strcmp(argv[1], "init1") == 0) return test_init_returns_non_null();

    /* createNode */
    if (strcmp(argv[1], "createNode1") == 0) return test_create_number_node();
    if (strcmp(argv[1], "createNode2") == 0) return test_create_operator_node();

    /* appendElementLinkedList */
    if (strcmp(argv[1], "append1") == 0) return test_append_to_empty_list();
    if (strcmp(argv[1], "append2") == 0) return test_append_multiple_elements();

    /* lengthOfLinkedList */
    if (strcmp(argv[1], "length1") == 0) return test_length_empty_list();
    if (strcmp(argv[1], "length2") == 0) return test_length_after_appends();

    /* getElementLinkedList */
    if (strcmp(argv[1], "get1") == 0) return test_get_first_element();
    if (strcmp(argv[1], "get2") == 0) return test_get_last_element();
    if (strcmp(argv[1], "get3") == 0) return test_get_middle_element();
    if (strcmp(argv[1], "get4") == 0) return test_get_invalid_position_negative();
    if (strcmp(argv[1], "get5") == 0) return test_get_invalid_position_out_of_bounds();
    if (strcmp(argv[1], "get6") == 0) return test_get_from_empty_list();

    /* deleteElementLinkedList */
    if (strcmp(argv[1], "delete1") == 0) return test_delete_first_element();
    if (strcmp(argv[1], "delete2") == 0) return test_delete_last_element();
    if (strcmp(argv[1], "delete3") == 0) return test_delete_middle_element();
    if (strcmp(argv[1], "delete4") == 0) return test_delete_only_element();

    /* insertElementLinkedList */
    if (strcmp(argv[1], "insert1") == 0) return test_insert_at_beginning();
    if (strcmp(argv[1], "insert2") == 0) return test_insert_at_end();
    if (strcmp(argv[1], "insert3") == 0) return test_insert_in_middle();
    if (strcmp(argv[1], "insert4") == 0) return test_insert_into_empty_list();

    /* changeElementLinkedList */
    if (strcmp(argv[1], "change1") == 0) return test_change_first_element();
    if (strcmp(argv[1], "change2") == 0) return test_change_last_element();
    if (strcmp(argv[1], "change3") == 0) return test_change_middle_element();

    /* copyElement */
    if (strcmp(argv[1], "copy1") == 0) return test_copy_number_node();
    if (strcmp(argv[1], "copy2") == 0) return test_copy_operator_node();
    if (strcmp(argv[1], "copy3") == 0) return test_copy_null_node();

    /* deleteLinkedList */
    if (strcmp(argv[1], "deleteList1") == 0) return test_delete_empty_list();
    if (strcmp(argv[1], "deleteList2") == 0) return test_delete_populated_list();

    /* Integration tests */
    if (strcmp(argv[1], "mixed1") == 0) return test_mixed_node_types();
    if (strcmp(argv[1], "integration1") == 0) return test_insert_then_delete_preserves_structure();
    if (strcmp(argv[1], "integration2") == 0) return test_sequential_deletes_from_front();

    /* stackInit */
    if (strcmp(argv[1], "stackInit1") == 0) return test_stack_init();

    /* stackPush */
    if (strcmp(argv[1], "stackPush1") == 0) return test_stack_push_single();
    if (strcmp(argv[1], "stackPush2") == 0) return test_stack_push_multiple();

    /* stackPop */
    if (strcmp(argv[1], "stackPop1") == 0) return test_stack_pop_returns_top();
    if (strcmp(argv[1], "stackPop2") == 0) return test_stack_pop_lifo_order();
    if (strcmp(argv[1], "stackPop3") == 0) return test_stack_pop_empty();

    /* stackPeek */
    if (strcmp(argv[1], "stackPeek1") == 0) return test_stack_peek();
    if (strcmp(argv[1], "stackPeek2") == 0) return test_stack_peek_empty();

    /* stackIsEmpty */
    if (strcmp(argv[1], "stackIsEmpty1") == 0) return test_stack_is_empty_true();
    if (strcmp(argv[1], "stackIsEmpty2") == 0) return test_stack_is_empty_false();

    /* stackIsFull */
    if (strcmp(argv[1], "stackIsFull1") == 0) return test_stack_is_full();

    /* stackSize */
    if (strcmp(argv[1], "stackSize1") == 0) return test_stack_size();

    /* stackMixed */
    if (strcmp(argv[1], "stackMixed1") == 0) return test_stack_mixed_types();

    /* queueInit */
    if (strcmp(argv[1], "queueInit1") == 0) return test_queue_init();

    /* queueEnqueue */
    if (strcmp(argv[1], "queueEnqueue1") == 0) return test_queue_enqueue_single();
    if (strcmp(argv[1], "queueEnqueue2") == 0) return test_queue_enqueue_multiple();

    /* queueDequeue */
    if (strcmp(argv[1], "queueDequeue1") == 0) return test_queue_dequeue_returns_front();
    if (strcmp(argv[1], "queueDequeue2") == 0) return test_queue_dequeue_fifo_order();
    if (strcmp(argv[1], "queueDequeue3") == 0) return test_queue_dequeue_empty();

    /* queuePeek */
    if (strcmp(argv[1], "queuePeek1") == 0) return test_queue_peek();
    if (strcmp(argv[1], "queuePeek2") == 0) return test_queue_peek_empty();

    /* queueIsEmpty */
    if (strcmp(argv[1], "queueIsEmpty1") == 0) return test_queue_is_empty_true();
    if (strcmp(argv[1], "queueIsEmpty2") == 0) return test_queue_is_empty_false();

    /* queueIsFull */
    if (strcmp(argv[1], "queueIsFull1") == 0) return test_queue_is_full();

    /* queueSize */
    if (strcmp(argv[1], "queueSize1") == 0) return test_queue_size();

    /* queueMixed */
    if (strcmp(argv[1], "queueMixed1") == 0) return test_queue_mixed_types();

    printf("Unknown test: %s\n", argv[1]);
    return 1;
}
