#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MENU_FILE "MENU.txt"
#define BILL_FILE "BILL.txt"
#define ADMIN_FILE "ADMIN.txt"

/* ================= STRUCT ================= */
struct Menu
{
    int item_no;
    char item_name[50];
    int item_price;
    char group[30];
};

/* ================= UTIL ================= */
int generate_token()
{
    FILE *fp = fopen(BILL_FILE, "r");
    int token = 1000, t;

    if(fp == NULL)
        return token;

    while(fscanf(fp, "%d", &t) == 1)
    {
        token = t;
        fscanf(fp, "%*[^\n]");
    }

    fclose(fp);
    return token + 1;
}

/* ================= SHOW MENU ================= */
void show_menu()
{
    FILE *fp = fopen(MENU_FILE, "r");

    if(fp == NULL)
    {
        printf("No menu found!\n");
        return;
    }

    struct Menu m;

    printf("\n====== MENU ======\n");

    while(fscanf(fp, "%d %s %d %s",
                 &m.item_no,
                 m.item_name,
                 &m.item_price,
                 m.group) == 4)
    {
        printf("%d. %s - Rs %d [%s]\n",
               m.item_no,
               m.item_name,
               m.item_price,
               m.group);
    }

    fclose(fp);
}

/* ================= ADD MENU ================= */
void add_menu()
{
    FILE *fp = fopen(MENU_FILE, "a");

    struct Menu m;
    int n, i;

    printf("How many items? ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        printf("\nItem No: ");
        scanf("%d", &m.item_no);

        printf("Name: ");
        scanf("%s", m.item_name);

        printf("Price: ");
        scanf("%d", &m.item_price);

        printf("Group: ");
        scanf("%s", m.group);

        fprintf(fp, "%d %s %d %s\n",
                m.item_no,
                m.item_name,
                m.item_price,
                m.group);
    }

    fclose(fp);
}

/* ================= FIND ITEM ================= */
struct Menu find_item(int id)
{
    FILE *fp = fopen(MENU_FILE, "r");
    struct Menu m;

    while(fp && fscanf(fp, "%d %s %d %s",
                       &m.item_no,
                       m.item_name,
                       &m.item_price,
                       m.group) == 4)
    {
        if(m.item_no == id)
        {
            fclose(fp);
            return m;
        }
    }

    if(fp) fclose(fp);

    struct Menu empty = {-1, "", 0, ""};
    return empty;
}

/* ================= BILL SYSTEM ================= */
void create_bill()
{
    int id, qty, total = 0, token;
    char more = 'y';

    token = generate_token();

    FILE *fp = fopen(BILL_FILE, "a");

    printf("\nTOKEN NO: %d\n", token);

    fprintf(fp, "%d ", token);

    while(more == 'y')
    {
        show_menu();

        printf("\nEnter item id: ");
        scanf("%d", &id);

        printf("Quantity: ");
        scanf("%d", &qty);

        struct Menu m = find_item(id);

        if(m.item_no == -1)
        {
            printf("Invalid item!\n");
            continue;
        }

        int cost = m.item_price * qty;
        total += cost;

        printf("%s x %d = %d\n", m.item_name, qty, cost);

        fprintf(fp, "%d:%d ", id, qty);

        printf("Add more? (y/n): ");
        scanf(" %c", &more);
    }

    fprintf(fp, "TOTAL:%d\n", total);

    fclose(fp);

    printf("\nTOTAL BILL = %d\n", total);
}

/* ================= VIEW SALES ================= */
void view_sales()
{
    FILE *fp = fopen(BILL_FILE, "r");
    char line[200];
    int total, grand = 0;

    if(!fp)
    {
        printf("No bills yet!\n");
        return;
    }

    printf("\n=== SALES REPORT ===\n");

    while(fgets(line, sizeof(line), fp))
    {
        printf("%s", line);

        char *p = strstr(line, "TOTAL:");
        if(p)
        {
            sscanf(p, "TOTAL:%d", &total);
            grand += total;
        }
    }

    fclose(fp);

    printf("\nTOTAL SALES = %d\n", grand);
}

/* ================= ADMIN ================= */
void admin_menu()
{
    int ch;

    while(1)
    {
        printf("\n--- ADMIN MENU ---\n");
        printf("1. Show Menu\n");
        printf("2. Add Menu\n");
        printf("3. View Sales\n");
        printf("4. Logout\n");
        scanf("%d", &ch);

        if(ch == 1) show_menu();
        else if(ch == 2) add_menu();
        else if(ch == 3) view_sales();
        else break;
    }
}

/* ================= ADMIN LOGIN ================= */
void admin_login()
{
    char user[20], pass[20];
    char u[20], p[20] = "1234";

    printf("Username: ");
    scanf("%s", user);

    printf("Password: ");
    scanf("%s", pass);

    strcpy(u, "admin");

    if(strcmp(user, u) == 0 && strcmp(pass, p) == 0)
        admin_menu();
    else
        printf("Invalid login!\n");
}

/* ================= MAIN MENU ================= */
int main()
{
    int ch;

    while(1)
    {
        printf("\n==== CANTEEN SYSTEM ====\n");
        printf("1. Admin Login\n");
        printf("2. Customer Order\n");
        printf("3. Exit\n");
        scanf("%d", &ch);

        if(ch == 1)
            admin_login();
        else if(ch == 2)
            create_bill();
        else
            break;
    }

    return 0;
}