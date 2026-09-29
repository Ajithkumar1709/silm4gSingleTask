#include "iothub.h"
#include "iothub_client_ll.h"
#include "iothubtransportmqtt.h"
#include "iothub_client_core_common.h"
#include "iothub_device_client.h"
#include "iothub_client_options.h"
#include "iothub_message.h"
#include "azure_c_shared_utility/threadapi.h"
#include "azure_c_shared_utility/platform.h"
#include "azure_c_shared_utility/xlogging.h"
#include "azure_c_shared_utility/crt_abstractions.h"
#include "azure_c_shared_utility/shared_util_options.h"
#include "parson.h"
#include "serializer.h"

//#include "ol_azureiot.h"
#include "mbtk_comm_api.h"
#include "mbtk_socket_api.h"
#include "mbtk_datacall_api.h"
#include "mbtk_os.h"


#define DEMO_TASK_STACK_SIZE    (1024 * 16)
#define DEMO_TASK_PRIORITY      (221)
#define SOCKET_LOCAL_CID mbtk_cid_index_2
#define LOCAL_CID_PDN_TYPE mbtk_data_call_v4v6

#define CMD_BUF_SIZE  100
#define DEFAULT_PUB_TIME 5

#define MESSAGERESPONSE(code, message) const char deviceMethodResponse[] = message; \
	*response_size = sizeof(deviceMethodResponse) - 1;                              \
	*response = ol_malloc(*response_size);                                             \
	(void)memcpy(*response, deviceMethodResponse, *response_size);                  \
	result = code;                                                                  \

#define FIRMWARE_UPDATE_STATUS_VALUES \
    DOWNLOADING,                      \
    APPLYING,                         \
    REBOOTING,                        \
    IDLE                              \

/*Enumeration specifying firmware update status */
DEFINE_ENUM(FIRMWARE_UPDATE_STATUS, FIRMWARE_UPDATE_STATUS_VALUES);
DEFINE_ENUM_STRINGS(FIRMWARE_UPDATE_STATUS, FIRMWARE_UPDATE_STATUS_VALUES);

/* Paste in your device connection string  */
const char *connect_string = "HostName=mbtk.azure-devices.net;DeviceId=Hx_test1;SharedAccessKey=PGYvthCKCduItjtF1VRcsfsY5tpydBqwgnnz9LaIUSc=";

IOTHUB_CLIENT_LL_HANDLE device_handle = NULL;
static char msgText[1024];
static size_t g_message_count_send_confirmations = 0;
static const char* initialFirmwareVersion = "1.0.0";

// <datadefinition>
typedef struct MESSAGESCHEMA_TAG
{
	char* name;
	char* format;
	char* fields;
} MessageSchema;

typedef struct TELEMETRYSCHEMA_TAG
{
	char* interval;
	char* messageTemplate;
	MessageSchema messageSchema;
} TelemetrySchema;

typedef struct TELEMETRYPROPERTIES_TAG
{
	TelemetrySchema temperatureSchema;
	TelemetrySchema humiditySchema;
	TelemetrySchema pressureSchema;
} TelemetryProperties;

typedef struct CHILLER_TAG
{
	// Reported properties
	char* protocol;
	char* supportedMethods;
	char* type;
	char* firmware;
	FIRMWARE_UPDATE_STATUS firmwareUpdateStatus;
	char* location;
	double latitude;
	double longitude;
	TelemetryProperties telemetry;

	// Manage firmware update process
	char* new_firmware_version;
	char* new_firmware_URI;
} Chiller;
// </datadefinition>

static void connection_status_callback(IOTHUB_CLIENT_CONNECTION_STATUS result, IOTHUB_CLIENT_CONNECTION_STATUS_REASON reason, void* user_context)
{
	(void)reason;
	(void)user_context;
    
	// This sample DOES NOT take into consideration network outages.
	if (result == IOTHUB_CLIENT_CONNECTION_AUTHENTICATED)
	{
		op_uart_printf("The device client is connected to iothub\r\n");
	}
	else
	{
		op_uart_printf("The device client has been disconnected\r\n");
	}
}

