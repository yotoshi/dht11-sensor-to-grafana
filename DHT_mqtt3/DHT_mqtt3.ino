#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

#define MEASUREMENT_TIMEINTERVAL 15 // Seconds

#define DHTPIN 2	// Pin which is connected to the DHT sensor.

// Uncomment the type of sensor in use:
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE	DHT22	// DHT 22 (AM2302)
//#define DHTTYPE	DHT21	// DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

const char* wifi_ssid = "Yourwifi";
const char* wifi_password = "YourWifiPassword";
const char* clientID = "The_client_id_define_on_RabbitMQ"; //dht_user
const char* mqtt_server = "your_mqtt_borker_adress";
const int mqtt_port = 1883;
const char* mqtt_user = "admin";
const char* mqtt_password = "password";

//#define dht11_topic "sensor/dht11"

// More information about the PubSubClient library
// https://pubsubclient.knolleary.net/api.html
// https://github.com/knolleary/pubsubclient
WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
    // handle message arrived
}

void setup() {
    Serial.begin(115200);
    dht.begin();
    WiFi.mode(WIFI_STA);
    setup_wifi();
    client.setServer(mqtt_server, mqtt_port);

    // The callback function is executed when some device publishes a message to a topic that your ESP8266 is subscribed to
    // client.setCallback(callback);
}

void setup_wifi() {
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println("Connecting to ");
    Serial.println(wifi_ssid);

    WiFi.begin(wifi_ssid, wifi_password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }

    Serial.println("Connected to the WiFi network");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

// This functions reconnects your ESP8266 to your MQTT broker
// Change the function below if you want to subscribe to more topics with your ESP8266
void reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
        Serial.println("Attempting MQTT connection...");

        if (client.connect(clientID, mqtt_user, mqtt_password)) {
            Serial.println("connected");

            // Subscribe or resubscribe to a topic
            // In this example we do not subscribe to any topic
            // client.subscribe("your_topic_of_interest");
        } else {
            Serial.print("failed with state ");
            Serial.println(client.state());

            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }

    if(!client.loop()) {
        client.connect(clientID);
    }

    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    // Read temperature as Celsius (false)
    float t = dht.readTemperature();

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    String data = "{\"temp\": \""+String(t)+"\"}";
    String data2 = "{\"humidity\": \""+String(h)+"\"}";
    Serial.print(data+"  ");
    Serial.println(data2);

    client.publish("temp_topic", data.c_str());
    delay(2);
    client.publish("humi_topic", data2.c_str());

    // Wait N seconds between measurements.
    delay(MEASUREMENT_TIMEINTERVAL * 1000);
}
