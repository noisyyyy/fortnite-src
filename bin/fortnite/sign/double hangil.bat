signtool.exe sign /v /ac SectigoPublicCodeSigningCAR36.crt /f HG.pfx /p aa123123 %1
signtool sign /as /fd sha256 /f HG.pfx  /p aa123123 %1
pause