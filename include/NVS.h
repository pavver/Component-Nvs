#pragma once

#include "esp_err.h"
#include "esp_partition.h"
#include "freertos/FreeRTOS.h"
#include "nvs_flash.h"
#include <freertos/semphr.h>
#include <freertos/task.h>

class Nvs
{
public:
  Nvs();
  Nvs(const char *partition_label);
  Nvs(const char *partition_label, const char *namespace_name, nvs_open_mode_t open_mode = NVS_READWRITE);
  ~Nvs();

  esp_err_t init(const char *partition_label);
  esp_err_t deinit();

  esp_err_t open(const char *namespace_name, nvs_open_mode_t open_mode = NVS_READWRITE);
  void close();

  bool eraseAll();
  bool erase(const char *key);

  /**
   * @brief set bool value for given key
   *
   * @param[in] key Key name. Maximum length is (NVS_KEY_NAME_MAX_SIZE-1) characters. Shouldn't be empty.
   * @param[in] value The value to set.
   * @return
   *             - ESP_OK if value was set successfully
   *             - ESP_FAIL if there is an internal error; most likely due to corrupted
   *               NVS partition (only if NVS assertion checks are disabled)
   *             - ESP_ERR_NVS_INVALID_HANDLE if handle has been closed or is NULL
   *             - ESP_ERR_NVS_READ_ONLY if storage handle was opened as read only
   *             - ESP_ERR_NVS_INVALID_NAME if key name doesn't satisfy constraints
   *             - ESP_ERR_NVS_NOT_ENOUGH_SPACE if there is not enough space in the
   *               underlying storage to save the value
   *             - ESP_ERR_NVS_REMOVE_FAILED if the value wasn't updated because flash
   *               write operation has failed. The value was written however, and
   *               update will be finished after re-initialization of nvs, provided that
   *               flash operation doesn't fail again.
   */
  esp_err_t setBoolean(const char *key, bool value);

  /**
   * @brief set uint8_t value for given key
   *
   * @param[in] key Key name. Maximum length is (NVS_KEY_NAME_MAX_SIZE-1) characters. Shouldn't be empty.
   * @param[in] value The value to set.
   * @return
   *             - ESP_OK if value was set successfully
   *             - ESP_FAIL if there is an internal error; most likely due to corrupted
   *               NVS partition (only if NVS assertion checks are disabled)
   *             - ESP_ERR_NVS_INVALID_HANDLE if handle has been closed or is NULL
   *             - ESP_ERR_NVS_READ_ONLY if storage handle was opened as read only
   *             - ESP_ERR_NVS_INVALID_NAME if key name doesn't satisfy constraints
   *             - ESP_ERR_NVS_NOT_ENOUGH_SPACE if there is not enough space in the
   *               underlying storage to save the value
   *             - ESP_ERR_NVS_REMOVE_FAILED if the value wasn't updated because flash
   *               write operation has failed. The value was written however, and
   *               update will be finished after re-initialization of nvs, provided that
   *               flash operation doesn't fail again.
   */
  esp_err_t setUInt8(const char *key, uint8_t value);

  /**
   * @brief set int16_t value for given key
   *
   * @param[in] key Key name. Maximum length is (NVS_KEY_NAME_MAX_SIZE-1) characters. Shouldn't be empty.
   * @param[in] value The value to set.
   * @return
   *             - ESP_OK if value was set successfully
   *             - ESP_FAIL if there is an internal error; most likely due to corrupted
   *               NVS partition (only if NVS assertion checks are disabled)
   *             - ESP_ERR_NVS_INVALID_HANDLE if handle has been closed or is NULL
   *             - ESP_ERR_NVS_READ_ONLY if storage handle was opened as read only
   *             - ESP_ERR_NVS_INVALID_NAME if key name doesn't satisfy constraints
   *             - ESP_ERR_NVS_NOT_ENOUGH_SPACE if there is not enough space in the
   *               underlying storage to save the value
   *             - ESP_ERR_NVS_REMOVE_FAILED if the value wasn't updated because flash
   *               write operation has failed. The value was written however, and
   *               update will be finished after re-initialization of nvs, provided that
   *               flash operation doesn't fail again.
   */
  esp_err_t setInt16(const char *key, int16_t value);

