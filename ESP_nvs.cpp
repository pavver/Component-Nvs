
#include "ESP_nvs.h"
#include "esp_partition.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "string.h"
#include <esp_err.h>
#include <freertos/semphr.h>

ESP_nvs::ESP_nvs()
{
}

ESP_nvs::ESP_nvs(const char *partition_label)
{
  _err = init(partition_label);
}

ESP_nvs::ESP_nvs(const char *partition_label, const char *namespace_name, nvs_open_mode_t open_mode)
{
  _err = init(partition_label);

  if (_err != ESP_OK)
    return;

  _err = open(namespace_name, open_mode);
}

ESP_nvs::~ESP_nvs()
{
  close();
  deinit();
}

esp_err_t ESP_nvs::init(const char *partition_label)
{
  if (strlen(partition_label) > 16)
    return ESP_ERR_INVALID_ARG;

  _partition = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_NVS, partition_label);
  if (_partition == NULL)
    return ESP_FAIL;

  _err = nvs_flash_init_partition_ptr(_partition);

  if (_err == ESP_ERR_NVS_NO_FREE_PAGES)
    _err = nvs_flash_erase_partition_ptr(_partition);

  return nvs_flash_init_partition_ptr(_partition);
}

esp_err_t ESP_nvs::deinit()
{
  _err = nvs_flash_deinit_partition(_partition->label);
  _partition = NULL;
  return _err;
}

esp_err_t ESP_nvs::open(const char *namespace_name, nvs_open_mode_t open_mode)
{
  if (strlen(namespace_name) > 16)
    return ESP_ERR_INVALID_ARG;

  _err = nvs_open_from_partition(_partition->label, namespace_name, open_mode, &_nvs_handle);

  if (_err != ESP_OK)
    return _err;

  _err = nvs_sync_create();

  return _err;
}

void ESP_nvs::close()
{
  nvs_close(_nvs_handle);
  nvs_sync_free();
}

bool ESP_nvs::setBoolean(const char *key, bool value)
{
  nvs_sync_lock();
  _err = nvs_set_i8(_nvs_handle, key, value ? 1 : 0);
  if (_err != ESP_OK)
  {
    nvs_sync_unlock();
    return false;
  }
  return commit();
}

bool ESP_nvs::setUInt8(const char *key, uint8_t value)
{
  nvs_sync_lock();
  _err = nvs_set_u8(_nvs_handle, key, value);
  if (_err != ESP_OK)
  {
    nvs_sync_unlock();
    return false;
  }
  return commit();
}

bool ESP_nvs::setInt16(const char *key, int16_t value)
{
  nvs_sync_lock();
  _err = nvs_set_i16(_nvs_handle, key, value);
  if (_err != ESP_OK)
  {
    nvs_sync_unlock();
    return false;
  }
  return commit();
}

bool ESP_nvs::setUInt16(const char *key, uint16_t value)
{
  nvs_sync_lock();
  _err = nvs_set_u16(_nvs_handle, key, value);
  if (_err != ESP_OK)
  {
    nvs_sync_unlock();
    return false;
  }
  return commit();
}

bool ESP_nvs::setInt32(const char *key, int32_t value)
{
  nvs_sync_lock();
  _err = nvs_set_i32(_nvs_handle, key, value);
  if (_err != ESP_OK)
  {
    nvs_sync_unlock();
    return false;
  }
  return commit();
}

bool ESP_nvs::setUInt32(const char *key, uint32_t value)
{
  nvs_sync_lock();
  _err = nvs_set_u32(_nvs_handle, key, value);
  if (_err != ESP_OK)
  {
    nvs_sync_unlock();
    return false;
  }
  return commit();
}
bool ESP_nvs::setInt64(const char *key, int64_t value)
{
  nvs_sync_lock();
  _err = nvs_set_i64(_nvs_handle, key, value);
  if (_err != ESP_OK)
  {
    nvs_sync_unlock();
    return false;
  }
  return commit();
}

bool ESP_nvs::setUInt64(const char *key, uint64_t value)
{
  nvs_sync_lock();
  _err = nvs_set_u64(_nvs_handle, key, value);
  if (_err != ESP_OK)
  {
    nvs_sync_unlock();
    return false;
  }
  return commit();
}

bool ESP_nvs::setFloat(const char *key, float value)
{
  return setObject(key, &value, sizeof(float));
}
bool ESP_nvs::setDouble(const char *key, double value)
{
  return setObject(key, &value, sizeof(double));
}

bool ESP_nvs::setCharArray(const char *key, const char *value)
{
  if (value == nullptr)
  {
    erase(key);
    return true;
  }
  nvs_sync_lock();
  _err = nvs_set_str(_nvs_handle, key, value);
  if (_err != ESP_OK)
  {
    nvs_sync_unlock();
    return false;
  }
  return commit();
}

bool ESP_nvs::setObject(const char *key, void *value, size_t length)
{
  nvs_sync_lock();
  _err = nvs_set_blob(_nvs_handle, key, value, length);
  if (_err != ESP_OK)
  {
    nvs_sync_unlock();
    return false;
  }
  return commit();
}

bool ESP_nvs::getBoolean(const char *key, bool defaultValue)
{
  int8_t ret;
  nvs_sync_lock();
  _err = nvs_get_i8(_nvs_handle, key, &ret);
  if (_err == ESP_OK)
  {
    nvs_sync_unlock();
    return ret == 1;
  }
  nvs_sync_unlock();
  return defaultValue;
}

uint8_t ESP_nvs::getUInt8(const char *key, uint8_t defaultValue)
{
  uint8_t ret;
  nvs_sync_lock();
  _err = nvs_get_u8(_nvs_handle, key, &ret);
  if (_err == ESP_OK)
  {
    nvs_sync_unlock();
    return ret;
  }
  nvs_sync_unlock();
  return defaultValue;
}

