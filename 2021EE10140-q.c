#include<stdio.h>
#include<stdlib.h>
#include <string.h>

// The following is a employee in the organisation, it has the pointer to two more employees a subordinate_1 and a subordinate_2
struct Employee {
    int emp_id; // emp_ids will be unique
    struct Employee* subordinate_1;
    struct Employee* subordinate_2;
};

// The following function creates a employee and returns its pointer
struct Employee* create_employee(int x) {
    struct Employee* ptr = (struct Employee*) malloc(sizeof(struct Employee));
    ptr->emp_id = x;
    ptr->subordinate_1 = NULL;
    ptr->subordinate_2 = NULL;
    return ptr;
}

// The following code creates a organisation from scanning the input file
struct Employee* create_company() {
    int x;
    scanf("%d", &x);

    if(x == -1) return NULL; // -1 is used when there is a NULL pointer ie when no value is present
    struct Employee* par = create_employee(x);

    par->subordinate_1 = create_company();
    par->subordinate_2 = create_company();
    
    return par;
}

// The following function 
void print_company_helper(struct Employee* ceo) {
    // take input
    if(!ceo) {
        printf("%d ", -1);
        return;
    }
    printf("%d ", ceo->emp_id);
    print_company_helper(ceo->subordinate_1);
    print_company_helper(ceo->subordinate_2);
    return;
}

void print_company(struct Employee* ceo) {
    print_company_helper(ceo);
    printf("\n");
    return;
} 

// --------------------------------------------------- YOU CAN EDIT BELOW THIS LINE -----------------------------------

// ---------------------------------------------------PYTHONLIST-------------------------------------------------------
// Copy pasting the Python List function and making some changes

struct Node{
    struct Employee* emp;
    struct Employee* boss;
    int level;
    struct Node* next;
};

struct Node* create_node(struct Employee* Emp, struct Employee* Boss, int level) {
    struct Node* ptr = malloc(sizeof(struct Node));
    ptr->next = NULL;
    ptr->emp = Emp;
    ptr->boss = Boss;
    ptr->level = level;
    return ptr;
}

void delete_node(struct Node* ptr) {
    free(ptr);
}

struct Node* PythonListHead = NULL;

//Renamed append to push
void push(struct Employee* x, struct Employee* y, int z) {
    struct Node* cur = PythonListHead;
    struct Node* add = create_node(x,y,z);
    if (PythonListHead == NULL)
        PythonListHead = add;
    else{
        while (cur->next != NULL)
            cur = cur->next;
        cur->next = add;
    }
}

void clear() {
    struct Node* cur = PythonListHead;
    PythonListHead = NULL;
    while(cur) {
        struct Node* next_node = cur->next;
        delete_node(cur);
        cur = next_node;
    }
}

// This ends the Linked list definition, I will use it as a stack for values of struct Employee*
//--------------------------------------------------------------PYTHONLIST ENDS---------------------------------------

//--------------------------------------SECOND PYTHON LIST---------------------------------------------------------

struct Node_1* PythonListHead_1 = NULL;

struct Node_1
{
    int data;
    struct Node_1* next;
};

// create a node with data as x
struct Node_1* create_node_1(int x) {
    struct Node_1* ptr = malloc(sizeof(struct Node_1));
    ptr->next = NULL;
    ptr->data = x;
    return ptr;
}

// delete the node at `ptr` and free its memory
void delete_node_1(struct Node_1* ptr) {
    free(ptr);
}

void append(int x) {
    struct Node_1* add = create_node_1(x);
    if (PythonListHead_1 == NULL)
        PythonListHead_1 = add;
    else{
        struct Node_1* store = PythonListHead_1;
        PythonListHead_1 = add;
        PythonListHead_1->next = store;
    }
}

void clear_1() {
    struct Node_1* cur = PythonListHead_1;
    PythonListHead_1 = NULL;
    while(cur) {
        struct Node_1* next_node = cur->next;
        delete_node_1(cur);
        cur = next_node;
    }
}

//----------------------------------- SECOND PYTHON LIST END-------------------------------------------------------

struct Employee* CEO = NULL;
// CEO is a global pointer that points to the CEO of the company

/*  In this function you have to print all the employees at a given level, Note that ceo is at level 0
In any of the functions which involve printing you need not print -1 for NULL pointers */

void same_level_helper(struct Employee* emp, int level){
    if(level == 0 && emp != NULL){
        printf("%d ", emp->emp_id);
        return;
    }
    if(!emp)
        return;
    same_level_helper(emp->subordinate_1, level-1);
    same_level_helper(emp->subordinate_2, level-1);
}