  /**
   * @brief set uint16_t value for given key
   *
   * @param[in] key Key name. Maximum length is (NVS_KEY_NAME_MAX_SIZE-1) characters. Shouldn't be empty.
   * @param[in] value The value to set.
   * @return
   *             - ESP_OK if value was set successfully
   *             - ESP_FAIL if there is an internal error; most likely due to corrupted
   *               NVS partition (only if NVS assertion checks are disabled)
   *             - ESP_ERR_NVS_INVALID_HANDLE if handle has been closed or is NULL
   *             - ESP_ERR_NVS_READ_ONLY if storage handle was opened as read only
   *             - ESP_ERR_NVS_INVALID_NAME if key name doesn't satisfy constraints
   *             - ESP_ERR_NVS_NOT_ENOUGH_SPACE if there is not enough space in the
   *               underlying storage to save the value
   *             - ESP_ERR_NVS_REMOVE_FAILED if the value wasn't updated because flash
   *               write operation has failed. The value was written however, and
   *               update will be finished after re-initialization of nvs, provided that
   *               flash operation doesn't fail again.
   */
  esp_err_t setUInt16(const char *key, uint16_t value);

  /**
   * @brief set int32_t value for given key
   *
   * @param[in] key Key name. Maximum length is (NVS_KEY_NAME_MAX_SIZE-1) characters. Shouldn't be empty.
   * @param[in] value The value to set.
   * @return
   *             - ESP_OK if value was set successfully
   *             - ESP_FAIL if there is an internal error; most likely due to corrupted
   *               NVS partition (only if NVS assertion checks are disabled)
   *             - ESP_ERR_NVS_INVALID_HANDLE if handle has been closed or is NULL
   *             - ESP_ERR_NVS_READ_ONLY if storage handle was opened as read only
   *             - ESP_ERR_NVS_INVALID_NAME if key name doesn't satisfy constraints
   *             - ESP_ERR_NVS_NOT_ENOUGH_SPACE if there is not enough space in the
   *               underlying storage to save the value
   *             - ESP_ERR_NVS_REMOVE_FAILED if the value wasn't updated because flash
   *               write operation has failed. The value was written however, and
   *               update will be finished after re-initialization of nvs, provided that
   *               flash operation doesn't fail again.
   */
  esp_err_t setInt32(const char *key, int32_t value);

  /**
   * @brief set uint32_t value for given key
   *
   * @param[in] key Key name. Maximum length is (NVS_KEY_NAME_MAX_SIZE-1) characters. Shouldn't be empty.
   * @param[in] value The value to set.
   * @return
   *             - ESP_OK if value was set successfully
   *             - ESP_FAIL if there is an internal error; most likely due to corrupted
   *               NVS partition (only if NVS assertion checks are disabled)
   *             - ESP_ERR_NVS_INVALID_HANDLE if handle has been closed or is NULL
   *             - ESP_ERR_NVS_READ_ONLY if storage handle was opened as read only
   *             - ESP_ERR_NVS_INVALID_NAME if key name doesn't satisfy constraints
   *             - ESP_ERR_NVS_NOT_ENOUGH_SPACE if there is not enough space in the
   *               underlying storage to save the value
   *             - ESP_ERR_NVS_REMOVE_FAILED if the value wasn't updated because flash
   *               write operation has failed. The value was written however, and
   *               update will be finished after re-initialization of nvs, provided that
   *               flash operation doesn't fail again.
   */
  esp_err_t setUInt32(const char *key, uint32_t value);

