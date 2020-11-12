#include "ext2.h"

#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <math.h>

#define BASE_OFFSET 1024 /* location of the superblock in the first group */

struct super_operations s_op;
struct inode_operations i_op;
struct file_operations f_op;

char fs_name[] = "ext2";
/*
int ceil(float num) {
    int inum = (int) num;
    if (num == (float) inum) {
        return inum;
    }
    return inum + 1;
}
*/



int isUsedBlock(unsigned int blockNo);

int getDataBlock(char *dataBlock,struct inode *inodePtr,unsigned long whichBlock){
    unsigned long ourBlockSize = mySuperBlock.s_blocksize;
    unsigned long blockPtrPerBlock = ourBlockSize/sizeof(unsigned int);
    loffset_t directBlocks = 12;
    loffset_t indirectBlocks = directBlocks+blockPtrPerBlock;
    loffset_t doubleBlocks = blockPtrPerBlock*blockPtrPerBlock+indirectBlocks;
    loffset_t tripleBlocks = blockPtrPerBlock*blockPtrPerBlock*blockPtrPerBlock+doubleBlocks;
    char takenBlock1[ourBlockSize];
    char takenBlock2[ourBlockSize];
    char takenBlock3[ourBlockSize];
    char *index1 = takenBlock1;
    char *index2 = takenBlock2;
    char *index3 = takenBlock3;
    unsigned int firstLevelBlockNo;
    unsigned int secondLevelBlockNo;
    unsigned int thirdLevelBlockNo;
    unsigned int temp;
    unsigned int sizeUInt = sizeof(unsigned int);
    if(whichBlock < directBlocks){
        if(!(inodePtr->i_block[whichBlock] &&(inodePtr->i_block[whichBlock] < mySuperBlock.s_blocks_count) && isUsedBlock(inodePtr->i_block[whichBlock]))){
            return 0;
        }
        lseek(myfs.file_descriptor,mySuperBlock.s_blocksize*inodePtr->i_block[whichBlock],SEEK_SET);
        read(myfs.file_descriptor,dataBlock,ourBlockSize);

        //TODO len indirect double veya triplea gecerse
    }
    else if(whichBlock < indirectBlocks){
        whichBlock-=directBlocks;
        if(!(inodePtr->i_block[12] &&(inodePtr->i_block[12] < mySuperBlock.s_blocks_count) && isUsedBlock(inodePtr->i_block[12]))){
            return 0;
        }
        lseek(myfs.file_descriptor,mySuperBlock.s_blocksize*inodePtr->i_block[12],SEEK_SET);
        read(myfs.file_descriptor,takenBlock1,ourBlockSize);
        index1= index1 + sizeUInt*(whichBlock); //alinacak block
        memcpy(&firstLevelBlockNo,index1,sizeUInt); //DATA
        if(!(firstLevelBlockNo &&(firstLevelBlockNo < mySuperBlock.s_blocks_count) && isUsedBlock(firstLevelBlockNo))){
            return 0;
        }
        lseek(myfs.file_descriptor,mySuperBlock.s_blocksize*firstLevelBlockNo,SEEK_SET);
        read(myfs.file_descriptor,dataBlock,ourBlockSize);
    }
    else if(whichBlock < doubleBlocks){
        whichBlock-=indirectBlocks;
        if(!(inodePtr->i_block[13] &&(inodePtr->i_block[13] < mySuperBlock.s_blocks_count) && isUsedBlock(inodePtr->i_block[13]))){
            return 0;
        }
        lseek(myfs.file_descriptor,mySuperBlock.s_blocksize*inodePtr->i_block[13],SEEK_SET);
        read(myfs.file_descriptor,takenBlock1,ourBlockSize);
        temp = (whichBlock/blockPtrPerBlock);
        index1 = index1+temp*sizeUInt;
        memcpy(&firstLevelBlockNo,index1,sizeUInt);
        if(!(firstLevelBlockNo &&(firstLevelBlockNo < mySuperBlock.s_blocks_count) && isUsedBlock(firstLevelBlockNo))){
            return 0;
        }
        lseek(myfs.file_descriptor,mySuperBlock.s_blocksize*firstLevelBlockNo,SEEK_SET);
        read(myfs.file_descriptor,takenBlock2,ourBlockSize);
        index2 = index2 + ((whichBlock % blockPtrPerBlock)*sizeUInt);
        memcpy(&secondLevelBlockNo,index2,sizeUInt);
        if(!(secondLevelBlockNo &&(secondLevelBlockNo < mySuperBlock.s_blocks_count) && isUsedBlock(secondLevelBlockNo))){
            return 0;
        }
        lseek(myfs.file_descriptor,mySuperBlock.s_blocksize*secondLevelBlockNo,SEEK_SET);
        read(myfs.file_descriptor,dataBlock,ourBlockSize);
        //TODO len triple'a gecerse
    }
    else if(whichBlock < tripleBlocks){
        whichBlock-=doubleBlocks;
        if(!(inodePtr->i_block[14] &&(inodePtr->i_block[14] < mySuperBlock.s_blocks_count) && isUsedBlock(inodePtr->i_block[14]))){
            return 0;
        }
        lseek(myfs.file_descriptor,mySuperBlock.s_blocksize*inodePtr->i_block[14],SEEK_SET);
        read(myfs.file_descriptor,takenBlock1,ourBlockSize);
        temp = (whichBlock/(blockPtrPerBlock*blockPtrPerBlock));
        index1 = index1+temp*sizeUInt;
        memcpy(&firstLevelBlockNo,index1,sizeUInt);
        if(!(firstLevelBlockNo &&(firstLevelBlockNo < mySuperBlock.s_blocks_count) && isUsedBlock(firstLevelBlockNo))){
            return 0;
        }
        lseek(myfs.file_descriptor,mySuperBlock.s_blocksize*firstLevelBlockNo,SEEK_SET);
        read(myfs.file_descriptor,takenBlock2,ourBlockSize);
        temp = ((whichBlock % (blockPtrPerBlock*blockPtrPerBlock)) / blockPtrPerBlock);
        index2 = index2+temp*sizeUInt;
        memcpy(&secondLevelBlockNo,index2,sizeUInt);
        if(!(secondLevelBlockNo &&(secondLevelBlockNo < mySuperBlock.s_blocks_count) && isUsedBlock(secondLevelBlockNo))){
            return 0;
        }
        lseek(myfs.file_descriptor,mySuperBlock.s_blocksize*secondLevelBlockNo,SEEK_SET);
        read(myfs.file_descriptor,takenBlock3,ourBlockSize);
        temp = ((whichBlock % (blockPtrPerBlock*blockPtrPerBlock)) % blockPtrPerBlock);
        index3 = index3+temp*sizeUInt;
        memcpy(&thirdLevelBlockNo,index3,sizeUInt);
        if(!(thirdLevelBlockNo &&(thirdLevelBlockNo < mySuperBlock.s_blocks_count) && isUsedBlock(thirdLevelBlockNo))){
            return 0;
        }
        lseek(myfs.file_descriptor,mySuperBlock.s_blocksize*thirdLevelBlockNo,SEEK_SET);
        read(myfs.file_descriptor,dataBlock,ourBlockSize);

    }
    return 1;
}


