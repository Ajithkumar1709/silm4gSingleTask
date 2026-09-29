

#ifndef _ALIOS_HISR_H_
#define _ALIOS_HISR_H_

#define ALI_THREAD_ID                            ((UINT32) 0x414C4954)
typedef struct abstract_task_tag
{
	ktask_t 	hisr_task;  /* task MUST be the first member */
    UINT32 		osa_system_reserved_1;  /* System reserved word   */
    UINT32 		osa_system_reserved_2;  /* System reserved word   */
    UINT32 		osa_system_reserved_3;  /* System reserved word   */
    UINT32 		osa_app_reserved_1;     /* App reserved word      */
    UINT32 		aos_thread_id;          /* Control block ID       */
}abstract_task;

typedef struct RHINO_HISR_STRUCT{

	abstract_task 		abs_task;  /* task MUST be the first member */
	ksem_t				hisr_semaphore;		//note: should not be a pointer
	VOID                (*hisr_entry)(UINT32);
	UINT32              hisr_entry_parameter;
	CHAR				*hisr_stack_start; 
	CHAR				*hisr_name;
}RHINO_HISR;


UINT32 _ali_hisr_create(RHINO_HISR *hisr_ptr, CHAR * name,VOID(* entry_function)(UINT32),
				UINT32 entry_input, UINT8 priority);
UINT32 _ali_hisr_delete(RHINO_HISR *hisr_ptr);
UINT32 _ali_hisr_activate(RHINO_HISR *hisr_ptr);



#endif /*HISR_H_*/