  /**
   * @brief set int64_t value for given key
   *
   * @param[in] key Key name. Maximum length is (NVS_KEY_NAME_MAX_SIZE-1) characters. Shouldn't be empty.
   * @param[in] value The value to set.
   * @return
   *             - ESP_OK if value was set successfully
   *             - ESP_FAIL if there is an internal error; most likely due to corrupted
   *               NVS partition (only if NVS assertion checks are disabled)
   *             - ESP_ERR_NVS_INVALID_HANDLE if handle has been closed or is NULL
   *             - ESP_ERR_NVS_READ_ONLY if storage handle was opened as read only
   *             - ESP_ERR_NVS_INVALID_NAME if key name doesn't satisfy constraints
   *             - ESP_ERR_NVS_NOT_ENOUGH_SPACE if there is not enough space in the
   *               underlying storage to save the value
   *             - ESP_ERR_NVS_REMOVE_FAILED if the value wasn't updated because flash
   *               write operation has failed. The value was written however, and
   *               update will be finished after re-initialization of nvs, provided that
   *               flash operation doesn't fail again.
   */
  esp_err_t setInt64(const char *key, int64_t value);

  /**
   * @brief set uint64_t value for given key
   *
   * @param[in] key Key name. Maximum length is (NVS_KEY_NAME_MAX_SIZE-1) characters. Shouldn't be empty.
   * @param[in] value The value to set.
   * @return
   *             - ESP_OK if value was set successfully
   *             - ESP_FAIL if there is an internal error; most likely due to corrupted
   *               NVS partition (only if NVS assertion checks are disabled)
   *             - ESP_ERR_NVS_INVALID_HANDLE if handle has been closed or is NULL
   *             - ESP_ERR_NVS_READ_ONLY if storage handle was opened as read only
   *             - ESP_ERR_NVS_INVALID_NAME if key name doesn't satisfy constraints
   *             - ESP_ERR_NVS_NOT_ENOUGH_SPACE if there is not enough space in the
   *               underlying storage to save the value
   *             - ESP_ERR_NVS_REMOVE_FAILED if the value wasn't updated because flash
   *               write operation has failed. The value was written however, and
   *               update will be finished after re-initialization of nvs, provided that
   *               flash operation doesn't fail again.
   */
  esp_err_t setUInt64(const char *key, uint64_t value);

  /**
   * @brief set double value for given key
   *
   * @param[in] key Key name. Maximum length is (NVS_KEY_NAME_MAX_SIZE-1) characters. Shouldn't be empty.
   * @param[in] value The value to set.
   * @return
   *             - ESP_OK if value was set successfully
   *             - ESP_FAIL if there is an internal error; most likely due to corrupted
   *               NVS partition (only if NVS assertion checks are disabled)
   *             - ESP_ERR_NVS_INVALID_HANDLE if handle has been closed or is NULL
   *             - ESP_ERR_NVS_READ_ONLY if storage handle was opened as read only
   *             - ESP_ERR_NVS_INVALID_NAME if key name doesn't satisfy constraints
   *             - ESP_ERR_NVS_NOT_ENOUGH_SPACE if there is not enough space in the
   *               underlying storage to save the value
   *             - ESP_ERR_NVS_REMOVE_FAILED if the value wasn't updated because flash
   *               write operation has failed. The value was written however, and
   *               update will be finished after re-initialization of nvs, provided that
   *               flash operation doesn't fail again.
   */
  esp_err_t setDouble(const char *key, double value);

  /**
   * @brief set float value for given key
   *
   * @param[in] key Key name. Maximum length is (NVS_KEY_NAME_MAX_SIZE-1) characters. Shouldn't be empty.
   * @param[in] value The value to set.
   * @return
   *             - ESP_OK if value was set successfully
   *             - ESP_FAIL if there is an internal error; most likely due to corrupted
   *               NVS partition (only if NVS assertion checks are disabled)
   *             - ESP_ERR_NVS_INVALID_HANDLE if handle has been closed or is NULL
   *             - ESP_ERR_NVS_READ_ONLY if storage handle was opened as read only
   *             - ESP_ERR_NVS_INVALID_NAME if key name doesn't satisfy constraints
   *             - ESP_ERR_NVS_NOT_ENOUGH_SPACE if there is not enough space in the
   *               underlying storage to save the value
   *             - ESP_ERR_NVS_REMOVE_FAILED if the value wasn't updated because flash
   *               write operation has failed. The value was written however, and
   *               update will be finished after re-initialization of nvs, provided that
   *               flash operation doesn't fail again.
   */
  esp_err_t setFloat(const char *key, float value);