unsigned int dirSearchInDataBlock(unsigned long blockNo,unsigned int *sizeOfDir,char *givenName,unsigned long *parentInodeNumber){
    char takenBlock[mySuperBlock.s_blocksize];
    char *index = takenBlock;
    char *temp;
    struct ext2_dir_entry tempDirEntry;
    unsigned long currentReadSize = 0;
    //lseek(myfs.file_descriptor,mySuperBlock.s_blocksize*blockNo,SEEK_SET);
    if((blockNo < mySuperBlock.s_blocks_count) && isUsedBlock(blockNo)){
        while(currentReadSize + sizeof(struct ext2_dir_entry)<= mySuperBlock.s_blocksize){ //TODO ?
           if(*sizeOfDir){
               lseek(myfs.file_descriptor,mySuperBlock.s_blocksize*(blockNo),SEEK_SET);
               read(myfs.file_descriptor,takenBlock,mySuperBlock.s_blocksize);
               memcpy(&tempDirEntry,index,sizeof(struct ext2_dir_entry));
               temp = malloc(sizeof(char)*tempDirEntry.name_len+1);
               index+=sizeof(struct ext2_dir_entry);
               memcpy(temp,index,tempDirEntry.name_len);
               temp[tempDirEntry.name_len] = '\0';

               if(strcmp(givenName,temp) == 0){
                   free(temp);
                   return tempDirEntry.inode;
               }
               if(strcmp("..",temp) == 0){
                   *parentInodeNumber = tempDirEntry.inode;
               }
               //*sizeOfDir-=tempDirEntry.rec_len;
               index = index + (tempDirEntry.rec_len-sizeof(struct ext2_dir_entry));
               currentReadSize+=tempDirEntry.rec_len;
               free(temp);
               //lseek(myfs.file_descriptor,tempDirEntry.rec_len-sizeof(struct ext2_dir_entry),SEEK_CUR);
           }
           else{
               return 0;
           }
       }
    }
    currentReadSize = 0;
    *sizeOfDir -= mySuperBlock.s_blocksize;
    return 0;
}

int callForEveryEntry(unsigned long blockNo, unsigned int *sizeOfDir,filldir_t callback){
    char takenBlock[mySuperBlock.s_blocksize];
    char *index = takenBlock;
    struct ext2_dir_entry tempDirEntry;
    int countEntry = 0;
    char *temp;
    unsigned long currentReadSize = 0;
    if((blockNo < mySuperBlock.s_blocks_count) && isUsedBlock(blockNo)){
        lseek(myfs.file_descriptor,mySuperBlock.s_blocksize*(blockNo),SEEK_SET);
        read(myfs.file_descriptor,takenBlock,mySuperBlock.s_blocksize);
        while(currentReadSize + sizeof(struct ext2_dir_entry)<= mySuperBlock.s_blocksize){
           if(*sizeOfDir){
               memcpy(&tempDirEntry,index,sizeof(struct ext2_dir_entry));
               temp = malloc(sizeof(char)*tempDirEntry.name_len+1);
               index+=sizeof(struct ext2_dir_entry);
               memcpy(temp,index,tempDirEntry.name_len);
               temp[tempDirEntry.name_len] = '\0';
               if(tempDirEntry.inode && (tempDirEntry.inode < mySuperBlock.s_blocks_count) && isUsedBlock(tempDirEntry.inode)){
                   callback(temp,tempDirEntry.name_len,tempDirEntry.inode);
                   countEntry++;
               }
               //*sizeOfDir-=tempDirEntry.rec_len;
               currentReadSize+=tempDirEntry.rec_len;
               //lseek(myfs.file_descriptor,tempDirEntry.rec_len-sizeof(struct ext2_dir_entry),SEEK_CUR);
               index = index + (tempDirEntry.rec_len-sizeof(struct ext2_dir_entry));
               free(temp);
           }
           else{
               break;
           }
       }
    }
    *sizeOfDir -= mySuperBlock.s_blocksize;
    currentReadSize = 0; // ? :D
    return countEntry;
}


int isUsedBlock(unsigned int blockNo){ //DOUBLE CHECK
    return 1;
    /*
    unsigned int blockGroup = (blockNo-mySuperBlock.s_first_data_block)/mySuperBlock.s_blocks_per_group;
    struct ext2_group_desc tempGroupDescriptor;
    double x = 1024+sizeof(struct ext2_super_block);
    double y = mySuperBlock.s_blocksize;
    int index = blockNo-mySuperBlock.s_first_data_block;
    unsigned char thatByte;
    off_t groupDescriptorEntryBase = ceil(x/y)*mySuperBlock.s_blocksize;
    lseek(myfs.file_descriptor,groupDescriptorEntryBase+blockGroup*sizeof(struct ext2_group_desc),SEEK_SET);
    read(myfs.file_descriptor,&tempGroupDescriptor,sizeof(struct ext2_group_desc));
    lseek(myfs.file_descriptor,mySuperBlock.s_blocksize*tempGroupDescriptor.bg_block_bitmap,SEEK_SET); //Bitmap blogu
    read(myfs.file_descriptor,&thatByte,1);
    return thatByte & 0x01; */
}

void fillTheInode(struct ext2_inode *inodePtr,unsigned long inodeNumber){
    //mySuperBlock
    struct ext2_group_desc tempGroupDescriptor;
    //struct inode tempInode;
    unsigned int blockGroup = (inodeNumber-1) / mySuperBlock.s_inodes_per_group;
    double x = 1024+sizeof(struct ext2_super_block);
    double y = mySuperBlock.s_blocksize;
    off_t groupDescriptorEntryBase = ceil(x/y)*mySuperBlock.s_blocksize;
    int whichGroup = (inodeNumber -1) /mySuperBlock.s_inodes_per_group;
    int index = (inodeNumber-1) % mySuperBlock.s_inodes_per_group;
    lseek(myfs.file_descriptor,groupDescriptorEntryBase+whichGroup*sizeof(struct ext2_group_desc),SEEK_SET);
    read(myfs.file_descriptor,&tempGroupDescriptor,sizeof(struct ext2_group_desc));
    lseek(myfs.file_descriptor,mySuperBlock.s_blocksize*tempGroupDescriptor.bg_inode_table+index*mySuperBlock.s_inode_size,SEEK_SET);
    read(myfs.file_descriptor,inodePtr,sizeof(struct ext2_inode)); //Inode'u aldikkkkkkkkk
}


