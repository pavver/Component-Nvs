#include "Nvs.h"
#include "esp_partition.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "string.h"
#include <esp_err.h>
#include <freertos/semphr.h>

#define CHECK_LEN_DEF(key, len, defaultValue) \
  if (strlen(key) > len)                      \
  {                                           \
    _err = ESP_ERR_INVALID_ARG;               \
    return defaultValue;                      \
  }

#define CHECK_LEN(key, len) \
  if (strlen(key) > len)    \
    return ESP_ERR_INVALID_ARG;

const char *defaultNvsPartitionName = "nvs";

Nvs::Nvs() : Nvs(defaultNvsPartitionName)
{
}

Nvs::Nvs(const char *partition_label) : Nvs(partition_label, partition_label, NVS_READWRITE)
{
}

Nvs::Nvs(const char *partition_label, const char *namespace_name, nvs_open_mode_t open_mode)
{
  _err = init(partition_label);

  if (_err != ESP_OK)
    return;

  _err = open(namespace_name, open_mode);
}

Nvs::~Nvs()
{
  close();
  deinit();
}

esp_err_t Nvs::init(const char *partition_label)
{
  CHECK_LEN(partition_label, 16);

  _partition = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_NVS, partition_label);
  if (_partition == NULL)
    return ESP_FAIL;

  _err = nvs_flash_init_partition_ptr(_partition);

  if (_err == ESP_ERR_NVS_NO_FREE_PAGES)
    _err = nvs_flash_erase_partition_ptr(_partition);

  return nvs_flash_init_partition_ptr(_partition);
}

esp_err_t Nvs::deinit()
{
  _err = nvs_flash_deinit_partition(_partition->label);
  _partition = NULL;
  return _err;
}

esp_err_t Nvs::open(const char *namespace_name, nvs_open_mode_t open_mode)
{
  CHECK_LEN(namespace_name, 16);
  return nvs_open_from_partition(_partition->label, namespace_name, open_mode, &_nvs_handle);
}

void Nvs::close()
{
  nvs_close(_nvs_handle);
}

esp_err_t Nvs::setBoolean(const char *key, bool value)
{
  _err = nvs_set_i8(_nvs_handle, key, value ? 1 : 0);
  if (_err != ESP_OK)
    return _err;
  return nvs_commit(_nvs_handle);
}

esp_err_t Nvs::setUInt8(const char *key, uint8_t value)
{
  _err = nvs_set_u8(_nvs_handle, key, value);
  if (_err != ESP_OK)
    return _err;
  return nvs_commit(_nvs_handle);
}

esp_err_t Nvs::setInt16(const char *key, int16_t value)
{
  CHECK_LEN(key, 16);
  _err = nvs_set_i16(_nvs_handle, key, value);
  if (_err != ESP_OK)
    return _err;
  return nvs_commit(_nvs_handle);
}

esp_err_t Nvs::setUInt16(const char *key, uint16_t value)
{
  CHECK_LEN(key, 16);
  _err = nvs_set_u16(_nvs_handle, key, value);
  if (_err != ESP_OK)
    return _err;
  return nvs_commit(_nvs_handle);
}

esp_err_t Nvs::setInt32(const char *key, int32_t value)
{
  CHECK_LEN(key, 16);
  _err = nvs_set_i32(_nvs_handle, key, value);
  if (_err != ESP_OK)
    return _err;
  return nvs_commit(_nvs_handle);
}

esp_err_t Nvs::setUInt32(const char *key, uint32_t value)
{
  CHECK_LEN(key, 16);
  _err = nvs_set_u32(_nvs_handle, key, value);
  if (_err != ESP_OK)
    return _err;
  return nvs_commit(_nvs_handle);
}

esp_err_t Nvs::setInt64(const char *key, int64_t value)
{
  CHECK_LEN(key, 16);
  _err = nvs_set_i64(_nvs_handle, key, value);
  if (_err != ESP_OK)
    return _err;
  return nvs_commit(_nvs_handle);
}

esp_err_t Nvs::setUInt64(const char *key, uint64_t value)
{
  CHECK_LEN(key, 16);
  _err = nvs_set_u64(_nvs_handle, key, value);
  if (_err != ESP_OK)
    return _err;
  return nvs_commit(_nvs_handle);
}

esp_err_t Nvs::setFloat(const char *key, float value)
{
  CHECK_LEN(key, 16);
  return setObject(key, &value, sizeof(float));
}

esp_err_t Nvs::setDouble(const char *key, double value)
{
  CHECK_LEN(key, 16);
  return setObject(key, &value, sizeof(double));
}

esp_err_t Nvs::setCharArray(const char *key, const char *value)
{
  CHECK_LEN(key, 16);
  if (value == nullptr)
  {
    erase(key);
    return true;
  }
  CHECK_LEN(value, 3999);
  _err = nvs_set_str(_nvs_handle, key, value);
  if (_err != ESP_OK)
    return _err;
  return nvs_commit(_nvs_handle);
}

esp_err_t Nvs::setObject(const char *key, void *value, size_t length)
{
  _err = nvs_set_blob(_nvs_handle, key, value, length);
  if (_err != ESP_OK)
    return _err;
  return nvs_commit(_nvs_handle);
}

