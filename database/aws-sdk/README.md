AWS SDK C++
How I built it
https://github.com/aws/aws-sdk-cpp/issues/1334

https://docs.aws.amazon.com/sdk-for-cpp/v1/developer-guide/setup.html
https://docs.aws.amazon.com/sdk-for-cpp/v1/developer-guide/build-cmake.html


First application build:
- project-root $  cmake . -DCMAKE_PREFIX_PATH=$HOME/TPark-SEM1/Proforgia/database/aws-sdk/install
- project-root/build $  make
- project-root/build $  ./{{ build target name }}  ($ ./Proforgia)

Encountered issues:
- “aws sdk for c++ is missing” problem:
for find_package to run, I hardcoded my path to Aws.h to .cmake file
- Problem with project building:
Failed to build with cmake .. at first, 
cmake . from Proforgia/ worked
Then cmake .. from Proforgia/build had worked as well
! After establishing work cmake .. without -DCMAKE_PREFIX_PATH was successfully working as well
