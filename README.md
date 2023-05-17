# ESP32 Async Webserver With SSD1306

## 1. Libraries

You can find all of them in **libraries** folder.

```cpp
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
```

## 2. API

| Endpoint | Method | Description                |
| :------- | :----- | :------------------------- |
| /api     | GET    | Get sensor status and name |
| /api     | PUT    | Set sensor name            |

## 3. Examples

**Curl**

```sh
# get status and name
curl esp32-ip-address/api

# update name
curl -X PUT esp32-ip-address/api -d "name=01"
```

**Fetch**

```js
// get data
function handleClick() {
  fetch("http://esp32-ip-address/api")
    .then((res) => res.json())
    .then((res) => console.log(res));
}

// put data
function handleSubmit(event) {
  event.preventDefault();
  const data = new FormData();
  data.append("name":"01");

  fetch("http://esp32-ip-address/api", { method: "PUT", body: data })
    .then((res) => res.json())
    .then((res) => console.log(res));
}
```

## 4. Demo Video
