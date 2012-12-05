#include "jet/HttpRequest.h"


namespace jet{



    HttpRequest::HttpRequest()
        :body(body), headers(headers), request_line(request_line)
    {


    }


    HttpRequest::HttpRequest( Utf8String body, HttpHeaderMap headers, Utf8String request_line )
        :body(body), headers(headers), request_line(request_line)
    {


    }



    HttpRequest::~HttpRequest(){


    }


    void HttpRequest::setBody( Utf8String body ){

        this->body = body;

    }


    Utf8String HttpRequest::getBody(){

        return this->body;

    }


    void HttpRequest::setHeaders( HttpHeaderMap headers ){

        this->headers = headers;

    }


    HttpHeaderMap HttpRequest::getHeaders(){

        return this->headers;

    }


    void HttpRequest::setRequestLine( Utf8String request_line ){

        this->request_line = request_line;

    }


    Utf8String HttpRequest::getRequestLine(){

        return this->request_line;

    }


}

