#ifndef STORE_H
#define STORE_H

#define STORE_SUCCESS 0
#define STORE_FAILURE 1

struct Product{
	int product_id;
	char product_name[50];
	int cost;
};

extern struct PDS_RepoInfo *repoHandle;

int add_product( struct Product *p );

int overwrite_product( struct Product *p );

void print_product( struct Product *p );

int search_product( int product_id, struct Product *p );

int store_products( char *product_data_file );

int search_product_by_product_name( char *product_name, struct Product *p, int *io_count );

int match_product_name(void *rec, void *key );

int delete_product ( int product_id );

#endif