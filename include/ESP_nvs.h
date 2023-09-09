#pragma once

#include "esp_err.h"
#include "esp_partition.h"
#include "freertos/FreeRTOS.h"
#include "nvs_flash.h"
#include <freertos/semphr.h>
#include <freertos/task.h>

class ESP_nvs
{
public:
  ESP_nvs();

  esp_err_t begin(const char *partitionName = NVS_DEFAULT_PART_NAME);
  void close();

  bool eraseAll();
  bool erase(const char *key);

  bool setBoolean(const char *key, bool value);
  bool setUInt8(const char *key, uint8_t value);
  bool setInt16(const char *key, int16_t value);
  bool setUInt16(const char *key, uint16_t value);
  bool setInt32(const char *key, int32_t value);
  bool setUInt32(const char *key, uint32_t value);
  bool setInt64(const char *key, int64_t value);
  bool setUInt64(const char *key, uint64_t value);
  bool setDouble(const char *key, double value);
  bool setFloat(const char *key, float value);
  bool setCharArray(const char *key, const char *value);
  bool setObject(const char *key, void *object, size_t length);

  bool getBoolean(const char *key, bool defaultValue);
  uint8_t getUInt8(const char *key, uint8_t defaultValue);
  int16_t getInt16(const char *key, int16_t defaultValue);
  uint16_t getUInt16(const char *key, uint16_t defaultValue);
  int32_t getInt32(const char *key, int32_t defaultValue);
  uint32_t getUInt32(const char *key, uint32_t defaultValue);
  int64_t getInt64(const char *key, int64_t defaultValue);
  uint64_t getUInt64(const char *key, uint64_t defaultValue);
  double getDouble(const char *key, double defaultValue);
  float getFloat(const char *key, float defaultValue);
  char *getCharArray(const char *key, const char *defaultValue);
  char *getCharArray(const char *key, size_t *required_size, const char *defaultValue);
  void *getObject(const char *key, void *defaultValue);

  bool exists(const char *key);

private:
  nvs_handle _nvs_handle;
  bool commit();
  SemaphoreHandle_t nvs_sync_mutex;
  esp_err_t nvs_sync_create();
  void nvs_sync_free();
  bool nvs_sync_lock();
  void nvs_sync_unlock();
};

extern ESP_nvs NVS;
