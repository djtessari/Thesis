@echo off
for /L %%X in (0,1,9) do ( for /L %%Y in (0,1,9) do ( Image --contrast 1.%%X%%Y --in shrek.bmp --out avi.%%X%%Y.bmp) )
	