#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid     = "moin";
const char* password = "Wahl2024";

WiFiServer server(80);
WiFiClient wifiClient;

IPAddress broker(192, 168, 22, 253);

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

PubSubClient client(wifiClient);

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("arduinoClient", "sc", "helloFl0")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      Serial.print("Published");
      // ... and resubscribe
      //client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  // Wire.begin();
  Serial.begin(115200);
  pinMode(2, OUTPUT);      // set the LED pin mode

  delay(10);

  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();

  client.setServer(broker, 1883);
  client.setCallback(callback);

}

int value = 0;

void loop() {
  float result[3] = {0, 1, 2};
  char message[20] = {0};

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  sprintf(message, "%04.2f;%02.2f;%02.2f", result[0], result[1], result[2]);
  Serial.println(message);
  client.publish("htl-kaindorf/RPH", message);
  
  
  delay(2000);
}
