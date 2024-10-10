#include "include/NVS.h"
#include "string.h"

#define CHECK_LEN(key)                         \
  if (strlen(key) > NVS_KEY_NAME_MAX_SIZE - 1) \
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
  {
    ESP_ERROR_CHECK(_err);
    return;
  }

  _err = open(namespace_name, open_mode);
}

Nvs::~Nvs()
{
  close();
  deinit();
}

esp_err_t Nvs::init(const char *partition_label)
{
  CHECK_LEN(partition_label);

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
  CHECK_LEN(namespace_name);
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
  CHECK_LEN(key);
  _err = nvs_set_i16(_nvs_handle, key, value);
  if (_err != ESP_OK)
    return _err;
  return nvs_commit(_nvs_handle);
}

esp_err_t Nvs::setUInt16(const char *key, uint16_t value)
{
  CHECK_LEN(key);
  _err = nvs_set_u16(_nvs_handle, key, value);
  if (_err != ESP_OK)
    return _err;
  return nvs_commit(_nvs_handle);
}

esp_err_t Nvs::setInt32(const char *key, int32_t value)
{
  CHECK_LEN(key);
  _err = nvs_set_i32(_nvs_handle, key, value);
  if (_err != ESP_OK)
    return _err;
  return nvs_commit(_nvs_handle);
}

esp_err_t Nvs::setUInt32(const char *key, uint32_t value)
{
  CHECK_LEN(key);
  _err = nvs_set_u32(_nvs_handle, key, value);
  if (_err != ESP_OK)
    return _err;
  return nvs_commit(_nvs_handle);
}

esp_err_t Nvs::setInt64(const char *key, int64_t value)
{
  CHECK_LEN(key);
  _err = nvs_set_i64(_nvs_handle, key, value);
  if (_err != ESP_OK)
    return _err;
  return nvs_commit(_nvs_handle);
}

esp_err_t Nvs::setUInt64(const char *key, uint64_t value)
{
  CHECK_LEN(key);
  _err = nvs_set_u64(_nvs_handle, key, value);
  if (_err != ESP_OK)
    return _err;
  return nvs_commit(_nvs_handle);
}

esp_err_t Nvs::setFloat(const char *key, float value)
{
  CHECK_LEN(key);
  return setObject(key, &value, sizeof(float));
}

esp_err_t Nvs::setDouble(const char *key, double value)
{
  CHECK_LEN(key);
  return setObject(key, &value, sizeof(double));
}

esp_err_t Nvs::setCharArray(const char *key, const char *value)
{
  CHECK_LEN(key);
  if (value == nullptr)
  {
    erase(key);
    return true;
  }

  if (strlen(key) > 3999)
    return ESP_ERR_INVALID_ARG;

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

esp_err_t Nvs::check_key_and_type(const char *key, nvs_type_t checkType)
{
  if (strlen(key) > NVS_KEY_NAME_MAX_SIZE - 1)
    return ESP_FAIL;

  nvs_type_t *type = NULL;
  esp_err_t _err = nvs_find_key(_nvs_handle, key, type);
  if (_err != ESP_OK || type == nullptr || *type != checkType)
    return ESP_FAIL;
  return ESP_OK;
}

bool Nvs::getBoolean(const char *key, bool defaultValue)
{
  if (check_key_and_type(key, NVS_TYPE_I8) == ESP_FAIL)
    return defaultValue;

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
  if (check_key_and_type(key, NVS_TYPE_U8) == ESP_FAIL)
    return defaultValue;

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
  if (check_key_and_type(key, NVS_TYPE_I16) == ESP_FAIL)
    return defaultValue;

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
  if (check_key_and_type(key, NVS_TYPE_U16) == ESP_FAIL)
    return defaultValue;

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
  if (check_key_and_type(key, NVS_TYPE_I32) == ESP_FAIL)
    return defaultValue;

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
  if (check_key_and_type(key, NVS_TYPE_U32) == ESP_FAIL)
    return defaultValue;

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
  if (check_key_and_type(key, NVS_TYPE_I64) == ESP_FAIL)
    return defaultValue;

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
  if (check_key_and_type(key, NVS_TYPE_U64) == ESP_FAIL)
    return defaultValue;

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
  // all checks are done in getObject
  float *ret = (float *)getObject(key, &defaultValue);
  return *ret;
}

double Nvs::getDouble(const char *key, double defaultValue)
{
  // all checks are done in getObject
  double *ret = (double *)getObject(key, &defaultValue);
  return *ret;
}

char *Nvs::getCharArray(const char *key, const char *defaultValue)
{
  if (check_key_and_type(key, NVS_TYPE_STR) == ESP_FAIL)
  {
    if (defaultValue == nullptr)
      return nullptr;
    return strdup(defaultValue);
  }

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

void *Nvs::getObject(const char *key, void *defaultValue)
{
  if (check_key_and_type(key, NVS_TYPE_BLOB) == ESP_FAIL)
    return defaultValue;

  size_t required_size;
  _err = nvs_get_blob(_nvs_handle, key, NULL, &required_size);
  if (_err != ESP_OK)
    return defaultValue;

  void *blob = (void *)malloc(required_size);
  nvs_get_blob(_nvs_handle, key, blob, &required_size);
  return blob;
}

esp_err_t Nvs::eraseAll()
{
  _err = nvs_erase_all(_nvs_handle);
  if (_err != ESP_OK)
    return _err;
  return nvs_commit(_nvs_handle);
}

esp_err_t Nvs::erase(const char *key)
{
  CHECK_LEN(key);
  _err = nvs_erase_key(_nvs_handle, key);
  if (_err != ESP_OK)
    return _err;
  return nvs_commit(_nvs_handle);
}
