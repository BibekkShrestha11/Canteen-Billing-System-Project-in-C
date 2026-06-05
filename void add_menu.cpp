#include<stdio.h>
void show_menu();
	struct Menu
	{
		int item_no;
		char item_name[255];
		int item_price;
		char group[255];
	};
	struct Menu menu[255];
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
int main()
{
	int n;
	printf("Enter a choice 1 to add 2 to show:");
	scanf("%d",&n);
	if (n==1)
	{
		add_menu();
	}
	else
	{
	show_menu();
	}
}

void show_menu()
{

    FILE *fp = fopen("MENU.txt", "r");

    if(fp == NULL)
    {
        printf("File not found!");
        return;
    }
    printf("****************");
    printf("\nMENU\n");

    while(fscanf(fp, "%d %s %d %s",&menu.item_no,menu.item_name,&menu.item_price,menu.group) == 4)
    {
        printf("%d %s %d %s\n",menu.item_no,menu.item_name,menu.item_price,menu.group);
    }

    fclose(fp);
}
	
