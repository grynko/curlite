/*
 * examples/upload_to_ftp.cpp
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

    return 0;
}