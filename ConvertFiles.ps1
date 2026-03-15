# カレントディレクトリ以下の .h, .cpp ファイルを取得
$files = Get-ChildItem -Path . -Include *.h, *.cpp -Recurse

foreach ($file in $files) {
    # 一度 UTF8 で読み込み、UTF8(BOM付き) で書き出す
    # Get-Content で読み込む際、Shift-JIS(CP932)として解釈し、BOM付きUTF8で出力する
    $content = Get-Content -Path $file.FullName -Encoding Default
    $content | Out-File -FilePath $file.FullName -Encoding UTF8
    Write-Host "Converted: $($file.FullName)"
}