#ifndef __MBTK_API_INIT_H__
#define __MBTK_API_INIT_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    void *user_data_api;
}open_api_table;

void mbtk_api_init(open_api_table *api_table);


#ifdef __cplusplus
}
#endif

#endif
