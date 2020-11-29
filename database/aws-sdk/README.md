AWS SDK C++
How I built it
https://github.com/aws/aws-sdk-cpp/issues/1334

https://docs.aws.amazon.com/sdk-for-cpp/v1/developer-guide/setup.html
https://docs.aws.amazon.com/sdk-for-cpp/v1/developer-guide/build-cmake.html

Lib build:
- project-root/database/aws-sdk/aws-sdk-cpp/build $ cmake .. -DCMAKE_BUILD_TYPE=Debug -DBUILD_ONLY="s3"  -DCMAKE_INSTALL_PREFIX=path/to/project/Proforgia/database/aws-sdk/install
- project-root/database/aws-sdk/aws-sdk-cpp/build $ make
- project-root/database/aws-sdk/aws-sdk-cpp/build $ make install

First application build:
- project-root $  cmake . -DCMAKE_PREFIX_PATH=path/to/project/Proforgia/database/aws-sdk/install
- project-root/build $  make
- project-root/build $  ./{{ build target name }}  ($ ./Proforgia)

Storage access credentials:
- install aws cli
- run $ aws configure and enter info (access key and other credentials can be found in ~/.aws on already working machine)
- this credentials should be placed in ~/.aws/config and ~/.aws/credentials files



Encountered issues:
- “aws sdk for c++ is missing” problem:
for find_package to run, I hardcoded my path to Aws.h to .cmake file
- Problem with project building:
Failed to build with cmake .. at first, 
cmake . from Proforgia/ worked
Then cmake .. from Proforgia/build had worked as well
! After establishing work cmake .. without -DCMAKE_PREFIX_PATH was successfully working as well
- Cmake version 19 failing to build lib
Use Cmake version 18.5 instead