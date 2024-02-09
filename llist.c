#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"

struct node *node_alloc(int value) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) {
        fprintf(stderr, "Error: Memory allocation Failed!\n");
        return NULL;
    }
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void node_free(struct node *n) {
    if (n != NULL) {
        free(n);
    }
}

void llist_insert_head(struct node **head, struct node *n) {
    if (n == NULL) {
        return;
    }
    n->next = *head;
    *head = n;
}

struct node *llist_delete_head(struct node **head) {
    if (*head == NULL) {
        return NULL;
    }
    struct node *temp = *head;
    *head = temp->next;
    temp->next = NULL;
    return temp;
}

void llist_insert_tail(struct node **head, struct node *n) {
    if (n == NULL) {
        return;
    }
    if (*head == NULL) {
        *head = n;
        return;
    }
    struct node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = n;
}

void llist_print(struct node *head) {
    struct node *current = head;
    if (current == NULL) {
        printf("[empty]\n");
    } else {
        while (current != NULL)
        {
            printf("%d -> ", current->value);
            current = current->next;
        }
        printf("Null\n");
    }
}

void llist_free(struct node **head) {
    struct node *current = *head;
    while (current != NULL) {
        struct node *temp = current;
        current = current->next;
        node_free(temp);
    }
    *head = NULL;
}

int main(int argc, char *argv[]) {
    int i;
    int value;
    char *cmd;
    struct node *head = NULL;

    // Skip program name
    i = 1;

    while (i < argc) {
        cmd = argv[i];

        // Parse the command line
        if (!strcmp(cmd, "ih") || !strcmp(cmd, "it")) {
            if (i + 1 >= argc || !atoi(argv[i + 1])) {
                fprintf(stderr, "Error: Missing value after command '%s'\n", cmd);
                return 1;
            }
            value = atoi(argv[i +1]);

            // Call function based on command
            if (!strcmp(cmd, "ih")) {
                struct node *n = node_alloc(value);
                if (n == NULL) {
                    return 1;
                }
                llist_insert_head(&head, n);
            } else {
                struct node *n = node_alloc(value);
                llist_insert_tail(&head, n);
            }

            i +=2;
        } else if (!strcmp(cmd, "dh")) {
            struct node *deleted = llist_delete_head(&head);
            if (deleted != NULL) {
                node_free(deleted);
            } else {
                printf("Error: Cannot delete head");
            }
            i++;
        } else if (!strcmp(cmd, "f")) {
            llist_free(&head);
            i++;
        } else if (!strcmp(cmd, "p"))
        {
            llist_print(head);
            i++;
        } else {
            fprintf(stderr, "Error, unkknown command! '%s'\n", cmd);
        }
    }
    llist_free(&head);

    return 0;
}