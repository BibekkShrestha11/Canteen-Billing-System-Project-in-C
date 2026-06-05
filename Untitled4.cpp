void bill_generator()
{
	int sub_total, discount, quantity, net_total, grand_total, tax, bill_no ;
	char more = 'y';
	
	bill_no=bill_token_generator();
	
	FILE *fp = fopen(BILL_FILE, "a");

    fprintf(fp, "%d ", bill_no);
    
    		struct Order item{
			int item_no;
			char name[255];
			int quantity;
			int price;
			char group[255];
		};
	
		int number_of_items; 
		printf("Enter How many items do you want to add ? ");
		scanf("%d",&number_of_items);
		
		for(i=0;i<=number_of_items;i++)
		{
			printf("Enter the Item no: ");
			scanf("%d",&id);
			printf("Enter the quantity: ");
			scanf("%d",&quantity);
			
			struct Menu menu = find_item(id);
			
			item[i].item_no = menu.item_no;
			item[i].name = menu.item_name;
			item[i].quantitiy = quantity;
			item[i].price = menu.item_price;
			item[i].group = menu.group;

		}

		
		printf("CANTEEN OF ARYAN");
		printf("\n----------------");
		printf("\n                 Canteen Invoice");
		printf("\n                  Bill no : %d",bill_no);
		printf("\n---------------------------------");
		printf("\nITEM    NAME    QUANTITY         PRICE PER UNIT           GROUP");
		for(i=0;i<=number_of_items;i++)
		{
			printf("\n%d       %s          %d                %d          %s",item[i].item_no,item[i].name,item[i].quantitiy,item[i].price,item[i].group);
			sub_total += item[i].price;
		}
		discount = 0.05*sub_total;
		net_total = sub_total - discount;
		tax = 0.05*net_total;
		grand_total = net_total+tax;
		
		printf("\n-------------------------------------");
		printf("\nSub-Total                             %d",sub_total);
		printf("\nDiscount @5%                             %d",discount);
		printf("\n                     ------");
		printf("\nNet Total                           %d", net_total);
		printf("\nTax                                  %d", tax);
		printf("\n-------------------------------------");
		printf("\nGrand-Total                            %d",grand_total);
	}

}

struct Menu find_item(int id)
{
	FILE *fp = fopen(MENU.txt, "r");
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

}