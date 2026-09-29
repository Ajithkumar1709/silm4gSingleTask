#ifndef _OL_AMAZONAWS_H_
#define _OL_AMAZONAWS_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    FP_MODE_WITH_CSR,
    FP_MODE_KEYS_CERT,
}fp_mode_enum_t;

typedef struct {
    fp_mode_enum_t fp_mode;
    const char *aws_iot_endpoint;
    const char *aws_mqtt_port;
    const char *root_ca_path;
    const char *claim_cert_path;
    const char *claim_private_key_path;
    const char *root_ca_buffer;
    const char *claim_cert_buffer;
    const char *claim_private_key_buffer;
    const char *provisioning_template_name;
    const char *device_serial_number;
}aws_iot_config_t;


typedef struct {
    char *aws_root_ca_cert;
    unsigned int aws_root_ca_cert_length;
    char *aws_iot_certificate;
    unsigned int aws_iot_certificate_length;
    char *aws_iot_private_key;
    unsigned int aws_iot_privatekey_length;
    char *aws_iot_thing_name;
    unsigned int aws_iot_thing_name_length;
}aws_iot_info_t;


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_aws_iot_fleet_provisioning
 * DESCRIPTION 
 *  		This API is to provision a device and install unique client certificates on it
 * PARAMETERS 
 *		aws_iot_config_t[IN]               aws_fp_config
	    aws_iot_info_t  [OUT]              aws_fp_info
 * RETURN VALUES
         false                     error
         true                      sucess
 *****************************************************************************/
bool ol_aws_iot_fleet_provisioning(aws_iot_config_t aws_fp_config, aws_iot_info_t *aws_fp_info);

#ifdef __cplusplus
}
#endif


#endif
