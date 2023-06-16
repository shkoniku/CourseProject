# CourseProject
Student's marks and statistics

There is no openssl files for program. You need to download it form https://slproweb.com/products/Win32OpenSSL.html. It should install in the same directory with program. You needed to pick "The OpenSSL binaries" after
choice of path. The name of directory should be change on "openssl" after all. Then you should create a public and private keys for program with open "openssl/bin" and run "openssl.exe" by type two commands: 
genrsa -out rsa.private 4096
rsa -in rsa.private -pubout -out rsa.public
Then this keys would be move in the same directory with program. AES would encrypt the whole information about students with key. RSA would be use for coding only key wich would be generate randomly everytime 
in program.  