/*  Converts the Chiller object into a JSON blob with reported properties ready to be sent across the wire as a twin. */
static char* serializeToJson(Chiller* chiller)
{
	char* result;

	op_uart_printf("serializeToJson 1");
	JSON_Value* root_value = json_value_init_object();
	op_uart_printf("serializeToJson 2 %x",root_value);
	JSON_Object* root_object = json_value_get_object(root_value);
	op_uart_printf("serializeToJson 3 %x",root_object);

	// Only reported properties:
	(void)json_object_set_string(root_object, "Protocol", chiller->protocol);
	op_uart_printf("serializeToJson 3.0");
/*
	(void)json_object_set_string(root_object, "SupportedMethods", chiller->supportedMethods);
	(void)json_object_set_string(root_object, "Type", chiller->type);
	(void)json_object_set_string(root_object, "Firmware", chiller->firmware);
	(void)json_object_set_string(root_object, "FirmwareUpdateStatus", ENUM_TO_STRING(FIRMWARE_UPDATE_STATUS, chiller->firmwareUpdateStatus));
	//(void)json_object_set_string(root_object, "FirmwareUpdateStatus", ENUM_TO_STRING(IOTHUB_CLIENT_RESULTX, IOTHUB_CLIENT_INVALID_ARGX));
	(void)json_object_set_string(root_object, "Location", chiller->location);
*/
	(void)json_object_set_number(root_object, "Latitude", chiller->latitude);
	(void)json_object_set_number(root_object, "Longitude", chiller->longitude);
	op_uart_printf("serializeToJson 3.1");
	(void)json_object_dotset_string(root_object, "Telemetry.TemperatureSchema.Interval", chiller->telemetry.temperatureSchema.interval);
	op_uart_printf("serializeToJson 3.2");
/*
	(void)json_object_dotset_string(root_object, "Telemetry.TemperatureSchema.MessageTemplate", chiller->telemetry.temperatureSchema.messageTemplate);
	(void)json_object_dotset_string(root_object, "Telemetry.TemperatureSchema.MessageSchema.Name", chiller->telemetry.temperatureSchema.messageSchema.name);
	(void)json_object_dotset_string(root_object, "Telemetry.TemperatureSchema.MessageSchema.Format", chiller->telemetry.temperatureSchema.messageSchema.format);
	(void)json_object_dotset_string(root_object, "Telemetry.TemperatureSchema.MessageSchema.Fields", chiller->telemetry.temperatureSchema.messageSchema.fields);
	(void)json_object_dotset_string(root_object, "Telemetry.HumiditySchema.Interval", chiller->telemetry.humiditySchema.interval);
	(void)json_object_dotset_string(root_object, "Telemetry.HumiditySchema.MessageTemplate", chiller->telemetry.humiditySchema.messageTemplate);
	(void)json_object_dotset_string(root_object, "Telemetry.HumiditySchema.MessageSchema.Name", chiller->telemetry.humiditySchema.messageSchema.name);
	(void)json_object_dotset_string(root_object, "Telemetry.HumiditySchema.MessageSchema.Format", chiller->telemetry.humiditySchema.messageSchema.format);
	(void)json_object_dotset_string(root_object, "Telemetry.HumiditySchema.MessageSchema.Fields", chiller->telemetry.humiditySchema.messageSchema.fields);
	(void)json_object_dotset_string(root_object, "Telemetry.PressureSchema.Interval", chiller->telemetry.pressureSchema.interval);
	(void)json_object_dotset_string(root_object, "Telemetry.PressureSchema.MessageTemplate", chiller->telemetry.pressureSchema.messageTemplate);
	(void)json_object_dotset_string(root_object, "Telemetry.PressureSchema.MessageSchema.Name", chiller->telemetry.pressureSchema.messageSchema.name);
	(void)json_object_dotset_string(root_object, "Telemetry.PressureSchema.MessageSchema.Format", chiller->telemetry.pressureSchema.messageSchema.format);
	(void)json_object_dotset_string(root_object, "Telemetry.PressureSchema.MessageSchema.Fields", chiller->telemetry.pressureSchema.messageSchema.fields);
*/

	op_uart_printf("serializeToJson 4");
	result = json_serialize_to_string(root_value);
	op_uart_printf("serializeToJson 5");

	json_value_free(root_value);
	op_uart_printf("serializeToJson 6");
	return result;
}


