#include <string>
#include <vector>
#include "../Utils/DBEntities.h"
#include "../Utils/ErrorCodes.h"

class StorageWrapper {
public:
    StorageWrapper() = default;
	virtual ~StorageWrapper() = default;

    StorageWrapper( const StorageWrapper& ) = delete;
    StorageWrapper& operator=( const StorageWrapper& ) = delete;

public:
	virtual std::string get_file_link( const std::string& filename, ErrorCodes &error ) const = 0;
	virtual std::string get_file_upload_link( const std::string& filename, ErrorCodes &error ) const = 0;
    virtual bool remove_file_from_storage( const std::string& filename, const std::string& remote_location /* ? */, ErrorCodes &error ) const = 0;
};