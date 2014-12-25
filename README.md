#Curlite
*Curlite* is developed as a lightweight wrapper over *[cURL] (http://curl.haxx.se/libcurl/)* library with the following points in mind:

+ Support of C++11 features
+ Type safety of curl options
+ Ease-of-use

The project is in development stage. Currently only `Easy` interface is implemented. 

##Examples

###Example 1. Write web page source to stdout
~~~cpp
try
{
    curlite::Easy easy;
    easy.set( CURLOPT_URL, "http://example.com" );
    easy.set( CURLOPT_FOLLOWLOCATION, true );

    // start download
    std::cout << easy;
}
catch( std::exception &e ) {
    std::cerr << "Got an exception: " << e.what() << std::endl;
}
~~~

or just use `curlite::download()` method:

~~~cpp
try
{    
    curlite::download( "http://example.com", std::cout, true );
}
catch( std::exception &e ) {
    std::cerr << "Got an exception: " << e.what() << std::endl;
}
~~~

###Example 2. Upload file to remote FTP server and show transfer time

~~~cpp
try
{
    curlite::Easy easy;
    easy.set( CURLOPT_URL, "ftp://example.com/file.txt" );
    easy.set( CURLOPT_USERNAME, "username" );
    easy.set( CURLOPT_PASSWORD, "password" );
    easy.set( CURLOPT_UPLOAD, true );

    // open input file stream
    std::ifstream ifs( "file.txt", std::ios::binary );

    // start upload
    ifs >> easy;
    
    double totalSecs = easy.getInfo<double>( CURLINFO_TOTAL_TIME );
    std::cout << "Upload time: " << totalSecs << " s" << std::endl;
}
catch( std::exception &e ) {
    std::cerr << "Got an exception: " << e.what() << std::endl;
    return 1;
}
~~~

And the same with `curlite::upload()` method:

~~~cpp
try
{
    std::ifstream ifs( "file.txt", std::ios::binary );  
    auto easy = curlite::upload( ifs, "ftp://example.com/file.txt", "username", "password" );
    
    double totalSecs = easy.getInfo<double>( CURLINFO_TOTAL_TIME );
    std::cout << "Upload time: " << totalSecs << " s" << std::endl;
}
catch( std::exception &e ) {
    std::cerr << "Got an exception: " << e.what() << std::endl;
}
~~~

##FAQ

###What is minimum supported *libcurl* version?
Curlite should work with libcurl 7.32 and later.

###What compilers are supported?
Curlite requires from compiler a basic support of *C++11*. The minimum supported version are: *g++ 4.6*, *clang 3.2*, *VS 2010* and later.

###What is the difference between `Easy::onWrite()` and `Easy::onWrite_()`?

The latter (with underscore) sets simplified handler, while the first sets usual *cURL* handler.

###Are *curlite* objects thread-safe?
No, they are not.

###Why the hell would anyone use *libcurl*, when there is *Qt* / *POCO* / *cpp-netlib* / *urdl* / ...

I like those libraries, but in some cases *libcurl* is the best choice: it's easy, stable and supports a huge number of protocols.
Download via HTTPS? - ok. Send email? - no problem.