static void send_confirm_callback(IOTHUB_CLIENT_CONFIRMATION_RESULT result, void* userContextCallback)
{
	(void)userContextCallback;
	g_message_count_send_confirmations++;
	op_uart_printf("Confirmation callback received for message %zu with result %s\r\n", g_message_count_send_confirmations, ENUM_TO_STRING(IOTHUB_CLIENT_CONFIRMATION_RESULT, result));
}

static void reported_state_callback(int status_code, void* userContextCallback)
{
	(void)userContextCallback;
	op_uart_printf("Device Twin reported properties update completed with result: %d\r\n", status_code);
}

static void sendChillerReportedProperties(Chiller* chiller)
{
	if (device_handle != NULL)
	{
		char* reportedProperties = serializeToJson(chiller);
		op_uart_printf("IoTHubDeviceClient_SendReportedState start %x",reportedProperties);
		(void)IoTHubDeviceClient_SendReportedState(device_handle, (const unsigned char*)reportedProperties, strlen(reportedProperties), reported_state_callback, NULL);
		ol_free(reportedProperties);
	}
}

// <firmwareupdate>
/*
 This is a thread allocated to process a long-running device method call.
 It uses device twin reported properties to communicate status values
 to the Remote Monitoring solution accelerator.
*/
static int do_firmware_update(void *param)
{
	Chiller *chiller = (Chiller *)param;
	op_uart_printf("Running simulated firmware update: URI: %s, Version: %s\r\n", chiller->new_firmware_URI, chiller->new_firmware_version);

	op_uart_printf("Simulating download phase...\r\n");
	chiller->firmwareUpdateStatus = DOWNLOADING;
	sendChillerReportedProperties(chiller);

	ThreadAPI_Sleep(5000);

	op_uart_printf("Simulating apply phase...\r\n");
	chiller->firmwareUpdateStatus = APPLYING;
	sendChillerReportedProperties(chiller);

	ThreadAPI_Sleep(5000);

	op_uart_printf("Simulating reboot phase...\r\n");
	chiller->firmwareUpdateStatus = REBOOTING;
	sendChillerReportedProperties(chiller);

	ThreadAPI_Sleep(5000);

	size_t size = strlen(chiller->new_firmware_version) + 1;
	(void)memcpy(chiller->firmware, chiller->new_firmware_version, size);

	chiller->firmwareUpdateStatus = IDLE;
	sendChillerReportedProperties(chiller);

	return 0;
}
// </firmwareupdate>

void getFirmwareUpdateValues(Chiller* chiller, const unsigned char* payload)
{
	ol_free(chiller->new_firmware_version);
	ol_free(chiller->new_firmware_URI);
	chiller->new_firmware_URI = NULL;
	chiller->new_firmware_version = NULL;

	JSON_Value* root_value = json_parse_string((char *)payload);
	JSON_Object* root_object = json_value_get_object(root_value);

	JSON_Value* newFirmwareVersion = json_object_get_value(root_object, "Firmware");

	if (newFirmwareVersion != NULL)
	{
		const char* data = json_value_get_string(newFirmwareVersion);
		if (data != NULL)
		{
			size_t size = strlen(data) + 1;
			chiller->new_firmware_version = ol_malloc(size);
			(void)memcpy(chiller->new_firmware_version, data, size);
		}
	}

	JSON_Value* newFirmwareURI = json_object_get_value(root_object, "FirmwareUri");

	if (newFirmwareURI != NULL)
	{
		const char* data = json_value_get_string(newFirmwareURI);
		if (data != NULL)
		{
			size_t size = strlen(data) + 1;
			chiller->new_firmware_URI = ol_malloc(size);
			(void)memcpy(chiller->new_firmware_URI, data, size);
		}
	}

	// Free resources
	json_value_free(root_value);

}

