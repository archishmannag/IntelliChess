$ErrorActionPreference = "Stop"

# Detect conan profile
Write-Host "Detecting conan profile..." -ForegroundColor Blue
try {
   $output = conan profile detect 2>&1
   # Check if it's the specific error we want to ignore
   if ($output -notlike "*Profile '*default' already exists*") {
       Write-Host $output -ForegroundColor Red
       exit 1
   }
} catch {
   if ($_.Exception.Message -like "*Profile '*default' already exists*") {
       Write-Host "Profile already exists, continuing..." -ForegroundColor Yellow
   } else {
       Write-Host "Failed to detect conan profile" -ForegroundColor Red
       Write-Host $_.Exception.Message
       exit 1
   }
}

# Install dependencies
Write-Host "Installing dependencies..." -ForegroundColor Blue
try {
   conan install . --build missing -c tools.system.package_manager:mode=install
} catch {
   Write-Host "Failed to install dependencies" -ForegroundColor Red
   exit 1
}

# Build project
Write-Host "Building project..." -ForegroundColor Blue
try {
   conan build .
} catch {
   Write-Host "Build failed" -ForegroundColor Red
   exit 1
}

Write-Host "Build completed successfully! Build files present in 'bin' directory." -ForegroundColor Green