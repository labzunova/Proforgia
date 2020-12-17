# Proforgia
Сервис для обмена организационной информацией и файлами в пределах группы

**Установка нужных библиотек:**
1. Boost:\
macos: `brew install boost`\
ubuntu: `sudo apt-get install -f libboost-all-dev`

2. Aws-sdk-cpp:\
macos: `brew aws-sdk-cpp`\
ubuntu:\
`sudo apt-get install libcurl4-openssl-dev libssl-dev uuid-dev zlib1g-dev libpulse-dev`\
`cd database`\
`git clone https://github.com/aws/aws-sdk-cpp.git`
`cd aws-sdk-cpp`\
`mkdir build`\
`cd build`\
`cmake .. -DCMAKE_BUILD_TYPE=Debug -DBUILD_ONLY="s3"`\
`make`\
`sudo make install`

3. openssl:\
ubuntu:\
`git clone https://github.com/openssl/openssl.git`
`cd openssl`\
`./Configure`\
`make -j4`\
`make text -j4` (не обязательно)\
`sudo make install`
