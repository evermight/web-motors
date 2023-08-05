#ifndef API_FUNCTIONS
#define API_FUNCTIONS

struct ApiResponse {
  int httpResponseCode;
  String motion;
};

ApiResponse api_get(String apiUrl);

#endif // API_FUNCTIONS
