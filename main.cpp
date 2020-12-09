#include <iostream>
#include "wt_templates/LoginTemplate.h"

int main() {
    auto loginTemplate = Wt::cpp14::make_unique<LoginTemplate>();

    std::cout << loginTemplate->getTemplateText() << std::endl;
    return 0;
}
