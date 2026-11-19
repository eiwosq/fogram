@echo off
setlocal

if not defined TDESKTOP_API_ID (
    echo TDESKTOP_API_ID is missing. Set your own Telegram API ID first.
    exit /b 1
)
if not defined TDESKTOP_API_HASH (
    echo TDESKTOP_API_HASH is missing. Set your own Telegram API hash first.
    exit /b 1
)

pushd "%~dp0Telegram" || exit /b 1
call configure.bat x64 -D TDESKTOP_API_ID=%TDESKTOP_API_ID% -D TDESKTOP_API_HASH=%TDESKTOP_API_HASH% -D DESKTOP_APP_DISABLE_AUTOUPDATE=ON -D DESKTOP_APP_ENABLE_LTO=OFF %*
set "configure_result=%ERRORLEVEL%"
popd

if not "%configure_result%"=="0" exit /b %configure_result%

echo Configuration ready. Build the Telegram project from out\Telegram.slnx.