void EmployeesAtSameLevel(int level) {
    // The level may be any integer
    same_level_helper(CEO, level);
    return;
}

// You have to print the employees as you search the organization look for the examples in the pdf and the input.txt and output.txt for details
// Note: You do not have to print -1 for NULL pointers

void get_employees_helper(struct Employee* emp) {
    // take input
    if(!emp) {
        return;
    }
    printf("%d ", emp->emp_id);
    get_employees_helper(emp->subordinate_1);
    get_employees_helper(emp->subordinate_2);
    return;
}

void get_employees() {
    get_employees_helper(CEO);
    return;
}

int mega_helper(struct Employee* emp, int emp_id, int level){
    if(CEO->emp_id == emp_id){
        push(CEO, NULL,0);
        return 1;
    }
    if(emp->subordinate_1 == NULL && emp->subordinate_2 == NULL)
        return 0;

    else if(emp->subordinate_1 == NULL){
        if(emp->subordinate_2->emp_id == emp_id){
            push(emp->subordinate_2, emp,level+1);
            return 1;
        }
        else{
            return mega_helper(emp->subordinate_2, emp_id,level+1);
        }
    }
    
    else if(emp->subordinate_2 == NULL){
        if(emp->subordinate_1->emp_id == emp_id){
            push(emp->subordinate_1, emp,level+1);
            return 1;
        }
        else{
            return mega_helper(emp->subordinate_1, emp_id,level+1);
        }
    }
    else{
        if(emp->subordinate_1->emp_id == emp_id){
            push(emp->subordinate_1, emp,level+1);
            return 1;
        }
        else if(emp->subordinate_2->emp_id == emp_id){
            push(emp->subordinate_2, emp,level+1);
            return 1;
        }
        else{
            return (mega_helper(emp->subordinate_1, emp_id,level+1) || mega_helper(emp->subordinate_2, emp_id,level+1));
        }
    }
}

/* In the following function you have to print the immediate team of a employee - it includes their boss and their subordinates
Note: You do not have to print -1 for NULL pointers */

void ImmediateTeam(int emp_id) {
    int val;
    clear();
    val = mega_helper(CEO, emp_id,0);
    if(val){
        if(PythonListHead->boss != NULL)
            printf("%d ", PythonListHead->boss->emp_id);
        if(PythonListHead->emp->subordinate_1 != NULL)
            printf("%d ", PythonListHead->emp->subordinate_1->emp_id);
        if(PythonListHead->emp->subordinate_2 != NULL)
            printf("%d ", PythonListHead->emp->subordinate_2->emp_id);
    clear();
    }
    else{
        return;
    }
}

int check_if_in(struct Employee* emp, int emp_id){
    if(emp == NULL)
        return 0;
    if(emp->emp_id == emp_id)
        return 1;
    else{
        return (check_if_in(emp->subordinate_1, emp_id) || check_if_in(emp->subordinate_2, emp_id));
    }
}

int first_common_node(int emp_id1, int emp_id2){
    if(emp_id1 == emp_id2)
        return emp_id1;
    clear();
    int val1 = mega_helper(CEO, emp_id1,0);
    if(val1){
        if(PythonListHead->boss == NULL)
            return CEO->emp_id;
        else if(check_if_in(PythonListHead->emp, emp_id2)){
            return emp_id1;
        }
        else{
            struct Employee* store = PythonListHead->boss;
            clear();
            int check = check_if_in(store,emp_id2);
            if(check)
                return store->emp_id;
            else
                return first_common_node(store->emp_id,emp_id2);
        }
    }
    }

// The following function returns the level of a employee with the given emp_id
int Level(int emp_id) {
    clear();
    int val = mega_helper(CEO,emp_id,0);
    if(val){
        int lvl = (PythonListHead->level);
        clear();
        return lvl;
    }
    return 0;
}

// The following function gives the distance between employees with emp_id1 and emp_id2
int Distance(int emp_id1, int emp_id2) {
    // If emp_id1 and emp_id2 are equal the distance is 0, both emp_id's will exist in the organisation
    if(emp_id1 == emp_id2)
        return 0;

    int common_id = first_common_node(emp_id1,emp_id2);
    clear();
    int val_1, val_2, val_3;
    val_1 = Level(emp_id1);
    val_2 = Level(emp_id2);
    val_3 = Level(common_id);
    return ((val_1 - val_3) + (val_2 - val_3));
}


