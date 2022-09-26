# ft_ssl_md5

ft_ssl_md5 is a student project where we reproduct the MD5 and SHA256 algorithm.
Currently my project can hash a string with more algorithm :
* `md5`
* `sha256`
* `sha224`
* `sha512`
* `sha384`

## Usage :
```
Make && ./ft_ssl [algo] [options] [file/string]
	example : echo "String to hash" > myFile.txt ; ./ft_ssl md5 myFile.txt
To use it with a string, provide the option '-s'
	example : ./ft_ssl sha256 -s "Hash me please"
```