void inodeEntryFiller(struct inode *inodePtrEntry,struct ext2_inode *ext2InodePtr,unsigned long inodeNumber){
    inodePtrEntry->i_ino = inodeNumber;
    inodePtrEntry->i_mode = ext2InodePtr->i_mode;
    inodePtrEntry->i_nlink = ext2InodePtr->i_links_count;
    inodePtrEntry->i_uid = ext2InodePtr->i_uid;
    inodePtrEntry->i_gid = ext2InodePtr->i_gid;
    inodePtrEntry->i_size = ext2InodePtr->i_size;
    inodePtrEntry->i_atime = ext2InodePtr->i_atime;
    inodePtrEntry->i_mtime = ext2InodePtr->i_mtime;
    inodePtrEntry->i_ctime = ext2InodePtr->i_ctime;
    inodePtrEntry->i_blocks = ext2InodePtr->i_blocks/(mySuperBlock.s_blocksize/512);
    for(int i=0;i<15;i++){
        inodePtrEntry->i_block[i] = ext2InodePtr->i_block[i];
    }
    inodePtrEntry->i_op = &i_op;
    inodePtrEntry->f_op = &f_op;
    inodePtrEntry->i_sb = &mySuperBlock;
    inodePtrEntry->i_state = 0; //TODO
    inodePtrEntry->i_flags = ext2InodePtr->i_mode& 0x00000FFF;
}


void fillTheDentryPtr(struct dentry *dentryPtr,unsigned long inodeNumber,unsigned long parentInodeNumber){
    struct ext2_inode tempInode;
    fillTheInode(&tempInode,inodeNumber);
    dentryPtr->d_flags = tempInode.i_mode & 0x00000FFF;
    dentryPtr->d_inode = malloc(sizeof(struct inode));
    inodeEntryFiller(dentryPtr->d_inode,&tempInode,inodeNumber);
    dentryPtr->d_sb =&mySuperBlock; //DEBUG BURDA KALDIM
    dentryPtr->d_fsdata = NULL;
    //Parent ?
}


char *getLinkValue(struct inode *inodePtr){
        char *buf = malloc(sizeof(char)*inodePtr->i_size+1);
        unsigned long sizeOfLink= inodePtr->i_size;
        buf[inodePtr->i_size] = '\0';
        unsigned long ourBlockSize = mySuperBlock.s_blocksize;
        ssize_t returnLen = 0;
        size_t indexOfCursor = 0;
        if(inodePtr->i_size <= sizeof(unsigned int)*15){
            int i=0;
            char *cursor = (char *) inodePtr->i_block;
            while(*cursor != EOF && sizeOfLink != 0){
                buf[returnLen] = cursor[i];
                returnLen++;
                i++;
                sizeOfLink--;
            }
            return buf;
        }
        else{
            unsigned int whichBlock = 0;
            unsigned int blockOffset =0;
            char dataBlock[ourBlockSize];
            char *dataBlockCursor = dataBlock;
            char *bufCursor = buf;
            unsigned int readCount;
            ssize_t returnLen = 0;
            size_t indexOfCursor = 0;
            if(sizeOfLink+blockOffset <= ourBlockSize){
                if(getDataBlock(dataBlock,inodePtr,whichBlock) == 0){
                    //filePtr->f_pos=*offset+returnLen;
                    return buf;
                }
                dataBlockCursor+=(blockOffset);
                //memcpy(buf,dataBlockCursor,len);
                while(*dataBlockCursor != EOF && sizeOfLink != 0){
                    bufCursor[returnLen] = *dataBlockCursor;
                    dataBlockCursor++;
                    returnLen++;
                    sizeOfLink--;
                }
                return buf;
            }
            else{
                unsigned long howManyBlockWeRead = (sizeOfLink - (ourBlockSize-blockOffset)) / ourBlockSize;
                howManyBlockWeRead++; //Double CHECK
                unsigned int readLengthFromLastBlock = (sizeOfLink - (ourBlockSize-blockOffset)) % ourBlockSize;
                if(getDataBlock(dataBlock,inodePtr,whichBlock) == 0){
                    //filePtr->f_pos=*offset+returnLen;
                    return buf;
                }
                dataBlockCursor+=(blockOffset);
                readCount = readCount-blockOffset;
                while(*dataBlockCursor != EOF && readCount != 0){
                    bufCursor[returnLen] = *dataBlockCursor;
                    dataBlockCursor++;
                    returnLen++;
                    readCount--;
                }
                if(*dataBlockCursor == EOF){
                    return buf;
                }
                whichBlock++;
                dataBlockCursor = dataBlock;
                while(howManyBlockWeRead--){
                    if(howManyBlockWeRead == 0){
                        if(getDataBlock(dataBlock,inodePtr,whichBlock) == 0){
                            return buf;
                        }
                        dataBlockCursor = dataBlock;
                        readCount = readLengthFromLastBlock;
                        while(*dataBlockCursor != EOF && readCount != 0){
                            bufCursor[returnLen] = *dataBlockCursor;
                            dataBlockCursor++;
                            readCount--;
                        }
                        return buf;
                    }
                    else{
                        if(getDataBlock(dataBlock,inodePtr,whichBlock) == 0){
                            return buf;
                        }
                        dataBlockCursor = dataBlock;
                        readCount = blockOffset;
                        while(*dataBlockCursor != EOF && readCount != 0){
                            bufCursor[returnLen] = *dataBlockCursor;
                            dataBlockCursor++;
                            returnLen++;
                            readCount--;
                        }
                        if(*dataBlockCursor == EOF){
                            return buf;
                        }
                        whichBlock++;
                    }
                }
            }
        }
}


