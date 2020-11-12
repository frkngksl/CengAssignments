#include "fs.h"
#include "ext2_fs/ext2.h"

#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char **parseAndReturnNames(char *pathPtr){
    char *path = malloc(sizeof(char)*strlen(pathPtr)+1);
    strcpy(path,pathPtr);
    path[strlen(pathPtr)] = '\0';
    int numberOfPieces = 0;
    int j=0;
    for(int i=0;i<strlen(path);i++){
        if(path[i] == '/'){
            ++numberOfPieces;
        }
    }
    char **fullPath = malloc(sizeof(char *)*(numberOfPieces+1));
    char *temp2 = malloc(sizeof(char)*2);
    temp2[0] = '/';
    temp2[1] = '\0';
    fullPath[0] = temp2;
    char *index = path+1;
    char *temp = malloc(sizeof(char));
    int length = 0;
    int index1 = 1;
        while(*index != '\0' ){
            if(*index == '/'){
                //temp[length] = '/';
                ++index;
                //++length;
                //temp = realloc(temp,(length+1)*sizeof(char));
                temp[length] = '\0';
                fullPath[index1++] = temp;
                temp = malloc(sizeof(char));
                length = 0;
            }else{
                temp[length] = *index;
                ++length;
                ++index;
                temp = realloc(temp,(length+1)*sizeof(char));
            }
        }
    ++length;
    temp = realloc(temp,length*sizeof(char));
    temp[length]= '\0';
    fullPath[index1++] = temp;
    /*int size1;
    int size2;
    char **last = malloc(sizeof(char *)*(numberOfPieces+1));
    temp  = malloc(sizeof(char)*2);
    temp[0] = '/';
    temp[1] = '\0';
    last[0] = temp;
    for(int i=1;i<numberOfPieces+1;i++){
        size1 = strlen(last[i-1]);
        size2 = strlen(fullPath[i]);
        last[i] = malloc(size1+size2+1);
        temp = last[i];
        index = last[i-1];
        for(int j=0;j<size1;j++){
            temp[j] = index[j];
        }
        index = fullPath[i];
        for(int j=0;j<size2;j++){
            temp[j+size1] = index[j];
        }
        temp[j+size1+size2] = '\0';
        //fullPath[i] = last[i];
    }*/
    free(path);
    /*for(int i=0;i<numberOfPieces+1;i++){
        free(fullPath[i]);
    }*/
    return fullPath;
}


int init_fs(const char *image_path) {
  current_fs = initialize_ext2(image_path); //This function fills the function pointer in super_operations, inode_operations, file_operations structs. It also
                                            //sets the name, file_descriptor, get_superblock fields of the file_system_type myfs defined in
                                            //ext2.h. It returns a pointer to myfs . myfs ext2.hda yazili
  current_sb = current_fs->get_superblock(current_fs); //This function
                                                    //allocates and fills the fields of the superblock of the file system fs returning a pointer to the
                                                    //allocated struct super_block .
  return !(current_fs && current_sb);
}

struct file *openfile(char *path) {
  struct file *f = malloc(sizeof(struct file)); //file table aciliyor
  f->f_path = malloc(strlen(path) + 1);
  strcpy(f->f_path, path); //ismi verildi
  struct dentry *dir = pathwalk(path); //o directory bulundu //This function takes an absolute path, path as a C string (e.g. /home/config) and returns its directory entry.
  if (!dir) {
    return NULL;
  }
  f->f_inode = dir->d_inode; //inodeu set edildi
  free(dir);
  if (f->f_inode->f_op->open(f->f_inode, f)) {
    return NULL;
  }
  return f;
}

int closefile(struct file *f) {
  if (f->f_op->release(f->f_inode, f)) {
    printf("Error closing file\n");
  }
  free(f);
  f = NULL;
  return 0;
}

int readfile(struct file *f, char *buf, int size, loffset_t *offset) {
  if (*offset >= f->f_inode->i_size) { //Buyukse salla
    return 0;
  }
  if (*offset + size >= f->f_inode->i_size) {
    size = f->f_inode->i_size - *offset; //short read engelle
  }
  // May add llseek call
  return f->f_op->read(f, buf, size, offset); //bizim implementeyi cagir
}

struct dentry *pathwalk(char *path) {
  /* Allocates and returns a new dentry for a given path */
  if((strcmp(path,".") == 0) || (strcmp(path,"/") == 0)){
      struct dentry *returningValue = malloc(sizeof(struct dentry));
      memcpy(returningValue,&rootEntry,sizeof(struct dentry));
      returningValue->d_inode = malloc(sizeof(struct inode));
      returningValue->d_name = malloc(2*sizeof(char));
      returningValue->d_name[0] = '/'; //TODO name ?
      returningValue->d_name[1] = '\0';
      memcpy(returningValue->d_inode,&rootInode,sizeof(struct inode));
      return returningValue;
  }
  else{
      char **eachDirName;
      struct dentry *parentDentry = malloc(sizeof(struct dentry));
      struct inode *parentInode = malloc(sizeof(struct inode));
      struct dentry *temp;
      memcpy(parentDentry,&rootEntry,sizeof(struct dentry));
      parentDentry->d_inode = parentInode;
      memcpy(parentInode,&rootInode,sizeof(struct inode));
      int numberOfPieces = 0;
      for(int i=0;i<strlen(path);i++){
          if(path[i] == '/'){
              ++numberOfPieces;
          }
      }
      eachDirName = parseAndReturnNames(path);
      parentDentry->d_name = eachDirName[0];
      for(int i=0;i<numberOfPieces;i++){
          temp = malloc(sizeof(struct dentry));
          temp->d_parent = parentDentry;
          temp->d_name = eachDirName[i+1];
          if(parentInode->i_op->lookup(parentInode,temp) == NULL){
              //Garbage collection
              return NULL;
          }
          parentDentry = temp;
          parentInode = temp->d_inode;
      }
      return temp;
  }
}

int statfile(struct dentry *d_entry, struct kstat *k_stat) {
  return d_entry->d_inode->i_op->getattr(d_entry, k_stat); //stati aliyor
}
