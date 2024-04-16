#ifndef PRODUCTCONFIG_H
#define PRODUCTONFIG_H

#include <ArduinoJson.h>
#include <tapproduct.h>

#define PARTYTAP_CFG_MAX_PRODUCTS 3

class ProductConfig {
    private:
        int numProducts;
        String key;
        TapProduct product[PARTYTAP_CFG_MAX_PRODUCTS];
        String serverVersion;
    public:
        ProductConfig();

        bool load();
        bool save();

        bool parse(DynamicJsonDocument *doc);

        int getNumProducts();

        const char *getKey();

        TapProduct *getProduct(int i);        

        const char *getServerVersion();
};

#endif