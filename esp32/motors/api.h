#ifndef API_FUNCTIONS
#define API_FUNCTIONS

struct ApiResponse {
  int httpResponseCode;
  char motion[2];
};

ApiResponse api_get(String apiUrl);

#endif // API_FUNCTIONS
