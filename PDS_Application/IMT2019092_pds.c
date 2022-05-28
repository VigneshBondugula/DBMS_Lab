#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

#include "pds.h"
#include "bst.h"

struct PDS_RepoInfo repo_handle;


int pds_create(char *repo_name) 
{
  char filename[30], indexfile[30];
  strcpy(filename,repo_name);
  strcpy(indexfile,repo_name);
  strcat(filename,".dat");
  strcat(indexfile,".ndx");
  FILE *fp = fopen(filename,"wb+");
  FILE *ifp = fopen(indexfile,"wb+");
  if(fp  == NULL || ifp == NULL) return PDS_FILE_ERROR;
  fclose(fp);
  fclose(ifp);
  
  return PDS_SUCCESS;
}


int pds_open(char* repo_name, int rec_size) // Same as before
{
  // Open the data file and index file in rb+ mode
  char filename[30], indexfile[30];
  strcpy(filename,repo_name);
  strcpy(indexfile,repo_name);
  strcat(filename,".dat");
  strcat(indexfile,".ndx");
  if(repo_handle.repo_status==PDS_REPO_OPEN){
        return PDS_REPO_ALREADY_OPEN;
  }
  repo_handle.pds_data_fp = fopen(filename,"rb+");
  repo_handle.pds_ndx_fp = fopen(indexfile,"rb+");

  if(repo_handle.pds_data_fp == NULL || repo_handle.pds_ndx_fp  == NULL){
      return PDS_FILE_ERROR;
  }
  // Update the fields of PDS_RepoInfo appropriately
  strcpy(repo_handle.pds_name,repo_name);
  repo_handle.repo_status = PDS_REPO_OPEN;
  repo_handle.rec_size = rec_size;
  // Build BST and store in pds_bst by reading index entries from the index file
  pds_load_ndx();
  // Close only the index file
  fclose(repo_handle.pds_ndx_fp);
  return PDS_SUCCESS;
}

int pds_load_ndx() // Same as before
{
  // Internal function used by pds_open to read index entries into BST
  while(!feof(repo_handle.pds_ndx_fp)){
    struct PDS_NdxInfo ndxtemp;
    fread(&ndxtemp, sizeof(struct PDS_NdxInfo), 1, repo_handle.pds_ndx_fp);
    struct PDS_NdxInfo *ndxtempptr = (struct PDS_NdxInfo*)malloc(sizeof(struct PDS_NdxInfo));
    // int *data = (int*)malloc(sizeof(int));
    // *data = ndxtemp.offset;
    *ndxtempptr = ndxtemp;
    if(bst_add_node(&repo_handle.pds_bst,ndxtemp.key,ndxtempptr) != 0){
      return PDS_NDX_SAVE_FAILED;
    }
  }}

int put_rec_by_key(int key, void*rec)
{
  if(repo_handle.repo_status == PDS_REPO_CLOSED) return PDS_FILE_ERROR;
  fseek(repo_handle.pds_data_fp,0, SEEK_END);
  // Create an index entry with the current data file location using ftell
  int *offset = (int*)malloc(sizeof(int));
  *offset = ftell(repo_handle.pds_data_fp);
  struct PDS_NdxInfo *ndxtemp = (struct PDS_NdxInfo*)malloc(sizeof(struct PDS_NdxInfo));
  ndxtemp->is_deleted = 0;
  ndxtemp->offset=ftell(repo_handle.pds_data_fp);
  ndxtemp->key = key;
  // Add index entry to BST using offset returned by ftell
  int result = bst_add_node(&repo_handle.pds_bst,key,ndxtemp);
  if(result == BST_DUP_KEY){
    return BST_DUP_KEY;
  }
  if(result != 0){
    return PDS_ADD_FAILED;
  }
  // Write the key at the current data file location
  // Write the record after writing the key
  if(fwrite(&key, sizeof(int), 1, repo_handle.pds_data_fp) && fwrite(rec, repo_handle.rec_size, 1, repo_handle.pds_data_fp)){
      return PDS_SUCCESS;
  }
  return PDS_ADD_FAILED;
}

int get_rec_by_ndx_key(int key, void*rec)
{  
  int keyr;
  void *recr;
  if(repo_handle.repo_status==PDS_REPO_CLOSED){
      return PDS_FILE_ERROR;
  }
  // Search for index entry in BST
  struct BST_Node* bstnode = bst_search(repo_handle.pds_bst,key);
  if(bstnode==NULL){
    return PDS_REC_NOT_FOUND;
  }
  // (NEW) Check if the entry is deleted and if it is deleted, return PDS_REC_NOT_FOUND
  struct PDS_NdxInfo *ndxtemp = bstnode->data;
  if(ndxtemp->is_deleted == 1){
    return PDS_REC_NOT_FOUND;
  }
  // Seek to the file location based on offset in index entry
  fseek(repo_handle.pds_data_fp,ndxtemp->offset, SEEK_SET);
  // Read the key at the current file location  
  fread(&keyr, sizeof(int), 1, repo_handle.pds_data_fp);
  // Read the record after reading the key
  if(keyr == key){
      fread(rec, repo_handle.rec_size, 1, repo_handle.pds_data_fp);
      return PDS_SUCCESS;
  }
  return PDS_REC_NOT_FOUND;
}


