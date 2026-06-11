#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#define ENTER 13

void login_page();

void customer_dashboard();
struct Menu find_item(int);
void bill_generator();
void admin_login();
void admin_dashboard();
void show_menu();
void add_menu();
void view_bills();
int bill_token_generator();

struct Menu
	{
		int item_no;
		char item_name[255];
		int item_price;
		char group[255];
	};
struct Menu menu[255];

int main()
{
    login_page();
}

void login_page()
{
    int choice;
    int attempt = 0;
    
    dash:

    printf("                            CANTEEN BILLING SYSTEM \n");
    printf("\n     [1] ADMIN LOGIN");
    printf("\n     [2] CUSTOMER INTERFACE");
    printf("\n     [3] Exit");
    printf("\n");
    printf("\n     Press 1 for admin login and 2 for customer interface.");
    
    top:
    printf("\n            Your Choice: ");
    scanf("%d", &choice);
    
    system (" CLS ");
    switch(choice)
    {
        case 1:
            admin_login();
            break;

        case 2:
            customer_dashboard();
            break;
            
        case 3:
        	printf("Thank you so much!!\n");
        	printf("            -Canteen");
        	exit(0);

        default:
        	    attempt++;

                if(attempt < 3)
                {
                    printf("Invalid Choice! %d attempts remaining.\n",3 - attempt);
                    goto top;
                }
                else
                {
                    printf("Too many invalid attempts!\n");
                    system ("CLS");
                    goto dash;
                }
    }
}

void customer_dashboard()
{
	printf("                       ========================\n");
	printf("                           CUSTOMER DASHBOARD\n");
	printf("                       ========================");
	printf("\n");
	
	bill_generator();
}

void admin_login()
{
	char username[255]="admin";
	char password[255]="admin";
	char user_name[255];
	char pass_word[255];
	char ch;
	int i =0;
	int tries =0;
	
	printf("========================");
	printf("\n    ADMIN LOGIN");
	printf("\n========================");
	printf("\n");
	
	pass:
	i =0;
	printf("Username: ");
	scanf("%s", user_name);
	printf("Password: ");
	while((ch=getch())!=13){
		pass_word[i]=ch;
		i++;
		printf("*");
	}
	pass_word[i]='\0';
	system("cls");
	
	if(strcmp(user_name,username)==0&&strcmp(pass_word,password)==0)
	{
		printf("Login Successful.");
		getch();
		system (" CLS ");
		admin_dashboard();
	}
	else {
		tries++;
		if(tries < 3)
                {
                    printf("Invalid Choice! %d attempts remaining.\n\n",3 - tries);
                    goto pass;
                }
                else
                {
                    printf("Too many invalid attempts!\n");
                    system( "CLS ");
                    login_page();
                }
	}
}

void admin_dashboard()
{
	int choice;
	printf("========================");
	printf("\n    ADMIN DASHBOARD");
	printf("\n========================\n");
	
	printf("\n[1] Add Menu Item");
	printf("\n[2] View Bills");
	printf("\n[3] Logout");
	printf("\n");
	printf("Enter your choice: ");
	top:
	scanf("%d",&choice);
	
	switch(choice)
	{
		case 1:
			system ("cls");
			add_menu();
			printf("Press any character to return. ");
			getch();
			printf("\n");
			system ("cls");
			admin_dashboard();
		case 2:
			system("cls");
			view_bills();
			printf("Press any character to return. ");
			getch();
			printf("\n");
			system ("cls");
			admin_dashboard();
		case 3:
			system("cls");
			login_page();
		default:
			printf("Invalid Choice!!");
			printf("\nChoose again:");
			goto top;
	}	
}


int bill_token_generator()
{
	int bill_no =1000;
	FILE *fp;
    

    fp = fopen("billno.txt", "r");

    if (fp == NULL)
    {
        bill_no = 1000;
    }
    else
    {
        fscanf(fp, "%d", &bill_no);
        fclose(fp);
    }

    bill_no++;

    fp = fopen("billno.txt", "w");
    fprintf(fp, "%d", bill_no);
    fclose(fp);

    return bill_no;
}

void add_menu()
{
	int count;
	int i;
	
	printf("Enter the amount of items you want to add in the Menu: ");
	scanf("%d", &count);
	printf("\n");
	
	for(i = 1;i<=count;i++)
	{
		printf("Details of the Item no. %d",i);
		printf("\n");
		printf("Enter the Item no: ");
		scanf("%d", &menu[i].item_no);
		printf("Enter the Item name: ");
		scanf("%s", menu[i].item_name);
		printf("Enter the Item Price: ");
		scanf("%d", &menu[i].item_price);
		printf("Enter the Group of item:");
		scanf("%s", menu[i].group);	
		printf("\n");
	}
	FILE *fp = fopen("MENU.txt","a+");
	for(i=1;i<=count;i++)
	{
		fprintf(fp,"%d %s %d %s\n",menu[i].item_no,menu[i].item_name,menu[i].item_price,menu[i].group);
		printf("\n");
	}	
	fclose(fp);
	
}

