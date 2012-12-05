#include "jet/HttpResponse.h"


namespace jet{



    HttpResponse::HttpResponse()
        :body(body), headers(headers), response_line(response_line)
    {


    }


    HttpResponse::HttpResponse( Utf8String body, HttpHeaderMap headers, Utf8String response_line )
        :body(body), headers(headers), response_line(response_line)
    {


    }



    HttpResponse::~HttpResponse(){


    }


    void HttpResponse::setBody( Utf8String body ){

        this->body = body;

    }


    Utf8String HttpResponse::getBody(){

        return this->body;

    }


    void HttpResponse::setHeaders( HttpHeaderMap headers ){

        this->headers = headers;

    }


    HttpHeaderMap HttpResponse::getHeaders(){

        return this->headers;

    }


    void HttpResponse::setResponseLine( Utf8String response_line ){

        this->response_line = response_line;

    }


    Utf8String HttpResponse::getResponseLine(){

        return this->response_line;

    }


}

