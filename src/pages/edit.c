/*
 * edit.c
 * 2023-2-19
 * Author: Niklas Hempel
 */
#include <stdio.h>
#include <stdlib.h>
#include "../lib/database.h"
#include "../lib/models.h"
#include "../lib/html.h"
#include "../lib/query.h"

int callback(int id, char *name, int type, char *creator, char *borrower);

int main()
{

    RequestMethod method = getRequestMethod();

    switch (method)
    {
    case GET:
    {
        int id = getIdFromQueryString();
        printHeader("Edit");
        dbFind(id, callback);
        printFooter();
    }
    break;

    case POST:
    {
        int id = getIdFromQueryString();
        char *body;
        getRequestBody(&body);
        if (body)
        {
            Medium medium;
            parseRequestBody(body, &medium);
            dbUpdate(id, &medium);
            free(body);
        }

        redirect("./default.cgi");
    }
    break;
    
    default:
        fprintf(stderr, "Error: Method not allowed.");
        return 1;
    }

    return 0;
}

int callback(int id, char *name, int type, char *creator, char *borrower)
{
    printf("\
            <h4 class='mb-3 m-md-0 p-2'>Edit medium</h4>\
            <form class='m-0 p-1' action='./edit.cgi?id=%d' method='post'>\
            <div class='form-group row mb-3 m-md-0 pb-2'>\
                <label for='inputName'>Name</label>\
                <input type='text' class='form-control' id='inputName' placeholder='Enter medium name' name='name' value='%s' required>\
            </div>\
            <div class='form-group row mb-3 m-md-0 pb-2'>\
                <label for='selectType'>Select medium type</label>\
                <select class='form-control' id='selectType' name='type'>\
                <option value='0' %s>Book</option>\
                <option value='1' %s>CD</option>\
                <option value='2' %s>DVD</option>\
                </select>\
            </div>\
            <div class='form-group row mb-3 m-md-0 pb-2'>\
                <label for='inputCreator'>Author/Interpreter</label>\
                <input type='text' class='form-control' id='inputCreator' placeholder='Enter author, interpreter etc.' name='creator' value='%s'>\
            </div>\
            <div class='form-group row mb-3 m-md-0 pb-2'>\
                <label for='inputBorrower'>Borrower</label>\
                <input type='text' class='form-control' id='inputBorrower' placeholder='Enter borrower' name='borrower' value='%s'>\
            </div>\
            <button type='submit' class='btn btn-primary'>Submit</button>\
            </form>",
           id, name, type == 0 ? "selected" : "", type == 1 ? "selected" : "",
           type == 2 ? "selected" : "", creator ? creator : "", borrower ? borrower : "");

    return 0;
}