void preorder(struct BST_Node* node)
{
    if(node == NULL)
        return;
    
    struct PDS_NdxInfo* ndxtempptr = node->data;
    struct PDS_NdxInfo ndxtemp;
    ndxtemp = *ndxtempptr;

    if(ndxtemp.is_deleted == 0){
      fwrite(&ndxtemp,sizeof(struct PDS_NdxInfo), 1, repo_handle.pds_ndx_fp);
    }
    preorder(node->left_child);
    preorder(node->right_child);
}

int pds_close() 
{
  char indexfile[30];
  strcpy(indexfile,repo_handle.pds_name);
  strcat(indexfile,".ndx");
  // Open the index file in wb mode (write mode, not append mode)
  repo_handle.pds_ndx_fp = fopen(indexfile,"wb");
  // Unload the BST into the index file by traversing it in PRE-ORDER (overwrite the entire index file)
  preorder(repo_handle.pds_bst);
  // Free the BST by calling bst_destroy()
  bst_destroy(repo_handle.pds_bst);
  // Close the index file and data file
  fclose(repo_handle.pds_ndx_fp);
  if(repo_handle.repo_status == PDS_REPO_OPEN){
      fclose(repo_handle.pds_data_fp);
      strcpy(repo_handle.pds_name, "");
      repo_handle.repo_status = PDS_REPO_CLOSED;
      repo_handle.pds_bst = NULL;
      return PDS_SUCCESS;
  }
  return PDS_REPO_NOT_OPEN;
}

int get_rec_by_non_ndx_key(void *key, void *rec, int (*matcher)(void *rec, void *key), int *io_count)
{
   // Seek to beginning of file
  int keyr;
  fseek(repo_handle.pds_data_fp,0, SEEK_SET);
  // Perform a table scan - iterate over all the records
   while(!feof(repo_handle.pds_data_fp)){
      //   Read the key and the record
      fread(&keyr, sizeof(int), 1, repo_handle.pds_data_fp);
      fread(rec, (repo_handle.rec_size), 1, repo_handle.pds_data_fp);
      //   Increment io_count by 1 to reflect count no. of records read
      *io_count = *io_count+1;
      //   Use the function in function pointer to compare the record with required key
      if(matcher(rec,key)==0){
          struct BST_Node* bstnode = bst_search(repo_handle.pds_bst,keyr);
          if(bstnode==NULL){
            return PDS_REC_NOT_FOUND;
          }
          struct PDS_NdxInfo *ndxtemp = bstnode->data;
          if(ndxtemp->is_deleted == 1){
            return PDS_REC_NOT_FOUND;
          }
        // Return success when record is found
        return PDS_SUCCESS;
      }
   }
  return PDS_REC_NOT_FOUND;
}

int delete_rec_by_ndx_key( int key) // New Function
{
  // Search for the record in the BST using the key
  struct BST_Node* bstnode = bst_search(repo_handle.pds_bst,key);
  // If record not found, return PDS_DELETE_FAILED
  if(bstnode==NULL){
    return PDS_DELETE_FAILED;
  }
  struct PDS_NdxInfo *ndxtemp = bstnode->data;
  // If record is found, check if it has already been deleted, if so return PDS_DELETE_FAILED
  if(ndxtemp->is_deleted == 1){
    return PDS_DELETE_FAILED;
  }
  // Else, set the record to deleted and return PDS_SUCCESS
  else{
    ndxtemp->is_deleted = 1;
    return PDS_SUCCESS;
  }
}

int pds_overwrite( int key, void *rec ){
  int keyr;
  void *recr;
  if(repo_handle.repo_status==PDS_REPO_CLOSED){
      return PDS_FILE_ERROR;
  }
  // Search for index entry in BST
  struct BST_Node* bstnode = bst_search(repo_handle.pds_bst,key);
  if(bstnode==NULL){
    return PDS_REC_NOT_FOUND;
  }
  // (NEW) Check if the entry is deleted and if it is deleted, return PDS_REC_NOT_FOUND
  struct PDS_NdxInfo *ndxtemp = bstnode->data;
  if(ndxtemp->is_deleted == 1){
    return PDS_REC_NOT_FOUND;
  }
  // Seek to the file location based on offset in index entry
  fseek(repo_handle.pds_data_fp,ndxtemp->offset, SEEK_SET);
  // Read the key at the current file location  
  fread(&keyr, sizeof(int), 1, repo_handle.pds_data_fp);
  // Read the record after reading the key
  if(keyr == key){
      fwrite(rec, repo_handle.rec_size, 1, repo_handle.pds_data_fp);
      return PDS_SUCCESS;
  }
  return PDS_UPDATE_FAILED;
}