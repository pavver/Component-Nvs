# Component-Nvs

```cpp
NVS *config = new NVS();

config->init("nvs"); // partition name
config->open("config"); // namespace name

// if the buffsize key exists, returns nvs, otherwise defaults to 4096
uint16_t buffsize = config->getInt16("buffsize", 4096);

// auto deinit / close
delete config;
```

or

```cpp
// partition name , namespace name
NVS *config = new NVS("nvs", "config");

// if the buffsize key exists, returns nvs, otherwise defaults to 4096
uint16_t buffsize = config->getInt16("buffsize", 4096);

delete config;
```

you can add error checking after any function or constructor

```cpp
// partition name , namespace name
NVS *config = new NVS("nvs", "config");

if (config->last_error() != ESP_OK)
{
  ...
}

// if the buffsize key exists, returns nvs, otherwise defaults to 4096
uint16_t buffsize = config->getInt16("buffsize", 4096);

// if any error occurred during reading, the default value will be returned
if (config->last_error() != ESP_OK)
{
  ...
}

delete config;
```
