#ifndef WIRELESS_NETWORK_FUNCTIONS
#define WIRELESS_NETWORK_FUNCTIONS

boolean wifi_is_connected();
void wifi_info_get();
void wifi_connect(const char* ssid, const char* pass);

#endif // WIRELESS_NETWORK_FUNCTIONS