struct super_block *allocate_superblock(struct file_system_type *fs){
    //This function allocates and fills the fields of the superblock of the file system fs returning a pointer to the
    //allocated struct super_block .
    struct ext2_super_block tempSuperBlock;
    struct ext2_inode tempRootInode;
    lseek(fs->file_descriptor,BASE_OFFSET,SEEK_SET);
    read(fs->file_descriptor,&tempSuperBlock,sizeof(struct ext2_super_block));
    //struct super_block *superblockPtr = malloc(sizeof(struct super_block));
    int logblocksize = tempSuperBlock.s_log_block_size+10;
    unsigned int numberOfPointersInBlock;
    unsigned long blockSize = 1;
    mySuperBlock.s_inodes_count = tempSuperBlock.s_inodes_count;
    mySuperBlock.s_blocks_count = tempSuperBlock.s_blocks_count;
    mySuperBlock.s_free_blocks_count = tempSuperBlock.s_free_blocks_count;
    mySuperBlock.s_free_inodes_count = tempSuperBlock.s_free_inodes_count;
    mySuperBlock.s_first_data_block = tempSuperBlock.s_first_data_block;
    for(int i=0;i<logblocksize;i++){
        blockSize *= 2;
    }
    mySuperBlock.s_blocksize = blockSize;
    mySuperBlock.s_blocksize_bits = logblocksize;
    mySuperBlock.s_blocks_per_group = tempSuperBlock.s_blocks_per_group;
    mySuperBlock.s_inodes_per_group = tempSuperBlock.s_inodes_per_group;
    mySuperBlock.s_minor_rev_level = tempSuperBlock.s_minor_rev_level;
    mySuperBlock.s_rev_level = tempSuperBlock.s_rev_level;
    mySuperBlock.s_first_ino = tempSuperBlock.s_first_ino;
    mySuperBlock.s_inode_size = tempSuperBlock.s_inode_size;
    mySuperBlock.s_block_group_nr = tempSuperBlock.s_block_group_nr;
    numberOfPointersInBlock = blockSize/4;
    mySuperBlock.s_maxbytes= blockSize*12+ numberOfPointersInBlock*blockSize + numberOfPointersInBlock*numberOfPointersInBlock*blockSize + numberOfPointersInBlock*numberOfPointersInBlock*numberOfPointersInBlock*blockSize;
    mySuperBlock.s_type = &myfs;
    mySuperBlock.s_op = &s_op;
    mySuperBlock.s_flags = 0; //TODO
    mySuperBlock.s_magic = tempSuperBlock.s_magic; // TODO ?
    //Root entry
    fillTheInode(&tempRootInode,EXT2_ROOT_INO);
    /*
        Root Inode Fill
    */
    rootInode.i_ino = EXT2_ROOT_INO;
    rootInode.i_mode = tempRootInode.i_mode;
    rootInode.i_nlink = tempRootInode.i_links_count;
    rootInode.i_uid = tempRootInode.i_uid;
    rootInode.i_gid = tempRootInode.i_gid;
    rootInode.i_size = tempRootInode.i_size;
    rootInode.i_atime = tempRootInode.i_atime;
    rootInode.i_mtime = tempRootInode.i_mtime;
    rootInode.i_ctime = tempRootInode.i_ctime;
    rootInode.i_blocks = tempRootInode.i_blocks/(mySuperBlock.s_blocksize/512); //TODO
    for(int i=0;i<15;i++){
        rootInode.i_block[i] = tempRootInode.i_block[i];
    }
    rootInode.i_op = &i_op;
    rootInode.f_op = &f_op;
    rootInode.i_sb = &mySuperBlock;
    rootInode.i_state = 0; //TODO
    rootInode.i_flags = tempRootInode.i_mode & 0x00000FFF;
    char *temp = malloc(2*sizeof(char));
    temp[0] = '/';
    temp[1] = '\0';
    rootEntry.d_name = temp;
    rootEntry.d_flags = tempRootInode.i_mode & 0x00000FFF; //TODO
    rootEntry.d_parent = &rootEntry;
    rootEntry.d_sb = &mySuperBlock;
    rootEntry.d_fsdata = NULL; //TODO
    rootEntry.d_inode = &rootInode;
    mySuperBlock.s_root = &rootEntry;
    mySuperBlock.s_fs_info = NULL; //TODO
    return &mySuperBlock;
}

/* Implement functions in s_op, i_op, f_op here */
void readInode(struct inode *inodePtr){
    //This function assumes that only the inode number field ( i_ino ) of the
    //passed in inode i is valid and the fucntion reads and populates the remaining fields of i .
    if(inodePtr != NULL){
        struct ext2_inode inodeTemp;
        fillTheInode(&inodeTemp,inodePtr->i_ino);
        inodePtr->i_mode = inodeTemp.i_mode;
        inodePtr->i_nlink = inodeTemp.i_links_count;
        inodePtr->i_uid = inodeTemp.i_uid;
        inodePtr->i_gid = inodeTemp.i_gid;
        inodePtr->i_size = inodeTemp.i_size;
        inodePtr->i_atime = inodeTemp.i_atime;
        inodePtr->i_mtime = inodeTemp.i_mtime;
        inodePtr->i_ctime = inodeTemp.i_ctime;
        inodePtr->i_blocks = inodeTemp.i_blocks/(mySuperBlock.s_blocksize/512); //TODO
        for(int i=0;i<15;i++){
            inodePtr->i_block[i] = inodeTemp.i_block[i];
        }
        inodePtr->i_op = &i_op;
        inodePtr->f_op = &f_op;
        inodePtr->i_sb = &mySuperBlock;
        inodePtr->i_state = 0; //TODO
        inodePtr->i_flags = inodeTemp.i_mode & 0x00000FFF;
    }
}


int myStatfs(struct super_block *super_blockPtr, struct kstatfs *kstatfsPtr){
    //This function fills in the fields of kstatfs struct stats with the information from the superblock sb .
    //Returns zero for successful operations.
    if(super_blockPtr != NULL && kstatfsPtr != NULL){
        kstatfsPtr->name = fs_name;
        kstatfsPtr->f_magic = super_blockPtr->s_magic;
        kstatfsPtr->f_bsize = super_blockPtr->s_blocksize;
        kstatfsPtr->f_blocks = super_blockPtr->s_blocks_count; //TODO
        kstatfsPtr->f_bfree = super_blockPtr->s_free_blocks_count;
        kstatfsPtr->f_inodes = super_blockPtr->s_inodes_count;
        kstatfsPtr->f_finodes = super_blockPtr->s_free_inodes_count;
        kstatfsPtr->f_inode_size = super_blockPtr->s_inode_size;
        kstatfsPtr->f_minor_rev_level = super_blockPtr->s_minor_rev_level;
        kstatfsPtr->f_rev_level = super_blockPtr->s_rev_level;
        kstatfsPtr->f_namelen = strlen(fs_name);
        return 0;
    }
    return -1;
}

struct dentry *myLookup(struct inode *inodePtr,struct dentry *dentryPtr){
     //This function assumes that only the name field ( d_name ) of the directory entry dir is valid and
     //searches for it in the directory pointed by inode i . If a matching directory entry is found, it
     //fills the rest of the directory entry dir . It returns the pointer to the filled directory entry.

