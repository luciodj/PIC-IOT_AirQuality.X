#ifndef IOT_SENSOR_NODE_CONFIG_H
#define IOT_SENSOR_NODE_CONFIG_H

// <h> Application Configuration

// <o> Send Interval <0-100000>
// <i> Send interval in seconds
// <id> application_send_interval
#define CFG_SEND_INTERVAL 2

// <o> Timeout <0-100000>
// <i> Timeout
// <id> application_timeout
#define CFG_TIMEOUT 5000

// </h>

// <h> Cloud Configuration

// <s> project id
// <i> Google Cloud Platform project id
// <id> project_id
#define CFG_PROJECT_ID "pic-iot"

// <s> project region
// <i> Google Cloud Platform project region
// <id> project_region
#define CFG_PROJECT_REGION "us-central1"

// <s> registry id
// <i> Google Cloud Platform registry id
// <id> registry_id
#define CFG_REGISTRY_ID "PIC-IOT"

// <s> mqtt host
// <i> mqtt host address
// <id> mqtt_host
#define CFG_MQTT_HOST "mqtt.googleapis.com"

// <s> mqtt port
// <i> mqtt port value
// <id> mqtt_port
#define CFG_MQTT_PORT 443

// <s> mqtt connect timeout
// <i> mqtt connect timeout length in seconds
// <id> mqtt_conn_timeout
#define CFG_MQTT_CONN_TIMEOUT 10

// </h>

// <h> Debug Configuration

// <q> Enable debug messages:
// <i> Check to enable debug messages
// <id> debug_msg
#define CFG_DEBUG_MSG 0

// </h>

// <h> CLI Support

// <q> Enable CLI:
// <i> Check to enable cli
// <id> enable_cli
#define CFG_ENABLE_CLI 1

// </h>


#endif // IOT_SENSOR_NODE_CONFIG_H
