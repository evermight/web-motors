#ifndef WIRELESS_NETWORK_FUNCTIONS
#define WIRELESS_NETWORK_FUNCTIONS

boolean connected_to_network();
void get_network_info();
void connect_network(const char* ssid, const char* pass);

#endif // WIRELESS_NETWORK_FUNCTIONS