     if(inodePtr != NULL && dentryPtr != NULL && S_ISDIR(inodePtr->i_mode)){ //TODO CHECK
         //Okumak
         char takenBlock1[mySuperBlock.s_blocksize];
         char takenBlock2[mySuperBlock.s_blocksize];
         char takenBlock3[mySuperBlock.s_blocksize];
         unsigned int sizeOfDir = inodePtr->i_size;
         unsigned long blocksMany = inodePtr->i_blocks;
         unsigned long ourBlockSize = mySuperBlock.s_blocksize;
         unsigned long parentInodeNumber = -1;
         unsigned int dataBlockIndex;
         unsigned int dataBlockDoubleIndex;
         unsigned int dataBlockTripleIndex;
         unsigned int sizeUInt = sizeof(unsigned int);
         char *index1 = takenBlock1;
         char *index2 = takenBlock2;
         char *index3 = takenBlock3;
         unsigned long inodeNo;
         for(int i=0;i<12;i++){
             //if(blocksMany){
                 if(inodePtr->i_block[i] &&(inodePtr->i_block[i] < mySuperBlock.s_blocks_count) && isUsedBlock(inodePtr->i_block[i])){
                     if((inodeNo = dirSearchInDataBlock(inodePtr->i_block[i],&sizeOfDir,dentryPtr->d_name,&parentInodeNumber))){
                         //we found
                         fillTheDentryPtr(dentryPtr,inodeNo,parentInodeNumber); //parent hep dolu mu ?
                         return dentryPtr;
                     }
                     blocksMany--;
                     if(sizeOfDir == 0){
                         return NULL;
                     }
                 }
             /*}
             else{
                 return NULL;
             }*/
         }
         index1 = takenBlock1;
         index2 = takenBlock2;
         index3 = takenBlock3;
         //INDIRECT - FIXED
         if(inodePtr->i_block[12] &&(inodePtr->i_block[12] < mySuperBlock.s_blocks_count) && isUsedBlock(inodePtr->i_block[12])){
         lseek(myfs.file_descriptor,mySuperBlock.s_blocksize*inodePtr->i_block[12],SEEK_SET);
         read(myfs.file_descriptor,takenBlock1,ourBlockSize);
         for(int i=0;i<mySuperBlock.s_blocksize;i+=sizeUInt){
             memcpy(&dataBlockIndex,index1,sizeUInt);
             index1+=sizeUInt;
             //if(blocksMany){
                 if(dataBlockIndex&&(dataBlockIndex< mySuperBlock.s_blocks_count) && isUsedBlock(dataBlockIndex)){
                     if((inodeNo = dirSearchInDataBlock(dataBlockIndex,&sizeOfDir,dentryPtr->d_name,&parentInodeNumber))){
                         //we found
                         fillTheDentryPtr(dentryPtr,inodeNo,parentInodeNumber); //parent hep dolu mu ? //CHECK
                         return dentryPtr;
                     }
                     if(sizeOfDir == 0){
                         return NULL;
                     }
                     blocksMany--;
                 }
            /* }
             else{
                 return NULL;
             } */
         }
     }
     index1 = takenBlock1;
     index2 = takenBlock2;
     index3 = takenBlock3;
     if(inodePtr->i_block[13] &&(inodePtr->i_block[13] < mySuperBlock.s_blocks_count) && isUsedBlock(inodePtr->i_block[13])){

         //DOUBLE
         //lseek(myfs.file_descriptor,mySuperBlock.s_blocksize*inodePtr->i_block[13],SEEK_SET);
         lseek(myfs.file_descriptor,mySuperBlock.s_blocksize*inodePtr->i_block[13],SEEK_SET);
         read(myfs.file_descriptor,takenBlock1,ourBlockSize);
         for(int i=0;i<mySuperBlock.s_blocksize;i+=sizeUInt){
             memcpy(&dataBlockDoubleIndex,index1,sizeUInt);
             index1+=sizeUInt;
             if(dataBlockDoubleIndex &&(dataBlockDoubleIndex< mySuperBlock.s_blocks_count) && isUsedBlock(dataBlockDoubleIndex)){
                 lseek(myfs.file_descriptor,mySuperBlock.s_blocksize*dataBlockDoubleIndex,SEEK_SET);
                 read(myfs.file_descriptor,&takenBlock2,ourBlockSize);
                 for(int j=0;j<mySuperBlock.s_blocksize;j+=sizeUInt){
                     memcpy(&dataBlockIndex,index2,sizeUInt);
                     index2+=sizeUInt;
                     //if(blocksMany){
                         if(dataBlockIndex&&(dataBlockIndex< mySuperBlock.s_blocks_count) && isUsedBlock(dataBlockIndex)){
                             if((inodeNo = dirSearchInDataBlock(dataBlockIndex,&sizeOfDir,dentryPtr->d_name,&parentInodeNumber))){
                                 //we found
                                 fillTheDentryPtr(dentryPtr,inodeNo,parentInodeNumber); //parent hep dolu mu ?
                                 return dentryPtr;
                             }
                             if(sizeOfDir == 0){
                                 return NULL;
                             }
                             blocksMany--;
                         }
                    /* }
                     else{
                         return NULL;
                     }*/
                 }
                 index2 = takenBlock2;
             }
         }
     }
     index1 = takenBlock1;
     index2 = takenBlock2;
     index3 = takenBlock3;
if(inodePtr->i_block[14] &&(inodePtr->i_block[14] < mySuperBlock.s_blocks_count) && isUsedBlock(inodePtr->i_block[14])){
         //TRIPLE
         lseek(myfs.file_descriptor,mySuperBlock.s_blocksize*inodePtr->i_block[14],SEEK_SET);
         read(myfs.file_descriptor,takenBlock1,ourBlockSize);
         for(int z=0;z<mySuperBlock.s_blocksize;z+=sizeUInt){
             memcpy(&dataBlockTripleIndex,index1,sizeUInt);
             index1+=sizeUInt;
             if(dataBlockTripleIndex&&(dataBlockTripleIndex< mySuperBlock.s_blocks_count) && isUsedBlock(dataBlockTripleIndex)){
                 lseek(myfs.file_descriptor,mySuperBlock.s_blocksize*dataBlockTripleIndex,SEEK_SET);
                 read(myfs.file_descriptor,takenBlock2,ourBlockSize);
                 for(int i=0;i<mySuperBlock.s_blocksize;i+=sizeUInt){
                     memcpy(&dataBlockDoubleIndex,index2,sizeUInt);
                     index2+=sizeUInt;
                     if(dataBlockDoubleIndex&&(dataBlockDoubleIndex< mySuperBlock.s_blocks_count) && isUsedBlock(dataBlockDoubleIndex)){
                         lseek(myfs.file_descriptor,mySuperBlock.s_blocksize*dataBlockDoubleIndex,SEEK_SET);
                         read(myfs.file_descriptor,takenBlock3,ourBlockSize);
                         for(int j=0;j<mySuperBlock.s_blocksize;j+=sizeUInt){
                             memcpy(&dataBlockIndex,index3,sizeUInt);
                             index3+=sizeUInt;
                             //if(blocksMany){
                                 if(dataBlockIndex&&(dataBlockIndex< mySuperBlock.s_blocks_count) && isUsedBlock(dataBlockIndex)){
                                     if((inodeNo = dirSearchInDataBlock(dataBlockIndex,&sizeOfDir,dentryPtr->d_name,&parentInodeNumber))){
                                         //we found
                                         fillTheDentryPtr(dentryPtr,inodeNo,parentInodeNumber); //parent hep dolu mu ?
                                         return dentryPtr;
                                     }
                                     if(sizeOfDir == 0){
                                         return NULL;
                                     }
                                     blocksMany--;
                                 }
                        /*     }
                             else{
                                 return NULL;
                             }*/
                         }
                         index3 = takenBlock3;
                     }
                 }
                 index2 = takenBlock2;
             }
         }
     }
     }
     return NULL;
}

