#include <iostream>
#include "database/include/Utils/DBEntities.h"

int main()
{
    ErrorCodes error;

    (*DBSession::get("problematic", error)).get_user(error)->print();

    return 0;
}