// <devicemethodcallback>
static int device_method_callback(const char* method_name, const unsigned char* payload, size_t size, unsigned char** response, size_t* response_size, void* userContextCallback)
{
	Chiller *chiller = (Chiller *)userContextCallback;

	int result;

	op_uart_printf("Direct method name:    %s\r\n", method_name);
	op_uart_printf("Direct method payload: %.*s\r\n", (int)size, (const char*)payload);

	if (strcmp("Reboot", method_name) == 0)
	{
		MESSAGERESPONSE(201, "{ \"Response\": \"Rebooting\" }")
	}
	else if (strcmp("EmergencyValveRelease", method_name) == 0)
	{
		MESSAGERESPONSE(201, "{ \"Response\": \"Releasing emergency valve\" }")
	}
	else if (strcmp("IncreasePressure", method_name) == 0)
	{
		MESSAGERESPONSE(201, "{ \"Response\": \"Increasing pressure\" }")
	}
	else if (strcmp("FirmwareUpdate", method_name) == 0)
	{
		if (chiller->firmwareUpdateStatus != IDLE)
		{
			op_uart_printf("Attempt to invoke firmware update out of order\r\n");
			MESSAGERESPONSE(400, "{ \"Response\": \"Attempting to initiate a firmware update out of order\" }")
		}
		else
		{
			getFirmwareUpdateValues(chiller, payload);

			if (chiller->new_firmware_version != NULL && chiller->new_firmware_URI != NULL)
			{
				// Create a thread for the long-running firmware update process.
				THREAD_HANDLE thread_apply;
				THREADAPI_RESULT t_result = ThreadAPI_Create(&thread_apply, do_firmware_update, chiller);
				if (t_result == THREADAPI_OK)
				{
					op_uart_printf("Starting firmware update thread\r\n");
					MESSAGERESPONSE(201, "{ \"Response\": \"Starting firmware update thread\" }")
				}
				else
				{
					op_uart_printf("Failed to start firmware update thread\r\n");
					MESSAGERESPONSE(500, "{ \"Response\": \"Failed to start firmware update thread\" }")
				}
			}
			else
			{
				op_uart_printf("Invalid method payload\r\n");
				MESSAGERESPONSE(400, "{ \"Response\": \"Invalid payload\" }")
			}
		}
	}
	else
	{
		// All other entries are ignored.
		op_uart_printf("Method not recognized\r\n");
		MESSAGERESPONSE(400, "{ \"Response\": \"Method not recognized\" }")
	}

	return result;
}
// </devicemethodcallback>

