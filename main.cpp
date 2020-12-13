#include <iostream>
#include "wt_templates/TemplateWrapper.h"

int main(int argc, char* argv[]) {
    std::map<std::string, std::string> ctx;
    std::string page = "page";
    std::string page_value = "tag";
    ctx.insert(std::pair<std::string, std::string>(page, page_value));
    std::cout << TemplateWrapper(ctx).getHTML();
    return 0;
}
