/** instructor_tests.c
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

    printf("Unknown test: %s\n", argv[1]);
    return 1;
}