bool Nvs::getBoolean(const char *key, bool defaultValue)
{
  CHECK_LEN_DEF(key, 16, defaultValue);
  int8_t ret;
  _err = nvs_get_i8(_nvs_handle, key, &ret);
  if (_err == ESP_OK)
  {
    return ret == 1;
  }
  return defaultValue;
}

uint8_t Nvs::getUInt8(const char *key, uint8_t defaultValue)
{
  CHECK_LEN_DEF(key, 16, defaultValue);
  uint8_t ret;
  _err = nvs_get_u8(_nvs_handle, key, &ret);
  if (_err == ESP_OK)
  {
    return ret;
  }
  return defaultValue;
}

int16_t Nvs::getInt16(const char *key, int16_t defaultValue)
{
  CHECK_LEN_DEF(key, 16, defaultValue);
  int16_t ret;
  _err = nvs_get_i16(_nvs_handle, key, &ret);
  if (_err == ESP_OK)
  {
    return ret;
  }
  return defaultValue;
}

uint16_t Nvs::getUInt16(const char *key, uint16_t defaultValue)
{
  CHECK_LEN_DEF(key, 16, defaultValue);
  uint16_t ret;
  _err = nvs_get_u16(_nvs_handle, key, &ret);
  if (_err == ESP_OK)
  {
    return ret;
  }
  return defaultValue;
}

int32_t Nvs::getInt32(const char *key, int32_t defaultValue)
{
  CHECK_LEN_DEF(key, 16, defaultValue);
  int32_t ret;
  _err = nvs_get_i32(_nvs_handle, key, &ret);
  if (_err == ESP_OK)
  {
    return ret;
  }
  return defaultValue;
}

uint32_t Nvs::getUInt32(const char *key, uint32_t defaultValue)
{
  CHECK_LEN_DEF(key, 16, defaultValue);
  uint32_t ret;
  _err = nvs_get_u32(_nvs_handle, key, &ret);
  if (_err == ESP_OK)
  {
    return ret;
  }
  return defaultValue;
}

int64_t Nvs::getInt64(const char *key, int64_t defaultValue)
{
  CHECK_LEN_DEF(key, 16, defaultValue);
  int64_t ret;
  _err = nvs_get_i64(_nvs_handle, key, &ret);
  if (_err == ESP_OK)
  {
    return ret;
  }
  return defaultValue;
}

uint64_t Nvs::getUInt64(const char *key, uint64_t defaultValue)
{
  CHECK_LEN_DEF(key, 16, defaultValue);
  uint64_t ret;
  _err = nvs_get_u64(_nvs_handle, key, &ret);
  if (_err == ESP_OK)
  {
    return ret;
  }
  return defaultValue;
}

float Nvs::getFloat(const char *key, float defaultValue)
{
  CHECK_LEN_DEF(key, 16, defaultValue);
  float *ret = (float *)getObject(key, &defaultValue);
  return *ret;
}

double Nvs::getDouble(const char *key, double defaultValue)
{
  CHECK_LEN(key, 16);
  double *ret = (double *)getObject(key, &defaultValue);
  return *ret;
}

char *Nvs::getCharArray(const char *key, const char *defaultValue)
{
  CHECK_LEN_DEF(key, 16, (char *)defaultValue);
  size_t required_size;
  _err = nvs_get_str(_nvs_handle, key, NULL, &required_size);
  if (_err != ESP_OK)
  {
    if (defaultValue == nullptr)
      return nullptr;
    return strdup(defaultValue);
  }
  char *value = (char *)malloc(required_size);
  nvs_get_str(_nvs_handle, key, value, &required_size);
  return value;
}

char *Nvs::getCharArray(const char *key, size_t *required_size, const char *defaultValue)
{
  CHECK_LEN_DEF(key, 16, (char *)defaultValue);
  _err = nvs_get_str(_nvs_handle, key, NULL, required_size);
  if (_err != ESP_OK)
  {
    return strdup(defaultValue);
  }
  char *value = (char *)malloc(*required_size);
  nvs_get_str(_nvs_handle, key, value, required_size);
  return value;
}

void *Nvs::getObject(const char *key, void *defaultValue)
{
  CHECK_LEN_DEF(key, 16, defaultValue);
  size_t required_size;
  _err = nvs_get_blob(_nvs_handle, key, NULL, &required_size);
  if (_err != ESP_OK)
  {
    return defaultValue;
  }
  void *blob = (void *)malloc(required_size);
  nvs_get_blob(_nvs_handle, key, blob, &required_size);
  return blob;
}

bool Nvs::eraseAll()
{
  _err = nvs_erase_all(_nvs_handle);
  if (_err != ESP_OK)
    return _err;
  return nvs_commit(_nvs_handle);
}

bool Nvs::erase(const char *key)
{
  CHECK_LEN(key, 16);
  _err = nvs_erase_key(_nvs_handle, key);
  if (_err != ESP_OK)
    return _err;
  return nvs_commit(_nvs_handle);
}