// <sendmessage>
static void send_message(IOTHUB_DEVICE_CLIENT_HANDLE handle, char* message, char* schema)
{
	unsigned int now;
	struct tm* timeinfo;
	char timebuff[50];
	
	IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(message);

	// Set system properties
	(void)IoTHubMessage_SetMessageId(message_handle, "MSG_ID");
	(void)IoTHubMessage_SetCorrelationId(message_handle, "CORE_ID");
	(void)IoTHubMessage_SetContentTypeSystemProperty(message_handle, "application%2fjson");
	(void)IoTHubMessage_SetContentEncodingSystemProperty(message_handle, "utf-8");

	// Set application properties
	MAP_HANDLE propMap = IoTHubMessage_Properties(message_handle);
	(void)Map_AddOrUpdate(propMap, "$$MessageSchema", schema);
	(void)Map_AddOrUpdate(propMap, "$$ContentType", "JSON");

	
	//strftime(timebuff, 50, "%Y-%m-%dT%H:%M:%SZ", timeinfo);
	now = ol_time(&now);	
	timeinfo = ol_gmtime(&now);
  sprintf_s(timebuff, sizeof(timebuff), "%d-%d-%dT%d:%d:%dZ",
      timeinfo->tm_year, timeinfo->tm_mon, timeinfo->tm_mday,
      timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	
  op_uart_printf("QT# time is %s\r\n", timebuff);
	(void)Map_AddOrUpdate(propMap, "$$CreationTimeUtc", timebuff);
	IoTHubDeviceClient_SendEventAsync(handle, message_handle, send_confirm_callback, NULL);
	IoTHubMessage_Destroy(message_handle);
}

void start_azureiot_session(void *param)
{
  int ret = 0;
	double minTemperature = 50.0;
	double minPressure = 55.0;
	double minHumidity = 30.0;
	double temperature = 0;
	double pressure = 0;
	double humidity = 0;
	int debugFlag = 1;

	srand((unsigned int)ol_time(NULL));
   
  // Used to initialize sdk subsystem
	IoTHub_Init();

  if ((device_handle = IoTHubDeviceClient_CreateFromConnectionString(connect_string, MQTT_Protocol)) == NULL)
  {
      op_uart_printf("QT# device_handle is NULL\r\n");
  }
  else
  {
  	(void)IoTHubDeviceClient_SetOption(device_handle,"logtrace",&debugFlag);
		//(void)IoTHubDeviceClient_SetOption(device_handle,"rawlogtrace",&debugFlag);
		// Setting connection status callback to get indication of connection to iothub
		(void)IoTHubDeviceClient_SetConnectionStatusCallback(device_handle, connection_status_callback, NULL);

    ThreadAPI_Sleep(5000);
		op_uart_printf("aaaaa");
		
		Chiller chiller;
		memset(&chiller, 0, sizeof(Chiller));
		chiller.protocol = "MQTT";
		chiller.supportedMethods = "Reboot,FirmwareUpdate,EmergencyValveRelease,IncreasePressure";
		chiller.type = "Chiller";
		size_t size = strlen(initialFirmwareVersion) + 1;
		chiller.firmware = ol_malloc(size);
		memcpy(chiller.firmware, initialFirmwareVersion, size);
		chiller.firmwareUpdateStatus = IDLE;
		chiller.location = "Building 44";
		chiller.latitude = 47.638928;
		chiller.longitude = -122.13476;
		chiller.telemetry.temperatureSchema.interval = "00:00:05";
		chiller.telemetry.temperatureSchema.messageTemplate = "{\"temperature\":${temperature},\"temperature_unit\":\"${temperature_unit}\"}";
		chiller.telemetry.temperatureSchema.messageSchema.name = "chiller-temperature;v1";
		chiller.telemetry.temperatureSchema.messageSchema.format = "JSON";
		chiller.telemetry.temperatureSchema.messageSchema.fields = "{\"temperature\":\"Double\",\"temperature_unit\":\"Text\"}";
		chiller.telemetry.humiditySchema.interval = "00:00:05";
		chiller.telemetry.humiditySchema.messageTemplate = "{\"humidity\":${humidity},\"humidity_unit\":\"${humidity_unit}\"}";
		chiller.telemetry.humiditySchema.messageSchema.name = "chiller-humidity;v1";
		chiller.telemetry.humiditySchema.messageSchema.format = "JSON";
		chiller.telemetry.humiditySchema.messageSchema.fields = "{\"humidity\":\"Double\",\"humidity_unit\":\"Text\"}";
		chiller.telemetry.pressureSchema.interval = "00:00:05";
		chiller.telemetry.pressureSchema.messageTemplate = "{\"pressure\":${pressure},\"pressure_unit\":\"${pressure_unit}\"}";
		chiller.telemetry.pressureSchema.messageSchema.name = "chiller-pressure;v1";
		chiller.telemetry.pressureSchema.messageSchema.format = "JSON";
		chiller.telemetry.pressureSchema.messageSchema.fields = "{\"pressure\":\"Double\",\"pressure_unit\":\"Text\"}";

		op_uart_printf("qqqqq");
		sendChillerReportedProperties(&chiller);
		op_uart_printf("bbbbb");
		(void)IoTHubDeviceClient_SetDeviceMethodCallback(device_handle, device_method_callback, &chiller);
		op_uart_printf("cccccc");

		while (1)
		{
			temperature = minTemperature + ((rand() % 10) + 5);
			pressure = minPressure + ((rand() % 10) + 5);
			humidity = minHumidity + ((rand() % 20) + 5);

			if (chiller.firmwareUpdateStatus == IDLE)
			{
				(void)sprintf_s(msgText, sizeof(msgText), "{\"temperature\":%d.%d,\"temperature_unit\":\"F\"}", 
						((int)temperature), ((int)(temperature*100))%100);
				op_uart_printf("Sending %s\r\n", msgText);
        send_message(device_handle, msgText, chiller.telemetry.temperatureSchema.messageSchema.name);
				
				(void)sprintf_s(msgText, sizeof(msgText), "{\"pressure\":%d.%d,\"pressure_unit\":\"psig\"}", 
     				((int)pressure), ((int)(pressure*100))%100);
				op_uart_printf("Sending %s\r\n", msgText);
				send_message(device_handle, msgText, chiller.telemetry.pressureSchema.messageSchema.name);

				(void)sprintf_s(msgText, sizeof(msgText), "{\"humidity\":%d.%d,\"humidity_unit\":\"%%\"}", 
        		((int)humidity), ((int)(humidity*100))%100);
				op_uart_printf("Sending %s\r\n", msgText);
        send_message(device_handle, msgText, chiller.telemetry.humiditySchema.messageSchema.name);
      }
			ThreadAPI_Sleep(200*10);
		}

		op_uart_printf("\r\nShutting down\r\n");

		// Clean up the iothub sdk handle and free resources
		IoTHubDeviceClient_Destroy(device_handle);
		ol_free(chiller.firmware);
		ol_free(chiller.new_firmware_URI);
		ol_free(chiller.new_firmware_version);
	}
}

int azure_demo_wait_network(void)
{
  if(ol_wait_network_regist(120) != mbtk_data_call_ok)
  {
    op_uart_printf("azure_demo_wait_network ol_wait_network_regist time out\n");
    return -1;
  }
  op_uart_printf("azure_demo_wait_network execute ol_data_call_start \n");
  if(ol_data_call_start(SOCKET_LOCAL_CID, LOCAL_CID_PDN_TYPE, "cmnet", "aaa", "bbb", 1) != mbtk_data_call_ok)
  {
    op_uart_printf("azure_demo_wait_network ol_data_call_start fail\n");
    return -1;
  }

  return 0;
}

void azure_demo(void)
{
  mbtk_os_status os_status;
	mbtk_taskref azure_task_ref;

	op_uart_printf("azure_demo satrt!!!");

	if(azure_demo_wait_network() != 0)
  {
    op_uart_printf("azure_demo_wait_network fail\n");
    return;
  }

  os_status = ol_os_task_creat(&azure_task_ref, NULL, DEMO_TASK_STACK_SIZE,
  	DEMO_TASK_PRIORITY, "azure_demo", start_azureiot_session,NULL);
  if (os_status != mbtk_os_success)
  {
    op_uart_printf("azure_demo ol_os_task_creat sub task fail, os_status = %d \n", os_status);
    return;
  }

	op_uart_printf("azureiot task process start\n");
	op_uart_printf("azure_demo end");
}

