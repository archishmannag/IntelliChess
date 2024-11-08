#! /bin/bash

# Detect conan profile
echo -e "\033[34mDetecting conan profile...\033[0m"
# Capture output and check for specific error
if output=$(conan profile detect 2>&1); then
   echo "$output"
else
   # Check if it's the "profile exists" error
   if echo "$output" | grep -q "Profile.*default.*already exists"; then
       echo -e "\033[33mProfile already exists, continuing...\033[0m"
   else
       echo -e "\033[31m$output\033[0m"
   fi
fi

# Install dependencies
echo -e "\033[34mInstalling dependencies...\033[0m"
sudo conan install . --build missing -c tools.system.package_manager:mode=install || exit 1

# Build project
echo -e "\033[34mBuilding project...\033[0m"
conan build . || exit 1

echo -e "\033[32mBuild completed successfully\033[0m"