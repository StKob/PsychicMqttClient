/**
 *   PsychicMqttClient
 *
 *   Simple Example for a minimal MQTT client using the PsychicMqttClient library.
 *
 *   Please change the ssid and pass to your actual WiFi credentials.
 *
 *   This example uses the public MQTT broker mqtt.eclipseprojects.io,
 *   registers a onTopic callback function subscribed to a unique topic
 *   and publishes a message to that topic. The echoed message payload will be
 *   printed to the serial monitor.
 *
 */

#include <Arduino.h>
#include <WiFi.h>
#include <PsychicMqttClient.h>

const char ssid[] = "ssid"; // your network SSID (name)
const char pass[] = "pass"; // your network password

/**
 * Create a PsychicMqttClient object
 */
PsychicMqttClient mqttClient;

void setup()
{
    Serial.begin(115200);

    /**
     * Connect to the WiFi network with the given ssid and pass.
     */
    WiFi.begin(ssid, pass);

    Serial.printf("Connecting to WiFi %s .", ssid);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }

    Serial.printf("\r\nConnected, IP address: %s \r\n", WiFi.localIP().toString().c_str());

    /**
     * Connect to the open MQTT broker mqtt.eclipseprojects.io.
     */
    mqttClient.setServer("mqtt://mqtt.eclipseprojects.io");

    /**
     * Lambda callback function for onTopic Event Handler
     *
     * Subscribes to the topic "{MAC-Address}/simple" with QoS 0.
     * The lambda callback function will be called when a message is received.
     */
    String topic = String(ESP.getEfuseMac()) + "/simple";

    mqttClient.onTopic(topic.c_str(), 0, [&](const char *topic, const char *payload, int retain, int qos, bool dup)
                       {
                        /**
                         * Using a lambda callback function is a very convenient way to handle the 
                         * received message. The function will be called when a message is received. 
                         * 
                         * The parameters are:
                         * - topic: The topic of the received message
                         * - payload: The payload of the received message
                         * - retain: The retain flag of the received message
                         * - qos: The qos of the received message
                         * - dup: The duplicate flag of the received message
                         * 
                         * It is important not to do any heavy calculations, hardware access, delays or 
                         * blocking code in the callback function.
                        */
                        Serial.printf("Received Topic: %s\r\n", topic);
                        Serial.printf("Received Payload: %s\r\n", payload); });

    /**
     * Connect to the MQTT broker
     */
    mqttClient.connect();

    /**
     * Wait blocking until the connection is established
     */
    while (!mqttClient.connected())
    {
        delay(500);
    }

    /**
     * Publish a message to the topic "{MAC-Address}/simple" with QoS 0 and retain flag 0.
     *
     * You can only publish messages after the connection is established.
     */
    mqttClient.publish(topic.c_str(), 0, 0, "Hello World!");
}

void loop()
{
    /**
     * Nothing to do here, the onTopic callback function will be called when a message is received.
     */
}