int myReadLink(struct dentry *dentryPtr, char *buf, int len){
    //This function reads the contents of the link in dir into the buffer buf provided by the user.
    //The read operation reads len bytes and returns the number of bytes read.
    if(dentryPtr != NULL && buf != NULL){
        struct inode *inodePtr = dentryPtr->d_inode;
        int len2 = len;
        if(!S_ISLNK(inodePtr->i_mode)){
            return -1;
        }
        unsigned long ourBlockSize = mySuperBlock.s_blocksize;
        if(inodePtr->i_size <= sizeof(unsigned int)*15){
            ssize_t returnLen = 0;
            int i=0;
            char *cursor = (char *) inodePtr->i_block;
            while(*cursor != EOF && len != 0){
                buf[returnLen] = cursor[i];
                returnLen++;
                len--;
                i++;
                if(len2 == returnLen){
                    return returnLen;
                }
            }
            return returnLen;
        }
        else{
            unsigned int whichBlock = 0;
            unsigned int blockOffset =0;
            char dataBlock[ourBlockSize];
            char *dataBlockCursor = dataBlock;
            char *bufCursor = buf;
            unsigned int readCount;
            ssize_t returnLen = 0;
            size_t indexOfCursor = 0;
            if(len+blockOffset <= ourBlockSize){
                if(getDataBlock(dataBlock,inodePtr,whichBlock) == 0){
                    //filePtr->f_pos=*offset+returnLen;
                    return returnLen;
                }
                dataBlockCursor+=(blockOffset);
                //memcpy(buf,dataBlockCursor,len);
                while(*dataBlockCursor != EOF && len != 0){
                    bufCursor[returnLen] = *dataBlockCursor;
                    dataBlockCursor++;
                    returnLen++;
                    len--;
                    if(len2 == returnLen){
                        return returnLen;
                    }
                }
                return returnLen;
            }
            else{
                unsigned long howManyBlockWeRead = (len - (ourBlockSize-blockOffset)) / ourBlockSize;
                howManyBlockWeRead++; //Double CHECK
                unsigned int readLengthFromLastBlock = (len - (ourBlockSize-blockOffset)) % ourBlockSize;
                if(getDataBlock(dataBlock,inodePtr,whichBlock) == 0){
                    //filePtr->f_pos=*offset+returnLen;
                    return returnLen;
                }
                dataBlockCursor+=(blockOffset);
                readCount = readCount-blockOffset;
                while(*dataBlockCursor != EOF && readCount != 0){
                    bufCursor[returnLen] = *dataBlockCursor;
                    dataBlockCursor++;
                    returnLen++;
                    readCount--;
                    if(len2 == returnLen){
                        return returnLen;
                    }
                }
                if(*dataBlockCursor == EOF){
                    return returnLen;
                }
                whichBlock++;
                dataBlockCursor = dataBlock;
                while(howManyBlockWeRead--){
                    if(howManyBlockWeRead == 0){
                        if(getDataBlock(dataBlock,inodePtr,whichBlock) == 0){
                            return returnLen;
                        }
                        dataBlockCursor = dataBlock;
                        readCount = readLengthFromLastBlock;
                        while(*dataBlockCursor != EOF && readCount != 0){
                            bufCursor[returnLen] = *dataBlockCursor;
                            dataBlockCursor++;
                            returnLen++;
                            readCount--;
                            if(len2 == returnLen){
                                return returnLen;
                            }
                        }
                        return returnLen;
                    }
                    else{
                        if(getDataBlock(dataBlock,inodePtr,whichBlock) == 0){
                            return returnLen;
                        }
                        dataBlockCursor = dataBlock;
                        readCount = blockOffset;
                        while(*dataBlockCursor != EOF && readCount != 0){
                            bufCursor[returnLen] = *dataBlockCursor;
                            dataBlockCursor++;
                            returnLen++;
                            readCount--;
                            if(len2 == returnLen){
                                return returnLen;
                            }
                        }
                        if(*dataBlockCursor == EOF){
                            return returnLen;
                        }
                        whichBlock++;
                    }
                }
            }
        }
    }
    return -1;
}

