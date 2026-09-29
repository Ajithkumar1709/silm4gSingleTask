/********************************************************************
	created:	2009/11/01
	modified:	5/11/2009
	filename: 	Integrated.c
	author:		Avishai Ziv
	
	purpose:	Integrate the Cortex binary into an existing GB binary	
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CORTEX_BINARY_SIZE (48 * 1024)		/*Cortex M3 binary size in bytes*/
#define MAXIMUM_BUFFER_TO_ALLOC (0x400000) 

typedef char BYTE;

int main(int argc, char *argv[]) 
{
	FILE * pInFileM3;
	FILE * pInFileGB;
	FILE * pOutFileGB;
	BYTE  *BufferM3;
	BYTE  *BufferGB_1stMB;
	BYTE  *BufferGB_2ndMB;
	int	  i;
	size_t result;
	long first_partition_size;
	long sequencer_memory_size;
	long second_partition_size;

	BufferM3 = (BYTE *) malloc (CORTEX_BINARY_SIZE);
	BufferGB_1stMB = (BYTE *) malloc (MAXIMUM_BUFFER_TO_ALLOC);
	BufferGB_2ndMB = (BYTE *) malloc (MAXIMUM_BUFFER_TO_ALLOC);

	/*command line parameters input check*/
	if (argc != 6)
	{
		printf("\nError - must have 5 arguments:\n #1 - GB binary file name\n #2 - Cortex binary file name\n #3 - first partition size\n #4 - sequencer memory size\n #5 - second partition size\n");
		exit(1);
	}


	first_partition_size = (long)atoi(argv[3]);
	sequencer_memory_size = (long)atoi(argv[4]);
	second_partition_size = (long)atoi(argv[5]);

#if 0
	printf("first: %X\n", first_partition_size);
	printf("2nd: %X\n", sequencer_memory_size);
	printf("3rd: %X\n", second_partition_size);
#endif

	/*open file for read - this is the Cortex M3 binary file*/
	pInFileM3 = fopen(argv[2], "rb");
	if (!pInFileM3)
	{
		printf("\nError opening file: %s!", argv[2]);
		exit(2);
	}


	/*read the cortex data*/
	result = fread (BufferM3,1,sequencer_memory_size,pInFileM3);

	if (result < sequencer_memory_size) 
	{
		printf("\nCortex binary size is less than 48KB... will pad with 0xFFFF\n");

		for (i = result; i < sequencer_memory_size; i++ )
			BufferM3[i] = (BYTE)0xFF;
	}
	else if (result > sequencer_memory_size) 
	{
		printf("\nError! Cortex binary size is more than 48KB!!!\n");
		exit(2);
	}

	fclose(pInFileM3);

	/*open file for read - this is the GB binary file*/
	pInFileGB = fopen(argv[1], "rb");
	if (!pInFileGB)
	{
		printf("\nError opening file: %s!", argv[1]);
		exit(2);
	}

	/*read the first partition GB data*/
	
	result = fread (BufferGB_1stMB,1,first_partition_size,pInFileGB);
	if (result != first_partition_size) {fputs ("Reading error 2 (first partition size incorrect)",stderr);  exit (3);}
	

	fseek ( pInFileGB , first_partition_size + sequencer_memory_size , SEEK_SET );

	result = fread (BufferGB_2ndMB, 1, second_partition_size, pInFileGB);
	if (result != second_partition_size) {fputs ("Reading error 3 (second partition size incorrect)",stderr); exit (3);}

	fclose(pInFileGB);
	

	/*open file for writing - this is the final GB binary file*/
	pOutFileGB = fopen(argv[1], "wb");
	if (!pOutFileGB)
	{
		printf("\nError opening file: %s!", argv[0]);
		exit(2);
	}

	
	/*write the buffer inside the GB file*/
	fwrite (BufferGB_1stMB  , 1 , first_partition_size , pOutFileGB );
	
	fwrite (BufferM3		, 1 , sequencer_memory_size		 , pOutFileGB );
	/*fseek ( pInFileGB , 0 , SEEK_END );*/
	
	fwrite (BufferGB_2ndMB  , 1 , second_partition_size , pOutFileGB );

	
	
	fclose(pOutFileGB);

	return 0;
}