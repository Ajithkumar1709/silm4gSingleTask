#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "mbtk_comm_api.h"
#ifdef MBTK_CJSON_SUPPORT
#include "cJSON.h"

// Function to parse ICCID from JSON
const char* parse_iccid(const char *json_str)
{
    cJSON *json = cJSON_Parse(json_str);
    if (json == NULL)
    {
        return NULL;
    }
    
    cJSON *payload = cJSON_GetObjectItemCaseSensitive(json, "payload");
    if (!cJSON_IsObject(payload))
    {
        cJSON_Delete(json);
        return NULL;
    }

    cJSON *data = cJSON_GetObjectItemCaseSensitive(payload, "data");
    if (!cJSON_IsArray(data))
    {
        cJSON_Delete(json);
        return NULL;
    }

    cJSON *data_item = cJSON_GetArrayItem(data, 0);
    if (!cJSON_IsObject(data_item))
    {
        cJSON_Delete(json);
        return NULL;
    }

    cJSON *iccid = cJSON_GetObjectItemCaseSensitive(data_item, "iccid");
    if (!cJSON_IsString(iccid) || (iccid->valuestring == NULL))
    {
        cJSON_Delete(json);
        return NULL;
    }

    char *iccid_str = strdup(iccid->valuestring);
    cJSON_Delete(json);
    return iccid_str;
}

// Function to parse profileState from JSON
const char* parse_profile_state(const char *json_str)
{
    cJSON *json = cJSON_Parse(json_str);
    if (json == NULL)
    {
        return NULL;
    }
    
    cJSON *payload = cJSON_GetObjectItemCaseSensitive(json, "payload");
    if (!cJSON_IsObject(payload))
    {
        cJSON_Delete(json);
        return NULL;
    }

    cJSON *data = cJSON_GetObjectItemCaseSensitive(payload, "data");
    if (!cJSON_IsArray(data))
    {
        cJSON_Delete(json);
        return NULL;
    }

    cJSON *data_item = cJSON_GetArrayItem(data, 0);
    if (!cJSON_IsObject(data_item))
    {
        cJSON_Delete(json);
        return NULL;
    }

    cJSON *profileState = cJSON_GetObjectItemCaseSensitive(data_item, "profileState");
    if (!cJSON_IsString(profileState) || (profileState->valuestring == NULL))
    {
        cJSON_Delete(json);
        return NULL;
    }

    char *profile_state_str = strdup(profileState->valuestring);
    cJSON_Delete(json);
    return profile_state_str;
}
#endif
