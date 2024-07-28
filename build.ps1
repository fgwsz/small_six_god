$root_path=Split-Path -Parent $MyInvocation.MyCommand.Definition
$project_name=Split-Path -Leaf $root_path
$build_path=Join-Path $root_path "build/windows"
if(!(Test-Path -Path $build_path)){
    mkdir $build_path
}
cd $build_path
cmake -G "Visual Studio 17 2022" ../..
cmake --build .
cd ../..
& "$build_path/Debug/$project_name.exe"