int myReadDir(struct inode *inodePtr, filldir_t callback){
    //This function calls the callback for every directory entry in inode i . It returns the total number
    //of entries in the directory.
    if(inodePtr != NULL && callback != NULL && S_ISDIR(inodePtr->i_mode)){
    char takenBlock1[mySuperBlock.s_blocksize];
    char takenBlock2[mySuperBlock.s_blocksize];
    char takenBlock3[mySuperBlock.s_blocksize];
    struct ext2_dir_entry tempDirEntry;
    unsigned int sizeOfDir = inodePtr->i_size;
    unsigned long blocksMany = inodePtr->i_blocks;
    unsigned long ourBlockSize = mySuperBlock.s_blocksize;
    unsigned int dataBlockIndex;
    unsigned int dataBlockDoubleIndex;
    unsigned int dataBlockTripleIndex;
    unsigned int sizeUInt = sizeof(unsigned int);
    int totalEntry = 0;
    int retEntry = 0;
    char *index1 = takenBlock1;
    char *index2 = takenBlock2;
    char *index3 = takenBlock3;
    for(int i=0;i<12;i++){
        //if(blocksMany){
            if(inodePtr->i_block[i]&&(inodePtr->i_block[i] < mySuperBlock.s_blocks_count) && isUsedBlock(inodePtr->i_block[i])){
                retEntry = callForEveryEntry(inodePtr->i_block[i],&sizeOfDir,callback);
                totalEntry+=retEntry;
                blocksMany--;
                if(sizeOfDir == 0){
                    return totalEntry;
                }
            }
        /*}
        else{
            return totalEntry;
        } */
    }
    index1 = takenBlock1;
    index2 = takenBlock2;
    index3 = takenBlock3;
    if(inodePtr->i_block[12]&&(inodePtr->i_block[12] < mySuperBlock.s_blocks_count) && isUsedBlock(inodePtr->i_block[12])){
    //INDIRECT
    lseek(myfs.file_descriptor,mySuperBlock.s_blocksize*inodePtr->i_block[12],SEEK_SET);
    read(myfs.file_descriptor,takenBlock1,ourBlockSize);
    for(int i=0;i<mySuperBlock.s_blocksize;i+=4){
        memcpy(&dataBlockIndex,index1,sizeUInt);
        index1+=sizeUInt;
        //if(blocksMany){
            if(dataBlockIndex&&(dataBlockIndex< mySuperBlock.s_blocks_count) && isUsedBlock(dataBlockIndex)){
                retEntry = callForEveryEntry(dataBlockIndex,&sizeOfDir,callback);
                totalEntry+=retEntry;
                blocksMany--;
                if(sizeOfDir == 0){
                    return totalEntry;
                }
            }
        /*}
        else{
            return totalEntry;
        }*/
    }
}
index1 = takenBlock1;
index2 = takenBlock2;
index3 = takenBlock3;
if(inodePtr->i_block[13]&&(inodePtr->i_block[13] < mySuperBlock.s_blocks_count) && isUsedBlock(inodePtr->i_block[13])){
    //DOUBLE
    lseek(myfs.file_descriptor,mySuperBlock.s_blocksize*inodePtr->i_block[13],SEEK_SET);
    read(myfs.file_descriptor,takenBlock1,ourBlockSize);
    for(int i=0;i<mySuperBlock.s_blocksize;i+=sizeUInt){
        memcpy(&dataBlockDoubleIndex,index1,sizeUInt);
        index1+=sizeUInt;
        if(dataBlockDoubleIndex&&(dataBlockDoubleIndex< mySuperBlock.s_blocks_count) && isUsedBlock(dataBlockDoubleIndex)){
            lseek(myfs.file_descriptor,mySuperBlock.s_blocksize*dataBlockDoubleIndex,SEEK_SET);
            read(myfs.file_descriptor,&takenBlock2,ourBlockSize);
            for(int j=0;j<mySuperBlock.s_blocksize;j+=sizeUInt){
                memcpy(&dataBlockIndex,index2,sizeUInt);
                index2+=sizeUInt;
                //if(blocksMany){
                    if(dataBlockIndex&&(dataBlockIndex< mySuperBlock.s_blocks_count) && isUsedBlock(dataBlockIndex)){
                        retEntry = callForEveryEntry(dataBlockIndex,&sizeOfDir,callback);
                        totalEntry+=retEntry;
                        blocksMany--;
                        if(sizeOfDir == 0){
                            return totalEntry;
                        }
                    }
            /*    }
                else{
                    return totalEntry;
                }*/
            }
            index2 = takenBlock2;
        }
    }
}
index1 = takenBlock1;
index2 = takenBlock2;
index3 = takenBlock3;
if(inodePtr->i_block[14]&&(inodePtr->i_block[14] < mySuperBlock.s_blocks_count) && isUsedBlock(inodePtr->i_block[14])){
    //TRIPLE
    lseek(myfs.file_descriptor,mySuperBlock.s_blocksize*inodePtr->i_block[14],SEEK_SET);
    read(myfs.file_descriptor,takenBlock1,ourBlockSize);
    for(int z=0;z<mySuperBlock.s_blocksize;z+=sizeUInt){
        memcpy(&dataBlockTripleIndex,index1,sizeUInt);
        index1+=sizeUInt;
        if(dataBlockTripleIndex&&(dataBlockTripleIndex< mySuperBlock.s_blocks_count) && isUsedBlock(dataBlockTripleIndex)){
            lseek(myfs.file_descriptor,mySuperBlock.s_blocksize*dataBlockTripleIndex,SEEK_SET);
            read(myfs.file_descriptor,takenBlock2,ourBlockSize);
            for(int i=0;i<mySuperBlock.s_blocksize;i+=sizeUInt){
                memcpy(&dataBlockDoubleIndex,index2,sizeUInt);
                index2+=sizeUInt;
                if(dataBlockDoubleIndex&&(dataBlockDoubleIndex< mySuperBlock.s_blocks_count) && isUsedBlock(dataBlockDoubleIndex)){
                    lseek(myfs.file_descriptor,mySuperBlock.s_blocksize*dataBlockDoubleIndex,SEEK_SET);
                    read(myfs.file_descriptor,takenBlock3,ourBlockSize);
                    for(int j=0;j<mySuperBlock.s_blocksize;j+=4){
                        memcpy(&dataBlockIndex,index3,sizeUInt);
                        index3+=sizeUInt;
                        //if(blocksMany){
                            if(dataBlockIndex&&(dataBlockIndex< mySuperBlock.s_blocks_count) && isUsedBlock(dataBlockIndex)){
                                retEntry = callForEveryEntry(dataBlockIndex,&sizeOfDir,callback);
                                totalEntry+=retEntry;
                                blocksMany--;
                                if(sizeOfDir == 0){
                                    return totalEntry;
                                }
                            }
                    /*    }
                        else{
                            return totalEntry;
                        }*/
                    }
                    index3 = takenBlock3;
                }
            }
            index2 = takenBlock2;
        }
    }
}
    return totalEntry;
}
return 0;
}

int myGetattr(struct dentry *dentryPtr, struct kstat *kstatPtr){
    //This function fills in the fields of kstat structure, stats with the information from the object
    //pointed by the directory entry dir . It returns zero for successful operation.
    if(dentryPtr != NULL && kstatPtr != NULL){
        struct inode *inodeTemp = dentryPtr->d_inode;
        kstatPtr->ino = inodeTemp->i_ino;
        kstatPtr->mode = inodeTemp->i_mode;
        kstatPtr->nlink = inodeTemp->i_nlink;
        kstatPtr->uid = inodeTemp->i_uid;
        kstatPtr->gid = inodeTemp->i_gid;
        kstatPtr->size = inodeTemp->i_size;
        kstatPtr->atime = inodeTemp->i_atime;
        kstatPtr->mtime = inodeTemp->i_mtime;
        kstatPtr->ctime = inodeTemp->i_ctime;
        kstatPtr->blksize = mySuperBlock.s_blocksize;
        kstatPtr->blocks = inodeTemp->i_blocks;
        return 0;
    }
    return -1;
}

loffset_t myLlseek(struct file *filePtr,loffset_t offset, int whence){
    //This function repositions the offset of the file f to o bytes relative to the beginning of the file,
    //the current file offset, or the end of the file, depending on whether whence is SEEK_SET, SEEK_CUR, or SEEK_END ,
    //respectively. It returns the resulting file position in the argument result.
    //offset sizedan buyuk olabılır mı ?
    if(whence == SEEK_SET){
        if(offset > filePtr->f_inode->i_size){
            filePtr->f_pos = filePtr->f_inode->i_size;
        }
        else if(offset < 0){
            filePtr->f_pos = 0;
        }
        else{
            filePtr->f_pos = offset;
        }
    }
    else if(whence == SEEK_CUR){
        if(offset+filePtr->f_pos >filePtr->f_inode->i_size ){
            filePtr->f_pos = filePtr->f_inode->i_size;
        }
        else if(offset + filePtr->f_pos < 0 ){
            filePtr->f_pos = 0;
        }
        else{
            filePtr->f_pos = filePtr->f_pos +  offset;
        }
    }
    else if(whence == SEEK_END){
        struct inode *tempInode = filePtr->f_inode;
        loffset_t sizeOfFile = tempInode->i_size;
        if(offset>0){
            filePtr->f_pos = filePtr->f_inode->i_size;
        }
        else if( offset+sizeOfFile < 0){
            filePtr->f_pos = 0;
        }
        else {
            filePtr->f_pos = sizeOfFile + offset;
        }
    }
    return filePtr->f_pos;
}

