/** test_linkedlist.c
 * ===========================================================
 * Unit tests for listAsLinkedList
 * ===========================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "listAsLinkedList.h"

// ---- Helpers ----
static int tests_passed = 0;
static int tests_failed = 0;

#define RUN_TEST(test_func) do { \
    printf("  Running %-50s", #test_func "..."); \
    test_func(); \
    tests_passed++; \
    printf("PASSED\n"); \
} while(0)

#define ASSERT_EQ_INT(expected, actual) do { \
    if ((expected) != (actual)) { \
        printf("FAILED\n    %s:%d: expected %d, got %d\n", __FILE__, __LINE__, (expected), (actual)); \
        tests_failed++; \
        return; \
    } \
} while(0)

#define ASSERT_EQ_DOUBLE(expected, actual) do { \
    if (fabs((expected) - (actual)) > 1e-9) { \
        printf("FAILED\n    %s:%d: expected %f, got %f\n", __FILE__, __LINE__, (expected), (actual)); \
        tests_failed++; \
        return; \
    } \
} while(0)

#define ASSERT_EQ_CHAR(expected, actual) do { \
    if ((expected) != (actual)) { \
        printf("FAILED\n    %s:%d: expected '%c', got '%c'\n", __FILE__, __LINE__, (expected), (actual)); \
        tests_failed++; \
        return; \
    } \
} while(0)

#define ASSERT_TRUE(cond) do { \
    if (!(cond)) { \
        printf("FAILED\n    %s:%d: condition false: %s\n", __FILE__, __LINE__, #cond); \
        tests_failed++; \
        return; \
    } \
} while(0)

#define ASSERT_NULL(ptr) do { \
    if ((ptr) != NULL) { \
        printf("FAILED\n    %s:%d: expected NULL\n", __FILE__, __LINE__); \
        tests_failed++; \
        return; \
    } \
} while(0)

#define ASSERT_NOT_NULL(ptr) do { \
    if ((ptr) == NULL) { \
        printf("FAILED\n    %s:%d: expected non-NULL\n", __FILE__, __LINE__); \
        tests_failed++; \
        return; \
    } \
} while(0)

// ===========================================================
// linkedListInit tests
// ===========================================================

void test_init_returns_non_null() {
    LinkedList* list = linkedListInit();
    ASSERT_NOT_NULL(list);
    ASSERT_NULL(list->head);
    ASSERT_NULL(list->tail);
    ASSERT_EQ_INT(0, list->numberOfItems);
    deleteLinkedList(list);
}

// ===========================================================
// createNode tests
// ===========================================================

void test_create_number_node() {
    Node* node = createNode(REAL_NUMBER, 3.14, '\0');
    ASSERT_NOT_NULL(node);
    ASSERT_EQ_DOUBLE(3.14, node->number);
    ASSERT_TRUE(node->dataType == REAL_NUMBER);
    ASSERT_NULL(node->next);
    free(node);
}

void test_create_operator_node() {
    Node* node = createNode(MATH_OPERATOR, 0.0, '+');
    ASSERT_NOT_NULL(node);
    ASSERT_EQ_CHAR('+', node->operator);
    ASSERT_TRUE(node->dataType == MATH_OPERATOR);
    ASSERT_NULL(node->next);
    free(node);
}

// ===========================================================
// appendElementLinkedList tests
// ===========================================================

void test_append_to_empty_list() {
    LinkedList* list = linkedListInit();
    Node* node = createNode(REAL_NUMBER, 5.0, '\0');
    appendElementLinkedList(list, node);

    ASSERT_EQ_INT(1, list->numberOfItems);
    ASSERT_TRUE(list->head == node);
    ASSERT_TRUE(list->tail == node);
    ASSERT_NULL(node->next);
    deleteLinkedList(list);
}

void test_append_multiple_elements() {
    LinkedList* list = linkedListInit();
    Node* n1 = createNode(REAL_NUMBER, 1.0, '\0');
    Node* n2 = createNode(MATH_OPERATOR, 0.0, '+');
    Node* n3 = createNode(REAL_NUMBER, 2.0, '\0');

    appendElementLinkedList(list, n1);
    appendElementLinkedList(list, n2);
    appendElementLinkedList(list, n3);

    ASSERT_EQ_INT(3, list->numberOfItems);
    ASSERT_TRUE(list->head == n1);
    ASSERT_TRUE(list->tail == n3);
    ASSERT_TRUE(n1->next == n2);
    ASSERT_TRUE(n2->next == n3);
    ASSERT_NULL(n3->next);
    deleteLinkedList(list);
}

// ===========================================================
// lengthOfLinkedList tests
// ===========================================================

void test_length_empty_list() {
    LinkedList* list = linkedListInit();
    ASSERT_EQ_INT(0, lengthOfLinkedList(list));
    deleteLinkedList(list);
}

void test_length_after_appends() {
    LinkedList* list = linkedListInit();
    for (int i = 0; i < 5; i++) {
        appendElementLinkedList(list, createNode(REAL_NUMBER, (double)i, '\0'));
    }
    ASSERT_EQ_INT(5, lengthOfLinkedList(list));
    deleteLinkedList(list);
}

// ===========================================================
// getElementLinkedList tests
// ===========================================================

void test_get_first_element() {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 10.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 20.0, '\0'));

    Node* node = getElementLinkedList(list, 0);
    ASSERT_NOT_NULL(node);
    ASSERT_EQ_DOUBLE(10.0, node->number);
    deleteLinkedList(list);
}

void test_get_last_element() {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 10.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 20.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 30.0, '\0'));

    Node* node = getElementLinkedList(list, 2);
    ASSERT_NOT_NULL(node);
    ASSERT_EQ_DOUBLE(30.0, node->number);
    deleteLinkedList(list);
}

void test_get_middle_element() {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 10.0, '\0'));
    appendElementLinkedList(list, createNode(MATH_OPERATOR, 0.0, '*'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 30.0, '\0'));

    Node* node = getElementLinkedList(list, 1);
    ASSERT_NOT_NULL(node);
    ASSERT_EQ_CHAR('*', node->operator);
    ASSERT_TRUE(node->dataType == MATH_OPERATOR);
    deleteLinkedList(list);
}

void test_get_invalid_position_negative() {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 1.0, '\0'));

    Node* node = getElementLinkedList(list, -1);
    ASSERT_NULL(node);
    deleteLinkedList(list);
}

void test_get_invalid_position_out_of_bounds() {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 1.0, '\0'));

    Node* node = getElementLinkedList(list, 5);
    ASSERT_NULL(node);
    deleteLinkedList(list);
}

void test_get_from_empty_list() {
    LinkedList* list = linkedListInit();
    Node* node = getElementLinkedList(list, 0);
    ASSERT_NULL(node);
    deleteLinkedList(list);
}

// ===========================================================
// deleteElementLinkedList tests
// ===========================================================

void test_delete_first_element() {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 10.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 20.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 30.0, '\0'));

    deleteElementLinkedList(list, 0);

    ASSERT_EQ_INT(2, list->numberOfItems);
    Node* first = getElementLinkedList(list, 0);
    ASSERT_NOT_NULL(first);
    ASSERT_EQ_DOUBLE(20.0, first->number);
    deleteLinkedList(list);
}

void test_delete_last_element() {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 10.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 20.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 30.0, '\0'));

    deleteElementLinkedList(list, 2);

    ASSERT_EQ_INT(2, list->numberOfItems);
    ASSERT_NOT_NULL(list->tail);
    ASSERT_EQ_DOUBLE(20.0, list->tail->number);
    deleteLinkedList(list);
}

void test_delete_middle_element() {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 10.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 20.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 30.0, '\0'));

    deleteElementLinkedList(list, 1);

    ASSERT_EQ_INT(2, list->numberOfItems);
    Node* second = getElementLinkedList(list, 1);
    ASSERT_NOT_NULL(second);
    ASSERT_EQ_DOUBLE(30.0, second->number);
    deleteLinkedList(list);
}

void test_delete_only_element() {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 42.0, '\0'));

    deleteElementLinkedList(list, 0);

    ASSERT_EQ_INT(0, list->numberOfItems);
    ASSERT_NULL(list->head);
    ASSERT_NULL(list->tail);
    deleteLinkedList(list);
}

// ===========================================================
// insertElementLinkedList tests
// ===========================================================

void test_insert_at_beginning() {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 20.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 30.0, '\0'));

    Node* newNode = createNode(REAL_NUMBER, 10.0, '\0');
    insertElementLinkedList(list, 0, newNode);

    ASSERT_EQ_INT(3, list->numberOfItems);
    ASSERT_TRUE(list->head == newNode);
    ASSERT_EQ_DOUBLE(10.0, getElementLinkedList(list, 0)->number);
    ASSERT_EQ_DOUBLE(20.0, getElementLinkedList(list, 1)->number);
    deleteLinkedList(list);
}

void test_insert_at_end() {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 10.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 20.0, '\0'));

    Node* newNode = createNode(REAL_NUMBER, 30.0, '\0');
    insertElementLinkedList(list, 2, newNode);

    ASSERT_EQ_INT(3, list->numberOfItems);
    ASSERT_TRUE(list->tail == newNode);
    ASSERT_EQ_DOUBLE(30.0, getElementLinkedList(list, 2)->number);
    deleteLinkedList(list);
}

void test_insert_in_middle() {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 10.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 30.0, '\0'));

    Node* newNode = createNode(MATH_OPERATOR, 0.0, '+');
    insertElementLinkedList(list, 1, newNode);

    ASSERT_EQ_INT(3, list->numberOfItems);
    Node* mid = getElementLinkedList(list, 1);
    ASSERT_NOT_NULL(mid);
    ASSERT_EQ_CHAR('+', mid->operator);
    deleteLinkedList(list);
}

void test_insert_into_empty_list() {
    LinkedList* list = linkedListInit();

    Node* newNode = createNode(REAL_NUMBER, 99.0, '\0');
    insertElementLinkedList(list, 0, newNode);

    ASSERT_EQ_INT(1, list->numberOfItems);
    ASSERT_TRUE(list->head == newNode);
    ASSERT_TRUE(list->tail == newNode);
    deleteLinkedList(list);
}

// ===========================================================
// changeElementLinkedList tests
// ===========================================================

void test_change_first_element() {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 10.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 20.0, '\0'));

    Node* replacement = createNode(REAL_NUMBER, 99.0, '\0');
    changeElementLinkedList(list, 0, replacement);

    ASSERT_EQ_INT(2, list->numberOfItems);
    ASSERT_EQ_DOUBLE(99.0, getElementLinkedList(list, 0)->number);
    ASSERT_EQ_DOUBLE(20.0, getElementLinkedList(list, 1)->number);
    deleteLinkedList(list);
}

void test_change_last_element() {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 10.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 20.0, '\0'));

    Node* replacement = createNode(MATH_OPERATOR, 0.0, '-');
    changeElementLinkedList(list, 1, replacement);

    ASSERT_EQ_INT(2, list->numberOfItems);
    Node* last = getElementLinkedList(list, 1);
    ASSERT_EQ_CHAR('-', last->operator);
    ASSERT_TRUE(list->tail == replacement);
    deleteLinkedList(list);
}

void test_change_middle_element() {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 1.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 2.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 3.0, '\0'));

    Node* replacement = createNode(REAL_NUMBER, 42.0, '\0');
    changeElementLinkedList(list, 1, replacement);

    ASSERT_EQ_INT(3, list->numberOfItems);
    ASSERT_EQ_DOUBLE(42.0, getElementLinkedList(list, 1)->number);
    // verify linkage is intact
    ASSERT_EQ_DOUBLE(1.0, getElementLinkedList(list, 0)->number);
    ASSERT_EQ_DOUBLE(3.0, getElementLinkedList(list, 2)->number);
    deleteLinkedList(list);
}

// ===========================================================
// copyElement tests
// ===========================================================

void test_copy_number_node() {
    Node* original = createNode(REAL_NUMBER, 7.5, '\0');
    Node* copy = copyElement(original);

    ASSERT_NOT_NULL(copy);
    ASSERT_TRUE(copy != original);  // different pointer
    ASSERT_EQ_DOUBLE(7.5, copy->number);
    ASSERT_TRUE(copy->dataType == REAL_NUMBER);
    ASSERT_NULL(copy->next);

    free(original);
    free(copy);
}

void test_copy_operator_node() {
    Node* original = createNode(MATH_OPERATOR, 0.0, '/');
    original->next = (Node*)0xDEADBEEF;  // set to some non-NULL value
    Node* copy = copyElement(original);

    ASSERT_NOT_NULL(copy);
    ASSERT_EQ_CHAR('/', copy->operator);
    ASSERT_TRUE(copy->dataType == MATH_OPERATOR);
    ASSERT_NULL(copy->next);  // copy should have next = NULL

    original->next = NULL;  // reset before free
    free(original);
    free(copy);
}

void test_copy_null_node() {
    Node* copy = copyElement(NULL);
    ASSERT_NULL(copy);
}

// ===========================================================
// deleteLinkedList tests
// ===========================================================

void test_delete_empty_list() {
    LinkedList* list = linkedListInit();
    deleteLinkedList(list);  // should not crash
    // if we get here, the test passed
}

void test_delete_populated_list() {
    LinkedList* list = linkedListInit();
    for (int i = 0; i < 10; i++) {
        appendElementLinkedList(list, createNode(REAL_NUMBER, (double)i, '\0'));
    }
    deleteLinkedList(list);  // should free all 10 nodes + list struct
}

// ===========================================================
// Integration / edge case tests
// ===========================================================

void test_mixed_node_types() {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 3.0, '\0'));
    appendElementLinkedList(list, createNode(MATH_OPERATOR, 0.0, '+'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 4.0, '\0'));
    appendElementLinkedList(list, createNode(MATH_OPERATOR, 0.0, '*'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 2.0, '\0'));

    ASSERT_EQ_INT(5, lengthOfLinkedList(list));

    // verify pattern: num op num op num
    ASSERT_TRUE(getElementLinkedList(list, 0)->dataType == REAL_NUMBER);
    ASSERT_TRUE(getElementLinkedList(list, 1)->dataType == MATH_OPERATOR);
    ASSERT_TRUE(getElementLinkedList(list, 2)->dataType == REAL_NUMBER);
    ASSERT_TRUE(getElementLinkedList(list, 3)->dataType == MATH_OPERATOR);
    ASSERT_TRUE(getElementLinkedList(list, 4)->dataType == REAL_NUMBER);
    deleteLinkedList(list);
}

void test_insert_then_delete_preserves_structure() {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 1.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 3.0, '\0'));

    // insert in middle
    insertElementLinkedList(list, 1, createNode(REAL_NUMBER, 2.0, '\0'));
    ASSERT_EQ_INT(3, list->numberOfItems);
    ASSERT_EQ_DOUBLE(2.0, getElementLinkedList(list, 1)->number);

    // delete the inserted element
    deleteElementLinkedList(list, 1);
    ASSERT_EQ_INT(2, list->numberOfItems);
    ASSERT_EQ_DOUBLE(1.0, getElementLinkedList(list, 0)->number);
    ASSERT_EQ_DOUBLE(3.0, getElementLinkedList(list, 1)->number);
    deleteLinkedList(list);
}

void test_sequential_deletes_from_front() {
    LinkedList* list = linkedListInit();
    appendElementLinkedList(list, createNode(REAL_NUMBER, 1.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 2.0, '\0'));
    appendElementLinkedList(list, createNode(REAL_NUMBER, 3.0, '\0'));

    deleteElementLinkedList(list, 0);
    deleteElementLinkedList(list, 0);
    deleteElementLinkedList(list, 0);

    ASSERT_EQ_INT(0, list->numberOfItems);
    ASSERT_NULL(list->head);
    ASSERT_NULL(list->tail);
    deleteLinkedList(list);
}

// ===========================================================
// Main test runner
// ===========================================================

int main() {
    printf("=== Linked List Unit Tests ===\n\n");

    printf("[linkedListInit]\n");
    RUN_TEST(test_init_returns_non_null);

    printf("\n[createNode]\n");
    RUN_TEST(test_create_number_node);
    RUN_TEST(test_create_operator_node);

    printf("\n[appendElementLinkedList]\n");
    RUN_TEST(test_append_to_empty_list);
    RUN_TEST(test_append_multiple_elements);

    printf("\n[lengthOfLinkedList]\n");
    RUN_TEST(test_length_empty_list);
    RUN_TEST(test_length_after_appends);

    printf("\n[getElementLinkedList]\n");
    RUN_TEST(test_get_first_element);
    RUN_TEST(test_get_last_element);
    RUN_TEST(test_get_middle_element);
    RUN_TEST(test_get_invalid_position_negative);
    RUN_TEST(test_get_invalid_position_out_of_bounds);
    RUN_TEST(test_get_from_empty_list);

    printf("\n[deleteElementLinkedList]\n");
    RUN_TEST(test_delete_first_element);
    RUN_TEST(test_delete_last_element);
    RUN_TEST(test_delete_middle_element);
    RUN_TEST(test_delete_only_element);

    printf("\n[insertElementLinkedList]\n");
    RUN_TEST(test_insert_at_beginning);
    RUN_TEST(test_insert_at_end);
    RUN_TEST(test_insert_in_middle);
    RUN_TEST(test_insert_into_empty_list);

    printf("\n[changeElementLinkedList]\n");
    RUN_TEST(test_change_first_element);
    RUN_TEST(test_change_last_element);
    RUN_TEST(test_change_middle_element);

    printf("\n[copyElement]\n");
    RUN_TEST(test_copy_number_node);
    RUN_TEST(test_copy_operator_node);
    RUN_TEST(test_copy_null_node);

    printf("\n[deleteLinkedList]\n");
    RUN_TEST(test_delete_empty_list);
    RUN_TEST(test_delete_populated_list);

    printf("\n[Integration Tests]\n");
    RUN_TEST(test_mixed_node_types);
    RUN_TEST(test_insert_then_delete_preserves_structure);
    RUN_TEST(test_sequential_deletes_from_front);

    printf("\n=== Results: %d passed, %d failed ===\n", tests_passed, tests_failed);
    return tests_failed > 0 ? 1 : 0;
}
