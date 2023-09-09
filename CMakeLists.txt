idf_component_register(SRCS "ESP_nvs.cpp"
                    INCLUDE_DIRS "include"
                    REQUIRES "esp_partition nvs_flash"
                    )
