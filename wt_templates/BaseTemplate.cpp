#include <map>
#include "BaseTemplate.h"

typedef std::map<std::string, std::string> ContextMap;

BaseTemplate::BaseTemplate(ContextMap& context) : context(context) {
}

std::vector<std::string> BaseTemplate::getCSS() {
    return std::vector<std::string>();
}

std::vector<std::string> BaseTemplate::getJS() {
    return std::vector<std::string>();
}
