# ft_ssl_md5

ft_ssl_md5 is a student project where we reproduct the MD5 and SHA256 algorithm.  
Currently my project works with different algorithms :  
* `md5`
* `sha256`
* `sha224`
* `sha512`
* `sha384`

## Option :

* `-s` means the next parameter will be the string to hash
* `-q` displays only the hash
* `-r` reverses the display order (i.e HASH - FILE)
* `-p` reads from stdin and display the string instead of the filename

## Usage :

`Make && ./ft_ssl [algo] [options] [file/string]`

example :  
```
echo "String to hash" > myFile.txt ; ./ft_ssl md5 myFile.txt
```

To use it with a string, provide the option **-s**.  
example : 
```
./ft_ssl sha256 -s "Hash me please"
```
