#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>

#include "pds.h"

// Define the global variable
struct PDS_RepoInfo repo_handle;

int pds_create(char *repo_name)
{
    // open file 
    //handle file error
    //close file
    //return PDS_SUCCESS
    if(repo_handle.repo_status==PDS_REPO_OPEN){
        return PDS_REPO_ALREADY_OPEN;
    }
    FILE *fptr;
    fptr = fopen(repo_name,"w");
    if(fptr == NULL){
        return PDS_FILE_ERROR;
    }
    fclose(fptr);
    return PDS_SUCCESS;
}

int pds_open( char *repo_name, int rec_size )
{
    //open file and store pointer to repo_handle
    //handle file pointer error
    //if successful update pds_name
    //update  repo_status
    //update rec_size
    //return PDS_SUCCESS
    if(repo_handle.repo_status==PDS_REPO_OPEN){
        return PDS_REPO_ALREADY_OPEN;
    }
    FILE *fptr;
    fptr = fopen(repo_name,"a+");
    if(fptr == NULL){
        return PDS_FILE_ERROR;
    }
    repo_handle.pds_data_fp= fptr;
    strcpy(repo_handle.pds_name,repo_name);
    repo_handle.repo_status=PDS_REPO_OPEN;
    repo_handle.rec_size = rec_size;
    return PDS_SUCCESS;
}


int put_rec_by_key( int key, void *rec )
{
    //check repo_status
    //set file pointer towards end of file
    //write key to file
    //write record to file
    //if write is successful return PDS_SUCCESS 
    //Else return error status accordingly
    if(repo_handle.repo_status==PDS_REPO_OPEN){
        fseek(repo_handle.pds_data_fp,0, SEEK_END);
        if(fwrite(&key, sizeof(int), 1, repo_handle.pds_data_fp) && fwrite(rec, repo_handle.rec_size, 1, repo_handle.pds_data_fp)){
            return PDS_SUCCESS;
        }
        return PDS_ADD_FAILED;
    }
    return PDS_REPO_CLOSED;
}


int get_rec_by_key( int key, void *rec )
{
    //check repo status
    //read file from begining
    // read key
    //compare key 
    //if key is found read the record into rec 
    // return success
    //else return error
    int keyr;
    void *recr;
    if(repo_handle.repo_status==PDS_REPO_OPEN){
        fseek(repo_handle.pds_data_fp,0, SEEK_SET);
        while(!feof(repo_handle.pds_data_fp)){
            fread(&keyr, sizeof(int), 1, repo_handle.pds_data_fp);
            if(keyr == key){
                fread(rec, repo_handle.rec_size, 1, repo_handle.pds_data_fp);
                return PDS_SUCCESS;
            }
            else{
                fread(recr, repo_handle.rec_size, 1, repo_handle.pds_data_fp);
            }
        }
        return PDS_REC_NOT_FOUND;
    }
    return PDS_REPO_CLOSED;

}

int pds_close()
{
    //check repo status
    //close file
    //reset repo_handle name
    //update repo_status
    //return PDS_SUCCESS
    if(repo_handle.repo_status == PDS_REPO_OPEN){
        fclose(repo_handle.pds_data_fp);
        strcpy(repo_handle.pds_name, "");
        repo_handle.repo_status = PDS_REPO_CLOSED;
        return PDS_SUCCESS;
    }
    return PDS_REPO_CLOSED;
}

