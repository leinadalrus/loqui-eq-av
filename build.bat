@echo off

set opts=-FC -GR- -EHa- -nologo -Zi
set code=%cd%
pushd output
cl %opts% %code%\loqui_src_main.cpp -Feloqui
popd
