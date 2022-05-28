#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "pds.h"
#include "store.h"

int store_products( char *product_data_file )
{
	FILE *pfptr;
	char product_line[500], token;
	struct Product p;

	pfptr = (FILE *) fopen("product_data_file", "r");
	while(fgets(product_line, sizeof(product_line)-1, pfptr)){
		sscanf(product_line, "%d%s%d", &(p.product_id),p.product_name,&(p.cost));
		print_product( &p );
		add_product( &p );
	}
}

void print_product( struct Product *p )
{
	printf("%d,%s,%d\n", p->product_id,p->product_name,p->cost);
}

int search_product( int product_id, struct Product *p )
{
	return get_rec_by_ndx_key( product_id, p );
}

int add_product( struct Product *p )
{
	int status;

	status = put_rec_by_key( p->product_id, p );

	if( status != PDS_SUCCESS ){
		fprintf(stderr, "Unable to add product with key %d. Error %d", p->product_id, status );
		return STORE_FAILURE;
	}
	return status;
}

int search_product_by_product_name( char *phone, struct Product *p, int *io_count )
{
	return get_rec_by_non_ndx_key(phone,p,&match_product_name,io_count);
}


int match_product_name( void *rec, void *key )
{
	struct Product *product; 
	product = rec;
	
	char *search_key = key;
	if(strcmp(product->product_name, search_key) == 0){
		return 0;
	}
	else if(strcmp(product->product_name, search_key) != 0){
		return 1;
	}
	return 2;
}

int delete_product ( int product_id )
{
	if(delete_rec_by_ndx_key(product_id) == PDS_SUCCESS){
		return STORE_SUCCESS;
	}
	return STORE_FAILURE;
}

int overwrite_product( struct Product *p ){
	if(pds_overwrite(p->product_id,p) == PDS_SUCCESS){
		return STORE_SUCCESS;
	}
	return STORE_FAILURE;
}
