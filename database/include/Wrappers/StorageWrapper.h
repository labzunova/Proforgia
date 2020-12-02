#include <string>
#include <vector>
#include "../Utils/DBEntities.h"
#include "../Utils/ErrorCodes.h"

/*
В каком виде будут приходить на сервер данные?
Скорее всего сеть будет принимать по сети буфер данных изображения/другого файла и располагать его в файле на сервере. 
ServerApi даст Datamanger путь к этому файлу и его Datamanger будет брать для отправки в хранилище
*/

class StorageWrapper {
public:
    StorageWrapper() = default;
	virtual ~StorageWrapper() = default;

    StorageWrapper( const StorageWrapper& ) = delete;
    StorageWrapper& operator=( const StorageWrapper& ) = delete;

public:
	virtual bool add_file_to_storage( const std::string& filename, const std::string& location /* ? */, ErrorCodes &error ) const = 0; // return location in storage
	virtual bool remove_file_from_storage( const std::string& filename, const std::string& remote_location /* ? */, ErrorCodes &error ) const = 0;

	virtual std::string get_file( const std::string& filename, const std::string& location_on_server, ErrorCodes &error ) const = 0;
	virtual bool clean_file( const std::string& filename, const std::string& location_on_server, ErrorCodes &error ) const = 0;
};