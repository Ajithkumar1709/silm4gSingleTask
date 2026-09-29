
typedef struct
{

}mbtk_user_api;



static mbtk_user_api g_user_api = 
{
	0
};

void mbtk_user_api_init(void **data)
{
	*data = &g_user_api;
}


