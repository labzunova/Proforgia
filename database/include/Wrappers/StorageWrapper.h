#include <string>
#include <vector>
#include "../Utils/InputEntities.h"
#include "../Utils/DBEntities.h"
#include "../Utils/ErrorCodes.h"

class StorageWrapper {
public:
    StorageWrapper() = default;
	virtual ~StorageWrapper() = default;

    StorageWrapper( const StorageWrapper& ) = delete;
    StorageWrapper& operator=( const StorageWrapper& ) = delete;

public:
	virtual std::string add_file_to_storage( const std::string& filename, const std::string& location /* ? */, ErrorCodes &error ) const = 0; // return location in storage
	virtual bool remove_file_from_storage( const std::string& filename, const std::string& remote_location /* ? */, ErrorCodes &error ) const = 0;
};