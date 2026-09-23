## Endpoints
- GET /sensor
```json
{
    "hmd" : "61",
    "tmp" : "28",
    "wet" : "DRY"
}
```

- POST /ai
body: 
```json
{
    "msg" : "AI INPUT HERE!"
}
```
respond
```json
{
    "res" : "AI Respond!"
}
```

## ARDUINO
- Arduino UNO
- Soil Sensor
- humidity and temperature sensor
- LCD_I2C 16x2

## Running
```
. .venv/bin/activate
flask --app main run
```