/* The following function takes an emp_id this will belong to a employee in the organisation and your task is to return the emp_id of its boss
Note: If the boss does not exit return -1 */
int Boss(int emp_id) {
    int val, boss_id;
    clear();
    val = mega_helper(CEO, emp_id,0);
    if(val){
        if(PythonListHead->boss != NULL)
            boss_id = PythonListHead->boss->emp_id;
        else
            boss_id = -1;
        clear();
        return boss_id;
    }
    else{
        return -1;
    }
}

/* The following function returns the diameter of a Organisation - 
a diameter is the maximum distance between any two emp_ids in the organisation. You can use the distance function implemented above */

void add_one_NULL_node(struct Employee* emp){
    if(emp->subordinate_1 == NULL && emp->subordinate_2 == NULL){
        append(emp->emp_id);
        return;
    }
    else if(emp->subordinate_1 == NULL){
        append(emp->emp_id);
        add_one_NULL_node(emp->subordinate_2);
    }
    else if(emp->subordinate_2 == NULL){
        append(emp->emp_id);
        add_one_NULL_node(emp->subordinate_1);
    }
    else{
        add_one_NULL_node(emp->subordinate_1);
        add_one_NULL_node(emp->subordinate_2);
    }
}


int Diameter() {
    if(CEO == NULL)
        return 0;
    if(CEO->subordinate_1 == NULL && CEO->subordinate_2 == NULL)
        return 0;
    clear();
    clear_1();
    add_one_NULL_node(CEO);
    struct Node_1* curr_1 = PythonListHead_1;
    struct Node_1* curr_2 = PythonListHead_1;

    int curr_dis = 0, max_dis = 0;

    while(curr_1 != NULL){
        while(curr_2 != NULL){
            curr_dis = Distance(curr_1->data, curr_2->data);
            if(curr_dis > max_dis)
                max_dis = curr_dis;
            curr_2 = curr_2->next;
        }
        curr_1 = curr_1->next;
        curr_2 = curr_1;
    }

    return max_dis;
}


/* The following function takes an emp_id of a employee and returns the number of employees directly connected to it.
NULL pointers are not included */

int TeamSize(int emp_id) {
    int val,count = 0;
    clear();
    val = mega_helper(CEO,emp_id,0);
    if(val){
        if(PythonListHead->boss != NULL)
            count++;
        if(PythonListHead->emp->subordinate_1 != NULL)
            count++;
        if(PythonListHead->emp->subordinate_2 != NULL)
            count++;
        clear();
        return count;
    }
    else{
        return 0;
    }
}

// --------------------------------------------------- YOU CAN EDIT ABOVE THIS LINE -----------------------------------

/* The following driver code creates a organisation for you and based on the input file
it will call all the functions that are necessary, your job is to edit the functions
above the line. Their descriptions are in the pdf and in the comments in the code. */

int main(int argc, char const *argv[])
{
    CEO = create_company();
    print_company(CEO);

    int T; 
    scanf("%d", &T);

    char operation_type[50];

    while(T--) {
        scanf("%s", operation_type);

        if(strcmp(operation_type, "level") == 0) {
            int x;
            scanf("%d", &x);
            int d = Level(x);
            printf("%d\n", d);
        } 

        if(strcmp(operation_type, "distance") == 0) {
            int x, y;
            scanf("%d %d", &x, &y);
            int d = Distance(x, y);
            printf("%d\n", d);
        }

        if(strcmp(operation_type, "employees_at_same_level") == 0) {
            int x;
            scanf("%d", &x);
            EmployeesAtSameLevel(x);
            printf("\n");
        }

        if(strcmp(operation_type, "get_employees") == 0) {
            get_employees();
            printf("\n");
        }

        if(strcmp(operation_type, "boss") == 0) {
            int x;
            scanf("%d", &x);
            int d = Boss(x);
            printf("%d\n", d);
        }

        if(strcmp(operation_type, "diameter") == 0) {
            int d = Diameter();
            printf("%d\n", d);
        }

        if(strcmp(operation_type, "immediate_team") == 0) {
            int x;
            scanf("%d", &x);
            ImmediateTeam(x);
            printf("\n");
        }

        if(strcmp(operation_type, "team_size") == 0) {
            int x;
            scanf("%d", &x);
            int d = TeamSize(x);
            printf("%d\n", d);
        }
    }

    return 0;
}