ssize_t myRead(struct file *filePtr, char *buf, size_t len, loffset_t *offset1){
    //This function reads the contents of file f into the buffer buf provided by the user. The read operation starts
    //from the o byte of the file and reads len bytes. It returns the number of bytes read.
    if(filePtr != NULL && buf != NULL && len != 0){
        //filePtr->
        loffset_t dummy = 0;
        loffset_t *offset;
        if(offset1 == NULL){
            dummy = filePtr->f_pos;
            offset = &dummy;
        }
        else{
            offset = offset1;
        }
        if(*offset < 0){
            return 0;
        }
        struct inode *inodePtr = filePtr->f_inode;
        unsigned long ourBlockSize = mySuperBlock.s_blocksize;
        unsigned int whichBlock = (*(offset)/ourBlockSize);
        unsigned int blockOffset =(*(offset)%ourBlockSize);
        char dataBlock[ourBlockSize];
        char *dataBlockCursor = dataBlock;
        char *bufCursor = buf;
        unsigned int readCount;
        ssize_t returnLen = 0;
        size_t indexOfCursor = 0;
        if(len+blockOffset <= ourBlockSize){
            if(getDataBlock(dataBlock,inodePtr,whichBlock) == 0){
                //filePtr->f_pos=*offset+returnLen;
                return returnLen;
            }
            dataBlockCursor+=(blockOffset);
            //memcpy(buf,dataBlockCursor,len);
            while(*dataBlockCursor != EOF && len != 0){
                bufCursor[returnLen] = *dataBlockCursor;
                dataBlockCursor++;
                returnLen++;
                len--;
            }
            filePtr->f_pos=*offset+returnLen;
            return returnLen;
        }
        else{
            unsigned long howManyBlockWeRead = (len - (ourBlockSize-blockOffset)) / ourBlockSize;
            howManyBlockWeRead++; //Double CHECK
            unsigned int readLengthFromLastBlock = (len - (ourBlockSize-blockOffset)) % ourBlockSize;
            if(getDataBlock(dataBlock,inodePtr,whichBlock) == 0){
                //filePtr->f_pos=*offset+returnLen;
                return returnLen;
            }
            dataBlockCursor+=(blockOffset);
            readCount = readCount-blockOffset;
            while(*dataBlockCursor != EOF && readCount != 0){
                bufCursor[returnLen] = *dataBlockCursor;
                dataBlockCursor++;
                returnLen++;
                readCount--;
            }
            if(*dataBlockCursor == EOF){
                filePtr->f_pos=*offset+returnLen;
                return returnLen;
            }
            whichBlock++;
            dataBlockCursor = dataBlock;
            while(howManyBlockWeRead--){
                if(howManyBlockWeRead == 0){
                    if(getDataBlock(dataBlock,inodePtr,whichBlock) == 0){
                        filePtr->f_pos=*offset+returnLen;
                        return returnLen;
                    }
                    dataBlockCursor = dataBlock;
                    readCount = readLengthFromLastBlock;
                    while(*dataBlockCursor != EOF && readCount != 0){
                        bufCursor[returnLen] = *dataBlockCursor;
                        dataBlockCursor++;
                        returnLen++;
                        readCount--;
                    }
                    filePtr->f_pos=*offset+returnLen;
                    return returnLen;
                }
                else{
                    if(getDataBlock(dataBlock,inodePtr,whichBlock) == 0){
                        return returnLen;
                    }
                    dataBlockCursor = dataBlock;
                    readCount = blockOffset;
                    while(*dataBlockCursor != EOF && readCount != 0){
                        bufCursor[returnLen] = *dataBlockCursor;
                        dataBlockCursor++;
                        returnLen++;
                        readCount--;
                    }
                    if(*dataBlockCursor == EOF){
                        filePtr->f_pos=*offset+returnLen;
                        return returnLen;
                    }
                    whichBlock++;
                }
            }
        }
    }
    return 0;
}

int myOpen(struct inode *inodePtr, struct file *filePtr){
    //This function reads the file pointed by inode i and fills the file struct f . It returns zero for successful operation.
    if(inodePtr != NULL && filePtr != NULL && !S_ISDIR(inodePtr->i_mode)){
        //Need Path
        while(S_ISLNK(inodePtr->i_mode)){
            //GARBAGE COLLECTION
            char *path = getLinkValue(inodePtr);
            struct dentry *dir = pathwalk(path);
            if (!dir) {
              return -1;
            }
            free(inodePtr);
            inodePtr = dir->d_inode; //inodeu set edildi
            free(dir);
        }
        filePtr->f_inode = inodePtr;
        filePtr->f_op = &f_op;
        filePtr->f_flags = inodePtr->i_flags;
        filePtr->f_mode = inodePtr->i_mode;
        filePtr->f_pos = 0; //TODO ?
        return 0;
    }
    return -1;
}

int myRelease(struct inode *inodePtr, struct file *filePtr){ //TODO DEBUG EVERYTHING AQ
    //This function is called when a file is closed. It performs clean up operations if necessary. Returns zero for
    //successful operation.
    if(inodePtr != NULL && filePtr != NULL){
        free(inodePtr);
        free(filePtr->f_path);
        return 0;
    }
    return -1;
}

//This function fills the function pointer in super_operations, inode_operations, file_operations structs. It also
//sets the name, file_descriptor, get_superblock fields of the file_system_type myfs defined in
//ext2.h. It returns a pointer to myfs .
struct file_system_type *initialize_ext2(const char *image_path) {
  /* fill super_operations s_op */
  /* fill inode_operations i_op */
  /* fill file_operations f_op */
  /* for example:
      s_op = (struct super_operations){
        .read_inode = your_read_inode_function,
        .statfs = your_statfs_function,
      };
  */
  myfs.file_descriptor = open(image_path, O_RDONLY);
  myfs.get_superblock = allocate_superblock;
  s_op.read_inode = readInode;
  s_op.statfs = myStatfs;

  i_op.lookup = myLookup;
  i_op.readlink = myReadLink;
  i_op.readdir = myReadDir;
  i_op.getattr = myGetattr;

  f_op.llseek = myLlseek;
  f_op.read = myRead;
  f_op.open = myOpen;
  f_op.release = myRelease;

  myfs.name = fs_name;
  return &myfs;
}
