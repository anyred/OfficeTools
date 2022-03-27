#include "cpprestsdk.h"
#include "scintilla/Scintilla.h"
#include <atlstr.h>
#include "wil/com.h"
#include <roapi.h>
#ifdef _WIN32
int wmain(int argc, wchar_t* args[])
#else
int main(int argc, char* args[])
#endif // _WIN32
{
    const string_t searchTerm(L"MQTS");
    const string_t outputFileName(L"Def.txt");
    // Open a stream to the file to write the HTTP response body into.
    auto fileBuffer = std::make_shared<streambuf<uint8_t>>();
    file_buffer<uint8_t>::open(outputFileName, std::ios::out)
        .then([=](streambuf<uint8_t> outFile) -> pplx::task<http_response> {
        *fileBuffer = outFile;

        // Create an HTTP request.
        // Encode the URI query since it could contain special characters like spaces.
        http_client client(U("http://www.bing.com/"));
        return client.request(methods::GET, uri_builder(U("/search")).append_query(U("q"), searchTerm).to_string());
    })

        // Write the response body into the file buffer.
        .then([=](http_response response) -> pplx::task<size_t> {
        printf("Response status code %u returned.\n", response.status_code());

        return response.body().read_to_end(*fileBuffer);
    })

        // Close the file buffer.
        .then([=](size_t) { return fileBuffer->close(); })

        // Wait for the entire response body to be written into the file.
        .wait();

    return 0;
}
