AsyncWebServer server(80);

// handle GET request
void handleGetRequest(AsyncWebServerRequest* request) {
  request->send(200, "application/json", "{\"name\":\"" + name + "\",\"status\":" + (status ? "true" : "false") + "}");
}

// handle PUT request
void handlePutRequest(AsyncWebServerRequest* request) {
  if (request->hasArg("name")) {
    name = request->arg("name");
    renderOled(name, status);
    storeConfigToEEPROM(name);
    request->send(200, "application/json", "{\"success\":true}");
  } else {
    request->send(400, "application/json", "{\"success\":false}");
  }
}

// handle OPTIONS and 404
void handleNotFound(AsyncWebServerRequest* request) {
  if (request->method() == HTTP_OPTIONS) {
    request->send(200);
  } else {
    request->send(404);
  }
}

void setupServer() {
  DefaultHeaders::Instance().addHeader("Server", "ESP Async Web Server");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "Content-Type");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");

  server.on("/api", HTTP_GET, handleGetRequest);
  server.on("/api", HTTP_PUT, handlePutRequest);
  server.onNotFound(handleNotFound);
  server.begin();
}
