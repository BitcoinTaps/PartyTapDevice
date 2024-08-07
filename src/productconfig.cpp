#include <productconfig.h>

#include <LittleFS.h>

#define PRODUCT_CONFIG_NUMPRODUCTS "numproducts"
#define PRODUCT_CONFIG_DEVICEKEY "devicekey"
#define PRODUCT_CONFIG_PRODUCT  "product"
#define PRODUCT_CONFIG_SWITCHID "switchid"
#define PRODUCT_CONFIG_LABEL "label"
#define PRODUCT_CONFIG_TAPDURATION "tapduration"
#define PRODUCT_CONFIG_AMOUNT "amount"
#define PRODUCT_CONFIG_CURRENCY "currency"

#define STR1(x)  #x
#define STR(x)  STR1(x)    

ProductConfig::ProductConfig() {
    this->numProducts = 0;
    this->key = "0000111122224444";

    // the extension version of the PartyTap extension at the server. If no version is provided, it is assumed that this is the version
    this->serverVersion = "";
    this->serverBranding = "";
}

int ProductConfig::getNumProducts() {
    return this->numProducts;
}

TapProduct *ProductConfig::getProduct(int i) {
    return &(this->product[i]);
}

const char *ProductConfig::getKey() {
    return this->key.c_str();
}

const char *ProductConfig::getServerVersion() {
    return this->serverVersion.c_str();
}

bool ProductConfig::parse(DynamicJsonDocument *doc) {
#ifdef DEBUG
    Serial.println("[ProductConfig::parse]");
#endif

    this->numProducts = 0;
    

    if ( doc->containsKey("version")) {
        this->serverVersion = (*doc)["version"].as<const char *>();
#ifdef DEBUG
        Serial.printf("[ProductConfig::parse] Server version: '%s'\n",this->serverVersion.c_str());
#endif
    }

    if ( doc->containsKey("branding")) {
        this->serverBranding = (*doc)["branding"].as<const char *>();
#ifdef DEBUG
        Serial.printf("[ProductConfig::parse] Server branding: '%s'\n",this->serverBranding.c_str());
#endif
    }

    if ( doc->containsKey("key") ) {
        this->key = (*doc)["key"].as<const char *>();    
#ifdef DEBUG
        Serial.printf("[ProductConfig::parse] Got encryption key\n");
#endif
    }

    if ( ! doc->containsKey("switches")) {
#ifdef DEBUG
        Serial.printf("[ProductConfig::parse] No switches in config\n");
#endif
        return true;        
    }

    JsonArray switches = (*doc)["switches"].as<JsonArray>();
    this->numProducts = switches.size() < PARTYTAP_CFG_MAX_PRODUCTS ? switches.size() : PARTYTAP_CFG_MAX_PRODUCTS;
#ifdef DEBUG
    Serial.printf("[ProductConfig::parse] num products = %d\n",this->numProducts);
#endif

    for (int i=0;i < this->numProducts;i++) {
        JsonObject obj = switches[i];
        this->product[i].setSwitchID(obj["id"].as<const char *>());
        this->product[i].setLabel(obj["label"].as<const char *>());
        this->product[i].setTapDuration(obj["duration"].as<int>());
        this->product[i].setCurrency(obj["currency"].as<const char *>());
        this->product[i].setAmount(obj["amount"].as<float>());

        this->product[i].initPayString();
    }


#ifdef DEBUG
    Serial.println("[ProductConfig::parse] succesfully completed");
#endif

    return true;
}

bool ProductConfig::save() {
#ifdef DEBUG
    Serial.println("[ProductConfig::save]");
#endif
    File file = LittleFS.open("/switches.json", "w");
    if (!file) {
        return false;
    }

    DynamicJsonDocument doc(2048);
    int item = 0;

    // store number of products
    doc[item]["name"] = PRODUCT_CONFIG_NUMPRODUCTS;
    doc[item]["value"] = this->numProducts;        
    item++;

    doc[item]["name"] = PRODUCT_CONFIG_DEVICEKEY;
    doc[item]["value"]= this->key;
    item++;

    for (int i=0;(i<this->numProducts);i++ ) {
        doc[item]["name"] = PRODUCT_CONFIG_PRODUCT;
        doc[item][PRODUCT_CONFIG_SWITCHID] = this->product[i].getSwitchID();
        doc[item][PRODUCT_CONFIG_LABEL] = this->product[i].getLabel();
        doc[item][PRODUCT_CONFIG_TAPDURATION] = this->product[i].getTapDuration();
        doc[item][PRODUCT_CONFIG_AMOUNT] = this->product[i].getAmount();
        doc[item][PRODUCT_CONFIG_CURRENCY] = this->product[i].getCurrency();
        item++;
    }

    String output = "";
    serializeJson(doc, output);
    serializeJson(doc, file);
    file.close();

    return true;
}

const char *ProductConfig::getServerBranding() {
    return this->serverBranding.c_str();
}

bool ProductConfig::load() {
    File file = LittleFS.open("/switches.json", "r");
    if (!file) {
        return false;
    }

    String content = file.readString();
    DynamicJsonDocument doc(2048);
    DeserializationError error = deserializeJson(doc, content);
    file.close();

    if ( error.code() !=  DeserializationError::Ok ) {
        return false;
    }

    JsonArray arr = doc.as<JsonArray>();
    int item = 0;
    for (JsonObject obj: arr) {
        String name = obj["name"];

        if ( name == PRODUCT_CONFIG_NUMPRODUCTS ) {
            this->numProducts = obj["value"].as<int>();
        } else if ( name == PRODUCT_CONFIG_DEVICEKEY ) {
            this->key = obj["value"].as<const char *>();
        } else if ( name == PRODUCT_CONFIG_PRODUCT ) {
            this->product[item].setSwitchID(obj[PRODUCT_CONFIG_SWITCHID].as<const char *>());
            this->product[item].setLabel(obj[PRODUCT_CONFIG_LABEL].as<const char *>());
            this->product[item].setTapDuration(obj[PRODUCT_CONFIG_TAPDURATION].as<int>());
            this->product[item].setAmount(obj[PRODUCT_CONFIG_AMOUNT].as<float>());
            this->product[item].setCurrency(obj[PRODUCT_CONFIG_CURRENCY].as<const char *>());
            this->product[item].initPayString();
            item++;                   
        }
      }

      return true;
}