void show_menu()
{
	
    FILE *fp = fopen("MENU.txt", "r");

struct Menu m;
	printf("                            ***************\n");
	printf("                                 MENU");
	printf("\n                            ***************\n");
	
	printf("\n");
	printf("\nITEM          NAME           PRICE PER UNIT                   GROUP");
	printf("\n----          ----           --------------                   ------");
while(fscanf(fp, "%d %s %d %s",
             &m.item_no,
             m.item_name,
             &m.item_price,
             m.group) == 4)
{

    printf("\n  %-5d       %-10s           %-15d          %-20s\n",
           m.item_no,
           m.item_name,
           m.item_price,
           m.group);
}
    fclose(fp);
}
	
void bill_generator()
{
	int id;
	top:
		
	show_menu();
	int sub_total=0, quantity;
	float discount,tax,grand_total,net_total;
	char customer_name[255];
	int bill_no;
	char more = 'y';
	
	bill_no=bill_token_generator();
	
	FILE *fp = fopen("BILL.txt", "a");

    
   	struct Order{
			int item_no;
			char name[255];
			int quantity;
			int price;
			char group[255];
		};
		struct Order item[255];
	
		int number_of_items; 
		printf("\n");
		printf("Enter your name for the invoice: ");
		scanf(" %[^\n]", customer_name);
		printf("Enter How many items do you want to add ? ");
		scanf("%d",&number_of_items);
		
		for(int i=0;i<number_of_items;i++)
		{
			printf("Enter the Item no: ");
			scanf("%d",&id);
			printf("Enter the quantity: ");
			scanf("%d",&quantity);
			
			struct Menu menu = find_item(id);
			if(menu.item_no == -1)
			{
    			printf("Item not found!\n");
    			i--;
    			continue;
			}
			
			item[i].item_no = menu.item_no;
			strcpy(item[i].name, menu.item_name);
			item[i].quantity = quantity;
			item[i].price = menu.item_price;
			strcpy(item[i].group,menu.group);

		}

		printf("\n---------------------------------------------------------------\n");
		printf("                       CANTEEN OF ARYAN");
		printf("\n---------------------------------------------------------------");
		printf("\n                       CANTEEN INVOICE");
		printf("\nCustomer Name: %s                                 ",customer_name);
		printf("\n                                                 Bill no: %d",bill_no);
		printf("\n---------------------------------------------------------------");
		printf("\nITEM   NAME        QUANTITY   PRICE PER UNIT    GROUP");
		for(int i=0;i<number_of_items;i++)
		{
		printf("\n%-6d %-18s %-8d %-12d %-12s",item[i].item_no,item[i].name,item[i].quantity,item[i].price,item[i].group);
			sub_total += item[i].price * item[i].quantity;
		}
		discount = 0.05*sub_total;
		net_total = sub_total - discount;
		tax = 0.10*net_total;
		grand_total = net_total+tax;
		
		printf("\n---------------------------------------------------------------");
		printf("\nSub-Total                                          %d",sub_total);
		printf("\nDiscount @5                                        %.2f",discount);
		printf("\n                                                 ------");
		printf("\nNet Total                                          %.2f", net_total);
		printf("\nTax@10                                             %.2f", tax);
		printf("\n---------------------------------------------------------------");
		printf("\nGrand-Total                                        %.2f",grand_total);
		printf("\n---------------------------------------------------------------");
		
		fprintf(fp, "%s %d %d %d\n",customer_name, bill_no, sub_total, grand_total);
		fclose(fp);
		
		printf("\n\nThANK YOU!!");
		printf("\nPress 1 to log out and any other key for next customer!");
		if(getch()=='1')
		{
			system ("CLS");
			login_page();
		}
		else 
		{
			system ("CLS");
			goto top;
		}

		
}



struct Menu find_item(int id)
{
	FILE *fp = fopen("MENU.txt", "r");
    struct Menu menu;

    while(fscanf(fp, "%d %s %d %s",
                       &menu.item_no,
                       menu.item_name,
                       &menu.item_price,
                       menu.group) == 4)
    {
        if(menu.item_no == id)
        {
            fclose(fp);
            return menu;
        }
    }
    fclose(fp);    
	menu.item_no = -1;
    return menu;
}

void view_bills()
{
    FILE *fp = fopen("BILL.txt", "r");

    if(fp == NULL)
    {
        printf("No bill records found!\n");
        return;
    }

    int token, subtotal;
    float grandtotal;
	char customer[255];

    printf("\n================ ALL BILLS ================\n");
    printf("TOKEN\tSUBTOTAL\tGRAND TOTAL\n");
    printf("------------------------------------------\n");

    while(fscanf(fp, "%s %d %d %.2f",customer, &token, &subtotal, &grandtotal) == 4)
    {
        printf("%s\t%d\t%d\t\t%d\n", customer, token, subtotal, grandtotal);
    }

    fclose(fp);
}