int16_t ESP_nvs::getInt16(const char *key, int16_t defaultValue)
{
  int16_t ret;
  nvs_sync_lock();
  _err = nvs_get_i16(_nvs_handle, key, &ret);
  if (_err == ESP_OK)
  {
    nvs_sync_unlock();
    return ret;
  }
  nvs_sync_unlock();
  return defaultValue;
}

uint16_t ESP_nvs::getUInt16(const char *key, uint16_t defaultValue)
{
  uint16_t ret;
  nvs_sync_lock();
  _err = nvs_get_u16(_nvs_handle, key, &ret);
  if (_err == ESP_OK)
  {
    nvs_sync_unlock();
    return ret;
  }
  nvs_sync_unlock();
  return defaultValue;
}

int32_t ESP_nvs::getInt32(const char *key, int32_t defaultValue)
{
  int32_t ret;
  nvs_sync_lock();
  _err = nvs_get_i32(_nvs_handle, key, &ret);
  if (_err == ESP_OK)
  {
    nvs_sync_unlock();
    return ret;
  }
  nvs_sync_unlock();
  return defaultValue;
}

uint32_t ESP_nvs::getUInt32(const char *key, uint32_t defaultValue)
{
  uint32_t ret;
  nvs_sync_lock();
  _err = nvs_get_u32(_nvs_handle, key, &ret);
  if (_err == ESP_OK)
  {
    nvs_sync_unlock();
    return ret;
  }
  nvs_sync_unlock();
  return defaultValue;
}

int64_t ESP_nvs::getInt64(const char *key, int64_t defaultValue)
{
  int64_t ret;
  nvs_sync_lock();
  _err = nvs_get_i64(_nvs_handle, key, &ret);
  if (_err == ESP_OK)
  {
    nvs_sync_unlock();
    return ret;
  }
  nvs_sync_unlock();
  return defaultValue;
}

uint64_t ESP_nvs::getUInt64(const char *key, uint64_t defaultValue)
{
  uint64_t ret;
  nvs_sync_lock();
  _err = nvs_get_u64(_nvs_handle, key, &ret);
  if (_err == ESP_OK)
  {
    nvs_sync_unlock();
    return ret;
  }
  nvs_sync_unlock();
  return defaultValue;
}

float ESP_nvs::getFloat(const char *key, float defaultValue)
{
  float *ret = (float *)getObject(key, &defaultValue);
  return *ret;
}
double ESP_nvs::getDouble(const char *key, double defaultValue)
{
  double *ret = (double *)getObject(key, &defaultValue);
  return *ret;
}

char *ESP_nvs::getCharArray(const char *key, const char *defaultValue)
{
  nvs_sync_lock();
  size_t required_size;
  _err = nvs_get_str(_nvs_handle, key, NULL, &required_size);
  if (_err != ESP_OK)
  {
    nvs_sync_unlock();
    if (defaultValue == nullptr)
      return nullptr;
    return strdup(defaultValue);
  }
  char *value = (char *)malloc(required_size);
  nvs_get_str(_nvs_handle, key, value, &required_size);
  nvs_sync_unlock();
  return value;
}

char *ESP_nvs::getCharArray(const char *key, size_t *required_size, const char *defaultValue)
{
  nvs_sync_lock();
  _err = nvs_get_str(_nvs_handle, key, NULL, required_size);
  if (_err != ESP_OK)
  {
    nvs_sync_unlock();
    return strdup(defaultValue);
  }
  char *value = (char *)malloc(*required_size);
  nvs_get_str(_nvs_handle, key, value, required_size);
  nvs_sync_unlock();
  return value;
}

void *ESP_nvs::getObject(const char *key, void *defaultValue)
{
  size_t required_size;
  nvs_sync_lock();
  _err = nvs_get_blob(_nvs_handle, key, NULL, &required_size);
  if (_err != ESP_OK)
  {
    nvs_sync_unlock();
    return defaultValue;
  }
  void *blob = (void *)malloc(required_size);
  nvs_get_blob(_nvs_handle, key, blob, &required_size);
  nvs_sync_unlock();
  return blob;
}

bool ESP_nvs::eraseAll()
{
  nvs_sync_lock();
  _err = nvs_erase_all(_nvs_handle);
  if (_err != ESP_OK)
  {
    nvs_sync_unlock();
    return false;
  }
  return commit();
}

bool ESP_nvs::erase(const char *key)
{
  nvs_sync_lock();
  _err = nvs_erase_key(_nvs_handle, key);
  if (_err != ESP_OK)
  {
    nvs_sync_unlock();
    return false;
  }
  return commit();
}

bool ESP_nvs::commit()
{
  _err = nvs_commit(_nvs_handle);
  if (_err != ESP_OK)
  {
    nvs_sync_unlock();
    return false;
  }
  nvs_sync_unlock();
  return true;
}

esp_err_t ESP_nvs::nvs_sync_create()
{
  if (nvs_sync_mutex != nullptr)
    return ESP_OK;

  nvs_sync_mutex = xSemaphoreCreateMutex();

  return nvs_sync_mutex ? ESP_OK : ESP_FAIL;
}

void ESP_nvs::nvs_sync_free()
{
  if (nvs_sync_mutex != nullptr)
  {
    vSemaphoreDelete(nvs_sync_mutex);
    nvs_sync_mutex = nullptr;
  }
}

bool ESP_nvs::nvs_sync_lock()
{
  return nvs_sync_mutex ? (xSemaphoreTake(nvs_sync_mutex, portMAX_DELAY) == pdTRUE) : false;
}

void ESP_nvs::nvs_sync_unlock()
{
  xSemaphoreGive(nvs_sync_mutex);
}

ESP_nvs NVS;
