$root_path=Split-Path -Parent $MyInvocation.MyCommand.Definition
$build_path=Join-Path $root_path "build/windows"
if(Test-Path -Path $build_path){
    Remove-Item $build_path -Recurse -Force
}
