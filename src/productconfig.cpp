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


ProductConfig::ProductConfig() {
    this->numProducts = 0;
    this->key = "0000111122224444";

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

bool ProductConfig::parse(DynamicJsonDocument *doc) {
    this->numProducts = 0;
    
#ifdef DEBUG
    Serial.println("ProductCondig::parse");
#endif

    JsonArray switches = (*doc)["switches"].as<JsonArray>();
    this->numProducts = switches.size() < PARTYTAP_CFG_MAX_PRODUCTS ? switches.size() : PARTYTAP_CFG_MAX_PRODUCTS;

#ifdef DEBUG
    Serial.printf("ProductConfig::parse, num produicts = %d\n",this->numProducts);
#endif


    if ( doc->containsKey("key") ) {
        this->key = (*doc)["key"].as<const char *>();    
#ifdef DEBUG
        Serial.printf("[ProductConfig::parse] Got encryption key: '%s'\n",this->key.c_str());
#endif
    }

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
    Serial.println("ProductCondif::parse finished");
#endif

    return true;
}

bool ProductConfig::save() {
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