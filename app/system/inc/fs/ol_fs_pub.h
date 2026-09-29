#ifndef _OL_FS_PUB_H_
#define _OL_FS_PUB_H_

#ifdef __cplusplus
extern "C" {
#endif

#define OL_FS_FILE_NAME_LEN 128
//err_no
typedef enum
{
	FILE_ERR_NONE = 0,
	FILE_ERR_EOF = -1,
	FILE_ERR_PARAM = -2,
	FILE_ERR_NOT_EXIST = -3,
	FILE_ERR_ACCESS = -4,
	FILE_ERR_OPEN = -5,
	FILE_ERR_READ = -6,
	FILE_ERR_WRITE = -7,
	

}OL_FILE_ERR;


enum lfs_error {
    LFS_ERR_OK          = 0,    // No error
    LFS_ERR_BLOCK       = -1,   // Error LFS block
    LFS_ERR_IO          = -5,   // Error during device operation
    LFS_ERR_CORRUPT     = -84,  // Corrupted
    LFS_ERR_NOENT       = -2,   // No directory entry
    LFS_ERR_EXIST       = -17,  // Entry already exists
    LFS_ERR_NOTDIR      = -20,  // Entry is not a dir
    LFS_ERR_ISDIR       = -21,  // Entry is a dir
    LFS_ERR_NOTEMPTY    = -39,  // Dir is not empty
    LFS_ERR_BADF        = -9,   // Bad file number
    LFS_ERR_FBIG        = -27,  // File too large
    LFS_ERR_INVAL       = -22,  // Invalid parameter
    LFS_ERR_NOSPC       = -28,  // No space left on device
    LFS_ERR_NOMEM       = -12,  // No more memory available
    LFS_ERR_NOATTR      = -61,  // No data/attr available
    LFS_ERR_NAMETOOLONG = -36,  // File name too long
};

//for file_seek <whence>
#define OL_FS_SEEK_SET 0
#define OL_FS_SEEK_CUR 1
#define OL_FS_SEEK_END 2


//for filefind info
typedef struct
{
	char 	file_name[OL_FS_FILE_NAME_LEN + 1];
	int   	time;          /* updated time stamp when modified */
	int  	date;          /* updated date stamp when modified */
	int  	size;          /* size of file data in bytes */
	int 	permissions;
}ol_FS_FIND_DATA, *ol_PFS_FIND_DATA;

#ifdef __cplusplus
}
#endif

#endif