  /**
   * @brief set string value for given key
   *
   * @param[in] key Key name. Maximum length is (NVS_KEY_NAME_MAX_SIZE-1) characters. Shouldn't be empty.
   * @param[in] value The value to set.
   * @return
   *             - ESP_OK if value was set successfully
   *             - ESP_FAIL if there is an internal error; most likely due to corrupted
   *               NVS partition (only if NVS assertion checks are disabled)
   *             - ESP_ERR_NVS_INVALID_HANDLE if handle has been closed or is NULL
   *             - ESP_ERR_NVS_READ_ONLY if storage handle was opened as read only
   *             - ESP_ERR_NVS_INVALID_NAME if key name doesn't satisfy constraints
   *             - ESP_ERR_NVS_NOT_ENOUGH_SPACE if there is not enough space in the
   *               underlying storage to save the value
   *             - ESP_ERR_NVS_REMOVE_FAILED if the value wasn't updated because flash
   *               write operation has failed. The value was written however, and
   *               update will be finished after re-initialization of nvs, provided that
   *               flash operation doesn't fail again.
   */
  esp_err_t setCharArray(const char *key, const char *value);

  /**
   * @brief set object value for given key
   *
   * @param[in] key Key name. Maximum length is (NVS_KEY_NAME_MAX_SIZE-1) characters. Shouldn't be empty.
   * @param[in] value The value to set.
   * @return
   *             - ESP_OK if value was set successfully
   *             - ESP_FAIL if there is an internal error; most likely due to corrupted
   *               NVS partition (only if NVS assertion checks are disabled)
   *             - ESP_ERR_NVS_INVALID_HANDLE if handle has been closed or is NULL
   *             - ESP_ERR_NVS_READ_ONLY if storage handle was opened as read only
   *             - ESP_ERR_NVS_INVALID_NAME if key name doesn't satisfy constraints
   *             - ESP_ERR_NVS_NOT_ENOUGH_SPACE if there is not enough space in the
   *               underlying storage to save the value
   *             - ESP_ERR_NVS_REMOVE_FAILED if the value wasn't updated because flash
   *               write operation has failed. The value was written however, and
   *               update will be finished after re-initialization of nvs, provided that
   *               flash operation doesn't fail again.
   */
  esp_err_t setObject(const char *key, void *object, size_t length);

  /**
   * @param[in] key Key name. Maximum length is (NVS_KEY_NAME_MAX_SIZE-1) characters. Shouldn't be empty.
   * @param[in] default_value
   * @return returns the read value, or default_value if the value could not be read
   */
  bool getBoolean(const char *key, bool default_value);

  int8_t getInt8(const char *key, int8_t default_value);
  uint8_t getUInt8(const char *key, uint8_t default_value);

  int16_t getInt16(const char *key, int16_t default_value);
  uint16_t getUInt16(const char *key, uint16_t default_value);

  int32_t getInt32(const char *key, int32_t default_value);
  uint32_t getUInt32(const char *key, uint32_t default_value);

  int64_t getInt64(const char *key, int64_t default_value);
  uint64_t getUInt64(const char *key, uint64_t default_value);

  double getDouble(const char *key, double default_value);
  float getFloat(const char *key, float default_value);
  char *getCharArray(const char *key, const char *default_value);

  char *getCharArray(const char *key, size_t *required_size, const char *defaultValue);
  void *getObject(const char *key, void *defaultValue);

  bool exists(const char *key);

  const esp_partition_t *_partition = NULL;

  esp_err_t last_error() { return _err; }

private:
  esp_err_t _err = ESP_OK;
  nvs_handle_t _nvs_handle;
  SemaphoreHandle_t nvs_sync_mutex;
};
