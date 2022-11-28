#include "configuration_store.hpp"
#include "configuration_store.h"
LOG_COMPONENT_DEF(ConfigurationStoreLog, LOG_SEVERITY_DEBUG);
using namespace configuration_store;

ConfigurationStore &config_store() {
    return ConfigurationStore::GetStore();
}
FreeRTOS_Mutex &configuration_store::get_item_mutex() {
    static FreeRTOS_Mutex mutex;
    return mutex;
}
void ConfigurationStore::init() {
    ItemUpdater updater(*this);
    std::visit([&](auto &access) { access.init(updater); },
        backend);
}

ConfigurationStore &ConfigurationStore::GetStore() {
    static ConfigurationStore store(EepromAccess {});
    return store;
}

/**
 * @brief sets values of items to their default value and invalidates data in eeprom
 * @tparam CONFIG
 */
void ConfigurationStore::factory_reset() {
    // just invalidate the eeprom and reset the printer
    std::unique_lock lock(get_item_mutex());
    std::visit([&](auto &access) { access.reset(); },
        backend);
}
