/*
 * examples/download_with_handlers.cpp
 *
 * The MIT License (MIT)
 * 
 * Copyright (c) 2014 Ivan Grynko
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <iostream>
#include <fstream>
#include <curlite.hpp>

int main()
{
    try
    {
        curlite::Easy easy;
        easy.set( CURLOPT_URL, "http://example.com" );
        easy.set( CURLOPT_FOLLOWLOCATION, true );

        std::ofstream ofs( "data.html" );

        // set simplified write handler
        easy.onWrite_( [&ofs]( char *data, size_t size ) -> bool
        {
            ofs.write( data, size );
            return ofs.good();
        });

        curl_off_t countedBytes = 0;

        // set simplified progress handler
        easy.onProgress_( [&countedBytes]( curl_off_t dTotal, curl_off_t dCurrent, curl_off_t, curl_off_t ) -> bool
        {
            // show progress value only if we've downloaded at least another 10% of size
            double progressInterval = 0.1 * dTotal;
            if( dCurrent - countedBytes > progressInterval ) {
                std::cout << "Progress: " << 100 * dCurrent / dTotal << "%" << std::endl;
                countedBytes = dCurrent;
            }
            return true;
        });

        // let's go
        easy.perform();
        std::cout << "Download is finished" << std::endl << std::endl;

        // get some transfer information
        std::cout << "Total time: " << easy.getInfo<double>( CURLINFO_TOTAL_TIME ) << " seconds" << std::endl;
        std::cout << "Transferred: " << easy.getInfo<double>( CURLINFO_SIZE_DOWNLOAD ) << " bytes" << std::endl;
    }
    catch( std::exception &e ) {
        std::cerr << "Got an exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}