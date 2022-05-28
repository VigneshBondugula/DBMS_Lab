#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "pds.h"
#include "store.h"

int main(){
    int open_menu = 1;
    while(open_menu){
        int choice;
        printf("0. CREATE PDS\n");
        printf("1. OPEN PDS\n");
        printf("2. ADD A PRODUCT TO THE STORE\n");
        printf("3. UPDATE A PRODUCT INFO IN THE STORE\n");
        printf("4. REMOVE A PRODUCT FROM THE STORE\n");
        printf("5. SEARCH A PRODUCT IN THE STORE\n");
        printf("6. SEARCH A PRODUCT IN THE STORE BY PRODUCT NAME\n");
        printf("7. CLOSE THE APPLICATION\n");

        printf("\n ENTER THE CHOICE : ");
        scanf("%d", &choice);

        if(choice == 0){
            int status = pds_create("Store_pds");
            if(status ==  PDS_SUCCESS){
                printf(" PDS created succesfully.\n\n");
            }
            else{
                printf(" Failed to create PDS.\n\n");
            }
        }
        if(choice == 1){
            int status =  pds_open("Store_pds", sizeof(struct Product));
            if(status ==  PDS_SUCCESS){
                printf(" PDS opened succesfully.\n\n");
            }
            else if(status== PDS_REPO_ALREADY_OPEN){
                printf(" PDS REPO is already open\n\n");
            }
            else{
                printf(" Failed to open PDS.\n\n");
            }
        }
        else if(choice == 2){
            struct Product p;

            printf("\n ENTER THE PRODUCT ID : ");
            scanf("%d", &p.product_id);
            printf("\n ENTER THE PRODUCT NAME : ");
            scanf("%s", p.product_name);
            printf("\n ENTER THE COST : ");
            scanf("%d", &p.cost);

            int status = add_product(&p);
            if(status == STORE_SUCCESS){
                printf(" Product added to the store succesfully.\n\n");
            }
            else{
                printf(" Failed to add the product.\n\n");
            }
        }
        else if(choice == 3){
            struct Product p;

            printf("\n ENTER THE PRODUCT ID OF THE PRODUCT TO BE UPDATED : ");
            scanf("%d", &p.product_id);
            printf("\n ENTER THE NEW PRODUCT NAME : ");
            scanf("%s", p.product_name);
            printf("\n ENTER THE NEW COST : ");
            scanf("%d", &p.cost);

            int status = overwrite_product(&p);
            if(status == STORE_SUCCESS){
                printf(" Product updated in the store succesfully.\n\n");
            }
            else{
                printf(" Failed to update the product.\n\n");
            }
        }
        else if(choice == 4){
            int id;
            printf("\n ENTER THE PRODUCT ID OF THE PRODUCT TO BE DELETED : ");
            scanf("%d", &id);

            int status = delete_product(id);
            if(status == STORE_SUCCESS){
                printf(" Product deleted from the store succesfully.\n\n");
            }
            else{
                printf(" Failed to delete the product.\n\n");
            }
        }
        else if(choice == 5){
            int id;
            struct Product p;
            printf("\n ENTER THE PRODUCT ID OF THE PRODUCT TO BE SEARCHED : ");
            scanf("%d", &id);

            int status = search_product(id, &p);
            if(status == STORE_SUCCESS){
                printf(" The product details are : ");
                print_product(&p);
                printf("\n\n");
            }
            else{
                printf(" Failed to find the product.\n\n");
            }
        }
        else if(choice == 6){
            char name[50];
            struct Product p;
            int count = 0;
            printf("\n ENTER THE PRODUCT NAME OF THE PRODUCT TO BE SEARCHED : ");
            scanf("%s", name);

            int status = search_product_by_product_name(name, &p,&count);
            if(status == STORE_SUCCESS){
                printf(" The product details are : ");
                print_product(&p);
                printf("\n\n");
            }
            else{
                printf(" Failed to find the product.\n\n");
            }
        }
        else if(choice == 7){
            pds_close();
            open_menu = 0;
        }
        else{
            printf(" ENTER THE RIGHT CHOICE.\n\n");
        }
    }
}
