#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

#include <iostream>

int main()
{
//     concurrency::streams::container_buffer<std::vector<uint8_t>> buf;
// 
//     web::uri_builder uri(U("http://localhost"));
//     web::http::client::http_client client(addr);
// 
//     web::http::http_request msg(web::http::methods::GET);
//     msg.set_response_stream(buf.create_ostream());
//     msg.headers().add(U("SessionHash"), U("1234"));
// 
//     client.request(msg, builder.to_string());

//     auto fileStream = std::make_shared<concurrency::streams::ostream>();
// 
//     // Open stream to output file.
//     pplx::task<void> requestTask = concurrency::streams::fstream::open_ostream(U("results.html")).then([=](concurrency::streams::ostream outFile)
//     {
//         *fileStream = outFile;
// 
//         // Create http_client to send the request.
//         web::http::client::http_client client(U("http://localhost/"));
// 
//         // Build request URI and start the request.
//         web::uri_builder builder(U("/login"));
//         //builder.append_query(U("q"), U("cpprestsdk github"));
//         return client.request(web::http::methods::GET, builder.to_string());
//     })
// 
//     // Handle response headers arriving.
//     .then([=](web::http::http_response response)
//     {
//         printf("Received response status code:%u\n", response.status_code());
// 
//         // Write response body into the file.
//         return response.body().read_to_end(fileStream->streambuf());
//     })
// 
//         // Close the file stream.
//         .then([=](size_t)
//     {
//         return fileStream->close();
//     });
// 
//     // Wait for all the outstanding I/O to complete and handle any exceptions
//     requestTask.wait();

//     web::uri_builder uri(U("http://localhost"));
//     //uri.set_path(U("/login"));
//     std::wstring addr = uri.to_uri().to_string();
// 
//     web::http::client::http_client client(addr);
//     
//     concurrency::streams::container_buffer<std::vector<uint8_t>> buf;
// 
//     web::http::http_request msg(web::http::methods::POST);
//     msg.set_response_stream(buf.create_ostream());
// 
//     msg.headers().add(U("SessionHash"), U("1234"));
//     
//     web::http::http_response response = client.request(msg).get();

    concurrency::streams::container_buffer<std::vector<uint8_t>> buf;

    web::uri_builder uri(U("http://localhost"));
    std::wstring addr = uri.to_uri().to_string();
    web::http::client::http_client client(addr);

    web::http::http_request msg(web::http::methods::GET);
    msg.set_response_stream(buf.create_ostream());

    web::uri_builder builder(U("/login"));
    msg.set_request_uri(builder.to_uri());

    msg.headers().add(U("SessionHash"), U("1234"));

    auto resp = client.request(msg).get();

    return 0;
}