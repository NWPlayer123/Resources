@echo off
if exist *.dir (
    echo DIR FOUND
    for /R %~dp0 %%f in (*.dir) do ".arc and .dir extractor.py" %%f
) else (
    echo DIR NOT FOUND
)

pause