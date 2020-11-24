//
// Created by Иван on 24.11.2020.
//

#include "../include/Wrappers/StorageWrapperRealisations/AmazonS3StorageWrapper.h"

std::string AmazonS3StorageWrapper::add_file_to_storage(const std::string &filename, const std::string &location,
                                                         ErrorCodes &error) const {
    return nullptr;
}

bool AmazonS3StorageWrapper::remove_file_from_storage(const std::string &filename, const std::string &remote_location,
                                                      ErrorCodes &error) const {
    return false;
}
