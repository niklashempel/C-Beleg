#include <stdio.h>
#include <stdlib.h>
#include "../lib/database.h"
#include "../lib/models.h"
#include "../lib/html.h"
#include "../lib/query.h"

int printForm();

int main()
{

    RequestMethod method = getRequestMethod();

    switch (method)
    {
    case GET:
        printHeader("New");
        printForm();
        printFooter();
        break;

    case POST:
    {
        char *body;
        getRequestBody(&body);
        if (body)
        {
            Medium medium;
            parseRequestBody(body, &medium);
            dbCreate(&medium);
            free(body);
        }

        redirect("./default.cgi");
    }
    break;

    default:
        return 1;
    }

    return 0;
}

int printForm()
{
    puts("\
    <h4 class='mb-3 m-md-0 p-2'>New medium</h4>\
    <form class='m-0 p-1' action='./new.cgi' method='post'>\
      <div class='form-group row mb-3 m-md-0 pb-2'>\
        <label for='inputName'>Name</label>\
        <input type='text' class='form-control' id='inputName' placeholder='Enter medium name' name='name' required>\
      </div>\
      <div class='form-group row mb-3 m-md-0 pb-2'>\
        <label for='selectType'>Select medium type</label>\
        <select class='form-control' id='selectType' name='type'>\
          <option value='0'>Book</option>\
          <option value='1'>CD</option>\
          <option value='2'>DVD</option>\
        </select>\
      </div>\
      <div class='form-group row mb-3 m-md-0 pb-2'>\
        <label for='inputCreator'>Author/Interpreter</label>\
        <input type='text' class='form-control' id='inputCreator' placeholder='Enter author, interpreter etc.' name='creator'>\
      </div>\
      <div class='form-group row mb-3 m-md-0 pb-2'>\
        <label for='inputBorrower'>Borrower</label>\
        <input type='text' class='form-control' id='inputBorrower' placeholder='Enter borrower' name='borrower'>\
      </div>\
      <button type='submit' class='btn btn-primary'>Submit</button>\
    </form>");

    return 0;
}