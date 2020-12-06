#include <iostream>

#include "database/include/Utils/DBEntities.h"

#include "database/include/Wrappers/StorageWrapperRealisations/AmazonS3StorageWrapper.h"
#include "database/include/Wrappers/DBWrapperRealisations/PostgreDBWrapper.h"



int main()
{
    PostgreDBWrapper db;
    // AmazonS3StorageWrapper st;
    ErrorCodes error;

    db.get_user_info(3, error).print();
    // st.get_file_link("dsdfsdf", error);

    return 0;
}